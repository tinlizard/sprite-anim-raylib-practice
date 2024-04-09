#include "raylib.h"
#define TEXTURE_LEN 480
#define IDLE_TEXTURE_LEN 1200
#define NUM_FIGHT_SPRITES 4
#define NUM_WALK_SPRITES 10
#define NUM_IDLE_SPRITES 10
#include <stdlib.h>
#include <stdio.h>

typedef struct Player {
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
   bool isIdling, isMoving, isFighting, facingRight;
} Player;


Player* initPlayer(){
    Player* player = malloc(sizeof(Player));

    player->fightTexture = LoadTexture("/home/ben/Downloads/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/crouch_attack.png");
    player->walkTexture = LoadTexture("/home/ben/Downloads/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/walk.png");
    player->idleTexture = LoadTexture("/home/ben/Downloads/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/idle.png");
    player->x = 40;
    player->y = 250;
    player->idleIndex = 0;
    player->walkIndex = 0;
    player->fightIndex = 0;
    player->textureWidth = TEXTURE_LEN/NUM_FIGHT_SPRITES;
    player->walkTextureWidth = IDLE_TEXTURE_LEN/NUM_WALK_SPRITES;
    player->idleTextureWidth = IDLE_TEXTURE_LEN/NUM_IDLE_SPRITES;
    player->textureHeight = 80;
    player->destRect = (Rectangle){player->x,player->y,190,150};
    player->isIdling = true; 
    player->isFighting = false;
    player->isMoving = false;
    player->destWalkRect = (Rectangle){player->x,player->y,190,150};
    player->facingRight = true;
    
    for(int i=0; i<NUM_FIGHT_SPRITES; i++){
      player->srcFightRects[i]= (Rectangle){player->textureWidth*i,0,player->textureWidth,player->textureHeight};
    }
    for(int i=0; i<NUM_WALK_SPRITES; i++){
        player->srcWalkRects[i] = (Rectangle) {player->walkTextureWidth*i,0,player->walkTextureWidth,player->textureHeight};
    }

    for(int i=0; i<NUM_IDLE_SPRITES; i++){
        player->srcIdleRects[i] = (Rectangle) {player->idleTextureWidth*i,0,player->textureWidth,player->textureHeight};
    }
    return player;
}

void animateFightPlayer(Player* player, int* fightIndex, float* currentTime){
        float fightInterval = 0.06f;
    
        if(*currentTime >= fightInterval){
            (*fightIndex)++;
            *currentTime = 0.0f;

            if(*fightIndex>NUM_FIGHT_SPRITES-1){
                *fightIndex = 0;
            }
        }
}

void animateWalkPlayer(Player* player, int* walkIndex, float* currentTime){
        float idleInterval = 0.06f;
    
        if(*currentTime >= idleInterval){
            (*walkIndex)++;
            *currentTime = 0.0f;

            if(*walkIndex>NUM_WALK_SPRITES-1){
                *walkIndex = 0;
            }
        }
}


void animateIdlePlayer(Player* player, int* idleIndex, float* currentTime){
        float idleInterval = 0.03f;
    
        if(*currentTime >= idleInterval){
            (*idleIndex)++;
            *currentTime = 0.0f;

            if(*idleIndex>NUM_IDLE_SPRITES-1){
                *idleIndex = 0;
            }
        }
}




int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Sprite practice");

    Player* player = initPlayer();
    float currentTime = GetTime();
	
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(BLACK);
            currentTime += GetFrameTime();
	        DrawFPS(10,10);

            if(IsKeyDown(KEY_X)){
                player->isFighting = true;
                player->isMoving = false;
                player->isIdling = false;
            }
            else if(IsKeyDown(KEY_D)){
                player->isMoving = true;
                player->isIdling = false;
                player->isFighting = false;
                player->facingRight = true;
                player->destWalkRect.x += 3;
                player->destRect.x+=3;
            }
            else if(IsKeyDown(KEY_A)){
                player->isMoving = true;
                player->isIdling = false;
                player->isFighting = false;
                player->facingRight = false;
                player->destWalkRect.x-=3;
                player->destRect.x-=3;

            }
            else {
                player->isIdling = true;
                player->isMoving = false;
                player->isFighting = false;
            }
           if (player->isIdling && !player->isMoving && !player->isFighting) {
                //player->isMoving = false;
                //player->isFighting = false;
                animateIdlePlayer(player,&player->idleIndex,&currentTime);
                DrawTexturePro(player->idleTexture,player->srcIdleRects[player->idleIndex],player->destRect,(Vector2){0,0},0.0f,RAYWHITE);
           }
           else if(player->isMoving && !player->isIdling && !player->isFighting){
                //player->isIdling = false;
                //player->isFighting = false;
                animateWalkPlayer(player,&player->walkIndex,&currentTime);
                DrawTexturePro(player->walkTexture,player->srcWalkRects[player->walkIndex],player->destWalkRect,(Vector2){0,0},0.0f,RAYWHITE);
            }
            else if(player->isFighting && !player->isIdling && !player->isMoving){
                animateFightPlayer(player,&player->fightIndex,&currentTime);
                DrawTexturePro(player->fightTexture,player->srcFightRects[player->fightIndex],player->destRect,(Vector2){0,0},0.0f,RAYWHITE);
            }
            else {
                player->isIdling = true;
                player->isMoving = false;
                //player->facingRight = true;
                player->isFighting = false;
            }

              if(!player->facingRight){
                player->srcWalkRects[player->walkIndex].width = -IDLE_TEXTURE_LEN/NUM_WALK_SPRITES;
                player->srcIdleRects[player->idleIndex].width = -IDLE_TEXTURE_LEN/NUM_IDLE_SPRITES;
              }
             else{
                 player->srcWalkRects[player->walkIndex].width = IDLE_TEXTURE_LEN/NUM_WALK_SPRITES;
                  player->srcIdleRects[player->idleIndex].width = IDLE_TEXTURE_LEN/NUM_IDLE_SPRITES;
             }

            /*
            if(!player->facingRight)
                player->srcWalkRects[player->walkIndex].width = -IDLE_TEXTURE_LEN/NUM_WALK_SPRITES;
            else
                player->srcWalkRects[player->walkIndex].width = IDLE_TEXTURE_LEN/NUM_WALK_SPRITES;
            */
            

            DrawText(player->facingRight ? "FACING RIGHT" : "FACING LEFT" ,30,30,20,RED); //debugging
            DrawText(player->isMoving ? "IS MOVING" : "IS NOT MOVING",30,50,20,RED);
            DrawText(player->isIdling ? "IS IDLING" : "IS NOT IDLING",30,70,20,RED);
            //char currentIdleIndexStr[10]; //debugging
            //sprintf(currentIdleIndexStr,"%d",IDLE_TEXTURE_LEN/NUM_IDLE_SPRITES);  //debugging
            //DrawText(currentIdleIndexStr,200,45,20,RED); //debugging
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    free(player);
    return 0;
}
