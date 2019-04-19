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
  PARK, 
  NUM_CAR_DIRS 
} car_move_t; 

typedef struct 
{
  uint8_t left_duty_cycle; 
  uint8_t right_duty_cycle; 
} car_speed_t; 

/* ----------------------------------------------- Public Function Prototypes */
void car_ctrl_init(void); 
void car_ctrl_move(car_move_t move); 
void car_ctrl_start(void); 
void car_ctrl_stop(void); 
void car_ctrl_adjust_speed(car_speed_t* speed); 

#define DEBUG_CAR
#ifdef DEBUG_CAR
void car_test(void); 
#endif 

#endif /* __CAR_CTRL_H__ */