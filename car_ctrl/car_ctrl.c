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
  car_ctrl_move(BRAKE); 
  // Set the speed to 0 :) 
  wheel_ctrl_speed(LEFT_WHEELS, BRAKE_CAR_SPEED); 
  wheel_ctrl_speed(RIGHT_WHEELS, BRAKE_CAR_SPEED); 
  
}


void car_ctrl_move(car_move_t move)
{
  switch(move)
  {
    case ADVANCE: 
      wheel_ctrl_rotation(LEFT_WHEELS, CLOCKWISE); 
      wheel_ctrl_rotation(RIGHT_WHEELS, CLOCKWISE);
      break; 
    case REVERSE:
      wheel_ctrl_rotation(LEFT_WHEELS, COUNTER_CLOCKWISE); 
      wheel_ctrl_rotation(RIGHT_WHEELS, COUNTER_CLOCKWISE);
      break; 
    case LEFT:
      wheel_ctrl_rotation(LEFT_WHEELS, CLOCKWISE); 
      wheel_ctrl_rotation(RIGHT_WHEELS, COUNTER_CLOCKWISE);
      break; 
    case RIGHT:
      wheel_ctrl_rotation(LEFT_WHEELS, COUNTER_CLOCKWISE); 
      wheel_ctrl_rotation(RIGHT_WHEELS, CLOCKWISE);
      break; 
    case BRAKE:
      wheel_ctrl_rotation(LEFT_WHEELS, NO_ROTATION); 
      wheel_ctrl_rotation(RIGHT_WHEELS, NO_ROTATION);
      break; 
  }
}