#include "LSM9DS1_Driver.h"

LSM9DS1_status_t LSM9DS1_driver_init(void)
{
}

LSM9DS1_status_t LSM9DS1_driver_register_operation(bool read_or_write, bool mag_or_ag, uint8_t address, uint8_t *buf, uint8_t num_bytes)
{
    LSM9DS1_status_t status = LSM9DS1_OK; 
    HAL_SPI_StateTypeDef spi_status = HAL_SPI_STATE_READY; 
    uint8_t mode_address_byte = 0x0000; 
    GPIO_TypeDef *cs_port = NULL; 
    uint16_t cs_pin = 0x0000; 
    if ( read_or_write == LSM9DS1_READ ) 
    {
        mode_address_byte = mode_address_byte | (LSM9DS1_READ_MODE);    /* Set to read mode */
#if  LSM9DS1_DEBUG
        usart_print("Read");     
#endif/* -----  end of ifdef LSM9DS1_DEBUG  ----- */
    }
    else 
    {
        mode_address_byte = mode_address_byte | (LSM9DS1_WRITE_MODE);    /* Set to write mode */
#if  LSM9DS1_DEBUG
        usart_print("Write");     
#endif/* -----  end of ifdef LSM9DS1_DEBUG  ----- */
    }/* ----------  end of if-else read_or_write == LSM9DS1_READ  ---------- */
    if ( mag_or_ag == MAGTYPE ) 
    {
        mode_address_byte = mode_address_byte | (address & 0x3F); 
        if ( num_bytes > 1 ) 
        {
            mode_address_byte = mode_address_byte | (1 << 6); 
        }/* ----------  end of if num_bytes > 1  ---------- */
        cs_port = ADA_BOB_MCS_GPIO_Port; 
        cs_pin = ADA_BOB_MCS_Pin; 
#if  LSM9DS1_DEBUG
        usart_print_ln(" request to Magnetometer");     
#endif/* -----  end of ifdef LSM9DS1_DEBUG  ----- */
    }
    else 
    {
        mode_address_byte = mode_address_byte | (address & 0x7F); 
        cs_port = ADA_BOB_AGCS_GPIO_Port; 
        cs_pin = ADA_BOB_AGCS_Pin; 
#if  LSM9DS1_DEBUG
        usart_print_ln(" request to Accelerometer/Gyroscope");     
#endif/* -----  end of ifdef LSM9DS1_DEBUG  ----- */
    }/* ----------  end of if-else mag_or_ag == MAGTYPE  ---------- */

#if  LSM9DS1_DEBUG
    usart_print("Starting Address: "); 
    usart_print_num_hex((uint8_t)address);usart_print_ln(""); 
    usart_print("Mode Address Byte: "); 
    usart_print_num_hex((uint16_t)mode_address_byte);usart_print_ln("");  
#endif/* -----  end of ifdef LSM9DS1_DEBUG  ----- */

    for ( int a = 0; a < 2; a += 1 ) {
        while ( 1 ) 
        {
            spi_status = HAL_SPI_GetState(&hspi1); 
            if(spi_status == HAL_SPI_STATE_READY)
            {
                if ( a == 0 ) 
                {
                    HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_RESET); /* Set CS LOW */
                    HAL_SPI_Transmit(&hspi1,&mode_address_byte,1,SPI_TIMEOUT); /* Need to transmit the address telling it to read */
                }
                else 
                {
                    if ( read_or_write == LSM9DS1_READ ) 
                    {
                        HAL_SPI_Receive(&hspi1,buf,num_bytes,SPI_TIMEOUT);
                    }
                    else 
                    {
                        HAL_SPI_Transmit(&hspi1,buf,num_bytes,SPI_TIMEOUT); 
                    }/* ----------  end of if-else read_or_write == LSM9DS1_READ  ---------- */
                    HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_SET); /* Set CS HIGH */
                }/* ----------  end of if-else a = 0  ---------- */
                break; 
            }/* ----------  end of if spi_stats == HAL_SPI_STATE_READY  ---------- */
        }/* ----------  end of while 1  ---------- */
    }/* ----------  end of for int a = 0; a < 2; a += 1  ---------- */
    
    return status; 
} 


LSM9DS1_status_t LSM9DS1_driver_print_all_registers ( bool mag_or_ag )
{
    LSM9DS1_status_t status = LSM9DS1_OK; 
#if  LSM9DS1_DEBUG
    uint8_t rx_buf[128] = {0}; 
    uint16_t max_register_num = 0; 

    if ( mag_or_ag == MAGTYPE ) 
    {
        max_register_num = MAG_MAX_REG_NUM;  
        usart_print_ln("Printing All Magnetometer Registers..."); 
    }
    else 
    {
        max_register_num = XG_MAX_REG_NUM;  
        usart_print_ln("Printing All Accelerometer/Gyroscope Registers..."); 
    }/* ----------  end of if-else mag_or_ag == MAGTYPE  ---------- */

    LSM9DS1_driver_register_operation(LSM9DS1_READ,mag_or_ag,0x00,rx_buf,max_register_num); 

    for ( uint16_t i = 0; i < max_register_num; i++ ) 
    {
        usart_print("Address:"); usart_print_num_hex(i); usart_print("      Value:"); 
        usart_print_num_hex((uint16_t) rx_buf[i]); 
        usart_print_ln(""); 
    }/* ----------  end of for int i = 0; i < max_register_num; i++  ---------- */
    usart_print_ln("");
#endif/* -----  end of ifdef LSM9DS1_DEBUG  ----- */
    return status;
}/* -----  end of function LSM9DS1_driver_print_all_registers  ----- */
