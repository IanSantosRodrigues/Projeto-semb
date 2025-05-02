#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include "main.h"

void Motor_Init(void);
void Motor_OpenLid(void);
void Motor_CloseLid(void);
void Motor_Stop(void);

#endif
