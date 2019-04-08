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
#define ADA_BOB_SCK_Pin GPIO_PIN_1
#define ADA_BOB_SCK_GPIO_Port GPIOA
#define DEBUG_UART_TX_Pin GPIO_PIN_2
#define DEBUG_UART_TX_GPIO_Port GPIOA
#define WHEEL_MOTOR_ENA_Pin GPIO_PIN_3
#define WHEEL_MOTOR_ENA_GPIO_Port GPIOA
#define ADA_BOB_ACS_Pin GPIO_PIN_4
#define ADA_BOB_ACS_GPIO_Port GPIOA
#define WHEEL_MOTOR_ENB_Pin GPIO_PIN_5
#define WHEEL_MOTOR_ENB_GPIO_Port GPIOA
#define ADA_BOB_MISO_Pin GPIO_PIN_6
#define ADA_BOB_MISO_GPIO_Port GPIOA
#define ADA_BOB_MOSI_Pin GPIO_PIN_7
#define ADA_BOB_MOSI_GPIO_Port GPIOA
#define MILL_MOTOR_IN3_Pin GPIO_PIN_0
#define MILL_MOTOR_IN3_GPIO_Port GPIOB
#define MILL_MOTOR_IN4_Pin GPIO_PIN_1
#define MILL_MOTOR_IN4_GPIO_Port GPIOB
#define LVL_SHIFTER_OE_HI_Pin GPIO_PIN_8
#define LVL_SHIFTER_OE_HI_GPIO_Port GPIOA
#define WHEEL_MOTOR_IN1_Pin GPIO_PIN_9
#define WHEEL_MOTOR_IN1_GPIO_Port GPIOA
#define WHEEL_MOTOR_IN2_Pin GPIO_PIN_10
#define WHEEL_MOTOR_IN2_GPIO_Port GPIOA
#define WHEEL_MOTOR_IN3_Pin GPIO_PIN_11
#define WHEEL_MOTOR_IN3_GPIO_Port GPIOA
#define WHEEL_MOTOR_IN4_Pin GPIO_PIN_12
#define WHEEL_MOTOR_IN4_GPIO_Port GPIOA
#define DEBUG_UART_RX_Pin GPIO_PIN_15
#define DEBUG_UART_RX_GPIO_Port GPIOA
#define ADA_BOB_MCS_Pin GPIO_PIN_3
#define ADA_BOB_MCS_GPIO_Port GPIOB
#define MILL_MOTOR_IN2_Pin GPIO_PIN_4
#define MILL_MOTOR_IN2_GPIO_Port GPIOB
#define TACH_INT_Pin GPIO_PIN_5
#define TACH_INT_GPIO_Port GPIOB
#define TACH_INT_EXTI_IRQn EXTI9_5_IRQn
#define MILL_MOTOR_IN1_Pin GPIO_PIN_7
#define MILL_MOTOR_IN1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
