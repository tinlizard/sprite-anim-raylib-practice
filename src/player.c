#include "player.h"

Player* initPlayer(){
    Player* player = malloc(sizeof(Player));

    player->fightTexture = LoadTexture("/home/ben/Documents/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/crouch_attack.png");
    player->walkTexture = LoadTexture("/home/ben/Documents/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/walk.png");
    player->idleTexture = LoadTexture("/home/ben/Documents/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/idle.png");
    player->x = 40;
    player->y = 555;
    player->idleIndex = 0;
    player->walkIndex = 0;
    player->fightIndex = 0;
    player->textureWidth = TEXTURE_LEN/NUM_FIGHT_SPRITES;
    player->walkTextureWidth = IDLE_TEXTURE_LEN/NUM_WALK_SPRITES;
    player->idleTextureWidth = IDLE_TEXTURE_LEN/NUM_IDLE_SPRITES;
    player->textureHeight = 80;
    player->destRect = (Rectangle){player->x,player->y,200,170};
    player->isIdling = true; 
    player->isFighting = false;
    player->isMoving = false;
    player->destWalkRect = (Rectangle){player->x,player->y,200,170};
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
        float idleInterval = 0.06f;
    
        if(*currentTime >= idleInterval){
            (*idleIndex)++;
            *currentTime = 0.0f;

            if(*idleIndex>NUM_IDLE_SPRITES-1){
                *idleIndex = 0;
            }
        }
}
