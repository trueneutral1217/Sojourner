#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

//buttons on the title screen + back button for screens like options
//const int TOTAL_BUTTONS = 15;

const int BUTTON_WIDTH = 103;
const int BUTTON_HEIGHT = 57;

//buttons in the menubar plus save & quit button .
//const static int TOTAL_CHAPTER_BUTTONS=9;
//new game, load game, options, credits, back button, chapters 1,2,3, and fullscreen on/off button.
const static int TOTAL_PREGAME_BUTTONS = 9;
//going to switch over to having each page load it's buttons at open, and free at close
const static int TOTAL_MAIN_BUTTONS = 4;
const static int TOTAL_NEWGAME_BUTTONS = 9;
const static int TOTAL_LOADGAME_BUTTONS = 9;
const static int TOTAL_OPTIONS_BUTTONS = 4;
const static int TOTAL_CREDITS_BUTTONS = 1;
//gamestate=6, stage1 buttons
//0=save/exit , 1=plant , 2=water, 3=sleep
const static int TOTAL_STAGE_BUTTONS = 10;

class button
{
    public:
		//Initializes internal variables
		button();
        ~button();

		//Sets top left position
		void setPosition( int x, int y );

		int getPositionX();
		int getPositionY();
		//options default is false for fullscreen, true for music and voice on.
		bool fullScreenToggle;
		bool musicToggle;
		bool voiceToggle;
		//true if mouse is over a button
		bool mouseOver;

		int chosenSave;

		//Handles pre-game user interface mouse events (mainly button clicks, like new game, load game, options, credits, etc)
		int handlePGUIEvent(SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );
        //handles buttons while player is in a chapter (menu bar buttons like backline, backpage, auto text speed, auto text toggle, and save + exit button
		//int handleChapterEvent( std::string buttonName, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );
        //handles mouse events in stages (currently not in use.
		int handleStageEvent( bool internalView, std::string buttonName, SDL_Event* e );


        Texture buttonTexture;
        Texture buttonMOTexture;

        void setFullScreenOn(SDL_Window* window,SDL_Renderer* renderer);
        void setFullScreenOff(SDL_Window* window,SDL_Renderer* renderer);

        void setMusicOn(SDL_Renderer* renderer);
        void setMusicOff(SDL_Renderer* renderer);

        void setVoiceOn(SDL_Renderer* renderer);
        void setVoiceOff(SDL_Renderer* renderer);

		std::string buttonName;

		std::string stageButtonNames[TOTAL_STAGE_BUTTONS];

		void setStageButtonName(int i);

		//determines which texture to show in options screen, red or green.
		void fullScreenButtonTextureToggle(SDL_Renderer* renderer);
        void musicButtonTextureToggle(SDL_Renderer* renderer);
        void voiceButtonTextureToggle(SDL_Renderer* renderer);

        void free();

	private:
		//Top left point of button image location
		SDL_Point position;

};

#endif // BUTTON_H
