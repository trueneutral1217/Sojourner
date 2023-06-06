#include "station.h"

station::station()
{
    bedX = 100;
    bedY = 300;
    collidable.x = bedX;
    collidable.y = bedY;
    collidable.w = 100;
    collidable.h = 50;
}

station::~station()
{

}

void station::loadStation(SDL_Renderer* renderer)
{
    bedTexture.loadFromFile("images/sprites/sleepingbag.png",renderer);
}

void station::updatePosition(int y)
{
    bedY = y+300;
    collidable.y=bedY;
    //std::cout<<"\n \n collidable.y: "<<collidable.y;
}

void station::renderStation(SDL_Renderer* renderer)
{
    bedTexture.render(bedX,bedY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::free()
{
	bedTexture.free();
}
