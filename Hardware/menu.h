#ifndef __MENU_H
#define __MENU_H

#include "bsp.h"

extern uint8_t menu_KeyNum;

#define MENU_CHOOSE_NUM 7

void menu_ShowClock(void);
uint8_t menu_FirstPage_Choose(void);
void menu_ShowSetting(void);
uint8_t menu_SecondPage_Setting_Choose(void);
void Menu_Animation(void);
void Set_Selection(uint8_t move_flag, uint8_t Pre_selection, uint8_t Target_selection);
uint8_t menu_SecondPage_Menu_Choose(void);

#endif
