#ifndef PARALLAX_H
#define PARALLAX_H

#include "Texture.h"

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

        void specialResetParallax();

        void parallaxRender(SDL_Renderer* renderer);

        void freeParallaxTexture();

    private:

    void resetParallax();
    void updateRects();

    float paraX,paraY;
    float paraX2,paraY2;
    float paraVelX;
};

#endif

