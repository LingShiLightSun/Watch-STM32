#ifndef __BSP_H
#define __BSP_H

#include "stm32f10x.h"                  // Device header

#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

#include "LED.h"
#include "Key.h"
#include "MyRTC.h"
#include "menu.h"
#include "menu_SetTime.h"
#include "MPU6050.h"
#include "math.h"
#include "dino.h"
#include "stdlib.h"

void bsp_Init(void);

#endif
