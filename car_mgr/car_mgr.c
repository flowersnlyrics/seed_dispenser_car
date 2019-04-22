/******************************************************************************
 * @file   CAR_mgr.c
 * @brief  
 * @date   
 ******************************************************************************/
/* ----------------------------------------------------------------- Includes */
#include "car_mgr.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "seed_car_freertos.h"
#include "tim.h"
#include "stm32l4xx_hal.h"
#include <limits.h>
#include <string.h>
#include "blade_ctrl.h"
#include "accel_ctrl.h"
#include <math.h>
   
/* ------------------------------------------------------ Private Definitions */
static osThreadDef_t g_thread_def;
static osThreadId g_taskHandle;

#define SLIDING_FILTER_SIZE 6

static const float MAX_DELTA_G = .05; 
static const float MIN_DELTA_G = -.05;
static const uint8_t MAX_DUTY_CYCLE = 100; 
static const uint8_t MIN_DUTY_CYCLE = 40; 
static const uint8_t NOM_DUTY_CYCLE = 60; 
static float DELTA_PER_PERCENT = 0 ; 

static const float MAX_INCLINE_G = 0.35; 
static const float MIN_INCLINE_G = -0.35; 
static const uint8_t MAX_DUTY_CYCLE_ADD = 10; 
static const uint8_t MIN_DUTY_CYCLE_ADD = 0; 
static const uint8_t NOM_DUTY_CYCLE_ADD = 5; 
static float INCLINE_PER_PERCENT = 0; 


static const float K_D = 1.0;
static const float K_P = 1.0; 


typedef struct
{
  uint8_t head; 
  uint8_t tail; 
  uint32_t num_reads; 
  float sum; 
  float avg; 
  float prev_avg; 
  float delta; 
  accel_read_t reads[SLIDING_FILTER_SIZE];
} accel_filter_t; 

static accel_filter_t g_accel_filter; 

/* ---------------------------------------------- Private Function Prototypes */
static void task_main(void const * argument);
   
/* ---------------------------------------------- Public Function Definitions */
/******************************************************************************
 * @fn      car_mgr_init
 * @brief
 * @return  
 ******************************************************************************/
bool car_mgr_init(void)
{ 
  //
  // Need the car control module to run the car manager task 
  //
  car_ctrl_init();
  
  //
  // Initialization of adc mgr task 
  //
  g_thread_def.name = CAR_MGR_TASK_NAME;
  g_thread_def.pthread = task_main;
  g_thread_def.tpriority = CAR_MGR_TASK_PRIO;
  g_thread_def.instances = 0;
  g_thread_def.stacksize = CAR_MGR_TASK_STACK_SIZE;
  
  g_taskHandle = osThreadCreate(&g_thread_def, NULL);

  if (g_taskHandle == NULL)
  {
    return false;
  }
  
  memset(&g_accel_filter, 0, sizeof(accel_filter_t));
  g_accel_filter.tail = 0; 
  g_accel_filter.head = 5;
  
  //Calculating delta per percent
  DELTA_PER_PERCENT = (MAX_DELTA_G - MIN_DELTA_G) / (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE); 
  INCLINE_PER_PERCENT = (MAX_INCLINE_G - MIN_INCLINE_G) / (MAX_DUTY_CYCLE_ADD - MIN_DUTY_CYCLE_ADD); 

  return true; 
}

/******************************************************************************
 * @fn      car_mgr_send_evt_from_isr
 * @brief   
 * @param   evt:
 * @return
*******************************************************************************/
bool car_mgr_send_evt_from_isr(car_mgr_event_t evt)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xTaskNotifyFromISR(g_taskHandle,
                     evt,
                     eSetBits,
                     &xHigherPriorityTaskWoken);
   
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  
  return true; 
}

/******************************************************************************
 * @fn      car_mgr_send_evt
 * @brief   
 * @param   evt:
 * @return
*******************************************************************************/
bool car_mgr_send_evt(car_mgr_event_t evt)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  
  xHigherPriorityTaskWoken = xTaskNotify(g_taskHandle,
                                         evt,
                                         eSetBits);
  
  return (xHigherPriorityTaskWoken == pdTRUE); 

}


