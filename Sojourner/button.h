#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

//buttons on the title screen + back button for screens like options
const int TOTAL_BUTTONS = 15;

const int BUTTON_WIDTH = 160;
const int BUTTON_HEIGHT = 120;

//buttons in the menubar plus save & quit button .
const static int TOTAL_CHAPTER_BUTTONS=9;
//new game, load game, options, credits, back button, chapters 1,2,3, and fullscreen on/off button.
const static int TOTAL_PREGAME_BUTTONS = 12;
//gamestate=6, stage1 buttons
const static int TOTAL_STAGE_BUTTONS = 1;

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
		bool fullScreen;
		bool musicOn;
		bool voiceOn;

		//Handles pre-game user interface mouse events (mainly button clicks, like new game, load game, options, credits, etc)
		int handlePGUIEvent( int gameState, std::string buttonName, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );
        //handles buttons while player is in a chapter (menu bar buttons like backline, backpage, auto text speed, auto text toggle, and save + exit button
		int handleChapterEvent( std::string buttonName, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );
        //handles mouse events in stages (currently not in use.
		int handleStageEvent( int gameState, std::string buttonName, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );


        Texture buttonTexture;

        bool setFullScreenOn(SDL_Window* window,SDL_Renderer* renderer);
        bool setFullScreenOff(SDL_Window* window,SDL_Renderer* renderer);

        bool setMusicOn();
        bool setMusicOff();

        bool setVoiceOn();
        bool setVoiceOff();


		std::string buttonName;

		std::string pregameButtonNames[TOTAL_PREGAME_BUTTONS];
		std::string chapterButtonNames[TOTAL_CHAPTER_BUTTONS];
		std::string stageButtonNames[TOTAL_STAGE_BUTTONS];
        //each button has a string that describes the button.
		void setChapterButtonName(int i);
		void setPregameButtonName(int i);
		void setStageButtonName(int i);
		//determines which texture to show in options screen, red or green.
		void fullScreenButtonTextureToggle(SDL_Renderer* renderer);
        void musicButtonTextureToggle(SDL_Renderer* renderer);
        void voiceButtonTextureToggle(SDL_Renderer* renderer);

	private:
		//Top left point of button image location
		SDL_Point position;

};

#endif // BUTTON_H
