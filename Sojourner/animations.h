#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Texture.h"


const int TAO_ANIMATION_FRAMES = 8;
const int TOASTER_ANIMATION_FRAMES = 8;
//I've made a second toaster, I'm testing out walking animation.
const int TOASTER2_ANIMATION_FRAMES = 3;
//these don't do anything in this project currently, will probably remove eventually.
const int BLACKSTAR_ANIMATION_FRAMES=9;
const int PORTAL_ANIMATION_FRAMES=20;
const int RAT_ANIMATION_FRAMES=11;
const int TRAILER_ANIMATION_FRAMES=16;
//used in opening sequence during house scene.
const int BUSH_ANIMATION_FRAMES = 4;

const int LEFTCURTAIN_ANIMATION_FRAMES = 4;
const int RIGHTCURTAIN_ANIMATION_FRAMES = 4;


class animations
{
    public:
        //constructor
        animations();
        //destructor
        ~animations();

        //timer for tao animation
        timer animationTimer;

        //timer for toaster the robot's animation
        timer animationTimer2;
        //timer for toaster the robot's 2nd animation.
        timer animationTimer3;

        //timer for black stars
        timer animationTimer4;
        timer animationTimer5;
        timer animationTimer6;
        timer animationTimer7;

        //portal timer
        timer animationTimer8;
        //rat animationTimer
        timer animationTimer9;
        //trailer animationTimer
        timer animationTimer10;
        //bush animation timer
        timer animationTimer11;

        timer animationTimer12;

        timer animationTimer13;

        bool aniCountUp;

        //tracker for the frame of the animation being used
        int aniFrame,aniFrame2;
        //track bush animation frame
        int aniFrame11;
        //for the curtains in the house scene.
        int aniFrame12,aniFrame13;


        //animation textures
        Texture toaster[TOASTER_ANIMATION_FRAMES];
        Texture bush[BUSH_ANIMATION_FRAMES];
        Texture leftCurtain[LEFTCURTAIN_ANIMATION_FRAMES];
        Texture rightCurtain[RIGHTCURTAIN_ANIMATION_FRAMES];

        //bool setAnimationTextures(SDL_Renderer* renderer);
        bool loadCreditsAnimationTextures(SDL_Renderer* renderer);

        void loadBushAnimationTextures(SDL_Renderer* renderer);

        void loadLeftCurtainAnimationTextures(SDL_Renderer* renderer);

        void loadRightCurtainAnimationTextures(SDL_Renderer* renderer);

        void freeCreditsAnimationTextures();

        void freeBushAnimationTextures();

        void freeLeftCurtainAnimationTextures();

        void freeRightCurtainAnimationTextures();

        //void freeAnimationTextures();

        void renderToaster(SDL_Renderer* renderer);

        //renders bush during house scene of opening sequence.
        void renderBush(SDL_Renderer* renderer);

        void renderLeftCurtain(SDL_Renderer* renderer);

        void renderRightCurtain(SDL_Renderer* renderer);

        void cycleAnimations();
        void oscillateCount();


        //void taoAnimationProgress();
        void toasterAnimationProgress();
        //progresses the bush animation during house scene of opening sequence.
        void bushAnimationProgress();

        void leftCurtainAnimationProgress();

        void rightCurtainAnimationProgress();

        //consolidates executing progress & cycle animations functions
        void progress();

        //reset animations when player leaves the page that animation is on.
        //void resetPortal();
        //void resetToaster2();

    private:

};

#endif // ANIMATIONS_H
