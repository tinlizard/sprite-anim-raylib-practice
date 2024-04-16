#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TEXTURE_LEN 480
#define IDLE_TEXTURE_LEN 1200
#define NUM_FIGHT_SPRITES 4
#define NUM_WALK_SPRITES 10
#define NUM_IDLE_SPRITES 10

typedef struct {
   int x, y, textureWidth, textureHeight, idleIndex, 
   walkIndex, fightIndex, walkTextureWidth, 
   idleTextureWidth,walkTexureHeight;
   Texture2D idleTexture, fightTexture, walkTexture;
   Rectangle srcFightRects[NUM_FIGHT_SPRITES];
   Rectangle srcWalkRects[NUM_WALK_SPRITES];
   Rectangle srcIdleRects[NUM_IDLE_SPRITES];
   //Rectangle idleRect; 

   Rectangle destRect;
   Rectangle destWalkRect;
   Rectangle collisionRect;
   bool isIdling, isMoving, isFighting, facingRight;
} Player;

Player* initPlayer();
void animateFightPlayer(Player* player, int* fightIndex, float* currentTime);
void animateWalkPlayer(Player* player, int* walkIndex, float* currentTime);
void animateIdlePlayer(Player* player, int* idleIndex, float* currentTime);
void moveCollisionRect(Player* player, const char* direction);

#endif
