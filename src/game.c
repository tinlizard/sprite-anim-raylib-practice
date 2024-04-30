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
    Platform* platform = initPlatform(40,750,200,40);
    Platform* platform2 = initPlatform(250,750,200,40);
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
	        DrawTexturePro(platform->texture,platform->srcRect,platform->destRect,(Vector2) {0,0}, 0.f,RAYWHITE);
	        DrawTexturePro(platform2->texture,platform2->srcRect,platform2->destRect,(Vector2){0,0},0.f,RAYWHITE);
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
		        moveCollisionRect(player,"right");
            }
            else if(IsKeyDown(KEY_A)){
                player->isMoving = true;
                player->isIdling = false;
                player->isFighting = false;
                player->facingRight = false;
                moveCollisionRect(player,"left");
            }
	        else if(IsKeyDown(KEY_SPACE)){
		        player->isJumping = true;
		        player->isIdling = false;
		        player->isFighting = false;
	        }
            else {
                player->isIdling = true;
                player->isMoving = false;
                player->isFighting = false;
		player->isJumping = false;
            }

            //if player is idling
           if (player->isIdling && !player->isMoving && !player->isFighting && !player->isJumping) {
                //player->isMoving = false;
                //player->isFighting = false;
                animateIdlePlayer(player,&player->idleIndex,&currentTime);
                DrawTexturePro(player->idleTexture,player->srcIdleRects[player->idleIndex],player->destRect,(Vector2){0,0},0.0f,RAYWHITE);
           }

           //if player is moving
           else if(player->isMoving && !player->isIdling && !player->isFighting && !player->isJumping){
                //player->isIdling = false;
                //player->isFighting = false;
                animateWalkPlayer(player,&player->walkIndex,&currentTime);
                DrawTexturePro(player->walkTexture,player->srcWalkRects[player->walkIndex],player->destWalkRect,(Vector2){0,0},0.0f,RAYWHITE);
            }

            //if player is fighting
            else if(player->isFighting && !player->isIdling && !player->isMoving&& !player->isJumping){
                animateFightPlayer(player,&player->fightIndex,&currentTime);
                DrawTexturePro(player->fightTexture,player->srcFightRects[player->fightIndex],player->destRect,(Vector2){0,0},0.0f,RAYWHITE);
            }

            //if player is jumping
	        else if(player->isJumping || (player->isMoving && player->isJumping) && !player->isIdling && !player->isFighting){
		        animateJumpPlayer(player,&player->jumpIndex,&currentTime);
		        DrawTexturePro(player->jumpTexture,player->srcJumpRects[player->jumpIndex],player->destJumpRect, (Vector2){0,0},0.0f,RAYWHITE);
                moveJumpRect(player);
	            //DrawRectangle(player->destJumpRect.x,player->destJumpRect.y,player->destJumpRect.width,player->destJumpRect.height,RED);
	        }

            //otherwise...
            else {
                player->isIdling = true;
                player->isMoving = false;
                player->isFighting = false;
		        player->isJumping = false;
            }

              //flip player sprite left if player is facing left instead of right
              if(!player->facingRight){
                for(int i=0; i<NUM_WALK_SPRITES; i++)
                    player->srcWalkRects[i] = (Rectangle) {player->walkTextureWidth*i,0,-player->walkTextureWidth,player->textureHeight};
                
                for(int i=0; i<NUM_IDLE_SPRITES; i++)
                    player->srcIdleRects[i] = (Rectangle) {player->idleTextureWidth*i,0,-player->textureWidth,player->textureHeight};
                
                for(int i=0; i<NUM_FIGHT_SPRITES; i++)
                    player->srcFightRects[i]= (Rectangle){player->textureWidth*i,0,-player->textureWidth,player->textureHeight};

		        for(int i=0; i<NUM_JUMP_SPRITES; i++)
		            player->srcJumpRects[i] = (Rectangle){player->jumpTextureWidth*i,0,-player->jumpTextureWidth,player->textureHeight};
              }

            //otherwise don't flip the sprite
             else{
                 for(int i=0; i<NUM_WALK_SPRITES; i++)
                    player->srcWalkRects[i] = (Rectangle) {player->walkTextureWidth*i,0,player->walkTextureWidth,player->textureHeight};

                for(int i=0; i<NUM_IDLE_SPRITES; i++)
                     player->srcIdleRects[i] = (Rectangle) {player->idleTextureWidth*i,0,player->textureWidth,player->textureHeight}; 

                 for(int i=0; i<NUM_FIGHT_SPRITES; i++)
                    player->srcFightRects[i]= (Rectangle){player->textureWidth*i,0,player->textureWidth,player->textureHeight};

		        for(int i=0; i<NUM_JUMP_SPRITES; i++)
                    player->srcJumpRects[i] = (Rectangle){player->jumpTextureWidth*i,0,player->jumpTextureWidth,player->textureHeight};

    
             }
            
    //check if colliding. If so, set gravity to zero. 
	if(isCollidingWithPlayer(player,platform) || isCollidingWithPlayer(player,platform2)){
	//	DrawRectangleRec(player->collisionRect,RED);
//		DrawRectangle(platform->x,platform->y,platform->width,platform->height,RED);
		gravity = 0;
	}
    //otherwise let the gravity pull the player downwards. 
	else {
		gravity = 9.81;
		player->destRect.y += (int) gravity;
		player->destWalkRect.y += (int) gravity;
		player->collisionRect.y += (int) gravity;
        player->destJumpRect.y += (int) gravity;
        //player->destJumpRect.y += (int) gravity;
	}

            //DrawText(player->facingRight ? "FACING RIGHT" : "FACING LEFT" ,30,30,20,RED); //debugging
            //DrawText(player->isMoving ? "IS MOVING" : "IS NOT MOVING",30,50,20,RED);
            //DrawText(player->isIdling ? "IS IDLING" : "IS NOT IDLING",30,70,20,RED);
            //DrawText(player->isFighting ? "IS FIGHTING" : "IS NOT FIGHTING",30,90,20,RED);
            //char currentIdleIndexStr[10]; //debugging
            //sprintf(currentIdleIndexStr,"%f",player->srcWalkRects[player->walkIndex].width);  //debugging
            //DrawText(currentIdleIndexStr,230,45,20,RED); //debugging

        //debugging sprintf statements. this one is for gravity.
	    char gravityString[10];
	    sprintf(gravityString,"%0.2f",gravity);
	    DrawText(gravityString,30,70,20,RED);

        //this is just debugging for the destWalkRect y position.
	    char y_pos[10];
	    sprintf(y_pos,"%f",player->destWalkRect.y);
	    DrawText(y_pos,30,95,20,RED);


        //this is debugging for the destJumpRect y position. 
         char jumpY[10];
        sprintf(jumpY,"%f",player->destJumpRect.y);
        DrawText(jumpY,30,120,20,RED);
        EndDrawing();
    }

    CloseWindow();      
    free(player);
    free(platform);
    return 0;
}
