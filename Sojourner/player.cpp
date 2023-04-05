#include "player.h"

player::player()
{
    playerX = playerY = pVelX = pVelY = 0;
}
player::~player()
{
    playerTexture.free();
}

void player::handleEvent(SDL_Event& e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_w:
            pVelY -= PLAYER_VEL;
            break;
        case SDLK_s:
            pVelY += PLAYER_VEL;
            break;
        case SDLK_a:
            pVelX -= PLAYER_VEL;
            break;
        case SDLK_d:
            pVelX += PLAYER_VEL;
            break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_w:
            pVelY += PLAYER_VEL;
            break;
        case SDLK_s:
            pVelY -= PLAYER_VEL;
            break;
        case SDLK_a:
            pVelX += PLAYER_VEL;
            break;
        case SDLK_d:
            pVelX -= PLAYER_VEL;
            break;
        }
    }
}


void player::move()
{
    playerX += pVelX;
    playerY += pVelY;
    if((playerX < 0) || (playerX + PLAYER_WIDTH > SCREEN_WIDTH))
    {
        playerX -= pVelX;
    }
    if((playerY < 0) || (playerY + PLAYER_HEIGHT > SCREEN_HEIGHT))
    {
        playerY -= pVelY;
    }
}

void player::loadPlayer(SDL_Renderer* renderer)
{
    playerTexture.loadFromFile( "images/sprites/tree1.png",renderer );
}

void player::render(SDL_Renderer* renderer)
{
    playerTexture.render(playerX,playerY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void player::freePlayer()
{
    playerTexture.free();
}

void player::setCamera(SDL_Rect& camera)
{
    camera.x = (playerCollisionBox.x + PLAYER_WIDTH/2) - SCREEN_WIDTH/2;
    camera.y = (playerCollisionBox.y + PLAYER_HEIGHT/2) - SCREEN_HEIGHT/2;
    //make sure player doesn't leave top or left side of screen
    if(camera.x < 0)
    {
        camera.x = 0;
    }
    if(camera.y < 0)
    {
        camera.y=0;
    }
    //screen width,height should be replaced by level width, height.
    if(camera.x>SCREEN_WIDTH-camera.w)
    {
        camera.x=SCREEN_WIDTH-camera.w;
    }
    if(camera.y>SCREEN_HEIGHT-camera.h)
    {
        camera.y=SCREEN_HEIGHT-camera.h;
    }
}
