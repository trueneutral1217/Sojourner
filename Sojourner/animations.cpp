#include "animations.h"

animations::animations()
{
    aniFrame=0;
    aniFrame2=0;

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

void animations::loadBushAnimationTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running animations::loadBushAnimationTextures(SDL_Renderer* renderer)";
    for(int i = 0; i<BUSH_ANIMATION_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss<<"images/animations/bush/bush"<<a<<".png";
        std::string str = ss.str();
        bush[i].loadFromFile(str,renderer);
    }
    if(!animationTimer11.isStarted())
    {
        animationTimer11.start();
        std::cout<<"\n \n starting bush animation timer";
    }
}

void animations::loadLeftCurtainAnimationTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running animations::loadLeftCurtainAnimationTextures(SDL_Renderer* renderer)";
    for(int i = 0; i<LEFTCURTAIN_ANIMATION_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss<<"images/animations/leftCurtain/leftCurtain"<<a<<".png";
        std::string str = ss.str();
        leftCurtain[i].loadFromFile(str,renderer);
    }
    if(!animationTimer12.isStarted())
    {
        animationTimer12.start();
        std::cout<<"\n \n starting leftCurtain animation timer";
    }
}

void animations::loadRightCurtainAnimationTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running animations::loadRightCurtainAnimationTextures(SDL_Renderer* renderer)";
    for(int i = 0; i<RIGHTCURTAIN_ANIMATION_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss<<"images/animations/rightCurtain/rightCurtain"<<a<<".png";
        std::string str = ss.str();
        rightCurtain[i].loadFromFile(str,renderer);
    }
    if(!animationTimer13.isStarted())
    {
        animationTimer13.start();
        std::cout<<"\n \n starting rightCurtain animation timer";
    }
}

void animations::freeCreditsAnimationTextures()
{
    std::cout<<"\n running animations::freeCreditsAnimationTextures()";
    for(int i=0;i<TOASTER_ANIMATION_FRAMES;i++)
    {
        toaster[i].free();
    }
}

void animations::freeBushAnimationTextures()
{
    std::cout<<"\n running animations::freeBushAnimationTextures()";
    for(int i = 0; i<BUSH_ANIMATION_FRAMES;i++)
    {
        bush[i].free();
    }
}

void animations::freeLeftCurtainAnimationTextures()
{
    std::cout<<"\n running animations::freeLeftCurtainAnimationTextures()";
    for(int i = 0; i<LEFTCURTAIN_ANIMATION_FRAMES;i++)
    {
        leftCurtain[i].free();
    }
}

void animations::freeRightCurtainAnimationTextures()
{
    std::cout<<"\n running animations::freeRightCurtainAnimationTextures()";
    for(int i = 0; i<RIGHTCURTAIN_ANIMATION_FRAMES;i++)
    {
        rightCurtain[i].free();
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

void animations::renderBush(SDL_Renderer* renderer)
{
    switch(aniFrame11)
    {
        case 0:bush[0].render(100,467,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 1:bush[1].render(100,467,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 2:bush[2].render(100,467,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 3:bush[3].render(100,467,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
    }
}

void animations::renderLeftCurtain(SDL_Renderer* renderer)
{
    switch(aniFrame12)
    {
        case 0:leftCurtain[0].render(387,256,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 1:leftCurtain[1].render(387,256,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 2:leftCurtain[2].render(387,256,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 3:leftCurtain[3].render(387,256,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
    }
}

void animations::renderRightCurtain(SDL_Renderer* renderer)
{
    switch(aniFrame13)
    {
        case 0:rightCurtain[0].render(485,253,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 1:rightCurtain[1].render(485,253,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 2:rightCurtain[2].render(485,253,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
        case 3:rightCurtain[3].render(485,253,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            break;
    }
}

void animations::cycleAnimations()
{
    if( aniFrame2 >= TOASTER_ANIMATION_FRAMES-1 )
    {
        aniCountUp = false;
    }
    else if(aniFrame2 <= 0)
    {
        aniCountUp = true;
    }
    if(aniFrame11 >= BUSH_ANIMATION_FRAMES)
    {
        aniFrame11 = 0;
    }
    if(aniFrame12 >= LEFTCURTAIN_ANIMATION_FRAMES)
    {
        aniFrame12 = 0;
    }
    if(aniFrame13 >= RIGHTCURTAIN_ANIMATION_FRAMES)
    {
        aniFrame13 = 0;
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
        SDL_Delay(50);//probably shouldn't use delay but since this is only on credits screen it doesn't effect anything
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

void animations::bushAnimationProgress()
{
    if((animationTimer11.getTicks() % 400) == 1)
    {
        aniFrame11++;
    }
}

void animations::leftCurtainAnimationProgress()
{
    if((animationTimer12.getTicks()%300) == 1)
    {
        aniFrame12++;
    }
}

void animations::rightCurtainAnimationProgress()
{
    if((animationTimer13.getTicks()%310) == 1)
    {
        aniFrame13++;
    }
}

void animations::progress()
{ //this function should probably be renamed to progressToaster in refactor
    //the tao animation timer
    //taoAnimationProgress();
    bushAnimationProgress();

    leftCurtainAnimationProgress();
    rightCurtainAnimationProgress();
    //the timer for toaster the robot's animation
    toasterAnimationProgress();
    //Cycle animation
    cycleAnimations();
}
