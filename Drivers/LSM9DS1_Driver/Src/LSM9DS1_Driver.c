#include "LSM9DS1_Driver.h"

LSM9DS1_status_t LSM9DS1_driver_init(void)
{
    LSM9DS1_status_t status = LSM9DS1_OK; 

    usart_print_ln("Initializing LSM9DS1"); 
    return status; 
}

//LSM9DS1_status_t LSM9DS1_driver_write(uint8_t address, uint8_t *data, uint8_t num_bytes)
//{
//
//    //variables & initializations
//    LSM9DS1_status_t status = LSM9DS1_OK; 
//    HAL_SPI_StateTypeDef spi_status = HAL_SPI_STATE_READY; 
//
//    //Setting
//    uint8_t mode_address_byte = (LSM9DS1_WRITE_MODE) | (address & 0x7); 
//
//    for ( int a = 0; a < 2; a += 1 ) 
//    {
//        while(1)                                    /* Check that we aren't trying to write spi when the engine isn't ready */
//        {
//            spi_status = HAL_SPI_GetState(&hspi1); 
//            if(spi_status == HAL_SPI_STATE_READY)
//            {
//                if(a == 0)
//                {
//#if  LSM9DS1_DEBUG
//                    usart_print("Mode Address Byte: "); usart_print_num_hex((uint16_t)mode_address_byte);
//                    usart_print_ln(""); 
//#endif     /* -----  end of ifdef LSM9DS1_DEBUG  ----- */
//                    //Here set cs 
//                    HAL_SPI_Transmit(&hspi1,&mode_address_byte,sizeof(mode_address_byte),SPI_TIMEOUT); /* Sending out the address byte first */
//                }else
//                {
//                    HAL_SPI_Transmit(&hspi1,data,num_bytes,SPI_TIMEOUT); /* Sending out the address byte first */
//                    //Here unset cs
//                }
//                break; 
//            }
//        }
//    }
//    return status; 
//}

LSM9DS1_status_t LSM9DS1_Mag_driver_read(uint8_t address, uint8_t *rx_buf, uint8_t num_bytes)
{

    LSM9DS1_status_t status = LSM9DS1_OK; 
    HAL_SPI_StateTypeDef spi_status = HAL_SPI_STATE_READY; 
    uint8_t mode_address_byte = (LSM9DS1_READ_MODE) | (address & 0x7F); 

    for ( int a = 0; a < 2; a += 1 ) {
        while ( 1 ) 
        {
            spi_status = HAL_SPI_GetState(&hspi1); 
            if(spi_status == HAL_SPI_STATE_READY)
            {
                if ( a == 0 ) 
                {
#if  LSM9DS1_DEBUG
                    usart_print("Mode Address Byte: "); usart_print_num_hex((uint16_t)mode_address_byte);
                    usart_print_ln(""); 
#endif/* -----  end of ifdef LSM9DS1_DEBUG  ----- */
                    HAL_GPIO_WritePin(ADA_BOB_MCS_GPIO_Port,ADA_BOB_MCS_Pin,GPIO_PIN_RESET); //,GPIO_PIN_SET); /* Set CS LOW */
                    HAL_SPI_Transmit(&hspi1,&mode_address_byte,1,SPI_TIMEOUT); /* Need to transmit the address telling it to read */
                }
                else 
                {
                    HAL_SPI_Receive(&hspi1,rx_buf,num_bytes,SPI_TIMEOUT);
                    HAL_GPIO_WritePin(ADA_BOB_MCS_GPIO_Port,ADA_BOB_MCS_Pin,GPIO_PIN_SET); //,GPIO_PIN_SET); /* Set CS LOW */
                }/* ----------  end of if-else a = 0  ---------- */
                break; 
            }/* ----------  end of if spi_stats == HAL_SPI_STATE_READY  ---------- */
        }/* ----------  end of while 1  ---------- */
    }/* ----------  end of for int a = 0; a < 2; a += 1  ---------- */
    
    return status; 
} 
