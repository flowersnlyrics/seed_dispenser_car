#ifndef __WHEEL_CTRL_H__
#define __WHEEL_CTRL_H__

/* ----------------------------------------------------------------- Includes */
#include "tim.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum 
{
  CLOCKWISE, 
  COUNTER_CLOCKWISE, 
  NO_ROTATION,
  NUM_MOTOR_DIRS
} wheel_rotation_t; 

typedef enum 
{
  LEFT_WHEELS = 0, 
  RIGHT_WHEELS,  
  NUM_WHEEL_SIDES
} wheel_side_t; 

/* ----------------------------------------------- Public Function Prototypes */
void wheel_init(void); 
void wheel_ctrl_start(wheel_side_t motor_grp); 
void wheel_ctrl_stop(wheel_side_t motor_grp); 
void wheel_ctrl_rotation(wheel_side_t motor_grp, wheel_rotation_t rotation); 
void wheel_ctrl_speed(wheel_side_t motor_grp, uint8_t speed); 

#endif /* __WHEEL_CTRL_H__ */