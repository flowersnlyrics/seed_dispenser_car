#include "LSM9DS1_Driver.h"

LSM9DS1_status_t LSM9DS1_driver_init(void)
{
    LSM9DS1_status_t status = LSM9DS1_OK; 

    usart_print_ln("Initializing LSM9DS1"); 
    return status; 
}

LSM9DS1_status_t LSM9DS1_driver_write(uint8_t address, uint8_t *data, uint8_t numBytes)
{

    //variables & initializations
    LSM9DS1_status_t status = LSM9DS1_OK; 
    HAL_SPI_StateTypeDef spi_status = HAL_SPI_STATE_READY; 
    uint8_t modeAddressByte = 0x00; 

    //Setting
    modeAddressByte = (LSM9DS1_WRITE_MODE) | (address & 0x7); 

    for ( int a = 0; a < 2; a += 1 ) {
        while(1)                                    /* Check that we aren't trying to write spi when the engine isn't ready */
        {
            spi_status = HAL_SPI_GetState(&hspi1); 
            if(spi_status == HAL_SPI_STATE_READY)
            {
                if(a == 0)
                {
                    //Here set cs 
                    HAL_SPI_Transmit(&hspi1,&modeAddressByte,sizeof(modeAddressByte),SPI_TIMEOUT); /* Sending out the address byte first */
                }else
                {
                    HAL_SPI_Transmit(&hspi1,data,numBytes,SPI_TIMEOUT); /* Sending out the address byte first */
                    //Here unset cs
                }
                break; 
            }
        }
    }
    return status; 
}

LSM9DS1_status_t LSM9DS1_driver_read(uint8_t address, uint8_t *buf, uint8_t numBytes)
{

    LSM9DS1_status_t status = LSM9DS1_OK; 

    

    return status; 

} 
