#include "player.h"

//player struct constructor    
Player* initPlayer(){
    Player* player = malloc(sizeof(Player));

    player->fightTexture = LoadTexture("/home/ben/Documents/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/crouch_attack.png");
    player->walkTexture = LoadTexture("/home/ben/Documents/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/walk.png");
    player->idleTexture = LoadTexture("/home/ben/Documents/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/idle.png");
    player->jumpTexture = LoadTexture("/home/ben/Documents/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/jump.png"); 
    player->x = 40;
    player->y = 555;
    player->idleIndex = 0;
    player->walkIndex = 0;
    player->fightIndex = 0;
    player->jumpIndex = 0; 
    player->textureWidth = TEXTURE_LEN/NUM_FIGHT_SPRITES;
    player->walkTextureWidth = IDLE_TEXTURE_LEN/NUM_WALK_SPRITES;
    player->idleTextureWidth = IDLE_TEXTURE_LEN/NUM_IDLE_SPRITES;
    player->jumpTextureWidth = JUMP_TEXTURE_LEN/NUM_JUMP_SPRITES;
    player->textureHeight = 80;
    player->destRect = (Rectangle){player->x,player->y,200,170};
    player->isIdling = true; 
    player->isFighting = false;
    player->isMoving = false;
    player->destWalkRect = (Rectangle){player->x,player->y,200,170};
    player->destJumpRect = (Rectangle){player->x,player->y,200,170}; 
    player->collisionRect = (Rectangle){player->x+75,player->y+70,50,100};
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

//fight animation function
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


//walk animation function
void animateWalkPlayer(Player* player, int* walkIndex, float* currentTime){
        float idleInterval = 0.06f;
    
        if(*currentTime >= idleInterval){
            (*walkIndex)++;
            *currentTime = 0.0f;

            if(*walkIndex>NUM_WALK_SPRITES-1){
                *walkIndex = 0;
            }
        }
        //printf("Player destwalkrect y is %f \n",player->destWalkRect.y);
}

//idle animation function
void animateIdlePlayer(Player* player, int* idleIndex, float* currentTime){
        float idleInterval = 0.06f;
    
        if(*currentTime >= idleInterval){
            (*idleIndex)++;
            *currentTime = 0.0f;

            if(*idleIndex>NUM_IDLE_SPRITES-1){
                *idleIndex = 0;
            }
        }
}

//jump animation function
void animateJumpPlayer(Player* player, int* jumpIndex, float* currentTime){
	float jumpInterval = 0.06f;

	if(*currentTime >= jumpInterval){
	   (*jumpIndex)++;
	   *currentTime = 0.0f;
	
	   if(*jumpIndex>NUM_JUMP_SPRITES-1){
	  	 *jumpIndex = 0;
	   }
	 }
     //printf("Player jump dest rect y is %f \n",player->destJumpRect.y);
}

//platform movement function
void moveCollisionRect(Player* player, const char* direction) {
	int numToAdd = 3;
	if(strcmp(direction, "left")==0){
		numToAdd = -3;
		player->destRect.x += numToAdd;
		player->destWalkRect.x += numToAdd;
		player->collisionRect.x += numToAdd;
        player->destJumpRect.x += numToAdd;
	//	printf("direction is left \n");
	}
	else if(strcmp(direction, "right")==0){
		numToAdd = 3;
		player->destRect.x += numToAdd;
		player->destWalkRect.x += numToAdd;
		player->collisionRect.x += numToAdd;
        player->destJumpRect.x += numToAdd;
	//	printf("direction is right \n");
	}
/*	else {
	   goto idling;
	}

idling: 
	printf("Player is idling\n");
	*/
}


//jump movement function
void moveJumpRect(Player* player) {
    int numToAdd = 3;

    if(player->isJumping && (player->destWalkRect.y<600)){
        player->destRect.y -= numToAdd*4;
        player->destWalkRect.y -= numToAdd*4;
        player->collisionRect.y -= numToAdd*4;
        player->destJumpRect.y -= numToAdd*4;
    }

    else {
        numToAdd = 0; 
    }

}
