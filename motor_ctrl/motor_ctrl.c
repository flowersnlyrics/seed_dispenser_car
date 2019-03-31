/*******************************************************************************
* @file           : main.c
* @brief          : Main program body
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include "motor_ctrl.h"

/* ------------------------------------------------------ Private Definitions */
#define MOTOR_CTRL_RIGHT_PWM_Channel TIM_CHANNEL_4
#define MOTOR_CTRL_LEFT_PWM_Channel TIM_CHANNEL_1
#define MOTOR_CTRL_PWM_Timer   htim2

typedef struct
{ 
  GPIO_TypeDef*     port; 
  uint16_t           pin; 
} dir_pin_t; 

typedef struct
{
  uint32_t          tim_channel; 
  uint8_t           speed;
  dir_pin_t         in1; 
  dir_pin_t         in0; 
} motor_grp_desc_t; 

motor_grp_desc_t MOTOR_GRP_DESC[NUM_MOTOR_GROUPS] = 
{
  // LEFT MOTORS //
  {
    MOTOR_CTRL_LEFT_PWM_Channel, 
    0, 
    {
      MOTOR_IN2_dir1PinL_GPIO_Port,
      MOTOR_IN2_dir1PinL_Pin 
    }, 
    {
      MOTOR_IN1_dir2PinL_GPIO_Port,
      MOTOR_IN1_dir2PinL_Pin 
    }, 
  }, 
  // RIGHT MOTORS //
  {
    MOTOR_CTRL_RIGHT_PWM_Channel, 
    0,
    {
      MOTOR_IN4_dir1PinR_GPIO_Port,
      MOTOR_IN4_dir1PinR_Pin 
    }, 
    {
      MOTOR_IN3_dir2PinR_GPIO_Port,
      MOTOR_IN3_dir2PinR_Pin 
    }, 
  }
}; 

/* ---------------------------------------------- Private Function Prototypes */

/* ---------------------------------------------- Public Function Definitions */
void motor_init(void)
{
  // TODO put timer init here after stmcube shit is over 
}

void motor_ctrl_start(motor_grp_t motor_grp)
{
  HAL_TIM_PWM_Start_IT(&MOTOR_CTRL_PWM_Timer, 
                       MOTOR_GRP_DESC[motor_grp].tim_channel); 
}

void motor_ctrl_stop(motor_grp_t motor_grp)
{
  HAL_GPIO_WritePin(MOTOR_GRP_DESC[motor_grp].in1.port, 
                    MOTOR_GRP_DESC[motor_grp].in1.pin,
                    GPIO_PIN_RESET);
    
  HAL_GPIO_WritePin(MOTOR_GRP_DESC[motor_grp].in0.port, 
                    MOTOR_GRP_DESC[motor_grp].in0.pin,
                    GPIO_PIN_RESET); 
  
  HAL_TIM_PWM_Stop_IT(&MOTOR_CTRL_PWM_Timer, 
                      MOTOR_GRP_DESC[motor_grp].tim_channel);
}

void motor_ctrl_direction(motor_grp_t motor_grp, motor_dir_t dir)
{
  GPIO_PinState in1_state; 
  GPIO_PinState in0_state; 
  
  if(dir == CLOCKWISE)
  {
    in1_state = GPIO_PIN_SET; 
    in0_state = GPIO_PIN_RESET; 
  }
  else if(dir == COUNTER_CLOCKWISE)
  {
    in1_state = GPIO_PIN_RESET; 
    in0_state = GPIO_PIN_SET; 
  }
  else // BRAKE
  {
    in1_state = GPIO_PIN_RESET; 
    in0_state = GPIO_PIN_RESET; 
  }
  
  HAL_GPIO_WritePin(MOTOR_GRP_DESC[motor_grp].in1.port, 
                    MOTOR_GRP_DESC[motor_grp].in1.pin,
                    in1_state);
    
  HAL_GPIO_WritePin(MOTOR_GRP_DESC[motor_grp].in0.port, 
                    MOTOR_GRP_DESC[motor_grp].in0.pin,
                    in0_state); 
}

void motor_ctrl_speed(motor_grp_t motor, uint8_t speed)
{
  //float new_duty_cycle; 
  
  
}
