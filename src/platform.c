#include "platform.h"
#include "player.h"

//platform struct constructor 
Platform* initPlatform(int x, int y, int width, int height){
    Platform* platform = malloc(sizeof(Platform));

    platform->x = x; 
    platform->y = y;
    platform->width = width;
    platform->height = height;
    platform->isCollider = true;
    platform->collisionRect = (Rectangle) {platform->x,platform->y,platform->width,platform->height};
    platform->texture = LoadTexture("/home/ben/Documents/FreeCuteTileset/ExampleTiles.png");
    platform->srcRect = (Rectangle) {20,0,80,96};
    platform->destRect = (Rectangle) {platform->x,platform->y,platform->width,platform->height};
    
    return platform;
}

//collision debugging function
bool isCollidingWithPlayer(Player* player, Platform* platform){
   if(CheckCollisionRecs(player->collisionRect,platform->collisionRect))
	   return true;	
   else 
    	return false;
}
