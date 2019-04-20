#ifndef __BLADE_CTRL_H__
#define __BLADE_CTRL_H__

/* ----------------------------------------------- Public Function Prototypes */
#include "main.h"


/* ----------------------------------------------- Public Function Prototypes */
void loop(void); // TODO delete after debugging 
void blade_ctrl_init(void); 
void blade_ctrl_move(uint8_t steps);

void blade_ctrl_inc(void); 

#endif /* __BLADE_CTRL_H__ */