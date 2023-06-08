#include "stage.h"

stage::stage()
{
    internalView=false;
    externalView=true;
    showPlayer=false;
    habInternalY1=0;
    habInternalY2=-600;
}

stage::~stage()
{

}

void stage::freeButtons()
{//free button textures
    for(int i = 0; i < TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].buttonTexture.free();
        buttons[i].buttonMOTexture.free();
    }
}

bool stage::setStageButtonTextures(SDL_Renderer* renderer, bool success)
{//stage button textures get loaded into array from array of string names, button positions set after.
    for( int i = 0; i < TOTAL_STAGE_BUTTONS; ++i )
    {
        std::stringstream ss;
        std::stringstream ssMO;
        ss << "images/buttons/" << buttons[i].buttonName << ".png";
        ssMO << "images/buttons/" << buttons[i].buttonName << "MO.png";
        std::string str = ss.str();
        std::string str2 = ssMO.str();
        success = buttons[i].buttonTexture.loadFromFile( str,renderer );
        success = buttons[i].buttonMOTexture.loadFromFile( str2,renderer );
        //buttons[ i ].setPosition( ((i*160)-80), SCREEN_HEIGHT - 140 );
    }
    //save and exit
    buttons[0].setPosition(600,20);
    return success;
}

void stage::setButtonNames()
{//array of buttons filled by button names from function in button class.
    for(int i = 0; i < TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].setStageButtonName(i);
    }
}

bool stage::setStageTextures(SDL_Renderer* renderer)
{  //stage background textures loaded from bgFileName array.
    bool success = true;
    setFileNames();
    for(int i = 0; i<TOTAL_STAGE_BACKGROUNDS;i++)
    {
        success = stage1BG[i].loadFromFile( bgFileName[i],renderer );
    }
    success = starsFore.parallaxTexture.loadFromFile("images/starlaxfore.png",renderer);
    success = starsMid.parallaxTexture.loadFromFile("images/starlaxmid.png",renderer);
    success = starsBack.parallaxTexture.loadFromFile("images/starlaxback.png",renderer);

    return success;
}

void stage::setFileNames()
{  //filenames being specified
    bgFileName[0] = "images/blackground.png";
    bgFileName[1] = "images/outerShip1.png";
    bgFileName[2] = "images/habitation1.png";
    bgFileName[3] = "images/habitation2.png";

}

void stage::freeBGTextures()
{//free resources
    for(int i = 0; i<TOTAL_STAGE_BACKGROUNDS;i++)
    {
        stage1BG[i].free();
    }
    starsFore.freeParallaxTexture();
    starsMid.freeParallaxTexture();
    starsBack.freeParallaxTexture();
}

void stage::loadFont()
{
    //load the font
	font = TTF_OpenFont( "fonts/NemoyMedium.ttf", 16 );
}

bool stage::loadStage(SDL_Renderer* renderer, bool success)
{//stage file names get set and loaded into texture arrays, player gets loaded from player class.
    setButtonNames();
    //updates font to stage font.
    loadFont();
    //load stage button textures and positions
    success = setStageButtonTextures(renderer,success);
    //set stage bg texture
    success = setStageTextures(renderer);
    //load player texture
    player1.loadPlayer(renderer);
    station.loadStation(renderer);
    return success;
}

void stage::free()
{//free resources
    freeButtons();
    freeBGTextures();
    player1.freePlayer();
}

void stage::handleStageButtonPresses(int buttonClicked,SDL_Renderer* renderer)
{
    if(buttonClicked==1)
    {//player clicked save & exit
        //voice.stopVoice();
        internalView = false;
        showPlayer = false;
        externalView = true;
    }
    else if(buttonClicked==2)
    {
        internalView=true;
        showPlayer=true;
        externalView=false;
    }
}

void stage::renderStage1(SDL_Renderer* renderer)
{//while stage scene is running this displays bgs,buttons, and player with updated positions.
    stage1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    starsHandleParallax(renderer);
    if(externalView)
    {//renders the exterior of the ship
        stage1BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    else if(internalView)
    {//renders the interior of the ship (supposed to parallax as player walks up or down.
        habInternalHandleParallax(renderer);
    }
    if(buttons[0].mouseOver==false)
    {
        buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    else
    {
        buttons[0].buttonMOTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(internalView)
    {
        station.renderStation(renderer);
    }
    if(showPlayer)
    {//player is shown if internalView is on.
        player1.render(renderer);
    }
}

void stage::starsHandleParallax(SDL_Renderer* renderer)
{//space parallax
    //slows down the animation of the parallax backgrounds
    SDL_Delay(10);
    //parallax rendering
    starsBack.parallaxRender(renderer);
    starsMid.parallaxRender(renderer);
    starsFore.parallaxRender(renderer);
    // parallax incrementation
    starsFore.incrementFore();
    starsMid.incrementMid();
    starsBack.incrementBack();
}

void stage::habInternalHandleParallax(SDL_Renderer* renderer)
{
    stage1BG[2].render(0,habInternalY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    stage1BG[3].render(0,habInternalY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void stage::move(int countedFrames)
{
    if( player1.getY() == 360 && player1.getPVelY() > 0 )
    {//player is heading down after hitting lower threshold.

        //y value of hab background continues to decrease as it moves up the screen
        if(habInternalY1 < -599)//if hab y value is -600 or less, reset hab background position to bottom of screen
        {
            habInternalY1 = 600;
        }
        if(habInternalY2 < -599)
        {
            habInternalY2 = 600;
        }

        habInternalY1-=player1.getPVelY();
        habInternalY2-=player1.getPVelY();

        std::cout<<"\n habY1: "<<habInternalY1<<", habY2: "<<habInternalY2;
    }
    if(player1.getY()==160 && player1.getPVelY()<0)//player is heading up,bg scrolling down
    {


        if(habInternalY1 > 599)
        {
            habInternalY1 = -600;
        }
        if(habInternalY2 > 599)
        {
            habInternalY2 = -600;
        }

        habInternalY1-=player1.getPVelY();
        habInternalY2-=player1.getPVelY();
        std::cout<<"\n habY1: "<<habInternalY1<<", habY2: "<<habInternalY2;
    }
    player1.move(countedFrames,station.collidable,station.STATIONS);
    station.updatePosition(habInternalY1);
}

void stage::setNewgameVars()
{
    player1.setX(380);
    player1.setY(260);
    habInternalY1 = 0;
    habInternalY2 = -600;
    //externalView=true;
}


void stage::loadSavedGameData(Uint32 d1,Uint32 d2, Uint32 d3, Uint32 d4)
{
    player1.setX(d1);
    player1.setY(d2);
    //load habitat Y1 and Y2 coords from safe file
    habInternalY1 = d3;
    habInternalY2 = d4;
}

