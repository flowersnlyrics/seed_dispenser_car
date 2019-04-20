/*******************************************************************************
* @file           : blade_ctrl.c
* @brief          : 
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include <stdbool.h>
#include "blade_ctrl.h"
#include "main.h"
#include "tim.h"

#define TIME_PER_STEP 2000 // mns

/* ------------------------------------------------------ Private Definitions */
int _step = 0; 
bool dir = true;// false=clockwise, true=counter clockwise
int count=0;

volatile uint32_t g_count = 0; 

typedef enum 
{
  STEP_1 = 0, 
  STEP_2, 
  STEP_3, 
  STEP_4, 
  STEP_5, 
  STEP_6, 
  STEP_7, 
  STEP_8, 
  NUM_STEPS 
} step_idx_t; 

typedef enum
{
  COIL_1 = 0, 
  COIL_2, 
  COIL_3, 
  COIL_4, 
  NUM_COILS
} coil_t; 

static GPIO_PinState STEP_DESC[NUM_STEPS][NUM_COILS] = 
{
  {GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET},
  {GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_SET},
  {GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET},
  {GPIO_PIN_RESET ,GPIO_PIN_SET,GPIO_PIN_SET,GPIO_PIN_RESET},  
  {GPIO_PIN_RESET,GPIO_PIN_SET,GPIO_PIN_RESET,GPIO_PIN_RESET},
  {GPIO_PIN_SET,GPIO_PIN_SET,GPIO_PIN_RESET,GPIO_PIN_RESET}, 
  {GPIO_PIN_SET,GPIO_PIN_RESET,GPIO_PIN_RESET,GPIO_PIN_RESET},
  {GPIO_PIN_SET,GPIO_PIN_RESET,GPIO_PIN_RESET,GPIO_PIN_SET}
};


typedef struct 
{
  GPIO_TypeDef* port; 
  uint16_t pin; 
} motor_pin_t; 

static motor_pin_t COIL_DESC[NUM_COILS] = 
{
  {MILL_MOTOR_IN1_GPIO_Port, MILL_MOTOR_IN1_Pin},
  {MILL_MOTOR_IN2_GPIO_Port, MILL_MOTOR_IN2_Pin},
  {MILL_MOTOR_IN3_GPIO_Port, MILL_MOTOR_IN3_Pin},
  {MILL_MOTOR_IN4_GPIO_Port, MILL_MOTOR_IN4_Pin},
};


/* ---------------------------------------------- Private Function Prototypes */
static void move(void); 

/* ---------------------------------------------- Public Function Definitions */

void loop(void)
{
  /* Run through these steps a certain number of times */
  //for(int i= 0; i < 512; i++) // 512 is about 8 seconds
  while(1)
  {
    /* Set the settings for each step */
    //for(step_idx_t step = STEP_1; step < NUM_STEPS; step++)
    for(step_idx_t step = STEP_8; step < NUM_STEPS; step--)
    {
       for(coil_t coil = COIL_1; coil< NUM_COILS; coil++)
       {
         HAL_GPIO_WritePin(COIL_DESC[coil].port,
                           COIL_DESC[coil].pin,
                           STEP_DESC[step][coil]); 
       }
       
       HAL_Delay(1); 
    }
  }  
}

/*******************************************************************************
 * @fn      blade_ctrl_move
 * @brief   
 ******************************************************************************/
void blade_ctrl_move(uint8_t steps)
{
  uint32_t wait = TIME_PER_STEP * steps;
  uint32_t start = 0; 
  
  tim_start(&htim6); 
  start = g_count; 
  
  while( (g_count - start) < wait)
  {
    move(); 
  }
  
  g_count = 0; 
  tim_stop(&htim6); 
}

/*******************************************************************************
 * @fn      blade_ctrl_init
 * @brief   
 ******************************************************************************/
void blade_ctrl_init(void)
{
  MX_TIM6_Init();
}

/*******************************************************************************
 * @fn      blade_ctrl_inc
 * @brief   
 ******************************************************************************/
void blade_ctrl_inc(void)
{
  g_count++;
}

/* --------------------------------------------- Private Function Definitions */
static void move(void)
{
  for(step_idx_t step = STEP_8; step < NUM_STEPS; step--)
  {
     for(coil_t coil = COIL_1; coil< NUM_COILS; coil++)
     {
       HAL_GPIO_WritePin(COIL_DESC[coil].port,
                         COIL_DESC[coil].pin,
                         STEP_DESC[step][coil]); 
     }
     
     HAL_Delay(1); 
  }
}