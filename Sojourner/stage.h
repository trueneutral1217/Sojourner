#ifndef STAGE_H
#define STAGE_H

//#include "Texture.h"
//#include "timer.h"
//#include "button.h"
#include "player.h"
#include "parallax.h"
//#include "saveGame.h"
//#include "station.h"
#include "ship.h"

//these are the parallax images used for the bg's.
const static int TOTAL_STAGE_BACKGROUNDS = 6;
//number of UI images
const int TOTAL_STAGE_UI = 1;

class stage
{
    public:
        //constructor
        stage();
        //destructor
        ~stage();
        //show externalView at start, external gets triggered at mouse movement, gonna have to fix that.
        bool externalView;
        //internal view keys internal habitat backgrounds to be rendered, stops rendering external background
        bool internalView;
        //player should not be displayed while in externalView
        bool showPlayer;
        //these will likely be saved just to remember the player's location correctly.
        bool inHab, inEng;

        bool buttonsFreed;


        //internal habitat needs 2 Y values for background rendering (parallax based on player Y-axis velocity at threshold points)
        int habInternalY1;
        int habInternalY2;
        //handling it like habInternal variables currently.
        int engInternalY1;
        int engInternalY2;

        int timeSurvived;

        Texture daysSurvived;
        Texture hoursSurvived;
        Texture minutesSurvived;



        //declare font
        TTF_Font *font;
        //temporary texture for stage background
        Texture thanksTexture;
        //stars going by in bg.
        parallax starsFore;
        parallax starsMid;
        parallax starsBack;
        //message of courage in external view
        std::string courage;
        //text texture for message of courage
        Texture courageTexture;
        //buttons for stage UI.
        button buttons[TOTAL_STAGE_BUTTONS];
        //array of background image names.
        std::string bgFileName[TOTAL_STAGE_BACKGROUNDS];
        //array of background images for stage1
        Texture stage1BG[TOTAL_STAGE_BACKGROUNDS];
        //UI image names
        std::string uiFileName[TOTAL_STAGE_UI];
        //UI texture(s) for stage
        Texture UI[TOTAL_STAGE_UI];
        //free resources
        void freeButtons();
        void freeBGTextures();
        void freeUITextures();
        //handles movement and rendering for parallax images
        void starsHandleParallax(SDL_Renderer* renderer);
        //button textures are applied via button names from button class
        bool setStageButtonTextures(SDL_Renderer* renderer, bool success);
        //background textures are applied via bgFileName array above.
        bool setStageTextures(SDL_Renderer* renderer);
        //bgFileName array is filled by this function
        void setFileNames();
        //set button names
        void setButtonNames();
        //user clicks a button in stage
        void handleStageButtonPresses(SDL_Renderer* renderer, int gameState);
        //handle stage button presses will be called in this function which is more over-arching
        int handleButtons(SDL_Renderer* renderer, SDL_Event* e );

        //declare player
        player player1;
        //declare station
        //station station;
        //declare ship
        ship ship;
        //loads resources at opening of stages.
        bool loadStage(SDL_Renderer* renderer, bool inHab, bool inEng, bool success);
        //free resources
        void free();
        //renders stages during play.
        void renderStage1(SDL_Renderer* renderer);
        //stage font is different from gohomeless chapter font
        void loadFont();
        //renders the habitat internal background images.
        void habInternalHandleParallax(SDL_Renderer* renderer);
        //renders internal engineering by bg images
        void engInternalHandleParallax(SDL_Renderer* renderer);
        //updates the Y coords for habitat background
        void move(int countedFrames);
        //new game created, this sets player coords and bg coords for hab internal view
        void setNewgameVars();
        //loads saved data from savesfile (player coords, location in habitat)
        void loadSavedGameData(Uint32 dataValues[]);
        //handles station interaction textures and updates station texture
        void handleStation(SDL_Renderer* renderer, TTF_Font* font);
        //
        void freeStationButtons();
        //
        void loadTimeSurvivedTextures(SDL_Renderer* renderer);
        //
        void renderTimeSurvivedTextTextures(SDL_Renderer* renderer);
        //
        void freeTimeSurvivedTextures();
        //refreshes the text textures for time survived so they render the correct TS.
        void refreshTS(SDL_Renderer* renderer);

    private:

};

#endif // STAGE_H
