#ifndef __MENU_H
#define __MENU_H

#include "bsp.h"

extern uint8_t menu_KeyNum;

#define YEAR    0
#define MONTH   1
#define DAY     2
#define HOUR    3
#define MINUTE  4
#define RECORD  5

#define SUB     0
#define ADD     1


void menu_ShowSetTime_FirstUI(void);
void menu_ShowSetTime_SecondUI(void);
uint8_t menu_ThirdPage_Choose(void);
void setTime_Change_RTCTime(uint8_t sub, uint8_t flag);
void setTime_setYear(void);
void setTime_setMonth(void);
void setTime_setDay(void);
void setTime_setHour(void);
void setTime_setMinute(void);
void setTime_setRecord(void);

#endif