/* --------------------------------------------- Private Function Definitions */

/******************************************************************************
 * @fn      task_main
 * @brief   tasks main function 
 ******************************************************************************/
static void task_main(void const * argument)
{
  const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 500 );
  BaseType_t xResult;
  uint32_t ulNotifiedValue; 

  /* Infinite loop */
  while(1)
  {
    /* Wait to be notified of an interrupt. */
    xResult = xTaskNotifyWait( pdFALSE,           // Don't clear bits on entry
                               ULONG_MAX,         // Clear all bits on exit
                               &ulNotifiedValue,  // Stores the notified value
                               xMaxBlockTime );

    if( xResult == pdPASS )
    {
      /* A notification was received.  See which bits were set. */
      if( ( ulNotifiedValue & START_CAR_EVT ) != 0 )
      {
        // Adjust the car to 50% duty cycle for the wheels
        car_speed_t speed = {NOM_DUTY_CYCLE, NOM_DUTY_CYCLE}; 
        car_ctrl_adjust_speed(&speed); 
        // Tell the car you're ready to start
        // at this point in the code the wheels are ready but the car is 
        // still in PARK :) 
        car_ctrl_start(); 
        // Tell the car to advance! 
        car_ctrl_move(ADVANCE);
      }
      if( ( ulNotifiedValue & STOP_CAR_EVT ) != 0 )
      {
        // Stop everything on the car!!!
        // Note this calls car_ctrl_adjust_speed 
        car_ctrl_stop(); 
      }
      if( ( ulNotifiedValue & MOVE_SEEDER_EVT ) != 0 )
      {
        blade_ctrl_move(1); 
      }
      if( ( ulNotifiedValue & CHECK_PWM_EVT ) != 0 )
      { 
        accel_read_t* curr_read;
        
        if(g_accel_filter.num_reads < SLIDING_FILTER_SIZE) // if sliding filter isn't full 
        {
          curr_read = &g_accel_filter.reads[g_accel_filter.num_reads];
          accel_ctrl_get_read(curr_read);
          g_accel_filter.sum += curr_read->y;
          g_accel_filter.avg = g_accel_filter.sum /(g_accel_filter.num_reads + 1);
        }
        else
        {
          curr_read = &g_accel_filter.reads[g_accel_filter.tail];
          
          // store previous average
          g_accel_filter.prev_avg = g_accel_filter.avg; 
          // subtract tail 
          g_accel_filter.sum -= curr_read->y;
          // get a new read 
          accel_ctrl_get_read(curr_read);
          g_accel_filter.sum += curr_read->y;
          g_accel_filter.avg = g_accel_filter.sum / SLIDING_FILTER_SIZE; 
          g_accel_filter.delta = g_accel_filter.avg - g_accel_filter.prev_avg; 
          // head and tail mental gymnastics 
          g_accel_filter.tail += 1; 

          if(g_accel_filter.tail == (SLIDING_FILTER_SIZE - 1))
          {
            g_accel_filter.tail = 0; 
          }
        }
        
        g_accel_filter.num_reads++; 

        uint8_t duty_cycle = 0; 
        
        // debug start
        
        if(g_accel_filter.delta > 0.1)
        {
          int you_a_bitch = 0; 
        }
        
        // debug end 
        
        duty_cycle = (uint8_t)
                     (floor((K_D * (g_accel_filter.delta / DELTA_PER_PERCENT))
                          + (K_P * (g_accel_filter.avg / INCLINE_PER_PERCENT))
                          + NOM_DUTY_CYCLE )
                      ); 
        
        if (duty_cycle > MAX_DUTY_CYCLE)
        {
          duty_cycle = MAX_DUTY_CYCLE; 
        }
        else if (duty_cycle < MIN_DUTY_CYCLE)
        {
          duty_cycle = MIN_DUTY_CYCLE; 
        }        

        wheel_ctrl_speed(LEFT_WHEELS, duty_cycle);
        wheel_ctrl_speed(RIGHT_WHEELS, duty_cycle); 
      }
      
    }
  }
}
