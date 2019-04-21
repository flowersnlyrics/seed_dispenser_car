#ifndef __CAR_MGR_H__
#define __CAR_MGR_H__

/* ----------------------------------------------------------------- Includes */
#include <stdbool.h>
#include <stdint.h>
#include "car_ctrl.h"

/* ------------------------------------------------------- Public Definitions */
// @note events need to be nonzero :) 
typedef enum
{
  START_CAR_EVT = 0x00000001, 
  STOP_CAR_EVT  = 0x00000002, 
} car_mgr_event_t;

/* ----------------------------------------------- Public Function Prototypes */
bool car_mgr_init(void); 

bool car_mgr_send_evt_from_isr(car_mgr_event_t evt); 
bool car_mgr_send_evt(car_mgr_event_t evt); 

#endif /* __CAR_MGR_H__ */