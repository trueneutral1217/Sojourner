#include "station.h"

station::station()
{
    //Setup coords & collision box for bed
    bedX = 100;
    bedY = 500;
    bedH = 37;
    bedBot = bedY + bedH;
    collidable[0].x = bedX;
    collidable[0].y = bedY+(bedH/2);
    collidable[0].w = 85;
    collidable[0].h = bedH/2;
    interactable[0].x=collidable[0].x-2;
    interactable[0].y=collidable[0].y-4;
    interactable[0].w=collidable[0].w+4;
    interactable[0].h=collidable[0].h+10;
    //setup coords & collision box for water Tank
    waterTankX = 100;
    waterTankY = 25;
    waterTankH = 34;
    waterTankBot = waterTankY + waterTankH;
    collidable[1].x = waterTankX;
    collidable[1].y = waterTankY+(waterTankH/2);
    collidable[1].w = 87;
    collidable[1].h = waterTankH/2;
    interactable[1].x=collidable[1].x-2;
    interactable[1].y = collidable[1].y-4;
    interactable[1].w=collidable[1].w+6;
    interactable[1].h = collidable[1].h+6;
    //setup coords for planter + it's collision box, plus it's interaction box.
    planterX = 600;
    planterY = 25;
    planterH = 50;
    planterBot = planterY+planterH;
    collidable[2].x = planterX;
    collidable[2].y = planterY+(planterH/2);
    collidable[2].w = 100;
    collidable[2].h = planterH/2;
    interactable[2].x=collidable[2].x-2;
    interactable[2].y=collidable[2].y-2;
    interactable[2].w=collidable[2].w+4;
    interactable[2].h=collidable[2].h+4;
    plantOkay = true;
    waterPlantsOkay = false;
    harvestOkay = false;

    planterSown = false;
    planterWatered = false;
    planterOptionsLoaded=false;
    //flag the interact buttons to reload.
    interacted = false;
    //setup coords for kitchen + it's collision box, plus it's interaction box.
    kitchenX = 100;
    kitchenY = 250;
    kitchenH = 100;
    kitchenBot = kitchenY+kitchenH;
    collidable[3].x = kitchenX;
    collidable[3].y = kitchenY+(kitchenH/2);
    collidable[3].w = 200;
    collidable[3].h = kitchenH/2;
    interactable[3].x=collidable[3].x-2;
    interactable[3].y=collidable[3].y-2;
    interactable[3].w=collidable[3].w+4;
    interactable[3].h=collidable[3].h+4;

    //collidable & interactable for infirm & bike may need some small adjustments to wrap the station better.
    infirmX = 500;
    infirmY = 250;
    infirmH = 100;
    infirmBot = infirmY+infirmH;
    collidable[4].x = infirmX+40;
    collidable[4].y = infirmY+(infirmH/2);
    collidable[4].w = 105;
    collidable[4].h = infirmH/2;
    interactable[4].x = collidable[4].x-2;
    interactable[4].y = collidable[4].y-2;
    interactable[4].w = collidable[4].w+4;
    interactable[4].h = collidable[4].h+4;

    bikeX = 100;
    bikeY = 850;
    bikeH = 100;
    bikeBot = bikeY+bikeH;
    collidable[5].x = bikeX + 40;
    collidable[5].y = bikeY+(bikeH/2);
    collidable[5].w = 100;
    collidable[5].h = bikeH/2;
    interactable[5].x = collidable[5].x-2;
    interactable[5].y = collidable[5].y-2;
    interactable[5].w = collidable[5].w+4;
    interactable[5].h = collidable[5].h+4;
}

station::~station()
{

}

void station::loadStation(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadStation(SDL_Renderer* renderer,TTF_Font* font)";
    bedTexture.loadFromFile("images/sprites/sleepingbag.png",renderer);
    waterTankTexture.loadFromFile("images/sprites/WaterTank.png",renderer);
    planterTexture.loadFromFile("images/sprites/planter.png",renderer);
    kitchenTexture.loadFromFile("images/sprites/kitchen.png",renderer);
    infirmaryTexture.loadFromFile("images/sprites/infirmary.png",renderer);
    bikeTexture.loadFromFile("images/sprites/stationaryBicycle.png", renderer);

    planterSownTexture.loadFromFile("images/sprites/planterSown.png",renderer);
    planterSownWateredTexture.loadFromFile("images/sprites/planterSownWatered.png",renderer);

    loadInteractWaterTank(renderer,font);
    loadInteractBed(renderer,font);
    //loadInteractPlanter(renderer,font);
    loadInteractKitchen(renderer,font);
    loadInteractInfirmary(renderer,font);
    loadInteractBike(renderer,font);
}

