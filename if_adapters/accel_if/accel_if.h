#ifndef __ACCEL_IF_H__
#define __ACCEL_IF_H__

/* ----------------------------------------------------------------- Includes */
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "i2c.h"
#include "accel_regs.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum 
{
  WHO_AM_I_XG = 0, 
  CTRL_REG5_XL, 
  CTRL_REG6_XL, 
  CTRL_REG_8,
  NUM_ACCEL_REGS
} accel_reg_t; 

/* ----------------------------------------------- Public Function Prototypes */

bool accel_if_init(void); 
bool accel_if_read_reg(accel_reg_t reg, uint8_t* buff);
bool accel_if_write_reg(accel_reg_t reg, uint8_t* buff); 
bool accel_if_reset(void);  

#endif /* __ACCEL_IF_H__ */ 