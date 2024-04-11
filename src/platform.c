#include "platform.h"
#include "player.h"

Platform* initPlatform(){
    Platform* platform = malloc(sizeof(Platform));

    platform->x = 40; 
    platform->y = 750;
    platform->width = 200;
    platform->height = 20;
    platform->isCollider = true;
    platform->collisionRect = (Rectangle) {platform->x,platform->y,platform->width,platform->height};
    platform->texture = LoadTexture("/home/ben/Documents/Free Pixel Art Forest/Preview/background.png");

    return platform;
}

//debugging function
bool isCollidingWithPlayer(Player* player, Platform* platform){
   if(CheckCollisionRecs(player->destRect,platform->collisionRect))
	return true;	
   else 
    	return false;
}
