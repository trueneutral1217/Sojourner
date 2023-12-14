#include "module.h"

module::module()
{

}

module::~module()
{

}

void module::loadHabitation(SDL_Renderer* renderer,TTF_Font* font,int gauge[],int need[])
{
    std::cout<<"\n running module::loadHabitation(SDL_Renderer* renderer,TTF_Font* font,int gauge[])";
    //load textures and interaction dialog etc for each station.
    waterTank.loadWaterTank(renderer,font,gauge[3]);
    kitchen.loadKitchen(renderer,font,need[2]);
    infirmary.loadInfirmary(renderer,font,need[0]);
    bed.loadBed(renderer,font,need[3]);
    bike.loadBike(renderer,font,need[1]);
    planter.loadPlanter(renderer,font);
    recreation.loadRec(renderer,font,need[4]);
    habExit.loadHabExit(renderer,font);

}

void module::loadEngineering(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running module::loadEngineering(SDL_Renderer* renderer,TTF_Font* font)";
    engExit.loadEngExit(renderer,font);
}

void module::free()
{
    std::cout<<"\n running module::free()";
    waterTank.free();
    kitchen.free();
    infirmary.free();
    bed.free();
    bike.free();
    planter.free();
    recreation.free();
}
