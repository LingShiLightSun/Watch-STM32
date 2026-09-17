#include "bsp.h"

void bsp_Init(void)
{
    OLED_Init();
    MyRTC_Init();
    Key_Init();
    LED_Init();
    Timer_Init();
}
