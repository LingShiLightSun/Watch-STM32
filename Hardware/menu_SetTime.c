#include "menu_SetTime.h"

/*********************
    作用：时间设置界面（首页->设置->日期时间设置）
    参数：无
    返回：无
***********************/
void menu_ShowSetTime_FirstUI(void)
{
    OLED_ShowImage(0,0,16,16,Return);
    OLED_Printf(0,16,OLED_8X16, "年:%d",MyRTC_Time[0]);
    OLED_Printf(0,32,OLED_8X16, "月:%d",MyRTC_Time[1]);
    OLED_Printf(0,48,OLED_8X16, "日:%d",MyRTC_Time[2]);
}

/*********************
    作用：时间设置界面（首页->设置->日期时间设置）
    参数：无
    返回：无
***********************/
void menu_ShowSetTime_SecondUI(void)
{
    OLED_Printf(0,0,OLED_8X16, "时:%d",MyRTC_Time[3]);
    OLED_Printf(0,16,OLED_8X16, "分:%d",MyRTC_Time[4]);
    OLED_Printf(0,32,OLED_8X16, "秒:%d",MyRTC_Time[5]);
}

/*********************
    作用：改变RTC时间（set系列函数都需要调用此函数）
    参数：
        1.RTC数组下标（年月日时分秒）
        2.加减标志位（0为减，1为加）
    返回：无
***********************/
void setTime_Change_RTCTime(uint8_t sub, uint8_t flag)
{
    if(flag == 0){MyRTC_Time[sub]--;}
    else if (flag == 1){MyRTC_Time[sub]++;}
    MyRTC_SetTime();
}

void setTime_setYear(void)
{
    while (1)
    {
        menu_KeyNum = Key_GetNum();
        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1){setTime_Change_RTCTime(YEAR, SUB);}//减时间
        else if(menu_KeyNum == 2){setTime_Change_RTCTime(YEAR, ADD);}//加时间
        else if(menu_KeyNum == 3){return ;}//退出  

        menu_ShowSetTime_FirstUI();
        OLED_ReverseArea(24,16,32,16);
        OLED_Update();
    }
    
}

void setTime_setMonth(void)
{
    while (1)
    {
        menu_KeyNum = Key_GetNum();
        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1){setTime_Change_RTCTime(MONTH, SUB);}//减时间
        else if(menu_KeyNum == 2){setTime_Change_RTCTime(MONTH, ADD);}//加时间
        else if(menu_KeyNum == 3){return ;}//退出  

        menu_ShowSetTime_FirstUI();
        OLED_ReverseArea(24,32,16,16);
        OLED_Update();

    }
    
}
void setTime_setDay(void)
{
    while (1)
    {
        menu_KeyNum = Key_GetNum();
        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1){setTime_Change_RTCTime(DAY, SUB);}//减时间
        else if(menu_KeyNum == 2){setTime_Change_RTCTime(DAY, ADD);}//加时间
        else if(menu_KeyNum == 3){return ;}//退出  

        menu_ShowSetTime_FirstUI();
        OLED_ReverseArea(24,48,16,16);
        OLED_Update();
    }
    
}
void setTime_setHour(void)
{
    while (1)
    {
        menu_KeyNum = Key_GetNum();
        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1){setTime_Change_RTCTime(HOUR, SUB);}//减时间
        else if(menu_KeyNum == 2){setTime_Change_RTCTime(HOUR, ADD);}//加时间
        else if(menu_KeyNum == 3){return ;}//退出  

        menu_ShowSetTime_SecondUI();
        OLED_ReverseArea(24,0,16,16);
        OLED_Update();
    }
    
  
}
void setTime_setMinute(void)
{
    while (1)
    {
        menu_KeyNum = Key_GetNum();
        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1){setTime_Change_RTCTime(MINUTE, SUB);}//减时间
        else if(menu_KeyNum == 2){setTime_Change_RTCTime(MINUTE, ADD);}//加时间
        else if(menu_KeyNum == 3){return ;}//退出  

        menu_ShowSetTime_SecondUI();
        OLED_ReverseArea(24,16,16,16);
        OLED_Update();
    }
    

}
void setTime_setRecord(void)
{
    while (1)
    {
        menu_KeyNum = Key_GetNum();
        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1){setTime_Change_RTCTime(RECORD, SUB);}//减时间
        else if(menu_KeyNum == 2){setTime_Change_RTCTime(RECORD, ADD);}//加时间
        else if(menu_KeyNum == 3){return ;}//退出  

        menu_ShowSetTime_SecondUI();
        OLED_ReverseArea(24,32,16,16);
        OLED_Update();
    }
}

/*********************
    作用：UI时间设置选择(首页->设置)
    参数：无
    返回：按键选择标志
***********************/
int8_t menu_SecondPage_ShowSetting;
uint8_t menu_ThirdPage_Choose(void)
{
    uint8_t KeyFlag;
    while (1)
    {
        KeyFlag = 0;
        menu_KeyNum = Key_GetNum();

        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1)//后退
        {
            menu_SecondPage_ShowSetting--;
            if(menu_SecondPage_ShowSetting <= 0){menu_SecondPage_ShowSetting = 1;}
        }   
        else if(menu_KeyNum == 2)//前进
        {
            menu_SecondPage_ShowSetting++;
            if(menu_SecondPage_ShowSetting >= 8){menu_SecondPage_ShowSetting = 7;}
        }   
        else if(menu_KeyNum == 3)//确定
        {

            OLED_Clear();
            OLED_Update();
            KeyFlag = menu_SecondPage_ShowSetting;
        }  

        if(KeyFlag == 1){return 0;}//选择“返回”
        else if(KeyFlag == 2){setTime_setYear();    }//选择“年”
        else if(KeyFlag == 3){setTime_setMonth();   }//选择“月”
        else if(KeyFlag == 4){setTime_setDay();     }//选择“日”
        else if(KeyFlag == 5){setTime_setHour();    }//选择“时”
        else if(KeyFlag == 6){setTime_setMinute();  }//选择“分”
        else if(KeyFlag == 7){setTime_setRecord();  }//选择“秒”


        switch (menu_SecondPage_ShowSetting)
        {
        case 0://未选中状态
            OLED_Clear();
            menu_ShowSetTime_FirstUI();
            OLED_Update();
            break;
        case 1://选中“返回”
            OLED_Clear();
            menu_ShowSetTime_FirstUI();
            OLED_ReverseArea(0,0,16,16);
           OLED_Update();
            break;
        case 2://选中“年”
            OLED_Clear();
            menu_ShowSetTime_FirstUI();
            OLED_ReverseArea(0,16,16,16);
            OLED_Update();
            break;    
        case 3://选中“月”
            OLED_Clear();
            menu_ShowSetTime_FirstUI();
            OLED_ReverseArea(0,32,16,16);
            OLED_Update();
            break;   
        case 4://选中“日”
            OLED_Clear();
            menu_ShowSetTime_FirstUI();
            OLED_ReverseArea(0,48,16,16);
            OLED_Update();
            break;   
        case 5://选中“时”
            OLED_Clear();
            menu_ShowSetTime_SecondUI();
            OLED_ReverseArea(0,0,16,16);
            OLED_Update();
            break;   
        case 6://选中“分”
            OLED_Clear();
            menu_ShowSetTime_SecondUI();
            OLED_ReverseArea(0,16,16,16);
            OLED_Update();

            break;   
        case 7://选中“秒”
            OLED_Clear();
            menu_ShowSetTime_SecondUI();
            OLED_ReverseArea(0,32,16,16);
            OLED_Update();
            break;   
        }
    } 
}









