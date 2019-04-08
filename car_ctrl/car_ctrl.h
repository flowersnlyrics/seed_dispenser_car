#ifndef __CAR_CTRL_H__
#define __CAR_CTRL_H__

/* ----------------------------------------------------------------- Includes */
<<<<<<< HEAD
#include "motor_c_ctrl.h"
=======
#include "wheel_ctrl.h"
>>>>>>> my_car

/* ------------------------------------------------------- Public Definitions */
typedef enum
{
  ADVANCE = 0, 
  REVERSE, 
  LEFT, 
  RIGHT,
  PARK, 
  NUM_CAR_DIRS 
} car_move_t; 

/* ----------------------------------------------- Public Function Prototypes */
void car_ctrl_init(void); 
void car_ctrl_move(car_move_t move); 
void car_start(void); 
void car_stop(void); 

#endif /* __CAR_CTRL_H__ */