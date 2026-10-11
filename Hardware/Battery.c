#include "Battery.h"

void Battery_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
    
    //开机：PB12 - 低电平、PB13 - 高电平；关机：PB12 - 高电平，PB13 - 低电平
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    GPIO_SetBits(GPIOB, GPIO_Pin_13);
}
