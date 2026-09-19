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

uint8_t pre_selection;      //上次选择
uint8_t target_selection;   //目标选择
uint8_t x_pre = 48;         //上次选择的X坐标
uint8_t speed = 4;          //切换速度
uint8_t move_flag;          //切换标志位：1表示移动，0表示静止

/*********************
    作用：菜单切换动画显示
    参数：无
    返回：无
***********************/
void Menu_Animation(void)
{
    OLED_Clear();
    OLED_ShowImage(42,10,44,44,Frame);//显示选中框

    if(pre_selection < target_selection)//往左选择，图标往右移
    {
        x_pre -= speed;
        if(x_pre == 0)
        {
            pre_selection++;//图标右移后，先前选择变到中间了
            move_flag = 0;  //移动完后，标志位置0，停止移动
            x_pre = 48;//移动完后，
        }
    }

    if(pre_selection > target_selection)//往右选择，图标往左移
    {
        x_pre += speed;
        if(x_pre == 96)
        {
            pre_selection--;//图标右移后，先前选择变到中间了
            move_flag = 0;  //移动完后，标志位置0，停止移动
            x_pre = 48;//移动完后，
        }
    }

    if(pre_selection >= 2)//前面2个图标（只有当你选择的是第3个图标时，前面才有2个图标）
    {
        OLED_ShowImage(x_pre-96,16,32,32,Menu_Graph[pre_selection-2]);   
    }
    if(pre_selection >= 1)//前面1个图标（只有当你选择的是第2个图标时，前面才有1个图标）
    {
        OLED_ShowImage(x_pre-48,16,32,32,Menu_Graph[pre_selection-1]);
    }

    OLED_ShowImage(x_pre,16,32,32,Menu_Graph[pre_selection]);
    OLED_ShowImage(x_pre+48,16,32,32,Menu_Graph[pre_selection + 1]);
    OLED_ShowImage(x_pre+96,16,32,32,Menu_Graph[pre_selection + 2]);//???那我觉得最后应该也会有，倒数

    OLED_Update();
}

/*********************
    作用：菜单选择
    参数：移动标志位（1为移动，0为不移动）; 先前选择位置; 目标位置
    返回：无
***********************/
void Set_Selection(uint8_t move_flag, uint8_t Pre_selection, uint8_t Target_selection)
{
    if(move_flag == 1)
    {
        pre_selection = Pre_selection;         //改变选中值
        target_selection = Target_selection;    //改变目标值
        Menu_Animation();                       //切换动画
    }
}
/*********************
    作用：菜单选择
    参数：无
    返回：选择标志位
***********************/
int8_t  menu_SecondPage_KeyFlag2 = 1;
uint8_t menu_SecondPage_Menu_Choose(void)
{
    uint8_t KeyFlag;
    uint8_t DirectFlag;//1：上一项；2：下一项
    uint8_t RepeatFlag;//1： 可以滑动；2：防止滑动；防止出现到顶重复滑动的标志位，主要用于优化
    while (1)
    {
        KeyFlag = 0;
        menu_KeyNum = Key_GetNum();

        /*按钮逻辑*//*按钮范围: 1~2*/
        if(menu_KeyNum == 1)//后退
        {   
            if(menu_SecondPage_KeyFlag2 > 1)               // ★ 只有真的能退，才开门
            {
                DirectFlag = 1;
                move_flag  = 1;
                menu_SecondPage_KeyFlag2--;
                LED1_Turn();
            }
        }   
        else if(menu_KeyNum == 2)//前进
        {
            if(menu_SecondPage_KeyFlag2 < 7)               // ★ 同样，到底了就别开门
            {
                DirectFlag = 2;
                move_flag  = 1;
                menu_SecondPage_KeyFlag2++;
                LED2_Turn();
            }
        }   
        else if(menu_KeyNum == 3)//确定
        {
            OLED_Clear();
            OLED_Update();
            KeyFlag = menu_SecondPage_KeyFlag2;
        }  

        if(KeyFlag == 1){return 0;}
        else if(KeyFlag == 2){}
        else if(KeyFlag == 3){}
        else if(KeyFlag == 4){}
        else if(KeyFlag == 5){}
        else if(KeyFlag == 6){}
        else if(KeyFlag == 7){}

        if(DirectFlag == 0)//用于进来时最开始的显示
        {
            OLED_ShowImage(42,10,44,44,Frame);//显示选中框
            OLED_ShowImage(x_pre,16,32,32,Menu_Graph[pre_selection]);
            OLED_ShowImage(x_pre+48,16,32,32,Menu_Graph[pre_selection + 1]);
            OLED_ShowImage(x_pre+96,16,32,32,Menu_Graph[pre_selection + 2]);
            OLED_Update();    
        }

        switch (menu_SecondPage_KeyFlag2)
        {
        case 1:
            if(DirectFlag == 1){
               Set_Selection(move_flag, 1, 0);
            }
            else if(DirectFlag == 2){Set_Selection(move_flag, 0, 0); RepeatFlag = 0;}//没有意义，从0移动到0
            break;
        case 2:
            if(DirectFlag == 1){Set_Selection(move_flag, 2, 1);}
            else if (DirectFlag == 2){Set_Selection(move_flag, 0, 1);}
            break;    
        case 3:
            if(DirectFlag == 1){Set_Selection(move_flag, 3, 2);}
            else if (DirectFlag == 2){Set_Selection(move_flag, 1, 2);}
            break;   
        case 4:
            if(DirectFlag == 1){Set_Selection(move_flag, 4, 3);}
            else if (DirectFlag == 2){Set_Selection(move_flag, 2, 3);}
            break;  
        case 5:
            if(DirectFlag == 1){Set_Selection(move_flag, 5, 4);}
            else if (DirectFlag == 2){Set_Selection(move_flag, 3, 4);}
            break;   
        case 6:
            if(DirectFlag == 1){Set_Selection(move_flag, 6, 5);}
            else if (DirectFlag == 2){Set_Selection(move_flag, 4, 5);}
            break;   
        case 7:
            if(DirectFlag == 1){Set_Selection(move_flag, 7, 6);}
            else if (DirectFlag == 2){
                Set_Selection(move_flag, 5, 6);
            }
            break;     
        
        }
    } 
}
