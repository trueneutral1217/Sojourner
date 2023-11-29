#include "station.h"

station::station()
{
    plantOkay = true;
    waterPlantsOkay = false;
    harvestOkay = false;
    planterTimeWatered=0;
    planterDaysState=0;
    planterState=-1;

//    planterSown = false;
    //planterWatered = false;
    planterOptionsLoaded=false;
    //flag the interact buttons to reload.
    interacted = false;

}

station::~station()
{

}

void station::loadStation(SDL_Renderer* renderer,TTF_Font* font,int shipGaugeValues[])
{
    std::cout<<"\n running station::loadStation(SDL_Renderer* renderer,TTF_Font* font)";

    //habExitTexture.loadFromFile("images/sprites/habExit.png",renderer);

/*
    planterSownTexture.loadFromFile("images/sprites/planterSown.png",renderer);
    planterSownWateredTexture.loadFromFile("images/sprites/planterSownWatered.png",renderer);
    planterSeedlingTexture.loadFromFile("images/sprites/planterSeedling.png",renderer);
    planterSeedlingWateredTexture.loadFromFile("images/sprites/planterSeedlingWatered.png",renderer);
    planterVegetativeTexture.loadFromFile("images/sprites/planterVegetative.png",renderer);
    planterVegatativeWateredTexture.loadFromFile("images/sprites/planterVegetativeWatered.png",renderer);
    planterFloweringTexture.loadFromFile("images/sprites/planterFlowering.png",renderer);
    planterFloweringWateredTexture.loadFromFile("images/sprites/planterFloweringWatered.png",renderer);
    planterRipeTexture.loadFromFile("images/sprites/planterRipe.png",renderer);
    planterRipeWateredTexture.loadFromFile("images/sprites/planterRipeWatered.png",renderer);
    */

    //loadInteractBed(renderer,font);
    //loadInteractPlanter(renderer,font);
    //loadInteractKitchen(renderer,font);
    //loadInteractInfirmary(renderer,font);
    //loadInteractBike(renderer,font);
    //loadInteractRec(renderer,font);
    //loadInteractHabExit(renderer,font);
    //loadInteractEngExit(renderer,font);
}

void station::loadWaterTank(SDL_Renderer* renderer, TTF_Font* font, int shipGaugeValues)
{
    std::cout<<"\n running station::loadWaterTank(SDL_Renderer* renderer, TTF_Font* font, int shipGaugeValues[])";

     //setup coords & collision box for water Tank
    stationX = 100;
    stationY = 25;
    stationInitialY = stationY;
    stationH = 34;
    stationBot = stationY + stationH;
    collidable.x = stationX;
    collidable.y = stationY+(stationH/2);
    collidable.w = 87;
    collidable.h = stationH/2;
    interactable.x=collidable.x-2;
    interactable.y=collidable.y-4;
    interactable.w=collidable.w+6;
    interactable.h=collidable.h+6;

    int waterGauge = shipGaugeValues;
    stationTexture.loadFromFile("images/sprites/WaterTank.png",renderer);
    stationDefaultInteractionText = std::to_string(waterGauge);
    stationDefaultInteractionText = stationDefaultInteractionText + " Liters";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render waterLevel string to waterLevelTexture!";
    }
}

void station::loadEngExit(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadEngExit(SDL_Renderer* renderer, TTF_Font* font)";

    stationX = 5;
    stationY = 400;
    stationInitialY = stationY;
    stationH = 10;
    stationBot = stationY + stationH;
    collidable.x = stationX;
    collidable.y = stationY + (stationH/2);
    collidable.w = 10;
    collidable.h = stationH/2;
    interactable.x = collidable.x-2;
    interactable.y = collidable.y - 2;
    interactable.w = collidable.w + 4;
    interactable.h = collidable.h + 4;

    stationTexture.loadFromFile("images/sprites/engExit.png",renderer);
    stationDefaultInteractionText = "Leaving Engineering Module";
    SDL_Color textColor = {255,255,255};
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(),textColor,font,renderer))
    {
       std::cout<<"\n unable to render engExitDefault string to engExitDefaultTexture!";
    }
}

