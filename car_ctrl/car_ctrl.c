/*******************************************************************************
* @file           : main.c
* @brief          : moves the car forward, backward, left and right 
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include "car_ctrl.h"

/* ------------------------------------------------------ Private Definitions */
#define BRAKE_CAR_SPEED 0x00

/* ---------------------------------------------- Private Function Prototypes */

/* ---------------------------------------------- Public Function Definitions */
void car_ctrl_init(void)
{
  // Make sure car doesn't move at start up 
  car_ctrl_move(PARK); 
  // Set the speed to 0 :) 
  motor_c_ctrl_speed(LEFT_MOTORS, BRAKE_CAR_SPEED); 
  motor_c_ctrl_speed(RIGHT_MOTORS, BRAKE_CAR_SPEED); 
  
}


void car_ctrl_move(car_move_t move)
{
  switch(move)
  {
    case ADVANCE: 
      motor_c_ctrl_rotation(LEFT_MOTORS, CLOCKWISE); 
      motor_c_ctrl_rotation(RIGHT_MOTORS, CLOCKWISE);
      break; 
    case REVERSE:
      motor_c_ctrl_rotation(LEFT_MOTORS, COUNTER_CLOCKWISE); 
      motor_c_ctrl_rotation(RIGHT_MOTORS, COUNTER_CLOCKWISE);
      break; 
    case LEFT:
      motor_c_ctrl_rotation(LEFT_MOTORS, CLOCKWISE); 
      motor_c_ctrl_rotation(RIGHT_MOTORS, COUNTER_CLOCKWISE);
      break; 
    case RIGHT:
      motor_c_ctrl_rotation(LEFT_MOTORS, COUNTER_CLOCKWISE); 
      motor_c_ctrl_rotation(RIGHT_MOTORS, CLOCKWISE);
      break; 
    case PARK:
      motor_c_ctrl_rotation(LEFT_MOTORS, NO_ROTATION); 
      motor_c_ctrl_rotation(RIGHT_MOTORS, NO_ROTATION);
      break; 
  }
}


void car_start(void)
{
  
}

void car_stop(void)
{
  car_ctrl_move(PARK); 
  motor_c_ctrl_stop(RIGHT_MOTORS); 
  motor_c_ctrl_stop(LEFT_MOTORS);
}


