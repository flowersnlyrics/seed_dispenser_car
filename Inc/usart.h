/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/*!
 * Print a string
 * @param array A pointer to a char array
 */
void usart_print(char * array); 

/*!
 * Print a string with a newline character at the end
 * @param array A pointer to a char array
 */
void usart_print_ln(char * array); 

/*!
 * Print an unsigned 16 bit number in hex format
 * @param number Value to print
 */
void usart_print_num_hex(uint16_t number);

/*!
 * Print an unsigned 16 bit number in binary format
 * @param number Value to print
 */
void usart_print_num_bin(uint16_t number);

/*!
 * Clears the uart screen
 * @param void
 */
void usart_clear_screen(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
