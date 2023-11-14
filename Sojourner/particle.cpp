#include "particle.h"

void Particle::createParticle(SDL_Renderer* renderer)
{
    //Set initial position and dimensions
    partX = 20 +  (rand() % 760) ;
    partY = 20 +  (rand() % 560) ;
//    fillRect = {partX,partY,10,10};

    //set initial frame
    frame = 0;
    //frame = rand() % 50;
    for(int i = 0; i<TOTAL_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss << "images/animations/star/star" << a << ".png";
        std::string str = ss.str();
        star[i].loadFromFile(str,renderer);
    }

    particleTimer.start();
/*

    //Set color
    switch( rand() % 4 )
    {
        case 0: SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );renderColor=0; break;//red
        //case 1: SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );renderColor=1; break;//green
        //case 2: SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );renderColor=2; break;//blue
        case 1: SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );renderColor=3; break;//yellow
        //case 4: SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );renderColor=4; break;//black
        case 2: SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );renderColor=5; break;//white
        //case 6: SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0xFF, 0xFF );renderColor=6; break;//lavender
        case 3: SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF );renderColor=7; break;//teal

    }
    */
}


void Particle::render(SDL_Renderer* renderer, int renderColor)
{
    /*
    //Show image
    switch( renderColor )
    {
        case 0: SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF ); break;//red
        case 1: SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF ); break;//green
        case 2: SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF ); break;//blue
        case 3: SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF ); break;//yellow
        case 4: SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF ); break;//black
        case 5: SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); break;//white
        case 6: SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0xFF, 0xFF ); break;//lavender
        case 7: SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF ); break;//Teal
    }

    SDL_RenderFillRect( renderer, &fillRect );
    */
    switch(frame)
    {
        case 0: star[0].render(partX,partY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 1: star[1].render(partX,partY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 2: star[2].render(partX,partY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 3: star[3].render(partX,partY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 4: star[4].render(partX,partY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    }

    if(particleTimer.getTicks() % 100 == 0)
    {
        frame++;
        particleTimer.restart();
    }
    //increment frame
   // frame++;
}

bool Particle::isDead()
{
    return frame > 4;
}

void Particle::incrementFrame()
{
    frame++;
}

