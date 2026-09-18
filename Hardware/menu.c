#include "menu.h"

/*********************
    作用：UI首页显示
    参数：无
    返回：无
***********************/\
uint8_t menu_KeyNum;

void menu_ShowClock(void)
{
    MyRTC_ReadTime();
    
    OLED_Printf(0,0, OLED_6X8, "%4d-%02d-%02d", MyRTC_Time[0], MyRTC_Time[1], MyRTC_Time[2]);
    OLED_Printf(32,24, OLED_8X16, "%2d:%02d:%02d", MyRTC_Time[3], MyRTC_Time[4], MyRTC_Time[5]);
    OLED_ShowString(0,48,"菜单",OLED_8X16);
    OLED_ShowString(96,48,"设置",OLED_8X16);
}


int8_t menu_FirstPage_KeyFlag;
/*********************
    作用：UI首页选择
    参数：无
    返回：按键选择标志
***********************/
uint8_t menu_FirstPage_Choose(void)
{
    
    while (1)
    {
        menu_KeyNum = Key_GetNum();

        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1)//后退
        {
            menu_FirstPage_KeyFlag--;
            if(menu_FirstPage_KeyFlag <= 0){menu_FirstPage_KeyFlag = 1;}
        }   
        else if(menu_KeyNum == 2)//前进
        {
            menu_FirstPage_KeyFlag++;
            if(menu_FirstPage_KeyFlag >= 3){menu_FirstPage_KeyFlag = 2;}
        }   
        else if(menu_KeyNum == 3)//确定
        {

            OLED_Clear();
            OLED_Update();
            return menu_FirstPage_KeyFlag;
        }  

        switch (menu_FirstPage_KeyFlag)
        {
        case 0://未选中状态
            menu_ShowClock();
            OLED_Update();
            break;
        case 1://选中“菜单”
            menu_ShowClock();
            OLED_ReverseArea(0,48,32,16);
            OLED_Update();
            break;
        case 2://选中“设置”
            menu_ShowClock();
            OLED_ReverseArea(96,48,32,16);
            OLED_Update();
            break;    
        }
    } 
}

/*********************
    作用：时间设置界面（首页->设置）
    参数：无
    返回：无
***********************/
void menu_ShowSetting(void)
{
    OLED_ShowImage(0,0,16,16,Return);
    OLED_ShowString(0,16,"日期时间设置",OLED_8X16);
}

/*********************
    作用：时间设置选择
    参数：无
    返回：选择标志位
***********************/
int8_t  menu_SecondPage_KeyFlag;

uint8_t menu_SecondPage_Setting_Choose(void)
{
    uint8_t KeyFlag;
    while (1)
    {
        KeyFlag = 0;
        menu_KeyNum = Key_GetNum();


        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1)//后退
        {
            menu_SecondPage_KeyFlag--;
            if(menu_SecondPage_KeyFlag <= 0){menu_SecondPage_KeyFlag = 1;}
        }   
        else if(menu_KeyNum == 2)//前进
        {
            menu_SecondPage_KeyFlag++;
            if(menu_SecondPage_KeyFlag >= 3){menu_SecondPage_KeyFlag = 2;}
        }   
        else if(menu_KeyNum == 3)//确定
        {
            OLED_Clear();
            OLED_Update();
            KeyFlag = menu_SecondPage_KeyFlag;
        }  

        if(KeyFlag == 1){return 0;}
        else if(KeyFlag == 2){menu_ThirdPage_Choose();}

        switch (menu_SecondPage_KeyFlag)
        {
        case 0://未选中状态
            OLED_Clear();
            menu_ShowSetting();
            OLED_Update();
            break;
        case 1://选中“返回”
            OLED_Clear();
            menu_ShowSetting();
            OLED_ReverseArea(0,0,16,16);
            OLED_Update();
            break;
        case 2://选中“日期时间设置”
            OLED_Clear();
            menu_ShowSetting();
            OLED_ReverseArea(0,16,96,16);
            OLED_Update();
            break;    
        }
    } 
}
