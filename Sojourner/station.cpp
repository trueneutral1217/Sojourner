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
    interactable[0].x=collidable[0].x-2;
    interactable[0].y=collidable[0].y-2;
    interactable[0].w=collidable[0].w+4;
    interactable[0].h=collidable[0].h+6;
    //setup coords & collision box for water Tank
    waterTankX = 200;
    waterTankY = 100;
    collidable[1].x = waterTankX;
    collidable[1].y = waterTankY;
    collidable[1].w = 87;
    collidable[1].h = 34;
    interactable[1].x=collidable[1].x-2;
    interactable[1].y = collidable[1].y-2;
    interactable[1].w=collidable[1].w+6;
    interactable[1].h = collidable[1].h+4;
}

station::~station()
{

}

void station::loadStation(SDL_Renderer* renderer,TTF_Font* font)
{
    bedTexture.loadFromFile("images/sprites/sleepingbag.png",renderer);
    waterTankTexture.loadFromFile("images/sprites/WaterTank.png",renderer);
    loadInteractWaterTank(renderer,font);
}

void station::loadInteractWaterTank(SDL_Renderer* renderer,TTF_Font* font)
{
    //setting text for waterTank interaction
    waterLevel = "100L";
    //test if water tank interaction function is running
    std::cout<<"\n interactWaterTank function executed";
    SDL_Color textColor = {0,0,0};//black
    if(!waterLevelTexture.loadFromRenderedText(waterLevel.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render laterLevel streamstring to waterLevelTexture!";
    }
}

void station::updatePosition(int y)
{
    //when player moves, background parallaxes, this makes sure the stations stay in their places.
    bedY = y+300;
    collidable[0].y=bedY;
    interactable[0].y=collidable[0].y-2;

    waterTankY = y+100;
    collidable[1].y=waterTankY;
    interactable[1].y=collidable[1].y-2;

    //std::cout<<"\n \n collidable.y: "<<collidable.y;
}

void station::renderInteractWaterTank(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    waterLevelTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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
	waterLevelTexture.free();
}
