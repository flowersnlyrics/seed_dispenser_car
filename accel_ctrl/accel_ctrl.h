#ifndef __ACCEL_CTRL_H__
#define __ACCEL_CTRL_H__

/* ----------------------------------------------------------------- Includes */
#include "accel_if.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum
{
  X_AXIS, 
  Y_AXIS, 
  Z_AXIS, 
  NUM_AXES
} axis_t; 

/* ----------------------------------------------- Public Function Prototypes */
bool accel_ctrl_init(void); 


#endif /* __ACCEL_CTRL_H__ */