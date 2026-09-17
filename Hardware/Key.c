#include "Key.h"

/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(KEY1_RCC_APB2PERIPH_GPIOx, ENABLE);		
	RCC_APB2PeriphClockCmd(KEY2_RCC_APB2PERIPH_GPIOx, ENABLE);		
	RCC_APB2PeriphClockCmd(KEY3_RCC_APB2PERIPH_GPIOx, ENABLE);		
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY1_GPIOx, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_Pin_x;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY2_GPIOx, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_Pin_x ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(KEY3_GPIOx, &GPIO_InitStructure);

}

/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */

uint8_t KeyNum;
uint8_t Key_GetNum(void)
{
    static uint8_t Key_Temp;
    Key_Temp = KeyNum;
    KeyNum = 0;

	return Key_Temp;
}

uint8_t Key_GetState(void)
{
    if (GPIO_ReadInputDataBit(KEY1_GPIOx, KEY1_GPIO_Pin_x) == 0)			//读PB1输入寄存器的状态，如果为0，则代表按键1按下
	{
		return 1;												//置键码为1
	}
	
	if (GPIO_ReadInputDataBit(KEY2_GPIOx, KEY2_GPIO_Pin_x) == 0)			//读PB11输入寄存器的状态，如果为0，则代表按键2按下
	{
		return 2;												//置键码为2
	}
	
    if (GPIO_ReadInputDataBit(KEY3_GPIOx, KEY3_GPIO_Pin_x) == 0)			//读PB11输入寄存器的状态，如果为0，则代表按键2按下
	{
		return 3;												//置键码为3
	}
    else
    {
        return 0;
    }
}


void Key_Tick(void)
{
    static uint8_t Key_Count;
    static uint8_t Key_PreState;
    static uint8_t Key_CurState;

    Key_Count++;

    if(Key_Count >= 20)
    {
        Key_Count = 0;

        Key_PreState = Key_CurState;    //先前 = 现在
        Key_CurState = Key_GetState();  //现在 = 获取
        
        if(Key_PreState != 0 && Key_CurState == 0)
        {
            KeyNum = Key_PreState;
        }
    }
}
