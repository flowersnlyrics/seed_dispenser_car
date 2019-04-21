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
   
/* ------------------------------------------------------ Private Definitions */
static osThreadDef_t g_thread_def;
static osThreadId g_taskHandle;

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
        car_speed_t speed = {50, 50}; 
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
    }
  }
}