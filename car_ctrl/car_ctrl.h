#ifndef __CAR_CTRL_H__
#define __CAR_CTRL_H__

/* ----------------------------------------------------------------- Includes */
#include "wheel_ctrl.h"

/* ------------------------------------------------------- Public Definitions */
typedef enum
{
  ADVANCE = 0, 
  REVERSE, 
  LEFT, 
  RIGHT,
  BRAKE, 
  NUM_CAR_DIRS 
} car_move_t; 

/* ----------------------------------------------- Public Function Prototypes */
void car_ctrl_init(void); 
void car_ctrl_move(car_move_t move); 

#endif /* __CAR_CTRL_H__ */