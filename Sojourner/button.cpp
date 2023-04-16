#include "button.h"

button::button()
{
	position.x = 0;
	position.y = 0;
    buttonName = "";
    fullScreen=false;
    musicOn=true;
    voiceOn=true;
    mouseOver=false;
    //move buttons 0-7 to pregameui
    pregameButtonNames[0]="back";
	pregameButtonNames[1]="new";
	pregameButtonNames[2]="load";
	pregameButtonNames[3]="options";
	pregameButtonNames[4]="credits";
	pregameButtonNames[5]="chapter1";
	pregameButtonNames[6]="fullScreenOff";
	pregameButtonNames[7]="stage1";
	pregameButtonNames[8]="chapter2";
	pregameButtonNames[9]="chapter3";
	pregameButtonNames[10]="musicOn";
	pregameButtonNames[11]="voiceOn";

	//move buttons 8-15 to chapter
	chapterButtonNames[0]="backPage";
	chapterButtonNames[1]="backLine";
	chapterButtonNames[2]="autoOn";
	chapterButtonNames[3]="autoOff";
	chapterButtonNames[4]="autoSpeed1";
	chapterButtonNames[5]="autoSpeed2";
	chapterButtonNames[6]="autoSpeed3";
    chapterButtonNames[7]="saveAndExit";
    chapterButtonNames[8]="nextPage";

    stageButtonNames[0]="saveAndExit";

    //buttonTexture=NULL;
}

button::~button()
{
    buttonTexture.free();
}

