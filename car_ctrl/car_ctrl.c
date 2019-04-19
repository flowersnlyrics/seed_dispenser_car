/*******************************************************************************
* @file           : main.c
* @brief          : moves the car forward, backward, left and right 
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include "car_ctrl.h"
#include <stdbool.h>

/* ------------------------------------------------------ Private Definitions */
#define BRAKE_CAR_SPEED 0x00



static car_speed_t g_wheel_speed = {BRAKE_CAR_SPEED, BRAKE_CAR_SPEED}; 
static bool g_car_running = false; 

/* ---------------------------------------------- Private Function Prototypes */

/* ---------------------------------------------- Public Function Definitions */


/*******************************************************************************
 * @fn      car_ctrl_init
 * @brief   
 ******************************************************************************/
void car_ctrl_init(void)
{
  // Make sure car doesn't move at start up 
  car_ctrl_move(PARK); 
  // Set the speed to 0 :) 
  wheel_ctrl_speed(LEFT_WHEELS, BRAKE_CAR_SPEED); 
  wheel_ctrl_speed(RIGHT_WHEELS, BRAKE_CAR_SPEED); 
}

/*******************************************************************************
 * @fn      car_ctrl_move
 * @brief   
 ******************************************************************************/
void car_ctrl_move(car_move_t move)
{
  if(g_car_running)
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
      case PARK:
        wheel_ctrl_rotation(LEFT_WHEELS, NO_ROTATION); 
        wheel_ctrl_rotation(RIGHT_WHEELS, NO_ROTATION);
        break; 
    }
  }
}

/*******************************************************************************
 * @fn      car_ctrl_start
 * @brief   
 ******************************************************************************/
void car_ctrl_start(void)
{
  g_car_running = true; 
  wheel_ctrl_speed(LEFT_WHEELS, g_wheel_speed.left_duty_cycle); 
  wheel_ctrl_speed(RIGHT_WHEELS, g_wheel_speed.right_duty_cycle); 
  wheel_ctrl_start(LEFT_WHEELS); 
  wheel_ctrl_start(RIGHT_WHEELS); 
}

/*******************************************************************************
 * @fn      car_ctrl_adjust_speed
 * @brief   
 ******************************************************************************/
void car_ctrl_adjust_speed(car_speed_t* speed)
{
  g_wheel_speed.left_duty_cycle = speed->left_duty_cycle; 
  g_wheel_speed.right_duty_cycle = speed->right_duty_cycle; 
  
  if(g_car_running)
  {
    wheel_ctrl_speed(LEFT_WHEELS, g_wheel_speed.left_duty_cycle); 
    wheel_ctrl_speed(RIGHT_WHEELS, g_wheel_speed.right_duty_cycle);
  }
}

/*******************************************************************************
 * @fn      car_ctrl_stop
 * @brief   
 ******************************************************************************/
void car_ctrl_stop(void)
{
  g_car_running = false; 
  car_ctrl_move(PARK); 
  wheel_ctrl_stop(RIGHT_WHEELS); 
  wheel_ctrl_stop(LEFT_WHEELS);
}

#ifdef DEBUG_CAR
/*******************************************************************************
 * @fn      car_test
 * @brief   
 ******************************************************************************/
void car_test(void)
{
  car_speed_t speed = {100,100};
  
  car_ctrl_start();
  car_ctrl_adjust_speed(&speed);
  
  for(car_move_t move = ADVANCE; move < NUM_CAR_DIRS; move++)
  {
    car_ctrl_move(move); 
    HAL_Delay(5000); 
  }
  
  speed.left_duty_cycle = 50; 
  speed.right_duty_cycle = 50; 
  car_ctrl_adjust_speed(&speed);
  
  for(car_move_t move = ADVANCE; move < NUM_CAR_DIRS; move++)
  {
    car_ctrl_move(move); 
    HAL_Delay(5000); 
  }
  
  speed.left_duty_cycle = 30; 
  speed.right_duty_cycle = 30;
  car_ctrl_adjust_speed(&speed);
  
  for(car_move_t move = ADVANCE; move < NUM_CAR_DIRS; move++)
  {
    car_ctrl_move(move); 
    HAL_Delay(5000); 
  }
  
  car_ctrl_stop(); 
}
#endif 
