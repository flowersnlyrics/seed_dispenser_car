#ifndef __MAG_IF_H__
#define __MAG_IF_H__

/* ----------------------------------------------------------------- Includes */
#include <stdbool.h>
#include "stm32l4xx_hal.h"
#include "i2c.h"
#include "mag_regs.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum 
{
  WHO_AM_I_M = 0, 
  CTRL_REG2_M,
  CTRL_REG3_M,
  NUM_MAG_REGS
} mag_reg_t; 

/* ----------------------------------------------- Public Function Prototypes */

bool mag_if_init(void); 
bool mag_if_read_reg(mag_reg_t reg, uint8_t* buff);
bool mag_if_write_reg(mag_reg_t reg, uint8_t* buff); 
bool mag_if_reset(void);  

#endif /* __MAG_IF_H__ */ 