#include "animations.h"

animations::animations()
{
    aniFrame=0;
    aniFrame2=0;
    aniFrame3=0;
    aniFrame4=0;
    aniFrame5=0;
    aniFrame6=0;
    aniFrame7=0;
    aniFrame8=0;
    aniFrame9=0;
    aniFrame10=0;
    aniCountUp=true;

}

animations::~animations()
{

}

bool animations::loadCreditsAnimationTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running animations::loadCreditsAnimationTextures(SDL_Renderer* renderer)";
    bool success = true;
    for(int i = 0; i<TOASTER_ANIMATION_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss << "images/animations/toaster/toaster" << a << ".png";
        std::string str = ss.str();
        success = toaster[i].loadFromFile(str,renderer);
    }
    return success;
}

void animations::freeCreditsAnimationTextures()
{
    std::cout<<"\n running animations::freeCreditsAnimationTextures()";
    for(int i=0;i<TOASTER_ANIMATION_FRAMES;i++)
    {
        toaster[i].free();
    }
}

void animations::renderToaster(SDL_Renderer* renderer)
{
    switch(aniFrame2)
    {
    case 0:toaster[0].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 1:toaster[1].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 2:toaster[2].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 3:toaster[3].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 4:toaster[4].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 5:toaster[5].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 6:toaster[6].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 7:toaster[7].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    }
}

void animations::cycleAnimations()
{
    if( aniFrame >= TAO_ANIMATION_FRAMES )
    {
        aniFrame = 0;
    }
    if(aniFrame3 >= TOASTER2_ANIMATION_FRAMES)
    {
        aniFrame3 = 0;
    }
    if( aniFrame2 >= TOASTER_ANIMATION_FRAMES-1 )
    {
        aniCountUp = false;
    }
    if( aniFrame4 >= BLACKSTAR_ANIMATION_FRAMES)
    {
        aniFrame4 = 0;
        bsX1=rand() % 200;
        bsY1=rand()% 350;
    }
    if( aniFrame5 >= BLACKSTAR_ANIMATION_FRAMES)
    {
        aniFrame5 = 0;
        bsX2=rand() % 200;
        bsX2+=200;
        bsY2=rand()% 350;
    }
    if( aniFrame6 >= BLACKSTAR_ANIMATION_FRAMES)
    {
        aniFrame6 = 0;
        bsX3=rand() % 200;
        bsX3+=400;
        bsY3=rand()% 350;
    }
    if( aniFrame7 >= BLACKSTAR_ANIMATION_FRAMES)
    {
        aniFrame7 = 0;
        bsX4=rand() % 200;
        bsX4+=550;
        bsY4=rand()% 350;
    }
    if(aniFrame8 >= PORTAL_ANIMATION_FRAMES)
    {
        aniFrame8 = 20;
    }
    else if(aniFrame2 <= 0)
    {
        aniCountUp = true;
    }
    if( aniFrame9 >= RAT_ANIMATION_FRAMES )
    {
        aniFrame9 = 0;
    }
    if( aniFrame10 >= TRAILER_ANIMATION_FRAMES )
    {
        aniFrame10 = 0;
    }
}

void animations::oscillateCount()
{
    if(aniCountUp)
    {
        aniFrame2++;
        SDL_Delay(50);//slow that shit down
    }
    else
    {
        aniFrame2--;
        SDL_Delay(50);
    }
}

void animations::toasterAnimationProgress()
{
    if(animationTimer2.getTicks() / 60 > 1)
    {
        oscillateCount();
        //animationTimer2.restart();
    }
}

void animations::progress()
{ //this function should probably be renamed to progressToaster in refactor
    //the tao animation timer
    //taoAnimationProgress();
    //the timer for toaster the robot's animation
    toasterAnimationProgress();
    //Cycle animation
    cycleAnimations();
}
