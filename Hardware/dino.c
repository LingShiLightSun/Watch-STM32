#include "dino.h"

uint32_t Score;

/*********************
    作用：恐龙游戏界面分数显示（首页->菜单->恐龙游戏）
    参数：无
    返回：无
***********************/
void dino_ShowScore(void)
{
    OLED_Printf(98,0,OLED_6X8,"%05d", Score);
}

uint32_t Ground_Pos;//地面显存数组偏移量
/*********************
    作用：恐龙游戏界面地面显示（首页->菜单->恐龙游戏）
    参数：无
    返回：无
***********************/
void dino_ShowGround(void)
{   
    if(Ground_Pos < 128)//偏移量小于一半,正常那地面数组右边数据即可
    {
        for (uint8_t i = 0; i < 128; i++)
        {
            OLED_DisplayBuf[7][i] = Ground[i + Ground_Pos];
        }
    }
    else//偏移量大于一半,先拿右边剩下数据,再拿左边的数据
    {
        for (uint8_t i = 0; i < 255 - Ground_Pos; i++)
        {
            OLED_DisplayBuf[7][i] = Ground[i + Ground_Pos];
        }
        for (uint8_t i = 255 - Ground_Pos; i < 128; i++)
        {
            OLED_DisplayBuf[7][i] = Ground[i - (255 - Ground_Pos)];
        }
    }
}

/*********************
    作用：恐龙游戏界面障碍物显示（首页->菜单->恐龙游戏）
    参数：无
    返回：无
***********************/
uint8_t barrier_flag;
uint8_t Barrier_pos;
Object_Position barrier_position;
void dino_ShowBarrier(void)
{       
    if(Barrier_pos >= 143 )
    {
        barrier_flag = rand()%3;
    }
    OLED_ShowImage(127-Barrier_pos,44,16,18,Barriers[barrier_flag]);

    //获取障碍物位置
    barrier_position.minX = 127-Barrier_pos;
    barrier_position.maxX = 143-Barrier_pos;
    barrier_position.minY = 44;
    barrier_position.maxY = 62;
}

/*********************
    作用：恐龙游戏界面云朵显示（首页->菜单->恐龙游戏）
    参数：无
    返回：无
***********************/
uint8_t Cloud_pos;
void dino_ShowCloud(void)
{       
    OLED_ShowImage(127-Cloud_pos,10,16,8,Cloud);
}

/*********************
    作用：恐龙游戏界面小恐龙显示（首页->菜单->恐龙游戏）
    参数：无
    返回：无
***********************/
uint8_t Dino_jump_flag = 0; //恐龙跳跃标志位: 0->奔跑;1->跳跃
uint8_t Dino_jump_pos;      //恐龙跳跃高度标志位
uint16_t Dino_jump_t;       //时间周期(三角函数参数)
Object_Position dino_position;
void dino_ShowDino(void)
{       
    Dino_jump_pos = 32 * sin((float)(PI * Dino_jump_t / 1000));

    if(Dino_jump_flag == 0)
    {
        if(Score % 2 == 0)//这里用Score的原因是因为Score每隔100ms++,代表着小恐龙换脚的频率为0.1Hz
        {
            OLED_ShowImage(4,44,16,18,Dino[0]);
        }
        else
        {
            OLED_ShowImage(4,44,16,18,Dino[1]);
        }
    }
    else if(Dino_jump_flag == 1)
    {
        OLED_ShowImage(4, 44-Dino_jump_pos, 16,18,Dino[2]);
    }
    
    dino_position.minX = 4;
    dino_position.maxX = 20;
    dino_position.minY = 44-Dino_jump_pos;
    dino_position.maxY = 62-Dino_jump_pos;
}

/*********************
    作用：恐龙游戏界面检测障碍物发生碰撞（放在计时器里；100ms增加1）
    参数：无
    返回：返回标志位，用于判断小恐龙有没有死亡
***********************/
uint8_t isColliding(Object_Position* a, Object_Position* b)
{
    if((a->maxX >= b->minX) && (a->minX <= b->maxX) && (a->minY <= b->maxY) && (a->maxY >= b->minY))
    {
        OLED_Clear();
        OLED_ShowString(28,24, "GAME OVER", OLED_8X16);
        OLED_Update();

        Delay_ms(1500);//游戏失败后，应该是全部重来
        OLED_Clear();
        OLED_Update();

        return 1;
    }
    return 0;
}


/*********************
    作用：恐龙游戏界面分数增加（放在计时器里；100ms增加1）
    参数：无
    返回：无
***********************/
void dino_Tick()
{
    static uint16_t score_count;//分数随时间增加的计数器
    static uint16_t ground_count;//地面随时间移动的计数器
    static uint16_t cloud_count;//地面随时间移动的计数器

    score_count++;
    ground_count++;
    cloud_count++;

    if(score_count >= 100)
    {
        score_count = 0;
        Score++;
        if(Score >= 99999)
        {
            Score = 0;
        }
    }

    if(ground_count >= 20)
    {
        ground_count = 0;
        Ground_Pos++;//地面偏移量
        Barrier_pos++;//障碍物偏移量
        
        if(Ground_Pos >= 256)
        {
            Ground_Pos = 0;
        }
        if(Barrier_pos >= 144)
        {
            Barrier_pos = 0;
        }
        
    }

    if(cloud_count >= 50)
    {
        cloud_count = 0;
        Cloud_pos++;
        if(Cloud_pos >= 200)
        {
            Cloud_pos = 0;
        }
    }

    if(Dino_jump_flag == 1)
    {
        Dino_jump_t++;
        if(Dino_jump_t >= 1000)
        {
            Dino_jump_t = 0;
            Dino_jump_flag = 0;//跳完一次后就不跳了
        }
    }
}


/*********************
    作用：恐龙游戏界面动画显示
    参数：无
    返回：返回标志位传到外层，用于判断小恐龙有没有死亡
***********************/
uint8_t dino_isColliding_Flag;
uint8_t dino_Animation()
{

    OLED_Clear();
    dino_ShowScore();
    dino_ShowGround();
    dino_ShowBarrier();
    dino_ShowCloud();
    dino_ShowDino();
    OLED_Update();    
    dino_isColliding_Flag = isColliding(&dino_position, &barrier_position);

    if(dino_isColliding_Flag == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    } 
}

/*********************
    作用：恐龙游戏界面动画显示（放在计时器里；100ms增加1）
    参数：无
    返回：返回标志位传到外层，用于判断小恐龙有没有死亡
***********************/
void dino_FlagInit(void)
{
    Score           = 0;
    Ground_Pos      = 0;
    Barrier_pos     = 0;
    Dino_jump_flag  = 0;
    Dino_jump_pos   = 0; 
    Dino_jump_t     = 0;   
}
