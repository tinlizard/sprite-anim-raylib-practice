#include "raylib.h"
#include "player.h"
#include "platform.h"
#include <stdlib.h>
#include <stdio.h>
 
static float gravity = 9.81;
static Texture2D backgroundTexture;

int main(void) {
    const int screenWidth = 928;
    const int screenHeight = 793;

    InitWindow(screenWidth, screenHeight, "Knight's Night");

    Player* player = initPlayer();
    Platform* platform = initPlatform();
    float currentTime = GetTime();
	backgroundTexture = LoadTexture("/home/ben/Documents/Free Pixel Art Forest/Preview/background.png");
    SetTargetFPS(60);               

    while (!WindowShouldClose())    
    {
        BeginDrawing();
            ClearBackground(BLACK);
            currentTime += GetFrameTime();
	        DrawFPS(10,10);
            DrawTexture(backgroundTexture,0,0,RAYWHITE);

            if(IsKeyDown(KEY_X)){
                player->isFighting = true;
                player->isMoving = false;
                player->isIdling = false;
            }
            else if(IsKeyDown(KEY_D) || IsKeyPressed(KEY_D)){
                player->isMoving = true;
                player->isIdling = false;
                player->isFighting = false;
                player->facingRight = true;
                player->destWalkRect.x += 3;
                player->destRect.x+=3;
            }
            else if(IsKeyDown(KEY_A) || IsKeyPressed(KEY_A)){
                player->isMoving = true;
                player->isIdling = false;
                player->isFighting = false;
                player->facingRight = false;
                player->x -= 3;
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
                player->isFighting = false;
            }

              if(!player->facingRight){
                for(int i=0; i<NUM_WALK_SPRITES; i++)
                    player->srcWalkRects[i] = (Rectangle) {player->walkTextureWidth*i,0,-player->walkTextureWidth,player->textureHeight};
                
                for(int i=0; i<NUM_IDLE_SPRITES; i++)
                    player->srcIdleRects[i] = (Rectangle) {player->idleTextureWidth*i,0,-player->textureWidth,player->textureHeight};
                
                for(int i=0; i<NUM_FIGHT_SPRITES; i++)
                    player->srcFightRects[i]= (Rectangle){player->textureWidth*i,0,-player->textureWidth,player->textureHeight};
              }
             else{
                 for(int i=0; i<NUM_WALK_SPRITES; i++)
                    player->srcWalkRects[i] = (Rectangle) {player->walkTextureWidth*i,0,player->walkTextureWidth,player->textureHeight};

                for(int i=0; i<NUM_IDLE_SPRITES; i++)
                     player->srcIdleRects[i] = (Rectangle) {player->idleTextureWidth*i,0,player->textureWidth,player->textureHeight}; 

                 for(int i=0; i<NUM_FIGHT_SPRITES; i++)
                    player->srcFightRects[i]= (Rectangle){player->textureWidth*i,0,player->textureWidth,player->textureHeight};
    
             }
            
	if(isCollidingWithPlayer(player,platform)){
		DrawRectangleRec(player->destRect,RED);
		DrawRectangleRec(player->destWalkRect,BLUE);
		DrawRectangle(platform->x,platform->y,platform->width,platform->height,RED);
		gravity = 0;
	}
	else {
		gravity = 9.81;
		player->destRect.y += (int) gravity;
		player->destWalkRect.y += (int) gravity;
	}

            //DrawText(player->facingRight ? "FACING RIGHT" : "FACING LEFT" ,30,30,20,RED); //debugging
            //DrawText(player->isMoving ? "IS MOVING" : "IS NOT MOVING",30,50,20,RED);
            //DrawText(player->isIdling ? "IS IDLING" : "IS NOT IDLING",30,70,20,RED);
            //DrawText(player->isFighting ? "IS FIGHTING" : "IS NOT FIGHTING",30,90,20,RED);
            //char currentIdleIndexStr[10]; //debugging
            //sprintf(currentIdleIndexStr,"%f",player->srcWalkRects[player->walkIndex].width);  //debugging
            //DrawText(currentIdleIndexStr,230,45,20,RED); //debugging
	    char gravityString[10];
	    sprintf(gravityString,"%0.2f",gravity);
	    DrawText(gravityString,30,70,20,RED);

	    char y_pos[10];
	    sprintf(y_pos,"%f",player->destWalkRect.y);
	    DrawText(y_pos,30,95,20,RED);
        EndDrawing();
    }

    CloseWindow();      
    free(player);
    free(platform);
    return 0;
}
