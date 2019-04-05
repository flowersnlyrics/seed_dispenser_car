#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__

/* ----------------------------------------------------------------- Includes */
#include "tim.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum 
{
  CLOCKWISE, 
  COUNTER_CLOCKWISE, 
  NO_ROTATION,
  NUM_MOTOR_DIRS
} motor_rotation_t; 

typedef enum 
{
  LEFT_MOTORS = 0, 
  RIGHT_MOTORS,  
  NUM_MOTOR_GROUPS
} motor_grp_t; 

/* ----------------------------------------------- Public Function Prototypes */
void motor_init(void); 
void motor_ctrl_start(motor_grp_t motor_grp); 
void motor_ctrl_stop(motor_grp_t motor_grp); 
void motor_ctrl_rotation(motor_grp_t motor_grp, motor_rotation_t rotation); 
void motor_ctrl_speed(motor_grp_t motor_grp, uint8_t speed); 

#endif /* __MOTOR_CTRL_H__ */