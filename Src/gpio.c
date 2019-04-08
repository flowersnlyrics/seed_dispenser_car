/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through 
        * the Code Generation settings)
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ADA_BOB_ACS_Pin|WHEEL_MOTOR_IN1_Pin|WHEEL_MOTOR_IN2_Pin|WHEEL_MOTOR_IN3_Pin 
                          |WHEEL_MOTOR_IN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
<<<<<<< HEAD
  HAL_GPIO_WritePin(GPIOB, WINDMILL_MOTOR_IN3_Pin|WINDMILL_MOTOR_IN4_Pin|ADA_BOB_MCS_Pin|WINDMILL_MOTOR_IN2_Pin, GPIO_PIN_RESET);
=======
  HAL_GPIO_WritePin(GPIOB, MILL_MOTOR_IN3_Pin|MILL_MOTOR_IN4_Pin|ADA_BOB_MCS_Pin|MILL_MOTOR_IN2_Pin, GPIO_PIN_RESET);
>>>>>>> my_car

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LVL_SHIFTER_OE_HI_GPIO_Port, LVL_SHIFTER_OE_HI_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
<<<<<<< HEAD
  HAL_GPIO_WritePin(WINDMILL_MOTOR_IN1_GPIO_Port, WINDMILL_MOTOR_IN1_Pin, GPIO_PIN_RESET);
=======
  HAL_GPIO_WritePin(MILL_MOTOR_IN1_GPIO_Port, MILL_MOTOR_IN1_Pin, GPIO_PIN_RESET);
>>>>>>> my_car

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin 
                           PAPin */
  GPIO_InitStruct.Pin = ADA_BOB_ACS_Pin|WHEEL_MOTOR_IN1_Pin|WHEEL_MOTOR_IN2_Pin|WHEEL_MOTOR_IN3_Pin 
                          |WHEEL_MOTOR_IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

<<<<<<< HEAD
  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = WINDMILL_MOTOR_IN3_Pin|WINDMILL_MOTOR_IN4_Pin|WINDMILL_MOTOR_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
=======
  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = MILL_MOTOR_IN3_Pin|MILL_MOTOR_IN4_Pin|ADA_BOB_MCS_Pin|MILL_MOTOR_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
>>>>>>> my_car
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LVL_SHIFTER_OE_HI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LVL_SHIFTER_OE_HI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
<<<<<<< HEAD
  GPIO_InitStruct.Pin = ADA_BOB_MCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ADA_BOB_MCS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
=======
>>>>>>> my_car
  GPIO_InitStruct.Pin = TACH_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TACH_INT_GPIO_Port, &GPIO_InitStruct);

<<<<<<< HEAD
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = WINDMILL_MOTOR_IN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(WINDMILL_MOTOR_IN1_GPIO_Port, &GPIO_InitStruct);
=======
  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = MILL_MOTOR_IN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MILL_MOTOR_IN1_GPIO_Port, &GPIO_InitStruct);
>>>>>>> my_car

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
