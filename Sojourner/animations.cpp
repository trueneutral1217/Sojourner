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
    animationTimer.start();
    animationTimer2.start();
    animationTimer3.start();
    animationTimer4.start();
    animationTimer5.start();
    animationTimer6.start();
    animationTimer7.start();
    animationTimer9.start();
    animationTimer10.start();
    //animationTimer8.start();

    //initialize x & y of blackstar animations 1 - 4.
    bsX1=rand() % 200;
    bsY1=rand()% 350;

    bsX2=rand() % 200;
    bsX2+=200;
    bsY2=rand()% 350;

    bsX3=rand() % 200;
    bsX3+=400;
    bsY3=rand()% 350;

    bsX4=rand() % 200;
    bsX4+=550;
    bsY4=rand()% 350;

    portalY=30;
    toaster2X=-50;

}

animations::~animations()
{

}

bool animations::setAnimationTextures(SDL_Renderer* renderer)
{
    bool success = true;
    //load tao animation images
    for(int i = 0; i<TAO_ANIMATION_FRAMES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << "images/animations/tao/tao" << a << ".png";
        std::string str = ss.str();
        success = tao[i].loadFromFile(str,renderer);
    }
    for(int i = 0; i<TOASTER_ANIMATION_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss << "images/animations/toaster/toaster" << a << ".png";
        std::string str = ss.str();
        success = toaster[i].loadFromFile(str,renderer);
    }
    for(int i = 0; i<TOASTER2_ANIMATION_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss << "images/animations/toaster2/toastersprite" << a << ".png";
        std::string str = ss.str();
        success = toaster2[i].loadFromFile(str,renderer);
    }
    for(int i = 0; i<BLACKSTAR_ANIMATION_FRAMES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << "images/animations/blackstar/blackstar" << a << ".png";
        std::string str = ss.str();
        success = blackstar[i].loadFromFile(str,renderer);
    }
    for(int i = 0; i<PORTAL_ANIMATION_FRAMES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << "images/animations/portal/portal" << a << ".png";
        std::string str = ss.str();
        success = portal[i].loadFromFile(str,renderer);
    }
    for(int i = 0; i<RAT_ANIMATION_FRAMES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << "images/animations/rat/rat" << a << ".png";
        std::string str = ss.str();
        success = rat[i].loadFromFile(str,renderer);
    }
    for(int i = 0; i<TRAILER_ANIMATION_FRAMES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << "images/animations/trailer/trailer" << a << ".png";
        std::string str = ss.str();
        success = trailer[i].loadFromFile(str,renderer);
    }
    return success;
}

void animations::freeAnimationTextures()
{
        //free the tao animation textures
    for(int i=0;i<TAO_ANIMATION_FRAMES;i++)
    {
        tao[i].free();
    }
    for(int i=0;i<TOASTER_ANIMATION_FRAMES;i++)
    {
        toaster[i].free();
    }
    for(int i=0;i<TOASTER2_ANIMATION_FRAMES;i++)
    {
        toaster2[i].free();
    }
    for(int i=0;i<BLACKSTAR_ANIMATION_FRAMES;i++)
    {
        blackstar[i].free();
    }
    for(int i=0;i<PORTAL_ANIMATION_FRAMES;i++)
    {
        portal[i].free();
    }
    for(int i = 0; i < RAT_ANIMATION_FRAMES;i++)
    {
        rat[i].free();
    }
    for(int i = 0; i < TRAILER_ANIMATION_FRAMES;i++)
    {
        trailer[i].free();
    }
}

