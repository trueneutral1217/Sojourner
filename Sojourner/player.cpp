#include "player.h"

player::player()
{
    pVelX = pVelY = walkFrame = moveState = 0;
    playerX = 380;//middle of screen (considering player width)
    playerY = 260;//also middle, considering player height.  player starts in screen center.
    playerBot = playerY+PLAYER_HEIGHT;
    flipHorizontal = false;
    inSpace=false;
    inRange=false;
    interact=false;
    interactBed=false;
    interactWaterTank=false;
    interactPlanter=false;
    interactKitchen=false;
    interactInfirmary = false;
    interactBike = false;

    //making the collision box a 30x20 pixel box at player's feet area.
    playerCollisionBox.x = playerX+5;
    playerCollisionBox.y = playerY+60;
    playerCollisionBox.w = 30;
    playerCollisionBox.h = PLAYER_HEIGHT/4;

    for(int i = 0; i<TOTAL_PLAYER_NEEDS; i++)
    {
        need[i] = 100;
    }
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
        else if(i==WALK_DLDR)
        {
            for(int k = 0; k<DLDR_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
        else if(i==WALK_ULUR)
        {
            for(int k = 0; k<ULUR_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
        else if(i==WALK_D)
        {
            for(int k = 0; k<D_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
        else if(i==WALK_U)
        {
            for(int k = 0; k<U_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
    }
    currentTexture.free();
    freeNeedsTextures();
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
        case SDLK_e:
            interact = true;
            std::cout<<"\n interact: "<<interact;
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
        case SDLK_e:
            interact = false;
            std::cout<<"\n interact: "<<interact;
            break;
        }
    }
}


void player::move(int tick, SDL_Rect collidable[],SDL_Rect interactable[],int STATIONS)
{
    playerX += pVelX;
    //keeps playerY within 100 pixels of center
    if(playerY<360 && pVelY>0)
    {
        playerY += pVelY;
    }
    if(playerY>160 && pVelY<0)
    {
        playerY+=pVelY;
    }


    if(pVelX > 0)//player is walking right
    {
        if(pVelY == 0)//player is not moving up or down
        {
            //the images used are right facing, therefore no need to flip.
            flipHorizontal=false;
            //moveState 1 = walking left/right
            moveState = WALK_LR;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= LR_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        else if(pVelY > 0)//player is walking right & down
        {
            flipHorizontal=false;
            moveState=WALK_DLDR;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= DLDR_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        else//player is walking right and up
        {
            flipHorizontal=false;
            moveState=WALK_ULUR;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= ULUR_TEXTURES)
                {
                    walkFrame=0;
                }
            }
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
            moveState=WALK_LR;
            if(tick%3 == 0)
            {
                walkFrame++;
                if(walkFrame >= LR_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        else if(pVelY > 0)//player is walking left and down
        {
            flipHorizontal=true;
            moveState=WALK_DLDR;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= DLDR_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        else//player is walking left and up
        {
            flipHorizontal=true;
            moveState=WALK_ULUR;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= ULUR_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        currentTexture = playerTexture[moveState][walkFrame];
        std::cout<<"\n\n moveState: "<<moveState<<"\n walkFrame:"<<walkFrame;
    }
    else
    {
        //player is idling,walking down, or walking up, no need for horizontal flip.
        flipHorizontal=false;

        if(pVelY > 0)//player is walking down
        {
            moveState=WALK_D;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= D_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        else if(pVelY < 0)//player is walking up
        {
            moveState=WALK_U;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= U_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        else//player is not moving up or down (idle)
        {
            //moveState 0 is idle
            moveState=IDLE;
            if(tick%3 == 0)//every 3 frames a new animation image is loaded
            {
                walkFrame++;
                if(walkFrame >= IDLE_TEXTURES)
                {
                    walkFrame=0;
                }
            }
        }
        //walkFrame is 0 since currently only 1 texture for idle state.
        //walkFrame = 0;
        currentTexture = playerTexture[moveState][walkFrame];
    }

    if((playerX < 0) || (playerX + PLAYER_WIDTH > SCREEN_WIDTH) )
    {
        playerX -= pVelX;
    }
    if((playerY < 0) || (playerY + PLAYER_HEIGHT > SCREEN_HEIGHT) )
    {
        playerY -= pVelY;
    }
    //update player collision box coords
    playerCollisionBox.x = playerX+5;
    playerCollisionBox.y = playerY+60;


    for(int i = 0; i<STATIONS;i++)
    {

        //prevent player from walking into station
        if(collisionDetector(collidable[i]))
        {
            std::cout<<"\n collision detected!";
            playerX-=pVelX;
            playerY-=pVelY;
        }
        //check if player is in range of interacting with a station
        if(collisionDetector(interactable[i]))
        {

            if(i==0)
            {
                //flag stage to render bed sleeptyTime text texture
                interactBed = true;
            }
            //watertank is interactable[1]
            if(i==1)
            {
                //flag stage to render watertank waterLevel text texture
                interactWaterTank = true;
            }
            if(i==2)
            {
                //flag stage to render planter plantStatus text texture
                interactPlanter = true;
            }
            if(i==3)
            {
                //flag stage to render kitchen foodTime text texture
                interactKitchen = true;
            }
            if(i==4)
            {
                interactInfirmary = true;
            }
            if(i==5)
            {
                interactBike = true;
            }
        }
        else
        {
            if(i==0)
            {
                //flag stage to render bed sleeptyTime text texture
                interactBed = false;
            }
            if(i==1)
            {
                //flag stage to render watertank waterLevel text texture
                interactWaterTank = false;
            }
            if(i==2)
            {
                //flag stage to render planter plantStatus text texture
                interactPlanter = false;
            }
            if(i==3)
            {
                //flag stage to render kitchen foodTime text texture
                interactKitchen = false;
            }
            if(i==4)
            {
                interactInfirmary = false;
            }
            if(i==5)
            {
                interactBike = false;
            }
        }
    }
    playerBot = playerY+PLAYER_HEIGHT;
}

void player::loadPlayer(SDL_Renderer* renderer)
{
    std::cout<<"\n running player::loadPlayer(SDL_Renderer* renderer)";
    //set up player collision box dimensions (lower quarter of player texture is the size of the collision box.
    playerCollisionBox.x = playerX+5;
    playerCollisionBox.y = playerY+60;
    playerCollisionBox.w=30;
    playerCollisionBox.h=20;

    //used for loading the player textures for walking animations
    std::stringstream ss,ss2,ss3;
    ss3.str("");
    ss3.clear();
    std::string str = ss3.str();
    for(int i = 0; i<MOVE_STATES;i++)
    {
        if(i==IDLE)
        {
            if(inSpace)
            {
                ss.str("images/sprites/PlayerCharacterSpaceDown1");
            }
            else
            {
                ss.str("images/sprites/PlayerCharacterDown1");
            }
            ss2.str(".png");

            for(int j = 0; j<IDLE_TEXTURES;j++)
            {
                ss3 << ss.str();
                //right here is where other idle images would be appended to ss3 for loading, if they existed
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][j].loadFromFile( str,renderer );
                ss3.str( "" );//reset ss3
                ss3.clear();
            }
        }
        else if(i==WALK_LR)
        {
            if(inSpace)
            {
                ss.str("images/sprites/PlayerCharacterSpaceRight");
            }
            else
            {
                ss.str("images/sprites/PlayerCharacterRight");
            }

            ss2.str(".png");
            for(int k = 0; k<LR_TEXTURES;k++)
            {
                ss3 << ss.str();
                ss3 << (k+1);
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][k].loadFromFile( str,renderer );
                ss3.str("");//reset ss3
                ss3.clear();
            }
        }
        else if(i==WALK_DLDR)//loads textures for walking downright and down left (downleft get flipped horizontally)
        {
            if(inSpace)
            {
                ss.str("images/sprites/PlayerCharacterSpaceRightDown");
            }
            else
            {
                ss.str("images/sprites/PlayerCharacterRightDown");
            }

            ss2.str(".png");
            for(int k = 0; k<DLDR_TEXTURES;k++)
            {
                ss3 << ss.str();
                ss3 << (k+1);
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][k].loadFromFile( str,renderer );
                ss3.str("");//reset ss3
                ss3.clear();
            }
        }
        else if(i==WALK_ULUR)//loads textures for walking up right and up left (up left get flipped horizontally)
        {
            if(inSpace)
            {
                ss.str("images/sprites/PlayerCharacterSpaceRightUp");
            }
            else
            {
                ss.str("images/sprites/PlayerCharacterRightUp");
            }

            ss2.str(".png");
            for(int k = 0; k<ULUR_TEXTURES;k++)
            {
                ss3 << ss.str();
                ss3 << (k+1);
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][k].loadFromFile( str,renderer );
                ss3.str("");//reset ss3
                ss3.clear();
            }
        }
        else if(i==WALK_D)//loads textures for walking down
        {
            if(inSpace)
            {
                ss.str("images/sprites/PlayerCharacterSpaceDown");
            }
            else
            {
                ss.str("images/sprites/PlayerCharacterDown");
            }

            ss2.str(".png");
            for(int k = 0; k<D_TEXTURES;k++)
            {
                ss3 << ss.str();
                ss3 << (k+1);
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][k].loadFromFile( str,renderer );
                ss3.str("");//reset ss3
                ss3.clear();
            }
        }
        else if(i==WALK_U)//loads textures for walking up
        {
            if(inSpace)
            {
                ss.str("images/sprites/PlayerCharacterSpaceUp");
            }
            else
            {
                ss.str("images/sprites/PlayerCharacterUp");
            }

            ss2.str(".png");
            for(int k = 0; k<U_TEXTURES;k++)
            {
                ss3 << ss.str();
                ss3 << (k+1);
                ss3 << ss2.str();
                str = ss3.str();
                playerTexture[i][k].loadFromFile( str,renderer );
                ss3.str("");//reset ss3
                ss3.clear();
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
    std::cout<<"\n running player::freePlayer()";
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
        else if(i==WALK_DLDR)
        {
            for(int k = 0; k<DLDR_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
        else if(i==WALK_ULUR)
        {
            for(int k = 0; k<ULUR_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
        else if(i==WALK_D)
        {
            for(int k = 0; k<D_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
        else if(i==WALK_U)
        {
            for(int k = 0; k<U_TEXTURES;k++)
            {
                playerTexture[i][k].free();
            }
        }
    }
    currentTexture.free();
    //frees text textures for player's needs in UI.
    freeNeedsTextures();
}

void player::setCamera(SDL_Rect& camera)
{
    std::cout<<"\n running player::setCamera(SDL_Rect& camera)";
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

int player::getX()
{
    return playerX;
}

int player::getY()
{
    return playerY;
}

int player::getPVelX()
{
    return pVelX;
}

int player::getPVelY()
{
    return pVelY;
}

void player::setX(int x)
{
    playerX = x;
}

void player::setY(int y)
{
    playerY = y;
}

bool player::collisionDetector(SDL_Rect collidable)
{
    //std::cout<<"\n running player::collisionDetector(SDL_Rect collidable)";
    int playerLeft, collidableLeft;
    int playerRight, collidableRight;
    int playerTop, collidableTop;
    int playerBottom, collidableBottom;

    playerLeft = playerCollisionBox.x;
    playerRight = playerCollisionBox.x + playerCollisionBox.w;
    playerTop = playerCollisionBox.y;
    playerBottom = playerCollisionBox.y + playerCollisionBox.h;

    collidableLeft = collidable.x;
    collidableRight = collidable.x+collidable.w;
    collidableTop = collidable.y;
    collidableBottom = collidable.y + collidable.h;

    if( playerBottom <= collidableTop )
    {
        return false;
    }

    if( playerTop >= collidableBottom )
    {
        return false;
    }

    if( playerRight <= collidableLeft )
    {
        return false;
    }

    if( playerLeft >= collidableRight )
    {
        return false;
    }

    return true;
}

void player::modifyNeeds(int modNeedValues[])
{
    std::cout<<"\n running player::modifyNeeds(int modNeedValues[])";
    //sends in an array (shouldn't be larger than TOTAL_PLAYER_NEEDS), gives the sum of the need before and after mod,
    //adjusts for a need going under 0 or over 100
    for(int i = 0; i<TOTAL_PLAYER_NEEDS; i++)
    {
        need[i] += modNeedValues[i];
        if(need[i] > 100)
        {
            need[i] = 100;
        }
        else if(need[i] < 0)
        {
            need[i] = 0;
        }
    }
}

void player::freeNeedsTextures()
{
    std::cout<<"\n running player::freeNeedsTextures()";
    for(int i = 0; i < TOTAL_PLAYER_NEEDS; i++)
    {
        needsTexture[i].free();
    }
}

void player::loadNeedsTextures(SDL_Renderer* renderer, TTF_Font* font)
{//stage gets copied when it gets sent into a savegame function, can't do that with stringstream
    std::cout<<"\n running player::loadNeedsTextures(SDL_Renderer* renderer, TTF_Font* font)";
    SDL_Color textColor = {0,128,200};
    for (int i = 0; i< TOTAL_PLAYER_NEEDS; i++)
    {
        //need[i] = 5+(i*15);

        //playerNeeds[i].str("");
        //needsTexture[i].free();
        playerNeeds[i] = std::to_string(need[i]);// << need[i];
        if(!needsTexture[i].loadFromRenderedText(playerNeeds[i], textColor,font,renderer))
        {
            std::cout<<"\n unable to load playerNeeds["<<i<<"] string to needsTexture["<<i<<"]";
        }
    }
}

void player::reloadNeedsTextures(SDL_Renderer* renderer, TTF_Font* font)
{//when something happens that affects the players needs, the text texture for that
    //need needs to be reloaded before being rendered again
    std::cout<<"\n running player::reloadNeedsTextures(SDL_Renderer* renderer, TTF_Font* font)";
    SDL_Color textColor = {0,128,200};
    for (int i = 0; i< TOTAL_PLAYER_NEEDS; i++)
    {
        //need[i] = 10+(i*15);

        //playerNeeds[i].str("");
        needsTexture[i].free();
        playerNeeds[i] = std::to_string(need[i]);// << need[i];
        if(!needsTexture[i].loadFromRenderedText(playerNeeds[i], textColor,font,renderer))
        {
            std::cout<<"\n unable to load playerNeeds["<<i<<"] string to needsTexture["<<i<<"]";
        }
    }
}

void player::renderNeedsTextures(SDL_Renderer* renderer)
{
    for(int i = 0; i<TOTAL_PLAYER_NEEDS; i++)
    {
        needsTexture[i].render(20+(i*70),40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void player::loadSavedPlayerData(Uint32 dataValues[])
{
    std::cout<<"\n running loadSavedPlayerData(Uint32 dataValues[])";
    //load character needs from save
    for(int i = 0; i<TOTAL_PLAYER_NEEDS; i++)
    {
        need[i] = dataValues[i];
    }
}
