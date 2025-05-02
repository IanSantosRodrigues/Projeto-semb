#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C" {
#endif


#include "display.h"
#include "motor.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>

void App_Init(void);
void App_Run(void);

#ifdef __cplusplus
}
#endif

#endif
