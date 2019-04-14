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

typedef struct
{
  float x; 
  float y; 
  float z; 
} accel_read_t; 

/* ----------------------------------------------- Public Function Prototypes */
bool accel_ctrl_init(void); 
bool accel_ctrl_get_read(accel_read_t* read); 

#endif /* __ACCEL_CTRL_H__ */