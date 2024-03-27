#include "module.h"

module::module()
{

}

module::~module()
{

}

void module::loadHabitation(SDL_Renderer* renderer,TTF_Font* font,int gauge[],int need[])
{
    std::cout<<"\n **********************************************************************************";
    std::cout<<"\n running module::loadHabitation(SDL_Renderer* renderer,TTF_Font* font,int gauge[])";
    std::cout<<"\n **********************************************************************************";

    std::cout<<"\n player needs 0: "<<need[0]<<" 1: "<<need[1]<<" 2: "<<need[2]<<" 3: "<<need[3]<<" 4: "<<need[4];
    //load textures and interaction dialog etc for each station.
    waterTank.loadWaterTank(renderer,font,gauge[3]);
    kitchen.loadKitchen(renderer,font,need[2]);
    infirmary.loadInfirmary(renderer,font,need[0]);
    bed.loadBed(renderer,font,need[3]);
    bike.loadBike(renderer,font,need[1]);
    planter.loadPlanter(renderer,font);
    planter.updatePlantTexture(renderer);
    recreation.loadRec(renderer,font,need[4]);
    habExit.loadHabExit(renderer,font);

}

void module::loadEngineering(SDL_Renderer* renderer,TTF_Font* font,int gauge[],int need[])
{
    std::cout<<"\n **********************************************************************************";
    std::cout<<"\n running module::loadEngineering(SDL_Renderer* renderer,TTF_Font* font)";
    std::cout<<"\n **********************************************************************************";
    engExit.loadEngExit(renderer,font);
    batteryArray.loadBatteryArray(renderer,font,gauge[2]);
    researchDesk.loadResearchDesk(renderer,font);
    engineStation.loadEngineStation(renderer,font,gauge[1]);
    cargoArea.loadCargoArea(renderer, font);
    commStation.loadCommStation(renderer, font);
}

void module::freeHab()
{
    std::cout<<"\n running module::freeHab()";
    waterTank.free();
    kitchen.free();
    infirmary.free();
    bed.free();
    bike.free();
    planter.free();
    recreation.free();
    habExit.free();
}

void module::freeEng()
{
    std::cout<<"\n Running module::freeEng()";
    engExit.free();
    batteryArray.free();
    //frees the researchBG texture
    researchDesk.freeInventory();
    researchDesk.free();
    engineStation.free();
    //frees the inventoryBG texture
    cargoArea.freeInventory();
    cargoArea.free();
    commStation.free();
}
