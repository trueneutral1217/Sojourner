#include "button.h"

button::button()
{
	position.x = 0;
	position.y = 0;
    buttonName = "";
    fullScreenToggle=false;
    musicToggle=true;
    voiceToggle=true;
    mouseOver=false;
    stageButtonNames[0]="saveAndExit";
    stageButtonNames[1]="plant";
    stageButtonNames[2]="waterPlants";
}

button::~button()
{
    buttonTexture.free();
}

void button::fullScreenButtonTextureToggle(SDL_Renderer* renderer)
{
    buttonTexture.free();
    if(fullScreenToggle)
    {
        buttonTexture.loadFromFile("images/buttons/fullScreenOn.png", renderer);
    }
    else
    {
        buttonTexture.loadFromFile("images/buttons/fullScreenToggle.png", renderer);
    }
}

void button::musicButtonTextureToggle(SDL_Renderer* renderer)
{
    buttonTexture.free();
    if(musicToggle)
    {
        buttonTexture.loadFromFile("images/buttons/musicToggle.png", renderer);
    }
    else
    {
        buttonTexture.loadFromFile("images/buttons/musicOff.png", renderer);
    }
}

void button::voiceButtonTextureToggle(SDL_Renderer* renderer)
{
    buttonTexture.free();
    if(voiceToggle)
    {
        buttonTexture.loadFromFile("images/buttons/voiceToggle.png", renderer);
    }
    else
    {
        buttonTexture.loadFromFile("images/buttons/voiceOff.png", renderer);
    }
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

void button::setFullScreenOn(SDL_Window* window,SDL_Renderer* renderer)
{
    fullScreenToggle = true;
    fullScreenButtonTextureToggle(renderer);
    SDL_SetWindowFullscreen( window, SDL_TRUE );
}

void button::setFullScreenOff(SDL_Window* window,SDL_Renderer* renderer)
{
    fullScreenToggle = false;
    fullScreenButtonTextureToggle(renderer);
    SDL_SetWindowFullscreen( window, SDL_FALSE );
}

void button::setMusicOn(SDL_Renderer* renderer)
{
    musicToggle = true;
    musicButtonTextureToggle(renderer);
}

void button::setMusicOff(SDL_Renderer* renderer)
{
    musicToggle=false;
    musicButtonTextureToggle(renderer);
}

void button::setVoiceOn(SDL_Renderer* renderer)
{
    voiceToggle = true;
    voiceButtonTextureToggle(renderer);
}

void button::setVoiceOff(SDL_Renderer* renderer)
{
    voiceToggle = false;
    voiceButtonTextureToggle(renderer);
}

void button::setStageButtonName(int i)
{
    buttonName=stageButtonNames[i];
}

int button::handlePGUIEvent(SDL_Event* e, SDL_Window* window, SDL_Renderer* renderer )
{
    int gameState=-1;
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
		}
		//Mouse is inside button
		else
		{
		    if(!mouseOver)
            {
                std::cout<<"\n \n mouseOver = true, buttonName: "<<buttonName;
                mouseOver=true;
		    }
            switch( e->type )
            {
                case SDL_MOUSEBUTTONDOWN:
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
                        else if(buttonName=="back")
                        {
                            printf("\n \n back button pressed \n \n");
                            gameState = 0;
                        }
                        else if(buttonName=="save1")
                        {
                            printf("\n \n save 1 button pressed \n \n");
                            chosenSave=0;
                            std::cout<<"\n chosen save: "<<chosenSave;
                            gameState = 5;
                        }
                        else if(buttonName=="save2")
                        {
                            printf("\n \n save 2 button pressed \n \n");
                            chosenSave=1;
                            std::cout<<"\n chosen save: "<<chosenSave;
                            gameState = 5;
                        }
                        else if(buttonName=="save3")
                        {
                            printf("\n \n save 3 button pressed \n \n");
                            chosenSave=2;
                            std::cout<<"\n chosen save: "<<chosenSave;
                            gameState = 5;
                        }
                        else if(buttonName=="trash1")
                        {
                            printf("\n \n trash1 button pressed \n \n");
                            gameState = 1;
                        }
                        else if(buttonName=="trash2")
                        {
                            printf("\n \n trash2 button pressed \n \n");
                            gameState = 2;
                        }
                        else if(buttonName=="trash3")
                        {
                            printf("\n \n trash3 button pressed \n \n");
                            gameState = 3;
                        }
                        else if(buttonName=="yes")
                        {
                            printf("\n \n yes button pressed \n \n");
                            gameState = 4;
                            //this button needs a way to delete the save data for the savegame that corresponds to
                            //the trashcan that was clicked.
                        }
                        else if(buttonName=="no")
                        {
                            printf("\n \n no button pressed \n \n");
                            gameState = 6;
                        }
                        else if(buttonName=="fullScreenToggle")
                        {
                            printf("\n \n fullScreen toggle button pressed \n \n");
                            if(!fullScreenToggle)
                                setFullScreenOn(window,renderer);
                            else
                                setFullScreenOff(window,renderer);
                            gameState = 3;
                        }
                        else if(buttonName=="musicToggle")
                        {
                            printf("\n \n music toggle button pressed \n \n");
                            if(!musicToggle)
                                setMusicOn(renderer);
                            else
                                setMusicOff(renderer);
                            gameState = 3;
                        }
                        else if(buttonName=="voiceToggle")
                        {
                            printf("\n \n voice toggle button pressed \n \n");
                            if(!voiceToggle)
                                setVoiceOn(renderer);
                            else
                                setVoiceOff(renderer);
                            gameState = 3;
                        }
                    break;
            }
		}
	}
	return gameState;
}

int button::handleStageEvent(bool internalView,std::string buttonName, SDL_Event* e )
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
		//std::cout<<"\n inside: "<<inside;
        //std::cout<<"\n mouse X: "<<x<<" mouse Y: "<<y;
		//Mouse is outside button
		if( !inside )
		{
		    mouseOver=false;
            buttonClicked=0;
            if(e->type == SDL_MOUSEBUTTONDOWN && !internalView)
            {
                buttonClicked=2;
            }
		}
		//Mouse is inside button
		else
		{
		    if(!mouseOver)
            {
                std::cout<<"\n \n mouseOver = true, buttonName: "<<buttonName;
                mouseOver=true;
		    }
                switch( e->type )
                {
                    case SDL_MOUSEBUTTONDOWN:

                        if(buttonName=="saveAndExit")
                        {
                            printf("\n \n saveAndExit button pressed");
                            buttonClicked=1;
                        }
                        else if(buttonName == "plant")
                        {
                            std::cout<<"\n user clicked 'plant' button";
                            buttonClicked = 3;
                        }
                        else if(buttonName == "waterPlants")
                        {
                            std::cout<<"\n user clicked 'waterPlants' button";
                            buttonClicked = 4;
                        }
                        else if(buttonName == "sleep")
                        {
                            std::cout<<"\n user clicked 'sleep' button";
                            buttonClicked = 5;
                        }
                    break;
                }
		}
	}
	return buttonClicked;
}

void button::free()
{   //frees button textures, clears the button name, sets position to 0,0.
    std::cout<<"\n running button::free()";
    buttonTexture.free();
    buttonMOTexture.free();
    buttonName = "";
    setPosition(0,0);
}
