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
    //pushes the foreground parallax image to the right.
    paraX+=1;
    paraX2+=1;
    updateRects();
    resetParallax();
}

void parallax::incrementAnteriorMid(){
    //this function is currently depricated.
    paraX+=.5;
    paraX2+=.5;
    updateRects();
    resetParallax();
}


void parallax::incrementMid(){
    //pushes the mid layer parallax image (slower than anterior, but faster than posterior).
    paraX+=.3;
    paraX2+=.3;
    updateRects();
    resetParallax();
}

void parallax::incrementBack(){
    //increments the farthest back layer, moves slowest forward for the illusion of perspective.
    paraX+=.1;
    paraX2+=.1;
    updateRects();
    resetParallax();
}

void parallax::specialIncrementFore(){
    //this function, and the special reset function are both depricated
    paraX+=4;
  //  paraX2+=4;
    updateRects();
    specialResetParallax();
}

void parallax::resetParallax()
{//parallax backgrounds go back to starting postion if they're at the end of their run
    if(paraX > 799.9){
        paraX = -799.9;
    }
    if(paraX2 > 799.9){
        paraX2 = -799.9;
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
    //updates rects created for the parallax images (though I'm not sure if they're necessary).
    parallaxRect1.x=(int)paraX;
    parallaxRect2.x=(int)paraX2;

}

void parallax::parallaxRender(SDL_Renderer* renderer)
{
    //renders the parallax image to the screen.
    parallaxTexture.render(parallaxRect1.x,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    parallaxTexture.render(parallaxRect2.x,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

}

void parallax::freeParallaxTexture(){

    parallaxTexture.free();

}
