/*******************************************************************************
* @file           : tach_ctrl.c
* @brief          : 
*******************************************************************************/
/* ----------------------------------------------------------------- Includes */
#include "main.h"
#include "tach_ctrl.h"

/* ------------------------------------------------------ Private Definitions */
volatile uint32_t g_spin_counter = 0; 


/* ---------------------------------------------- Public Function Definitions */

/******************************************************************************
 * @fn      tach_ctrl_init
 * @brief  
 * @return  
 ******************************************************************************/
void tach_ctrl_init(void)
{
  g_spin_counter = 0; 
}


void tach_ctrl_inc(void)
{
  g_spin_counter++; 
}


/* void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 {
   if(GPIO_Pin == TACH_INT_Pin)
   {
     g_spin_counter++; 
     while(HAL_GPIO_ReadPin(TACH_INT_GPIO_Port, TACH_INT_Pin) != GPIO_PIN_RESET); 
   }
 }*/