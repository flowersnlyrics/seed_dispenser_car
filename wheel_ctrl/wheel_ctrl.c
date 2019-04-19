/*******************************************************************************
* @file           : wheel_ctrl.c
* @brief          : Controls PWM & rotating motors clockwise/counterclockwise
*******************************************************************************/

/* ----------------------------------------------------------------- Includes */
#include "wheel_ctrl.h"
#include "tim.h"

/* ------------------------------------------------------ Private Definitions */
#define MOTOR_CTRL_RIGHT_PWM_Channel    TIM_CHANNEL_4
#define MOTOR_CTRL_LEFT_PWM_Channel     TIM_CHANNEL_1
#define MOTOR_CTRL_PWM_Timer            htim2

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

motor_grp_desc_t MOTOR_GRP_DESC[NUM_WHEEL_SIDES] = 
{
  // LEFT MOTORS //
  {
    MOTOR_CTRL_LEFT_PWM_Channel, 
    0, 
    {
      WHEEL_MOTOR_IN4_GPIO_Port,
      WHEEL_MOTOR_IN4_Pin 
    }, 
    {
      WHEEL_MOTOR_IN3_GPIO_Port,
      WHEEL_MOTOR_IN3_Pin 
    }, 
  }, 
  // RIGHT MOTORS //
  {
    MOTOR_CTRL_RIGHT_PWM_Channel, 
    0,
    {
      WHEEL_MOTOR_IN2_GPIO_Port,
      WHEEL_MOTOR_IN2_Pin 
    }, 
    {
      WHEEL_MOTOR_IN1_GPIO_Port,
      WHEEL_MOTOR_IN1_Pin 
    }, 
  }
}; 

static uint32_t g_period = 0;

/* ---------------------------------------------- Private Function Prototypes */

/* ---------------------------------------------- Public Function Definitions */

/*******************************************************************************
 * @fn      wheel_ctrl_init
 * @brief   
 ******************************************************************************/
void wheel_ctrl_init(void)

{
  // TODO put timer init here after stmcube shit is over 
  MX_TIM2_Init(); 
  g_period = htim2.Init.Period;
}

/*******************************************************************************
 * @fn      wheel_ctrl_start
 * @brief   
 ******************************************************************************/
void wheel_ctrl_start(wheel_side_t motor_grp)
{
  HAL_TIM_PWM_Start_IT(&MOTOR_CTRL_PWM_Timer, 
                       MOTOR_GRP_DESC[motor_grp].tim_channel); 
}

/*******************************************************************************
 * @fn      wheel_ctrl_stop
 * @brief   
 ******************************************************************************/
void wheel_ctrl_stop(wheel_side_t motor_grp)
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

/*******************************************************************************
 * @fn      wheel_ctrl_rotation
 * @brief   
 ******************************************************************************/
void wheel_ctrl_rotation(wheel_side_t motor_grp, wheel_rotation_t rotation)
{
  GPIO_PinState in1_state; 
  GPIO_PinState in0_state; 
  
  if(rotation == CLOCKWISE)
  {
    in1_state = GPIO_PIN_SET; 
    in0_state = GPIO_PIN_RESET; 
  }
  else if(rotation == COUNTER_CLOCKWISE)
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

/*******************************************************************************
 * @fn      wheel_ctrl_speed
 * @brief   
 ******************************************************************************/
void wheel_ctrl_speed(wheel_side_t motor_grp, uint8_t duty_cycle)
{
  __HAL_TIM_SET_COMPARE(&MOTOR_CTRL_PWM_Timer, 
                        MOTOR_GRP_DESC[motor_grp].tim_channel, 
                        (uint32_t)((duty_cycle/100.0) * g_period)); 
}