void button::fullScreenButtonTextureToggle(SDL_Renderer* renderer)
{
    buttonTexture.free();
    if(fullScreen)
    {
        buttonTexture.loadFromFile("images/buttons/fullScreenOn.png", renderer);
    }
    else
    {
        buttonTexture.loadFromFile("images/buttons/fullScreenOff.png", renderer);
    }
    buttonTexture.render(getPositionX(),getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void button::musicButtonTextureToggle(SDL_Renderer* renderer)
{
    buttonTexture.free();
    if(musicOn)
    {
        buttonTexture.loadFromFile("images/buttons/musicOn.png", renderer);
    }
    else
    {
        buttonTexture.loadFromFile("images/buttons/musicOff.png", renderer);
    }
    buttonTexture.render(getPositionX(),getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void button::voiceButtonTextureToggle(SDL_Renderer* renderer)
{
    buttonTexture.free();
    if(voiceOn)
    {
        buttonTexture.loadFromFile("images/buttons/voiceOn.png", renderer);
    }
    else
    {
        buttonTexture.loadFromFile("images/buttons/voiceOff.png", renderer);
    }
    buttonTexture.render(getPositionX(),getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void button::setPosition( int x, int y )
{
	position.x = x;
	position.y = y;
}

int button::getPositionX()
{
    return position.x;
}
int button::getPositionY()
{
    return position.y;
}

bool button::setFullScreenOn(SDL_Window* window,SDL_Renderer* renderer)
{
    fullScreen = true;
    SDL_SetWindowFullscreen( window, SDL_TRUE );
    return fullScreen;
}

bool button::setFullScreenOff(SDL_Window* window,SDL_Renderer* renderer)
{
    fullScreen = false;
    SDL_SetWindowFullscreen( window, SDL_FALSE );
    return fullScreen;
}

bool button::setMusicOn()
{
    musicOn = true;
    return musicOn;
}

bool button::setMusicOff()
{
    musicOn=false;
    return musicOn;
}

bool button::setVoiceOn()
{
    voiceOn = true;
    return voiceOn;
}

bool button::setVoiceOff()
{
    voiceOn = false;
    return voiceOn;
}

void button::setChapterButtonName(int i)
{
    buttonName=chapterButtonNames[i];
}

void button::setPregameButtonName(int i)
{
    buttonName=pregameButtonNames[i];
}

void button::setStageButtonName(int i)
{
    buttonName=stageButtonNames[i];
}

int button::handlePGUIEvent(int gameState, std::string buttonName, SDL_Event* e, SDL_Window* window, SDL_Renderer* renderer )
{
    //If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > position.x + buttonTexture.getWidth() )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + buttonTexture.getHeight() )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
            mouseOver=false;
            //std::cout << "\n mouseOver: " << std::to_string( mouseOver );
		}
		//Mouse is inside button
		else
		{
		    mouseOver=true;

		    //if(buttonName=="new")
            //{
                //std::cout<<"new game button mouseover == true";
                //std::cout << "\n mouseOver: " << std::to_string( mouseOver );
            //}

                switch( e->type )
                {
                    case SDL_MOUSEBUTTONDOWN:
                        if(gameState==0)
                        {//button pressed in main screen
                            if(buttonName=="new")
                            {
                                printf("\n \n new game button pressed \n \n");
                                gameState = 1;
                            }
                            else if(buttonName=="load")
                            {
                                printf("\n \n load game button pressed \n \n");
                                gameState = 2;
                            }
                            else if(buttonName=="options")
                            {
                                printf("\n \n options button pressed \n \n");
                                gameState = 3;
                            }
                            else if(buttonName=="credits")
                            {
                                printf("\n \n credits button pressed \n \n");
                                gameState = 4;
                            }
                        }
                        else if(gameState==1)
                        {//button pressed in newgame screen
                            if(buttonName=="back")
                            {
                                printf("\n \n back button pressed from newgame \n \n");
                                gameState = 0;
                            }
                            else if(buttonName=="chapter1")
                            {
                                printf("\n \n chapter 1 button pressed from newgame \n \n");
                                gameState = 5;
                            }
                        }
                        else if(gameState==2)
                        {//button pressed in loadgame screen
                            if(buttonName=="back")
                            {
                                printf("\n \n back button pressed from loadgame \n \n");
                                gameState = 0;
                            }
                            else if(buttonName=="chapter1")
                            {
                                printf("\n \n chapter 1 button pressed from loadgame \n \n");
                                gameState = 5;
                            }
                            else if(buttonName=="chapter2")
                            {
                                printf("\n \n chapter 2 button pressed from loadgame \n \n");
                                gameState = 7;
                            }
                            else if(buttonName=="chapter3")
                            {
                                printf("\n \n chapter 3 button pressed from loadgame \n \n");
                                gameState = 8;
                            }
                            else if(buttonName=="stage1")
                            {
                                printf("\n \n stage 1 button pressed from loadgame \n \n");
                                gameState = 6;
                            }
                        }
                        else if(gameState==3)
                        {
                            if(buttonName=="back")
                            {
                                printf("\n \n back button pressed from options \n \n");
                                gameState = 0;
                            }
                            else if(buttonName=="fullScreenOff")
                            {
                                printf("\n \n fullScreenOff button pressed \n \n");
                                if(!fullScreen)
                                    setFullScreenOn(window,renderer);
                                else
                                    setFullScreenOff(window,renderer);
                                gameState = 3;
                            }
                            else if(buttonName=="musicOn")
                            {
                                printf("\n \n musicOn button pressed \n \n");
                                if(!musicOn)
                                    setMusicOn();
                                else
                                    setMusicOff();
                                gameState = 3;
                            }
                            else if(buttonName=="voiceOn")
                            {
                                printf("\n \n voiceOn button pressed \n \n");
                                if(!voiceOn)
                                    setVoiceOn();
                                else
                                    setVoiceOff();
                                gameState = 3;
                            }
                        }
                        else if(gameState==4)
                        {
                            if(buttonName=="back")
                            {
                                printf("\n \n back button pressed from credits \n \n");
                                gameState = 0;
                            }
                        }
                        break;
                }

		}
	}
	return gameState;
}

int button::handleChapterEvent( std::string buttonName, SDL_Event* e, SDL_Window* window, SDL_Renderer* renderer )
{
    int buttonClicked = 0;
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > position.x + buttonTexture.getWidth() )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + buttonTexture.getHeight() )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
            buttonClicked=0;
		}
		//Mouse is inside button
		else
		{
                switch( e->type )
                {
                    case SDL_MOUSEBUTTONDOWN:

                        //stage 1 not currently implemented
                        /*
                        else if(buttonName=="stage1" && gameState==2)
                        {
                            printf("\n \n Stage 1 button pressed \n \n");
                            gameState = 6;
                        }*/
                        if(buttonName=="saveAndExit")
                        {
                            printf("\n \n saveAndExit button pressed \n \n");
                            buttonClicked=1;
                        }
                        else if(buttonName=="backPage")
                        {
                            printf("\n \n backPage button pressed \n \n");
                            buttonClicked=2;
                        }
                        else if(buttonName=="backLine")
                        {
                            printf("\n \n backLine button pressed \n \n");
                            buttonClicked=3;
                        }
                        else if(buttonName=="autoOn")
                        {
                            printf("\n \n autotexton button pressed \n \n");
                            buttonClicked=4;
                        }
                        else if(buttonName=="autoOff")
                        {
                            printf("\n \n autotextoff button pressed \n \n");
                            buttonClicked=5;
                        }
                        else if(buttonName=="autoSpeed1")
                        {
                            printf("\n \n autospeed1 button pressed \n \n");
                            buttonClicked=6;
                        }
                        else if(buttonName=="autoSpeed2")
                        {
                            printf("\n \n autospeed2 button pressed \n \n");
                            buttonClicked=7;
                        }
                        else if(buttonName=="autoSpeed3")
                        {
                            printf("\n \n autospeed3 button pressed \n \n");
                            buttonClicked=8;
                        }
                        else if(buttonName=="nextPage")
                        {
                            printf("\n \n nextPage button pressed \n \n");
                            buttonClicked=9;
                        }
                    break;
                }
		}
	}
	return buttonClicked;
}

int button::handleStageEvent(std::string buttonName, SDL_Event* e, SDL_Window* window, SDL_Renderer* renderer )
{
    int buttonClicked = 0;
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > position.x + buttonTexture.getWidth() )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + buttonTexture.getHeight() )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
            buttonClicked=0;
		}
		//Mouse is inside button
		else
		{
                switch( e->type )
                {
                    case SDL_MOUSEBUTTONDOWN:

                        if(buttonName=="saveAndExit")
                        {
                            printf("\n \n saveAndExit button pressed \n \n");
                            buttonClicked=1;
                        }


                    break;
                }
		}
	}
	return buttonClicked;
}