void animations::renderTao(SDL_Renderer* renderer)
{
    switch(aniFrame){
        case 0:tao[0].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:tao[1].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:tao[2].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:tao[3].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:tao[4].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:tao[5].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:tao[6].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:tao[7].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
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

void animations::renderToaster2(SDL_Renderer* renderer)
{
    if(!animationTimer3.isStarted())
    {
        animationTimer3.start();
    }
    switch(aniFrame3)
    {
    case 0:toaster2[0].render(toaster2X,250,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 1:toaster2[1].render(toaster2X,250,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 2:toaster2[2].render(toaster2X,250,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;

    }
}

void animations::renderBlackstar(SDL_Renderer* renderer)
{
    switch(aniFrame4){
        case 0:blackstar[0].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:blackstar[1].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:blackstar[2].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:blackstar[3].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:blackstar[4].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:blackstar[5].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:blackstar[6].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:blackstar[7].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 8:blackstar[8].render(bsX1,bsY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
    switch(aniFrame5){
        case 0:blackstar[0].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:blackstar[1].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:blackstar[2].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:blackstar[3].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:blackstar[4].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:blackstar[5].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:blackstar[6].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:blackstar[7].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 8:blackstar[8].render(bsX2,bsY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
    switch(aniFrame6){
        case 0:blackstar[0].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:blackstar[1].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:blackstar[2].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:blackstar[3].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:blackstar[4].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:blackstar[5].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:blackstar[6].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:blackstar[7].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 8:blackstar[8].render(bsX3,bsY3,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
    switch(aniFrame7){
        case 0:blackstar[0].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:blackstar[1].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:blackstar[2].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:blackstar[3].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:blackstar[4].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:blackstar[5].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:blackstar[6].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:blackstar[7].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 8:blackstar[8].render(bsX4,bsY4,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
}

void animations::renderPortal(SDL_Renderer* renderer)
{
    if(!animationTimer8.isStarted())
    {
        animationTimer8.start();
    }
    switch(aniFrame8){
        case 0:portal[0].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:portal[1].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:portal[2].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:portal[3].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:portal[4].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:portal[5].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:portal[6].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:portal[7].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 8:portal[8].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 9:portal[9].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 10:portal[10].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 11:portal[11].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 12:portal[12].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 13:portal[13].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 14:portal[14].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 15:portal[15].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 16:portal[16].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 17:portal[17].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 18:portal[18].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 19:portal[19].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 20:portal[19].render(350,portalY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
}

void animations::renderRat(SDL_Renderer* renderer)
{
    switch(aniFrame9){
        case 0:rat[0].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:rat[1].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:rat[2].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:rat[3].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:rat[4].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:rat[5].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:rat[6].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:rat[7].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 8:rat[8].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 9:rat[9].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 10:rat[10].render(750,555,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
}

void animations::renderTrailer(SDL_Renderer* renderer)
{
    switch(aniFrame10){
        case 0:trailer[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:trailer[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:trailer[2].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:trailer[3].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:trailer[4].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:trailer[5].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:trailer[6].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:trailer[7].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 8:trailer[8].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 9:trailer[9].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 10:trailer[10].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 11:trailer[11].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 12:trailer[12].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 13:trailer[13].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 14:trailer[14].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 15:trailer[15].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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
    }
    else
    {
        aniFrame2--;
    }
}

void animations::taoAnimationProgress()
{
    if(animationTimer.getTicks() / 500 > 1)
    {
        ++aniFrame;
        animationTimer.restart();
    }
}

void animations::toasterAnimationProgress()
{
    if(animationTimer2.getTicks() / 60 > 1)
    {
        oscillateCount();
        animationTimer2.restart();
    }
}

void animations::toaster2AnimationProgress()
{
    if(animationTimer3.getTicks() / 60 > 1)
    {
        if(aniFrame3<TOASTER2_ANIMATION_FRAMES)
        {
            aniFrame3++;
        }
        if(toaster2X < 800)
        {
            toaster2X++;
        }
        else
        {
            toaster2X=-50;
        }
        animationTimer3.restart();
    }
}

void animations::blackstarAnimationProgress()
{

    if(animationTimer4.getTicks() / 25 > 1)
    {
        aniFrame4++;
        animationTimer4.restart();
    }
    if(animationTimer5.getTicks() / 20 > 1)
    {
        aniFrame5++;
        animationTimer5.restart();
    }
    if(animationTimer6.getTicks() / 30 > 1)
    {
        aniFrame6++;
        animationTimer6.restart();
    }
    if(animationTimer7.getTicks() / 15 > 1)
    {
        aniFrame7++;
        animationTimer7.restart();
    }
}

void animations::portalAnimationProgress()
{

    if(animationTimer8.getTicks() / 60 > 1)
    {
        if(aniFrame8<PORTAL_ANIMATION_FRAMES)
            aniFrame8++;
        if(aniFrame8==20 && portalY > -400)
            portalY-=10;
        animationTimer8.restart();
    }
}

void animations::ratAnimationProgress()
{
    if(animationTimer9.getTicks() / 100 > 1)
    {
        ++aniFrame9;
        animationTimer9.restart();
    }
}

void animations::trailerAnimationProgress()
{
    if(animationTimer10.getTicks() / 16 > 1)
    {
        ++aniFrame10;
        animationTimer10.restart();
    }
}

void animations::resetPortal()
{
    animationTimer8.stop();
    aniFrame8 = 0;
    portalY = 30;
}

void animations::resetToaster2()
{
    animationTimer3.stop();
    aniFrame3 = 0;
    toaster2X = -50;
}

void animations::progress()
{
    //the tao animation timer
    taoAnimationProgress();
    //the timer for toaster the robot's animation
    toasterAnimationProgress();

    toaster2AnimationProgress();

    blackstarAnimationProgress();

    portalAnimationProgress();

    ratAnimationProgress();

    trailerAnimationProgress();
    //Cycle animation
    cycleAnimations();
}
