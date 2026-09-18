#include "bsp.h"

uint8_t key_num;
uint8_t firstPage_KeyFlag;

int main(void)
{
    /*初始化*/
    bsp_Init();
    menu_ShowClock();   
    OLED_Update();

	while (1)
	{
        /*首页*/
        firstPage_KeyFlag = menu_FirstPage_Choose();

        /*第一页：菜单 | 设置*/
        if(firstPage_KeyFlag == 1){}
        else if(firstPage_KeyFlag == 2){
            menu_SecondPage_Setting_Choose();
        }
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
