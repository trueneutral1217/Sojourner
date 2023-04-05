#ifndef STAGE_H
#define STAGE_H

#include "Texture.h"
//#include "timer.h"
#include "button.h"
#include "player.h"

const static int TOTAL_STAGE_BACKGROUNDS = 1;

class stage
{
    public:
        //constructor
        stage();
        //destructor
        ~stage();
        //declare font
        TTF_Font *font;
        //temporary texture for stage background
        Texture thanksTexture;
        //buttons for stage UI.
        button buttons[TOTAL_STAGE_BUTTONS];
        //array of background image names.
        std::string bgFileName[TOTAL_STAGE_BACKGROUNDS];
        //array of background images for stage1
        Texture stage1BG[TOTAL_STAGE_BACKGROUNDS];
        //free resources
        void freeButtons();
        void freeBGTextures();
        //button textures are applied via button names from button class
        bool setStageButtonTextures(SDL_Renderer* renderer, bool success);
        //background textures are applied via bgFileName array above.
        bool setStageTextures(SDL_Renderer* renderer);
        //bgFileName array is filled by this function
        void setFileNames();
        //set button names
        void setButtonNames();
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

    private:

};

#endif // STAGE_H
