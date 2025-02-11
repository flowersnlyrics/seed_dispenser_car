/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DEBUG_UART_TX_Pin //GPIO_PIN_2
#define DEBUG_UART_TX_GPIO_Port //GPIOA

#define WHEEL_MOTOR_ENA_Pin GPIO_PIN_3
#define WHEEL_MOTOR_ENA_GPIO_Port GPIOA

#define MILL_MOTOR_IN1_Pin GPIO_PIN_11
#define MILL_MOTOR_IN1_GPIO_Port GPIOA

#define WHEEL_MOTOR_ENB_Pin GPIO_PIN_5
#define WHEEL_MOTOR_ENB_GPIO_Port GPIOA

#define MILL_MOTOR_IN3_Pin GPIO_PIN_1//GPIO_PIN_15
#define MILL_MOTOR_IN3_GPIO_Port GPIOB//GPIOC

#define MILL_MOTOR_IN4_Pin GPIO_PIN_0//GPIO_PIN_14
#define MILL_MOTOR_IN4_GPIO_Port GPIOB//GPIOC

#define LVL_SHIFTER_OE_1_Pin GPIO_PIN_4
#define LVL_SHIFTER_OE_1_GPIO_Port GPIOB

#define LVL_SHIFTER_OE_2_Pin GPIO_PIN_2
#define LVL_SHIFTER_OE_2_GPIO_Port GPIOA

#define WHEEL_MOTOR_IN1_Pin GPIO_PIN_1
#define WHEEL_MOTOR_IN1_GPIO_Port GPIOA

#define WHEEL_MOTOR_IN2_Pin GPIO_PIN_4
#define WHEEL_MOTOR_IN2_GPIO_Port GPIOA

#define WHEEL_MOTOR_IN3_Pin GPIO_PIN_0//GPIO_PIN_9//GPIO_PIN_6
#define WHEEL_MOTOR_IN3_GPIO_Port GPIOA

#define WHEEL_MOTOR_IN4_Pin GPIO_PIN_7
#define WHEEL_MOTOR_IN4_GPIO_Port GPIOA

#define DEBUG_UART_RX_Pin //GPIO_PIN_15
#define DEBUG_UART_RX_GPIO_Port //GPIOA

#define MILL_MOTOR_IN2_Pin GPIO_PIN_8
#define MILL_MOTOR_IN2_GPIO_Port GPIOA

#define TACH_INT_Pin GPIO_PIN_5
#define TACH_INT_GPIO_Port GPIOB
#define TACH_INT_EXTI_IRQn EXTI9_5_IRQn

#define START_CAR_Pin GPIO_PIN_10
#define START_CAR_GPIO_Port GPIOA
#define START_CAR_EXTI_IRQn EXTI10_15_IRQn

#define STOP_CAR_Pin GPIO_PIN_12
#define STOP_CAR_GPIO_Port GPIOA
#define STOP_CAR_EXTI_IRQn EXTI15_10_IRQn

#define SPARE_BUTTON_3_Pin GPIO_PIN_9
#define SPARE_BUTTON_3_GPIO_Port GPIOA
#define SPARE_BUTTON_3_EXTI_IRQn EXTI9_5_IRQn


#define SPARE_BUTTON_4_Pin GPIO_PIN_3
#define SPARE_BUTTON_4_GPIO_Port GPIOB
#define SPARE_BUTTON_4_EXTI_IRQn EXTI3_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/