#ifndef PARALLAX_H
#define PARALLAX_H

#include "Texture.h"


/*
SDL_Rect starlax;
starlax.x = 0;
starlax.y = 0;
starlax.w = 800;
starlax.h = 600;

SDL_Rect starlax2;
starlax2.x = -799;
starlax2.y = 0;
starlax2.w = 800;
starlax2.h = 600;
*/

const int PARALLAX_WIDTH = 800;
const int PARALLAX_HEIGHT = 600;


class parallax
{
    public:
		//Initializes internal variables
		parallax();
        ~parallax();

        Texture parallaxTexture;

        SDL_Rect parallaxRect1;
        SDL_Rect parallaxRect2;

        void incrementBack();
        void incrementFore();
        void incrementMid();
        void incrementAnteriorMid();

        void specialIncrementFore();

        //might be able to privatize. both of the following functions
        void resetParallax();
        void updateRects();

        void specialResetParallax();

        void parallaxRender(SDL_Renderer* renderer);

        void freeParallaxTexture();

    private:

    int paraX,paraY;
    int paraX2,paraY2;
    int paraVelX;
};

#endif

