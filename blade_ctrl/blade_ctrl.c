/*******************************************************************************
* @file           : blade_ctrl.c
* @brief          : 
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include <stdbool.h>
#include "blade_ctrl.h"
#include "main.h"

/* ------------------------------------------------------ Private Definitions */
int _step = 0; 
bool dir = true;// false=clockwise, true=counter clockwise
int count=0;

/* Private Function Prototypes */

/* Public Function Definitions */
#define LOW GPIO_PIN_RESET
#define HIGH GPIO_PIN_SET

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

#define Pin1 MILL_MOTOR_IN1_GPIO_Port, MILL_MOTOR_IN1_Pin
#define Pin2 MILL_MOTOR_IN2_GPIO_Port, MILL_MOTOR_IN2_Pin
#define Pin3 MILL_MOTOR_IN3_GPIO_Port, MILL_MOTOR_IN3_Pin
#define Pin4 MILL_MOTOR_IN4_GPIO_Port, MILL_MOTOR_IN4_Pin

void loop(void)
{
  /* Run through these steps a certain number of times */
  //for(int i= 0; i < 512; i++) // 512 is about 8 seconds
  while(1)
  {
    /* Set the settings for each step */
    for(step_idx_t step = STEP_1; step < NUM_STEPS; step++)
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

//void loop(void)
//{
//  while(1)
//  {
//    
//  
//    switch(_step){ 
//     case 0: 
//       HAL_GPIO_WritePin(Pin1, LOW);  
//       HAL_GPIO_WritePin(Pin2, LOW); 
//       HAL_GPIO_WritePin(Pin3, LOW); 
//       HAL_GPIO_WritePin(Pin4, HIGH); 
//     break;  
//     case 1: 
//       HAL_GPIO_WritePin(Pin1, LOW);  
//       HAL_GPIO_WritePin(Pin2, LOW); 
//       HAL_GPIO_WritePin(Pin3, HIGH); 
//       HAL_GPIO_WritePin(Pin4, HIGH); 
//     break;  
//     case 2: 
//       HAL_GPIO_WritePin(Pin1, LOW);  
//       HAL_GPIO_WritePin(Pin2, LOW); 
//       HAL_GPIO_WritePin(Pin3, HIGH); 
//       HAL_GPIO_WritePin(Pin4, LOW); 
//     break;  
//     case 3: 
//       HAL_GPIO_WritePin(Pin1, LOW);  
//       HAL_GPIO_WritePin(Pin2, HIGH); 
//       HAL_GPIO_WritePin(Pin3, HIGH); 
//       HAL_GPIO_WritePin(Pin4, LOW); 
//     break;  
//     case 4: 
//       HAL_GPIO_WritePin(Pin1, LOW);  
//       HAL_GPIO_WritePin(Pin2, HIGH); 
//       HAL_GPIO_WritePin(Pin3, LOW); 
//       HAL_GPIO_WritePin(Pin4, LOW); 
//     break;  
//     case 5: 
//       HAL_GPIO_WritePin(Pin1, HIGH);  
//       HAL_GPIO_WritePin(Pin2, HIGH); 
//       HAL_GPIO_WritePin(Pin3, LOW); 
//       HAL_GPIO_WritePin(Pin4, LOW); 
//     break;  
//       case 6: 
//       HAL_GPIO_WritePin(Pin1, HIGH);  
//       HAL_GPIO_WritePin(Pin2, LOW); 
//       HAL_GPIO_WritePin(Pin3, LOW); 
//       HAL_GPIO_WritePin(Pin4, LOW); 
//     break;  
//     case 7: 
//       HAL_GPIO_WritePin(Pin1, HIGH);  
//       HAL_GPIO_WritePin(Pin2, LOW); 
//       HAL_GPIO_WritePin(Pin3, LOW); 
//       HAL_GPIO_WritePin(Pin4, HIGH); 
//     break;  
//     default: 
//       HAL_GPIO_WritePin(Pin1, LOW);  
//       HAL_GPIO_WritePin(Pin2, LOW); 
//       HAL_GPIO_WritePin(Pin3, LOW); 
//       HAL_GPIO_WritePin(Pin4, LOW); 
//     break;  
//   } 
//   if(dir){ 
//     _step++; 
//   }else{ 
//     _step--; 
//   } 
//   if(_step>7){ 
//     _step=0; 
//   } 
//   if(_step<0){ 
//     _step=7; 
//   } 
//   HAL_Delay(1); 
//  }
//}