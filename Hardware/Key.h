#ifndef __KEY_H
#define __KEY_H

#include "bsp.h"

#define KEY1_RCC_APB2PERIPH_GPIOx   RCC_APB2Periph_GPIOB
#define KEY2_RCC_APB2PERIPH_GPIOx   RCC_APB2Periph_GPIOA
#define KEY3_RCC_APB2PERIPH_GPIOx   RCC_APB2Periph_GPIOA
#define KEY1_GPIOx                  GPIOB
#define KEY2_GPIOx                  GPIOA
#define KEY3_GPIOx                  GPIOA
#define KEY1_GPIO_Pin_x             GPIO_Pin_0
#define KEY2_GPIO_Pin_x             GPIO_Pin_6
#define KEY3_GPIO_Pin_x             GPIO_Pin_4

void Key_Init(void);
uint8_t Key_GetNum(void);
uint8_t Key_GetState(void);
void Key_Tick(void);

#endif
