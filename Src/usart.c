/**
  ******************************************************************************
  * File Name          : USART.c
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart2;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA15 (JTDI)     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = VCP_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(VCP_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = VCP_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_USART2;
    HAL_GPIO_Init(VCP_RX_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA15 (JTDI)     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, VCP_TX_Pin|VCP_RX_Pin);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void usart_print(char * array){
	uint8_t i = 0;
	while(array[i] != '\0'){
		i++;
	}
	HAL_UART_Transmit(&huart2,(uint8_t *)array,i,1000);
}

void usart_print_ln(char *array){
	uint8_t i = 0;
	uint8_t endLineChars[2] = {0};

	endLineChars[0] = '\n';
	endLineChars[1] = '\r';

	while(array[i] != '\0'){
		i++;
	}
	HAL_UART_Transmit(&huart2,(uint8_t *)array,i,1000);
	HAL_UART_Transmit(&huart2,(uint8_t *)endLineChars,2,1000);

}
void usart_print_num_hex(uint16_t number){
	char tempArray[7] = {'0','x','0','0','0','0','\0'};
	char hexArray[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	uint16_t temp2 = number;
	int trackNum = 0;


	for(int i = 4; i >= 0; i--){
		if(trackNum == 0){
			trackNum = trackNum + 2;

		}else if((trackNum == 1) | (trackNum == 6) | (trackNum == 11)| (trackNum == 16)){
			trackNum++;
		}

		tempArray[trackNum]= hexArray[((temp2 & 0xf000) >> 12)];
		temp2 = temp2 << 4;
		trackNum++;
	}

	usart_print_ln(tempArray);
}
void usart_print_num_bin(uint16_t number){
	char tempArray[22] = {'0','b','0','0','0','0','_','0','0','0','0','_','0','0','0','0','_','0','0','0','0','\0'};
	uint16_t temp2 = number;
	int trackNum = 0;

	for(int i = 15; i >= 0; i--){

		if(trackNum == 0){
			trackNum = trackNum + 2;
		}else if((trackNum == 1) | (trackNum == 6) | (trackNum == 11)| (trackNum == 16)){
			trackNum++;
		}

		if((temp2 & 0x8000) >> 15 == 1){
			tempArray[trackNum] = '1';
		}else{
			tempArray[trackNum] = '0';
		}

		trackNum++;
		temp2 = temp2 << 1;

	}

	usart_print_ln(tempArray);
}

void usart_clear_screen(void)
{
    //Move cursor to 0,0
    usart_print("\033[0;0H"); 

    //Clear the screen
    usart_print("\033[2J"); 
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
