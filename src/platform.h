#ifndef PLATFORM_H
#define PLATFORM_H
#include "raylib.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x,y,width,height;
    bool isCollider;
    Rectangle collisionRect;
    Texture2D texture;
} Platform;

Platform* initPlatform();
bool isCollidingWithPlayer(Player* player, Platform* platform);

#endif 
