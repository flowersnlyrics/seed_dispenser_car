#ifndef __MOTOR_CTRL_H__
#define __MOTOR_CTRL_H__

/* ----------------------------------------------------------------- Includes */
#include "tim.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum 
{
  CLOCKWISE, 
  COUNTER_CLOCKWISE, 
  BREAK,
  NUM_MOTOR_DIRS
} motor_dir_t; 

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
void motor_ctrl_direction(motor_grp_t motor, motor_dir_t dir); 
void motor_ctrl_speed(motor_grp_t motor, uint8_t speed); 

#endif /* __MOTOR_CTRL_H__ */