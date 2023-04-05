#include "stage.h"

stage::stage()
{

}

stage::~stage()
{

}

void stage::freeButtons()
{//free button textures
    for(int i = 0; i < TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].buttonTexture.free();
    }
}

bool stage::setStageButtonTextures(SDL_Renderer* renderer, bool success)
{//stage button textures get loaded into array from array of string names, button positions set after.
    for( int i = 0; i < TOTAL_STAGE_BUTTONS; ++i )
    {
        std::stringstream ss;
        ss << "images/buttons/" << buttons[i].buttonName << ".png";
        std::string str = ss.str();
        success = buttons[i].buttonTexture.loadFromFile( str,renderer );
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

    return success;
}

void stage::setFileNames()
{  //filenames being specified
    bgFileName[0] = "images/thanks.png";
}

void stage::freeBGTextures()
{//free resources
    stage1BG[0].free();
}

void stage::loadFont()
{
    //load the font
	font = TTF_OpenFont( "fonts/NemoyLight.ttf", 16 );
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
    return success;
}

void stage::free()
{//free resources
    freeButtons();
    freeBGTextures();
    player1.freePlayer();
}

void stage::renderStage1(SDL_Renderer* renderer)
{//while stage scene is running this displays bgs,buttons, and player with updated positions.
    stage1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    player1.render(renderer);
    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}
