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
const int BUSH_ANIMATION_FRAMES = 2;


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

        bool aniCountUp;

        //tracker for the frame of the animation being used
        int aniFrame,aniFrame2,aniFrame3;

        //aniFrame4, 5,6,and 7 are for the blackstar animations
        int aniFrame4,aniFrame5,aniFrame6,aniFrame7;
        //for the portal animation
        int aniFrame8;
        //keeps track of frame for rat animation
        int aniFrame9;
        //track trailer frame
        int aniFrame10;
        //track bush animation frame
        int aniFrame11;
        //creating 4 blackstar animations with random x/y coords to be displayed
        int bsX1,bsX2,bsX3,bsX4,bsY1,bsY2,bsY3,bsY4;

        //variable coordinates for animations
        int portalY;
        int toaster2X;

        //animation textures
        Texture tao[TAO_ANIMATION_FRAMES];
        Texture toaster[TOASTER_ANIMATION_FRAMES];
        Texture toaster2[TOASTER2_ANIMATION_FRAMES];
        Texture blackstar[BLACKSTAR_ANIMATION_FRAMES];
        Texture portal[PORTAL_ANIMATION_FRAMES];
        Texture rat[RAT_ANIMATION_FRAMES];
        Texture trailer[TRAILER_ANIMATION_FRAMES];
        Texture bush[BUSH_ANIMATION_FRAMES];

        //bool setAnimationTextures(SDL_Renderer* renderer);
        bool loadCreditsAnimationTextures(SDL_Renderer* renderer);

        void loadBushAnimationTextures(SDL_Renderer* renderer);

        void freeCreditsAnimationTextures();

        void freeBushAnimationTextures();

        //void freeAnimationTextures();

        //void renderTao(SDL_Renderer* renderer);
        void renderToaster(SDL_Renderer* renderer);
        //void renderToaster2(SDL_Renderer* renderer);
        //void renderBlackstar(SDL_Renderer* renderer);
        //void renderPortal(SDL_Renderer* renderer);
        //void renderRat(SDL_Renderer* renderer);
        //void renderTrailer(SDL_Renderer* renderer);
        //renders bush during house scene of opening sequence.
        void renderBush(SDL_Renderer* renderer);

        void cycleAnimations();
        void oscillateCount();


        //void taoAnimationProgress();
        void toasterAnimationProgress();
        //progresses the bush animation during house scene of opening sequence.
        void bushAnimationProgress();
        //void toaster2AnimationProgress();
        //void blackstarAnimationProgress();
        //void portalAnimationProgress();
        //void ratAnimationProgress();
        //void trailerAnimationProgress();

        //consolidates executing progress & cycle animations functions
        void progress();

        //reset animations when player leaves the page that animation is on.
        //void resetPortal();
        //void resetToaster2();

    private:

};

#endif // ANIMATIONS_H
