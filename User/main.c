#include "bsp.h"

uint8_t key_num;
uint8_t firstPage_KeyFlag;

int main(void)
{
    /*初始化*/
    bsp_Init();
    menu_ShowClock();   
    OLED_Update();
    LED1_ON();
    LED2_ON();

	while (1)
	{
        /*首页*/
        firstPage_KeyFlag = menu_FirstPage();

        /*第一页*/
        if(firstPage_KeyFlag == 1){}
        else if(firstPage_KeyFlag == 2){}

	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Key_Tick();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
