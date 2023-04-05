#include "parallax.h"

parallax::parallax()
{

    paraX=0;
    paraY=0;
    paraX2=-799;
    paraY2=0;
    paraVelX=0;

    parallaxRect1.x = paraX;
    parallaxRect1.y = paraY;
    parallaxRect1.w = PARALLAX_WIDTH;
    parallaxRect1.h = PARALLAX_HEIGHT;

    parallaxRect2.x = paraX2;
    parallaxRect2.y = paraY2;
    parallaxRect2.w = PARALLAX_WIDTH;
    parallaxRect2.h = PARALLAX_HEIGHT;

}

parallax::~parallax(){

    parallaxTexture.free();

}

void parallax::incrementFore(){
    paraX+=4;
    paraX2+=4;
    updateRects();
    resetParallax();
}

void parallax::incrementAnteriorMid(){
    paraX+=3;
    paraX2+=3;
    updateRects();
    resetParallax();
}


void parallax::incrementMid(){
    paraX+=2;
    paraX2+=2;
    updateRects();
    resetParallax();
}

void parallax::incrementBack(){
    paraX+=1;
    paraX2+=1;
    updateRects();
    resetParallax();
}

void parallax::specialIncrementFore(){
    paraX+=4;
  //  paraX2+=4;
    updateRects();
    specialResetParallax();
}

void parallax::resetParallax()
{
    if(paraX > 799){
        paraX = -799;
    }
    if(paraX2 > 799){
        paraX2 = -799;
    }
}

void parallax::specialResetParallax()
{
    if(paraX>799){
        paraX=-1599;
    }
    /*
    if(paraX2>799){
        paraX2=-1599;
    }*/
}

void parallax::updateRects()
{

    parallaxRect1.x=paraX;
    parallaxRect2.x=paraX2;

}

void parallax::parallaxRender(SDL_Renderer* renderer)
{

    parallaxTexture.render(parallaxRect1.x,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    parallaxTexture.render(parallaxRect2.x,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

}

void parallax::freeParallaxTexture(){

    parallaxTexture.free();

}
