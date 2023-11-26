#include "ship.h"

ship::ship()
{
    for(int i = 0; i<TOTAL_SHIP_GAUGES; i++)
    {
        gauge[i] = 100;
    }
}

ship::~ship()
{

}

void ship::modifyGauges(int modGaugeValues[])
{
    std::cout<<"\n running ship::modifyGauges(int modGaugeValues[])";
    //sends in an array (shouldn't be larger than TOTAL_SHIP_GAUGES), gives the sum of the gauge before and after mod,
    //adjusts for a gauge going under 0 or over 100
    for(int i = 0; i<TOTAL_SHIP_GAUGES; i++)
    {
        gauge[i] += modGaugeValues[i];
        if(gauge[i] > 100)
        {
            gauge[i] = 100;
        }
        else if(gauge[i] < 0)
        {
            gauge[i] = 0;
        }
    }
}


void ship::loadGaugesTextures(SDL_Renderer* renderer, TTF_Font* font)
{
//stage gets copied when it gets sent into a savegame function, can't do that with stringstream
    std::cout<<"\n running ship::loadGaugesTextures(SDL_Renderer* renderer, TTF_Font* font)";
    SDL_Color textColor = {0,128,200};//font blue
    for (int i = 0; i< TOTAL_SHIP_GAUGES; i++)
    {
        std::cout<<"\n gauge["<<i<<"] value: "<<gauge[i];
        shipGauges[i] = std::to_string(gauge[i]);// << need[i];
        if(!gaugesTexture[i].loadFromRenderedText(shipGauges[i], textColor,font,renderer))
        {
            std::cout<<"\n unable to load shipGauges["<<i<<"] string to gaugesTexture["<<i<<"]";
        }
    }
}

void ship::reloadGaugesTextures(SDL_Renderer* renderer,TTF_Font* font)
{
    freeGaugesTextures();
    //when something happens that affects the ship's gauges, the text texture for that
    //gauge needs to be reloaded before being rendered again
    std::cout<<"\n running ship::reloadGaugesTextures(SDL_Renderer* renderer,TTF_Font* font)";
    SDL_Color textColor = {0,128,200}; //font blue
    for (int i = 0; i< TOTAL_SHIP_GAUGES; i++)
    {
        shipGauges[i] = std::to_string(gauge[i]);
        if(!gaugesTexture[i].loadFromRenderedText(shipGauges[i], textColor,font,renderer))
        {
            std::cout<<"\n unable to load shipGauges["<<i<<"] string to gaugesTexture["<<i<<"]";
        }
    }
}

void ship::renderGaugesTextures(SDL_Renderer* renderer)
{
    for(int i = 0; i<TOTAL_SHIP_GAUGES; i++)
    {
        gaugesTexture[i].render(450+(i*60),40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void ship::freeGaugesTextures()
{
    std::cout<<"\n running ship::freeGaugesTextures()";
    for(int i = 0; i < TOTAL_SHIP_GAUGES; i++)
    {
        gaugesTexture[i].free();
    }
}

void ship::free()
{
    habitation.free();
    engineering.free();
    freeGaugesTextures();
}

void ship::loadSavedShipData(Uint32 dataValues[])
{
    std::cout<<"\n running ship::loadSavedShipData(Uint32 dataValues[])";
    //load ship gauges from save
    for(int i = 0; i<TOTAL_SHIP_GAUGES; i++)
    {
        gauge[i] = dataValues[i];
        std::cout<<"\n gauge["<<i<<"]: "<<gauge[i];
    }
}

void ship::loadShip(SDL_Renderer* renderer,TTF_Font* font)
{
    habitation.loadModule(renderer,font,gauge);
}

