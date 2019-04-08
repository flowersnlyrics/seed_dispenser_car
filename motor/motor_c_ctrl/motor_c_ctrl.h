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
} motor_c_rotation_t; 

typedef enum 
{
  LEFT_MOTORS = 0, 
  RIGHT_MOTORS,  
  NUM_MOTOR_GROUPS
} motor_c_grp_t; 

/* ----------------------------------------------- Public Function Prototypes */
void motor_c_init(void); 
void motor_c_ctrl_start(motor_c_grp_t motor_grp); 
void motor_c_ctrl_stop(motor_c_grp_t motor_grp); 
void motor_c_ctrl_rotation(motor_c_grp_t motor_grp, motor_c_rotation_t rotation); 
void motor_c_ctrl_speed(motor_c_grp_t motor_grp, uint8_t speed); 

#endif /* __MOTOR_CTRL_H__ */