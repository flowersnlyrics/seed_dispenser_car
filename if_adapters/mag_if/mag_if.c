/*******************************************************************************
* @file           : mag_if.c
* @brief          : Talk to the accelerometer on the Adafruit BB 
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include "mag_if.h"

/* ------------------------------------------------------ Private Definitions */
#define MAG_I2C_HANDLE hi2c1 

static uint8_t ADDR_DESC[NUM_MAG_REGS] = 
{
  WHO_AM_I_M_ADDR, 
  CTRL_REG2_M_ADDR, 
};

/* ---------------------------------------------- Private Function Prototypes */
static bool read(uint8_t* rx, uint8_t size);
static bool write(uint8_t* tx, uint8_t size);

/* ---------------------------------------------- Public Function Definitions */

/******************************************************************************
 * @fn      mag_if_init
 * @brief  
 * @note    Need to reset all interfaces on the SDA bus because
 *          sometimes when they come up they hold the line low, making
 *          a fake busy signal 
 * @return  
 ******************************************************************************/
bool mag_if_init(void)
{
  return mag_if_reset(); 
}
 
/******************************************************************************
 * @fn      mag_if_read_reg
 * @brief  
 * @param   
 * @param   buff: current value of register
 * @return  
 ******************************************************************************/
bool mag_if_read_reg(mag_reg_t reg, uint8_t* buff)
{ 
  if(!write(&ADDR_DESC[reg], SIZE_OF_MAG_REGISTER))
  {
    return false; 
  }
  
  return read(buff, SIZE_OF_MAG_REGISTER);
}

/******************************************************************************
 * @fn      mag_if_write_reg
 * @brief  
 * @param   
 * @param    buff: value you want the register to be 
 * @return  
 ******************************************************************************/
bool mag_if_write_reg(mag_reg_t reg, uint8_t* buff)
{ 
  if(!write(&ADDR_DESC[reg], 
            (SIZE_OF_MAG_REGISTER + SIZE_OF_MAG_REGISTER_ADDR))
     )
  {
    return false; 
  }
  
  return i2c_wait_for_i2c(&MAG_I2C_HANDLE);
}

/******************************************************************************
 * @fn      mag_if_reset
 * @brief  
 * @return  
 ******************************************************************************/
bool mag_if_reset(void)
{
  uint8_t reset_cmd =  CTRL_REG2_M_REBOOT_REBOOT | CTRL_REG2_M_SOFT_RST_RESET; 
  
  if(!mag_if_write_reg(CTRL_REG2, &reset_cmd))
  {
    return false; 
  }
  
  HAL_Delay(10);
  
  return true; 
}

/* --------------------------------------------- Private Function Definitions */

/******************************************************************************
 * @fn      read
 * @brief  
 * @param   rx: buffer to store received data 
 * @param   
 * @return  
 ******************************************************************************/
static bool read(uint8_t* rx, uint8_t size)
{
  if (HAL_I2C_Master_Receive_IT(&MAG_I2C_HANDLE, 
                                MAG_I2C_WRITE_ADDR, 
                                rx, 
                                size) 
      != HAL_OK)
  {
    return false;
  }
  
  if (!i2c_wait_for_i2c(&MAG_I2C_HANDLE))
  { 
    return false;
  }
  
  return true; 
}

/******************************************************************************
 * @fn      write
 * @brief  
* @param   tx: Buffer to write to accelerometer 
 * @param   
 * @return  
 ******************************************************************************/
static bool write(uint8_t* tx, uint8_t size)
{
  if (HAL_I2C_Master_Transmit_IT(&MAG_I2C_HANDLE, 
                                 MAG_I2C_WRITE_ADDR, 
                                 tx, 
                                 size) 
      != HAL_OK)
  {
    return false;
  }
  
  if (!i2c_wait_for_i2c(&MAG_I2C_HANDLE))
  { 
    return false;
  }
  
  return true; 
}

