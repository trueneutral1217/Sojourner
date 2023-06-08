#include "station.h"

station::station()
{
    //Setup coords & collision box for bed
    bedX = 100;
    bedY = 300;
    collidable[0].x = bedX;
    collidable[0].y = bedY;
    collidable[0].w = 85;
    collidable[0].h = 37;
    //setup coords & collision box for water Tank
    waterTankX = 200;
    waterTankY = 100;
    collidable[1].x = waterTankX;
    collidable[1].y = waterTankY;
    collidable[1].w = 87;
    collidable[1].h = 34;
}

station::~station()
{

}

void station::loadStation(SDL_Renderer* renderer)
{
    bedTexture.loadFromFile("images/sprites/sleepingbag.png",renderer);
    waterTankTexture.loadFromFile("images/sprites/WaterTank.png",renderer);
}

void station::updatePosition(int y)
{
    //when player moves, background parallaxes, this makes sure the stations stay in their places.
    bedY = y+300;
    collidable[0].y=bedY;

    waterTankY = y+100;
    collidable[1].y=waterTankY;

    //std::cout<<"\n \n collidable.y: "<<collidable.y;
}

void station::renderStation(SDL_Renderer* renderer)
{
    bedTexture.render(bedX,bedY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    waterTankTexture.render(waterTankX,waterTankY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::free()
{
	bedTexture.free();
	waterTankTexture.free();
}