void station::loadHabExit(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadHabExit(SDL_Renderer* renderer, TTF_Font* font)";

    stationX = 790;
    stationY = 395;
    stationInitialY = stationY;
    stationH = 10;
    stationBot = stationY +stationH;
    collidable.x = stationX;
    collidable.y = stationY + (stationH/2);
    collidable.w = 10;
    collidable.h = stationH/2;
    interactable.x = collidable.x - 2;
    interactable.y = collidable.y - 2;
    interactable.w = collidable.w + 4;
    interactable.h = collidable.h + 4;

    stationTexture.loadFromFile("images/sprites/habExit.png",renderer);
    stationDefaultInteractionText = "Leaving Habitation Module";
    SDL_Color textColor = {255,255,255};
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(),textColor,font,renderer))
    {
       std::cout<<"\n unable to render habExitDefault string to habExitDefaultTexture!";
    }
}

void station::loadRec(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadRec(SDL_Renderer* renderer, TTF_Font* font)";

    stationX = 510;
    stationY = 850;
    stationInitialY = stationY;
    stationH = 100;
    stationBot = stationY+stationH;
    collidable.x = stationX;
    collidable.y = stationY+(stationH/2);
    collidable.w = 120;
    collidable.h = stationH/2;
    interactable.x = collidable.x-2;
    interactable.y = collidable.y-2;
    interactable.w = collidable.w+4;
    interactable.h = collidable.h+4;

    stationTexture.loadFromFile("images/sprites/recreation.png",renderer);
    //setting text for recreation interaction
    stationDefaultInteractionText = "I'm Happy";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render recDefault string to recDefaultTexture!";
    }
}

void station::loadBike(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadBike(SDL_Renderer* renderer, TTF_Font* font)";


    stationX = 100;
    stationY = 850;
    stationInitialY = stationY;
    stationH = 100;
    stationBot = stationY+stationH;
    collidable.x = stationX + 40;
    collidable.y = stationY+(stationH/2);
    collidable.w = 100;
    collidable.h = stationH/2;
    interactable.x = collidable.x-2;
    interactable.y = collidable.y-2;
    interactable.w = collidable.w+4;
    interactable.h = collidable.h+4;

    //setting bike image to station texture
    stationTexture.loadFromFile("images/sprites/stationaryBicycle.png", renderer);
    //setting text for bike interaction
    stationDefaultInteractionText = "Stronk";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render bikeDefault string to bikeDefaultTexture!";
    }
}

void station::loadInfirmary(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadInfirmary(SDL_Renderer* renderer,TTF_Font* font)";

    //collidable & interactable for infirm & bike may need some small adjustments to wrap the station better.
    stationX = 500;
    stationY = 250;
    stationInitialY = stationY;
    stationH = 100;
    stationBot = stationY+stationH;
    collidable.x = stationX+40;
    collidable.y = stationY+(stationH/2);
    collidable.w = 105;
    collidable.h = stationH/2;
    interactable.x = collidable.x-2;
    interactable.y = collidable.y-2;
    interactable.w = collidable.w+4;
    interactable.h = collidable.h+4;

    //set infirmary image to stationTexture
    stationTexture.loadFromFile("images/sprites/infirmary.png",renderer);
    //setting text for station interaction
    stationDefaultInteractionText = "Healthy";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render infirmDefault string to infirmDefaultTexture!";
    }
}

void station::loadKitchen(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadKitchen(SDL_Renderer* renderer,TTF_Font* font)";

    //setup coords for kitchen + it's collision box, plus it's interaction box.
    stationX = 100;
    stationY = 250;
    stationInitialY = stationY;
    stationH = 100;
    stationBot = stationY+stationH;
    collidable.x = stationX;
    collidable.y = stationY+(stationH/2);
    collidable.w = 200;
    collidable.h = stationH/2;
    interactable.x=collidable.x-2;
    interactable.y=collidable.y-2;
    interactable.w=collidable.w+4;
    interactable.h=collidable.h+4;

    stationTexture.loadFromFile("images/sprites/kitchen.png",renderer);
    //setting text for waterTank interaction
    stationDefaultInteractionText = "Not Hungry";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render foodTime string to foodTimeTexture!";
    }
}

