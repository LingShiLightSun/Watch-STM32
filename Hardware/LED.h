#ifndef __LED_H
#define __LED_H

#include "bsp.h"


#define LED1_RCC_APB2PERIPH_GPIOx    RCC_APB2Periph_GPIOA
#define LED2_RCC_APB2PERIPH_GPIOx    RCC_APB2Periph_GPIOA
#define LED1_GPIOx                   GPIOA
#define LED2_GPIOx                   GPIOA
#define LED1_GPIO_Pin_x              GPIO_Pin_0
#define LED2_GPIO_Pin_x              GPIO_Pin_2




void LED_Init(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED1_Turn(void);
void LED2_ON(void);
void LED2_OFF(void);
void LED2_Turn(void);
void LED2_ON(void);
void LED2_OFF(void);
void LED2_Turn(void);

#endif
