/*******************************************************************************
* @file           : accel_if.c
* @brief          : Talk to the accelerometer on the Adafruit BB 
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include "accel_if.h"
#include "mag_if.h"

/* ------------------------------------------------------ Private Definitions */
#define ACCEL_I2C_HANDLE hi2c1 

static uint8_t ADDR_DESC[NUM_ACCEL_REGS] = 
{
  WHO_AM_I_XG_ADDR, 
  CTRL_REG5_XL_ADDR,
  CTRL_REG6_XL_ADDR,
  CTRL_REG8_ADDR, 
};

/* ---------------------------------------------- Private Function Prototypes */
static bool read(uint8_t* rx, uint8_t size);
static bool write(uint8_t* tx, uint8_t size);

/* ---------------------------------------------- Public Function Definitions */

/******************************************************************************
 * @fn      accel_if_init
 * @brief  
 * @note    Need to reset all interfaces on the SDA bus because
 *          sometimes when they come up they hold the line low, making
 *          a fake busy signal 
 * @return  
 ******************************************************************************/
bool accel_if_init(void)
{
  if(accel_if_reset())
  {
    return mag_if_reset();
  }
  
  return false; 
}
 
/******************************************************************************
 * @fn      accel_if_read_reg
 * @brief  
 * @param   
 * @param   buff: current value of register
 * @return  
 ******************************************************************************/
bool accel_if_read_reg(accel_reg_t reg, uint8_t* buff)
{ 
  if(!write(&ADDR_DESC[reg], SIZE_OF_ACCEL_REGISTER))
  {
    return false; 
  }
  
  return read(buff, SIZE_OF_ACCEL_REGISTER);
}

/******************************************************************************
 * @fn      accel_if_write_reg
 * @brief  
 * @param   
 * @param    buff: value you want the register to be 
 * @return  
 ******************************************************************************/
bool accel_if_write_reg(accel_reg_t reg, uint8_t* buff)
{ 
  uint8_t tx[2] = {ADDR_DESC[reg], *buff};
  
  if(!write(tx, 
            (SIZE_OF_ACCEL_REGISTER + SIZE_OF_ACCEL_REGISTER_ADDR))
     )
  {
    return false; 
  }
  
  return i2c_wait_for_i2c(&ACCEL_I2C_HANDLE);
}

/******************************************************************************
 * @fn      accel_if_reset
 * @brief  
 * @return  
 ******************************************************************************/
bool accel_if_reset(void)
{
  uint8_t reset_cmd =  CTRL_REG8_SW_RESET_RESET | CTRL_REG8_IF_ADD_INC_EN; 
  
  if(!accel_if_write_reg(CTRL_REG_8, &reset_cmd))
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
  if (HAL_I2C_Master_Receive_IT(&ACCEL_I2C_HANDLE, 
                                ACCEL_I2C_WRITE_ADDR, 
                                rx, 
                                size) 
      != HAL_OK)
  {
    return false;
  }
  
  if (!i2c_wait_for_i2c(&ACCEL_I2C_HANDLE))
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
  if (HAL_I2C_Master_Transmit_IT(&ACCEL_I2C_HANDLE, 
                                 ACCEL_I2C_WRITE_ADDR, 
                                 tx, 
                                 size) 
      != HAL_OK)
  {
    return false;
  }
  
  if (!i2c_wait_for_i2c(&ACCEL_I2C_HANDLE))
  { 
    return false;
  }
  
  return true; 
}

