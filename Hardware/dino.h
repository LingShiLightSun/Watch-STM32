#ifndef __DINO_H
#define __DINO_H

#include "bsp.h"

typedef struct Object_Position{ //物体具体位置：用于检测碰撞
    uint8_t minX;
    uint8_t minY;
    uint8_t maxX;
    uint8_t maxY;
}Object_Position;

void dino_ShowScore(void);
void dino_ShowGround(void);
void dino_ShowBarrier(void);
void dino_ShowCloud(void);
void dino_ShowDino(void);
void dino_Tick(void);
uint8_t dino_Animation(void);
uint8_t isColliding(Object_Position* a, Object_Position* b);
void dino_FlagInit(void);

#endif