void station::loadPlanter(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadPlanter(SDL_Renderer* renderer,TTF_Font* font)";

    //setup coords for planter + it's collision box, plus it's interaction box.
    stationX = 600;
    stationY = 25;
    stationInitialY = stationY;
    stationH = 50;
    stationBot = stationY+stationH;
    collidable.x = stationX;
    collidable.y = stationY+(stationH/2);
    collidable.w = 100;
    collidable.h = stationH/2;
    interactable.x=collidable.x-2;
    interactable.y=collidable.y-2;
    interactable.w=collidable.w+4;
    interactable.h=collidable.h+4;

    stationTexture.loadFromFile("images/sprites/planter.png",renderer);
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

void station::loadBed(SDL_Renderer* renderer,TTF_Font* font)
{
    std::cout<<"\n running station::loadBed(SDL_Renderer* renderer,TTF_Font* font)";
    //Setup coords & collision box for bed
    stationX = 100;
    stationY = 500;
    stationInitialY = stationY;
    stationH = 37;
    stationBot = stationY + stationH;
    collidable.x = stationX;
    collidable.y = stationY+(stationH/2);
    collidable.w = 85;
    collidable.h = stationH/2;
    interactable.x=collidable.x-2;
    interactable.y=collidable.y-4;
    interactable.w=collidable.w+4;
    interactable.h=collidable.h+10;


    stationTexture.loadFromFile("images/sprites/sleepingbag.png",renderer);
    //setting text for station interaction
    stationDefaultInteractionText = "Not Tired";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render sleepyTime string to sleepyTimeTexture!";
    }
}

void station::updateHabPosition(int y)
{

    stationY = y + stationInitialY;
    stationBot = stationY + stationH;
    collidable.y=stationY + (stationH/2);
    interactable.y=collidable.y-4;
    /*
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

    habExitY = y+395;
    habExitBot = habExitY + habExitH;
    collidable[7].y = habExitY +(habExitH/2);
    interactable[7].y = collidable[7].y-2;



    //std::cout<<"\n \n collidable.y: "<<collidable.y;
    */
}

void station::updateEngPosition(int y)
{

    stationY = y + stationInitialY;
    stationBot = stationY + stationH;
    collidable.y = stationY + (stationH/2);
    interactable.y = collidable.y -4;
    /*
    engExitY = y+395;
    engExitBot = engExitY + engExitH;
    collidable[8].y=engExitY+(engExitH/2);
    interactable[8].y=collidable[8].y-4;
    */
}

void station::updateHabPosition2(int y)
{
    stationY = y + (stationInitialY - 600);
    stationBot = stationY + stationH;
    collidable.y = stationY + (stationH/2);
    interactable.y = collidable.y - 2;
    /*
    //this needs to be modified, stationary bicycle isn't showing up sometimes when it should.
    //std::cout<<"\n y: "<<y;
    bikeY = y+250;
    bikeBot = bikeY+bikeH;
    collidable[5].y = bikeY + (bikeH/2);
    interactable[5].y = collidable[5].y-2;

    recY = y + 250;
    recBot = recY + recH;
    collidable[6].y = recY + (recH/2);
    interactable[6].y = collidable[6].y-2;

    */
}

void station::updateEngPosition2(int y)
{

    stationY = y + stationInitialY;
    stationBot = stationY + stationH;
    collidable.y = stationY + (stationH/2);
    interactable.y = collidable.y -4;
    /*engExitY = y+395;
    engExitBot = engExitY + engExitH;
    collidable[8].y=engExitY+(engExitH/2);
    interactable[8].y=collidable[8].y-4;*/
}

