#include "player.h"

player::player()
{
    playerX = playerY = pVelX = pVelY = walkFrame = moveState = 0;
    flipHorizontal = countDown = false;
}
player::~player()
{
    for(int i = 0; i<MOVE_STATES;i++)
    {
        if(i==IDLE)
        {
            for(int j = 0; j<IDLE_TEXTURES;j++)
            {
                playerTexture[i][j].free();
            }
        }
        else if(i==WALK_LR)
        {
            for(int k = 0; k<LR_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
    }
    currentTexture.free();
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


void player::move(int tick)
{
    playerX += pVelX;
    playerY += pVelY;

    if(pVelX > 0)//player is walking right
    {
        if(pVelY == 0)//player is not moving up or down
        {
            //the images used are right facing, therefore no need to flip.
            flipHorizontal=false;
            //moveState 1 = walking left/right
            moveState = 1;
            if(tick%3 == 0)
            {
                if(!countDown)
                {
                    walkFrame++;
                    if(walkFrame >= LR_TEXTURES)
                    {
                        countDown = true;
                        walkFrame--;
                    }
                }
                else
                {
                    walkFrame--;
                    if(walkFrame< 1)
                    {
                        countDown=false;
                        walkFrame++;
                    }
                }
            }
        }
        else if(pVelY > 0)//player is walking right & up
        {

        }
        else//player is walking right and down
        {

        }
        currentTexture = playerTexture[moveState][walkFrame];
        std::cout<<"\n\n moveState: "<<moveState<<"\n walkFrame:"<<walkFrame;
    }
    else if(pVelX < 0)//player is walking left
    {
        if(pVelY == 0)//player is not moving up or down
        {
            //images are right facing, player is walking left, so flip horizontal.
            flipHorizontal=true;
            //moveState 1 is walking left/right
            moveState=1;
            if(tick%3 == 0)
            {
                if(!countDown)
                {
                    walkFrame++;
                    if(walkFrame >= LR_TEXTURES)
                    {
                        countDown = true;
                        walkFrame--;
                    }
                }
                else
                {
                    walkFrame--;
                    if(walkFrame< 1)
                    {
                        countDown=false;
                        walkFrame++;
                    }
                }
            }
        }
        else if(pVelY > 0)//player is walking left and up
        {

        }
        else//player is walking left and down
        {

        }
        currentTexture = playerTexture[moveState][walkFrame];
        std::cout<<"\n\n moveState: "<<moveState<<"\n walkFrame:"<<walkFrame;
    }
    else
    {
        //player is idling, no need for horizontal flip.
        flipHorizontal=false;
        //currently no idle animation, so no need to cycle back through frames.
        countDown=false;
        //moveState 0 is idle
        moveState=0;
        //walkFrame is 0 since currently only 1 texture for idle state.
        walkFrame = 0;
        currentTexture = playerTexture[moveState][walkFrame];
    }

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

    std::stringstream ss,ss2,ss3;


    ss3.str("");
    std::string str = ss3.str();
    for(int i = 0; i<MOVE_STATES;i++)
    {
        if(i==IDLE)
        {
            ss.str("images/sprites/PlayerCharacter");
            ss2.str(".png");

            for(int j = 0; j<IDLE_TEXTURES;j++)
            {
                ss3 << ss.str();
                //right here is where other idle images would be appended to ss3 for loading, if they existed
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][j].loadFromFile( str,renderer );
                ss3.str( "" );//reset ss3
            }
        }
        else if(i==WALK_LR)
        {
            ss.str("images/sprites/PlayerCharacterRight");
            ss2.str(".png");
            for(int k = 0; k<LR_TEXTURES;k++)
            {
                ss3 << ss.str();
                ss3 << (k+1);
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][k].loadFromFile( str,renderer );
                ss3.str("");//reset ss3
            }
        }
    }
    currentTexture = playerTexture[moveState][walkFrame];//beginning texture for currentTexture is idle 0 (standing around)
}

void player::render(SDL_Renderer* renderer)
{
    if(flipHorizontal)
    {
        currentTexture.render(playerX,playerY,NULL,0.0,NULL,SDL_FLIP_HORIZONTAL,renderer);
    }
    else
    {
        currentTexture.render(playerX,playerY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }

}

void player::freePlayer()
{
    for(int i = 0; i<MOVE_STATES;i++)
    {
        if(i==IDLE)
        {
            for(int j = 0; j<IDLE_TEXTURES;j++)
            {
                playerTexture[i][j].free();
            }
        }
        else if(i==WALK_LR)
        {
            for(int k = 0; k<LR_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
    }
    currentTexture.free();
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
