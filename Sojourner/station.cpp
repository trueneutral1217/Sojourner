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

    planterX = 400;
    planterY = 200;
    collidable[2].x = planterX;
    collidable[2].y = planterY;
    collidable[2].w = 100;
    collidable[2].h = 50;
    interactable[2].x=collidable[2].x-2;
    interactable[2].y=collidable[2].y-2;
    interactable[2].w=collidable[2].w+4;
    interactable[2].h=collidable[2].h+4;
}

station::~station()
{

}

void station::loadStation(SDL_Renderer* renderer,TTF_Font* font)
{
    bedTexture.loadFromFile("images/sprites/sleepingbag.png",renderer);
    waterTankTexture.loadFromFile("images/sprites/WaterTank.png",renderer);
    planterTexture.loadFromFile("images/sprites/planter.png",renderer);
    loadInteractWaterTank(renderer,font);
    loadInteractBed(renderer,font);
    loadInteractPlanter(renderer,font);
}

void station::loadInteractPlanter(SDL_Renderer* renderer,TTF_Font* font)
{
    //setting text for waterTank interaction
    plantStatus = "Not Planted";
    //test if water tank interaction function is running
    std::cout<<"\n loadInteractPlanter function executed";
    SDL_Color textColor = {0,0,0};//black
    if(!plantStatusTexture.loadFromRenderedText(plantStatus.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render plantStatus string to plantStatusTexture!";
    }
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
        std::cout<<"\n unable to render laterLevel string to waterLevelTexture!";
    }
}

void station::loadInteractBed(SDL_Renderer* renderer,TTF_Font* font)
{
    //setting text for waterTank interaction
    sleepyTime = "Not Tired";
    //test if water tank interaction function is running
    std::cout<<"\n loadInteractBed function executed";
    SDL_Color textColor = {0,0,0};//black
    if(!sleepyTimeTexture.loadFromRenderedText(sleepyTime.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render sleepyTime string to sleepyTimeTexture!";
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

    planterY = y+200;
    collidable[2].y=planterY;
    interactable[2].y=collidable[2].y-2;

    //std::cout<<"\n \n collidable.y: "<<collidable.y;
}

void station::renderInteractWaterTank(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    waterLevelTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractBed(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    sleepyTimeTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractPlanter(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    plantStatusTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderStation(SDL_Renderer* renderer)
{
    bedTexture.render(bedX,bedY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    waterTankTexture.render(waterTankX,waterTankY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    planterTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::free()
{
	bedTexture.free();
	waterTankTexture.free();
	waterLevelTexture.free();
	sleepyTimeTexture.free();
	planterTexture.free();
	plantStatusTexture.free();
}
