#ifndef __MENU_H
#define __MENU_H

#include "bsp.h"

extern uint8_t menu_KeyNum;

void menu_ShowClock(void);
uint8_t menu_FirstPage_Choose(void);
void menu_ShowSetting(void);
uint8_t menu_SecondPage_Setting_Choose(void);

#endif
