#ifndef STAGE_H
#define STAGE_H

#include "Texture.h"
//#include "timer.h"
#include "button.h"
#include "player.h"
#include "parallax.h"

const static int TOTAL_STAGE_BACKGROUNDS = 4;

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
        //internal habitat needs 2 Y values for background rendering (parallax based on player Y-axis velocity at threshold points)
        int habInternalY1;
        int habInternalY2;

        //declare font
        TTF_Font *font;
        //temporary texture for stage background
        Texture thanksTexture;
        //stars going by in bg.
        parallax starsFore;
        parallax starsMid;
        parallax starsBack;
        //buttons for stage UI.
        button buttons[TOTAL_STAGE_BUTTONS];
        //array of background image names.
        std::string bgFileName[TOTAL_STAGE_BACKGROUNDS];
        //array of background images for stage1
        Texture stage1BG[TOTAL_STAGE_BACKGROUNDS];
        //free resources
        void freeButtons();
        void freeBGTextures();
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
        void handleStageButtonPresses(int gameState,SDL_Renderer* renderer);
        //declare player
        player player1;
        //loads resources at opening of stages.
        bool loadStage(SDL_Renderer* renderer, bool success);
        //free resources
        void free();
        //renders stages during play.
        void renderStage1(SDL_Renderer* renderer);
        //stage font is different from gohomeless chapter font
        void loadFont();
        //renders the habitat internal background images.
        void habInternalHandleParallax(SDL_Renderer* renderer);
        //updates the Y coords for habitat background
        void move();
        //new game created, this sets player coords and bg coords for hab internal view
        void setNewgameVars();

    private:

};

#endif // STAGE_H
