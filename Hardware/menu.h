#ifndef __MENU_H
#define __MENU_H

#include "bsp.h"

extern uint8_t menu_KeyNum;

#define MENU_CHOOSE_NUM 7
#define PI              3.1415926

void menu_ShowClock(void);
uint8_t menu_FirstPage_Choose(void);
void menu_ShowSetting(void);
uint8_t menu_SecondPage_Setting_Choose(void);
void Menu_Animation(void);
void Set_Selection(uint8_t move_flag, uint8_t Pre_selection, uint8_t Target_selection);
uint8_t menu_SecondPage_Menu_Choose(void);
void Stopwatch_Tick(void);
void menu_ShowStopwatch(void);
uint8_t menu_ThirdPage_Stopwatch(void);
void menu_ShowFlashlight(void);
uint8_t menu_ThirdPage_Flashlight(void);
void MPU6050_Calculation(void);
void Show_MPU6050_UI(void);
uint8_t menu_ThirdPage_MPU6050(void);
uint8_t menu_ThirdPage_Game(void);
void Show_Emoji_UI(void);
uint8_t menu_ThirdPage_Emoji(void);
void Show_Level_UI(void);
uint8_t menu_Level_Emoji(void);
#endif