void station::renderInteractEngExit(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractHabExit(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    x-=60;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

}

void station::renderInteractStation(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

/*
void station::renderInteractRec(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractBike(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractInfirmary(SDL_Renderer* renderer, int x, int y)
{
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractKitchen(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractWaterTank(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractBed(SDL_Renderer* renderer,int x, int y)
{
    //displays texture above player's head
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}*/

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

void station::renderHabStationBehindPlayer(SDL_Renderer* renderer,int playerBot)
{

    if(playerBot>stationBot)
    {
        stationTexture.render(stationX,stationY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }



    /*
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
        //planter textures going to have to change after timeSurvived - planterTimeWatered = 24hrs or greater
        //if planterDaysState is 5 or greater, planter state (texture) will have to progress
        //planterDaysState gets to 5 from being watered 5 times and a day passing after each of those 5 waterings

        if(planterState == 0  && !plantOkay)
        {
            //if player has sown the crops, but not yet watered
            if(waterPlantsOkay)
            {
                planterSownTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has sown & watered
            else if(!waterPlantsOkay)
            {
                planterSownWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 1)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterSeedlingTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterSeedlingWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 2)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterVegetativeTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterVegatativeWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 3)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterFloweringTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterFloweringWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 4)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterRipeTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterRipeWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }

        //if player hasn't sown or watered
        else if(plantOkay && !waterPlantsOkay)
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
    if(playerBot>recBot)
    {
        recTexture.render(recX,recY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot>habExitBot)
    {
        habExitTexture.render(habExitX,habExitY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    */

}

void station::renderEngStationBehindPlayer(SDL_Renderer* renderer,int playerBot)
{
    if(playerBot>stationBot)
    {
        stationTexture.render(stationX,stationY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void station::renderHabStationFrontPlayer(SDL_Renderer* renderer, int playerBot)
{

    if(playerBot<=stationBot)
    {
        stationTexture.render(stationX,stationY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }


    /*
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
        if(planterState == 0  && !plantOkay)
        {
            //if player has sown the crops, but not yet watered
            if(waterPlantsOkay)
            {
                planterSownTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has sown & watered
            else if(!waterPlantsOkay)
            {
                planterSownWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 1)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterSeedlingTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterSeedlingWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 2)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterVegetativeTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterVegatativeWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 3)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterFloweringTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterFloweringWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(planterState == 4)
        {
            //if player has not yet watered
            if(waterPlantsOkay)
            {
                planterRipeTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            //if player has watered
            else if(!waterPlantsOkay)
            {
                planterRipeWateredTexture.render(planterX,planterY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }

        //if player hasn't sown or watered
        else if(plantOkay && !waterPlantsOkay)
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
    if(playerBot<=recBot)
    {
        recTexture.render(recX,recY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(playerBot<=habExitBot)
    {
        habExitTexture.render(habExitX,habExitY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    */
}

void station::renderEngStationFrontPlayer(SDL_Renderer* renderer, int playerBot)
{
    if(playerBot<=stationBot)
    {
        stationTexture.render(stationX,stationY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}
void station::free()
{
    std::cout<<"\n running station::free()";
    stationTexture.free();
    stationDefaultInteractionTextTexture.free();
    /*
    habExitDefaultTexture.free();
    habExitTexture.free();
    engExitDefaultTexture.free();
    engExitTexture.free();
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
	recTexture.free();
	recDefaultTexture.free();*/
}

void station::updatePlant(int timeSurvived)
{
    std::cout<<"\n running station::updatePlant(int timeSurvived)";
    if(planterState<4)
    {
        if(timeSurvived-planterTimeWatered > 1440 && !waterPlantsOkay && !harvestOkay)
        {
            //1440 minutes is 24 hours... if at least that much time has passed, the plant is ready to be
            //watered again.  If the plant is harvestable, no need to water, so let's save the player from
            //accidentally wasting time watering.
            waterPlantsOkay = true;
            if(!harvestOkay)
            {//as long as the plant isn't ready for harvest, the number of days in current state of plant life cycle
                //increments.
                planterDaysState++;
            }
            if(planterDaysState >= 5 && !harvestOkay)
            {
                //if the plant has been at it's current state for 5+ days and isn't harvestable yet, increment the
                //state, then reset days at state to 0.
                planterState++;
                planterDaysState = 0;
                if(planterState == 4)
                {//if plant is old enough, it is harvestable.
                    harvestOkay = true;
                    waterPlantsOkay = false;
                }
            }
        }
    }

    std::cout<<"\n waterPlantsOkay: "<<waterPlantsOkay;
    std::cout<<"\n planterDaysState: "<<planterDaysState;
    std::cout<<"\n planterState: "<<planterState;
    std::cout<<"\n harvestOkay: "<<harvestOkay;
}
