#ifndef __CAR_CTRL_H__
#define __CAR_CTRL_H__

/* ----------------------------------------------------------------- Includes */
#include "motor_ctrl.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum
{
  ADVANCE = 0, 
  REVERSE, 
  LEFT, 
  RIGHT,
  NUM_CAR_DIRS 
} car_dir_t; 

/* ----------------------------------------------- Public Function Prototypes */
void car_ctrl_init(void); 
void car_ctrl_direction(car_dir_t dir); 

#endif /* __CAR_CTRL_H__ */