void station::loadInteractBike(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadInteractBike(SDL_Renderer* renderer, TTF_Font* font)";
    //setting text for waterTank interaction
    bikeDefault = "Stronk";
    SDL_Color textColor = {255,255,255};//white
    if(!bikeDefaultTexture.loadFromRenderedText(bikeDefault.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render bikeDefault string to bikeDefaultTexture!";
    }
}

void station::loadInteractInfirmary(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadInteractInfirmary(SDL_Renderer* renderer,TTF_Font* font)";
    //setting text for waterTank interaction
    infirmDefault = "Healthy";
    SDL_Color textColor = {255,255,255};//white
    if(!infirmDefaultTexture.loadFromRenderedText(infirmDefault.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render infirmDefault string to infirmDefaultTexture!";
    }
}

void station::loadInteractKitchen(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadInteractKitchen(SDL_Renderer* renderer,TTF_Font* font)";
    //setting text for waterTank interaction
    foodTime = "Not Hungry";
    SDL_Color textColor = {255,255,255};//white
    if(!foodTimeTexture.loadFromRenderedText(foodTime.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render foodTime string to foodTimeTexture!";
    }
}

void station::loadInteractPlanter(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadInteractPlanter(SDL_Renderer* renderer,TTF_Font* font)";
    //setting text for planter interaction
    plant="Plant";
    waterPlants = "Water Plants";
    harvest = "Harvest";
    //cancel = "cancel";
    SDL_Color textColor = {255,255,255};//white
    SDL_Color unavailable = {0,0,0};//black

    if(plantOkay)
    {
        if(!plantTexture.loadFromRenderedText(plant.c_str(), textColor,font,renderer))
        {
            std::cout<<"\n unable to render plant string to plantTexture!";
        }
    }
    else
    {
        if(!plantTexture.loadFromRenderedText(plant.c_str(), unavailable,font,renderer))
        {
            std::cout<<"\n unable to render plant string to plantTexture!";
        }
    }
    if(waterPlantsOkay)
    {
        if(!waterPlantsTexture.loadFromRenderedText(waterPlants.c_str(), textColor,font,renderer))
        {
            std::cout<<"\n unable to render waterPlants string to waterPlantsTexture!";
        }
    }
    else
    {
        if(!waterPlantsTexture.loadFromRenderedText(waterPlants.c_str(), unavailable,font,renderer))
        {
            std::cout<<"\n unable to render waterPlants string to waterPlantsTexture!";
        }
    }
    if(harvestOkay)
    {
        if(!harvestTexture.loadFromRenderedText(harvest.c_str(), textColor,font,renderer))
        {
            std::cout<<"\n unable to render harvest string to harvestTexture!";
        }
    }
    else
    {
        if(!harvestTexture.loadFromRenderedText(harvest.c_str(), unavailable,font,renderer))
        {
            std::cout<<"\n unable to render harvest string to harvestTexture!";
        }
    }
planterOptionsLoaded = true;
planterOptionsFreed = false;
}

void station::freePlanterOptions()
{
    plantTexture.free();
    waterPlantsTexture.free();
    harvestTexture.free();
    planterOptionsFreed = true;
    planterOptionsLoaded=false;
}

void station::loadInteractWaterTank(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadInteractWaterTank(SDL_Renderer* renderer,TTF_Font* font)";
    //setting text for waterTank interaction
    waterLevel = "100L";
    SDL_Color textColor = {255,255,255};//white
    if(!waterLevelTexture.loadFromRenderedText(waterLevel.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render laterLevel string to waterLevelTexture!";
    }
}

void station::loadInteractBed(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadInteractBed(SDL_Renderer* renderer,TTF_Font* font)";
    //setting text for waterTank interaction
    sleepyTime = "Not Tired";
    SDL_Color textColor = {255,255,255};//white
    if(!sleepyTimeTexture.loadFromRenderedText(sleepyTime.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render sleepyTime string to sleepyTimeTexture!";
    }
}

void station::updatePosition(int y)
{
    //when player moves, background parallaxes, this makes sure the stations stay in their places.
    //bedY = y+300;
    bedY = y+500;
    bedBot = bedY + bedH;
    collidable[0].y=bedY+(bedH/2);
    interactable[0].y=collidable[0].y-4;

    waterTankY = y+25;
    waterTankBot = waterTankY+waterTankH;
    collidable[1].y=waterTankY + (waterTankH/2);
    interactable[1].y=collidable[1].y-4;

    planterY = y+25;
    planterBot = planterY + planterH;
    collidable[2].y=planterY+(planterH/2);
    interactable[2].y=collidable[2].y-2;

    kitchenY = y+250;
    kitchenBot = kitchenY+kitchenH;
    collidable[3].y=kitchenY+(kitchenH/2);
    interactable[3].y=collidable[3].y-2;

    infirmY = y+250;
    infirmBot = infirmY + infirmH;
    collidable[4].y = infirmY + (infirmH/2);
    interactable[4].y = collidable[4].y-2;

    //this needs to be modified, stationary bicycle isn't showing up sometimes when it should.
    //std::cout<<"\n y: "<<y;
    bikeY = y+850;
    bikeBot = bikeY+bikeH;
    collidable[5].y = bikeY + (bikeH/2);
    interactable[5].y = collidable[5].y-2;

    //std::cout<<"\n \n collidable.y: "<<collidable.y;
}

void station::renderInteractBike(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    bikeDefaultTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractInfirmary(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    infirmDefaultTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractKitchen(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    foodTimeTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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
{//these are the buttons that pop up when player is next to the planter and presses 'e'
    //displays textures to the right of player texture
    x+=50;
    //displays texture above player's head
    y-=20;
    plantTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //render below previous option
    y+=20;
    waterPlantsTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //render below previous option
    y+=20;
    harvestTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderStationBehindPlayer(SDL_Renderer* renderer,int playerBot)
{

    if(playerBot>bedBot)
    {
        bedTexture.render(bedX,bedY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot>waterTankBot)
    {
        waterTankTexture.render(waterTankX,waterTankY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot>planterBot)
    {
        if(planterSown && !planterWatered)
        {
            planterSownTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(planterSown && planterWatered)
        {
            planterSownWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(!planterSown && !planterWatered)
        {
            planterTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }
    if(playerBot>kitchenBot)
    {
        kitchenTexture.render(kitchenX,kitchenY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot>infirmBot)
    {
        infirmaryTexture.render(infirmX,infirmY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot>bikeBot)
    {
        //std::cout<<"\n playerBot: "<<playerBot<<" bikeBot: "<<bikeBot;
        bikeTexture.render(bikeX,bikeY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void station::renderStationFrontPlayer(SDL_Renderer* renderer, int playerBot)
{
    if(playerBot<=bedBot)
    {
        bedTexture.render(bedX,bedY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot<=waterTankBot)
    {
        waterTankTexture.render(waterTankX,waterTankY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot<=planterBot)
    {
        if(planterSown && !planterWatered)
        {
            planterSownTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(planterSown && planterWatered)
        {
            planterSownWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(!planterSown && !planterWatered)
        {
            planterTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }
    if(playerBot<=kitchenBot)
    {
        kitchenTexture.render(kitchenX,kitchenY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot<=infirmBot)
    {
        infirmaryTexture.render(infirmX,infirmY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot<=bikeBot)
    {
        //std::cout<<"\n playerBot: "<<playerBot<<" bikeBot: "<<bikeBot;
        bikeTexture.render(bikeX,bikeY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void station::free()
{
    std::cout<<"\n running station::free()";
	bedTexture.free();
	waterTankTexture.free();
	waterLevelTexture.free();
	sleepyTimeTexture.free();
	planterTexture.free();
	kitchenTexture.free();
	foodTimeTexture.free();
	plantTexture.free();
	waterPlantsTexture.free();
	harvestTexture.free();
	infirmaryTexture.free();
	infirmDefaultTexture.free();
	bikeTexture.free();
	bikeDefaultTexture.free();
}
