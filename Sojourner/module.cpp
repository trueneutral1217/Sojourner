#include "module.h"

module::module()
{

}

module::~module()
{

}

void module::loadHabitation(SDL_Renderer* renderer,TTF_Font* font,int gauge[])
{
    //load textures and interaction dialog etc for each station.
    waterTank.loadWaterTank(renderer,font,gauge[3]);
    kitchen.loadKitchen(renderer,font);
    infirmary.loadInfirmary(renderer,font);
    bed.loadBed(renderer,font);
    bike.loadBike(renderer,font);
    planter.loadPlanter(renderer,font);
    recreation.loadRec(renderer,font);
}

void module::loadEngineering(SDL_Renderer* renderer,TTF_Font* font)
{
    engExit.loadEngExit(renderer,font);
}

void module::free()
{
    //station.free();
}
