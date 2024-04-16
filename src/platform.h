#ifndef PLATFORM_H
#define PLATFORM_H
#include "raylib.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x,y,width,height;
    bool isCollider;
    Rectangle collisionRect, srcRect, destRect;
    Texture2D texture;
} Platform;

Platform* initPlatform(int x,int y, int width, int height);
bool isCollidingWithPlayer(Player* player, Platform* platform);

#endif 
