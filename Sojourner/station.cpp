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
    stationOptionsLoaded=false;
    //flag the interact buttons to reload.
    //interacted = false;

}

station::~station()
{

}

void station::loadStation(SDL_Renderer* renderer,TTF_Font* font,int shipGaugeValues[])
{
    std::cout<<"\n running station::loadStation(SDL_Renderer* renderer,TTF_Font* font)";

    //habExitTexture.loadFromFile("images/sprites/habExit.png",renderer);

/*

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

void station::loadRec(SDL_Renderer* renderer, TTF_Font* font, int need)
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
    buttonString.push_back("Relax");
    std::cout<<"\n buttonString[0]: "<<buttonString[0];
    Texture tempTextTexture;
    buttonTextTexture.push_back(tempTextTexture);
    loadStationButtonTextTextures(renderer,font,need);
}

void station::loadStationButtonTextTextures(SDL_Renderer* renderer,TTF_Font* font,int need)
{
    std::cout<<"\n running station::loadStationButtonTextTextures(SDL_Renderer* renderer,TTF_Font* font,int need)";
    std::cout<<"\n buttonTextTexture.size() = "<<buttonTextTexture.size();
    //Texture tempTextTexture;
    if(need == 100)
    {
        std::cout<<"\n unavailable";
        if(!buttonTextTexture[0].loadFromRenderedText(buttonString[0],unavailable,font,renderer))
        {
            std::cout<<"\n unable to render station button text to station button text texture!";
        }
    }
    else
    {
        std::cout<<"\n available";
        if(!buttonTextTexture[0].loadFromRenderedText(buttonString[0],available,font,renderer))
        {
            std::cout<<"\n unable to render station button text to station button text texture!";
        }
    }
    //buttonTextTexture.push_back(tempTextTexture);
    std::cout<<"\n buttonTextTexture.size() = "<<buttonTextTexture.size();
    //tells the stage.handleStation function not to keep running this function.
    stationOptionsLoaded = true;
}

void station::loadBike(SDL_Renderer* renderer, TTF_Font* font, int need)
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
    buttonString.push_back("Exercise");
    std::cout<<"\n buttonString[0]: "<<buttonString[0];
    Texture tempTextTexture;
    buttonTextTexture.push_back(tempTextTexture);
    loadStationButtonTextTextures(renderer,font,need);
}

void station::loadInfirmary(SDL_Renderer* renderer,TTF_Font* font,int need)
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
    interactable.y = collidable.y-3;
    interactable.w = collidable.w+4;
    interactable.h = collidable.h+6;
    //set infirmary image to stationTexture
    stationTexture.loadFromFile("images/sprites/infirmary.png",renderer);
    buttonString.push_back("Heal");
    std::cout<<"\n buttonString[0]: "<<buttonString[0];
    Texture tempTextTexture;
    buttonTextTexture.push_back(tempTextTexture);
    loadStationButtonTextTextures(renderer,font,need);
}

void station::loadKitchen(SDL_Renderer* renderer,TTF_Font* font, int need)
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
    interactable.y=collidable.y-3;
    interactable.w=collidable.w+4;
    interactable.h=collidable.h+6;
    stationTexture.loadFromFile("images/sprites/kitchen.png",renderer);
    buttonString.push_back("Eat");
    std::cout<<"\n buttonString[0]: "<<buttonString[0];
    Texture tempTextTexture;
    buttonTextTexture.push_back(tempTextTexture);
    loadStationButtonTextTextures(renderer,font,need);
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
    if(planterState == -1)
    {
        stationTexture.loadFromFile("images/sprites/planter.png",renderer);
    }

    //setting text for planter interaction
    plant="Plant";
    waterPlants = "Water Plants";
    harvest = "Harvest";

    loadPlanterTextTextures(renderer,font);
}

void station::loadPlanterTextTextures(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadPlanterTextTextures(SDL_Renderer* renderer, TTF_Font* font)";
    std::cout<<"\n plant string: "<<plant;
    if(plantOkay)
    {
        if(!plantTexture.loadFromRenderedText(plant.c_str(), available,font,renderer))
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
        if(!waterPlantsTexture.loadFromRenderedText(waterPlants.c_str(), available,font,renderer))
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
        if(!harvestTexture.loadFromRenderedText(harvest.c_str(), available,font,renderer))
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

stationOptionsLoaded = true;
}

void station::loadBed(SDL_Renderer* renderer,TTF_Font* font,int need)
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
    buttonString.push_back("Sleep");
    std::cout<<"\n buttonString[0]: "<<buttonString[0];
    Texture tempTextTexture;
    buttonTextTexture.push_back(tempTextTexture);
    loadStationButtonTextTextures(renderer,font,need);
}

void station::updateHabPosition(int y)
{
    //when player moves, background parallaxes, this makes sure the stations move with the bg.
    stationY = y + stationInitialY;
    stationBot = stationY + stationH;
    collidable.y=stationY + (stationH/2);
    interactable.y=collidable.y-4;

}

void station::updateEngPosition(int y)
{

    stationY = y + stationInitialY;
    stationBot = stationY + stationH;
    collidable.y = stationY + (stationH/2);
    interactable.y = collidable.y -4;

}

void station::updateHabPosition2(int y)
{
    stationY = y + (stationInitialY - 600);
    stationBot = stationY + stationH;
    collidable.y = stationY + (stationH/2);
    interactable.y = collidable.y - 2;

}

void station::updateEngPosition2(int y)
{

    stationY = y + stationInitialY;
    stationBot = stationY + stationH;
    collidable.y = stationY + (stationH/2);
    interactable.y = collidable.y -4;

}

void station::renderInteractStation(SDL_Renderer* renderer, int x, int y)
{
    //std::cout<<"\n running station::renderInteractStation(SDL_Renderer* renderer, int x, int y)";
    std::cout<<"\n"<<stationDefaultInteractionText;
    y-=20;
    stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractStationButtons(SDL_Renderer* renderer, int x, int y)
{
    x+=50;
    y-=20;
    buttonTextTexture[0].render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderInteractPlanter(SDL_Renderer* renderer,int x, int y)
{//these are the buttons that pop up when player is next to the planter and presses 'e'
    //displays textures to the right of player texture
    x+=50;
    //displays texture above player's head
    y-=20;
    //text texture 'Plant'
    plantTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //render below previous option
    y+=20;
    //text texture 'water'
    waterPlantsTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //render below previous option
    y+=20;
    //text texture 'harvest'
    harvestTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void station::renderHabStationBehindPlayer(SDL_Renderer* renderer,int playerBot)
{
    if(playerBot>stationBot)
    {
        stationTexture.render(stationX,stationY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
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
    for(int i=0;i<buttonString.size();i++)
    {
        buttonString[i] = "";
        buttonString.pop_back();
    }
    for(int i=0;i<buttonTextTexture.size();i++)
    {
        buttonTextTexture[i].free();
        buttonTextTexture.pop_back();
    }
    //sleepTexture.free();
}

void station::updatePlant(SDL_Renderer* renderer, int timeSurvived)
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
    updatePlantTexture(renderer);
}

void station::updatePlantTexture(SDL_Renderer* renderer)
{
    std::cout<<"\n running station::updatePlantTexture(SDL_Renderer* renderer)";
    stationTexture.free();
    std::cout<<"\n waterPlantsOkay: "<<waterPlantsOkay;
    std::cout<<"\n planterState: "<<planterState;
    if(waterPlantsOkay)
    {//if plants are dry
        switch(planterState)
        {//load texture based on state (lifecycle) of the plant.
            case 0:
                stationTexture.loadFromFile("images/sprites/planterSown.png",renderer);
                break;
            case 1:
                stationTexture.loadFromFile("images/sprites/planterSeedling.png",renderer);
                break;
            case 2:
                stationTexture.loadFromFile("images/sprites/planterVegetative.png",renderer);
                break;
            case 3:
                stationTexture.loadFromFile("images/sprites/planterFlowering.png",renderer);
                break;
            case 4:
                stationTexture.loadFromFile("images/sprites/planterRipe.png",renderer);
                break;
        }
    }
    else
    {//plants are watered
        switch(planterState)
        {
            case 0:
                stationTexture.loadFromFile("images/sprites/planterSownWatered.png",renderer);
                break;
            case 1:
                stationTexture.loadFromFile("images/sprites/planterSeedlingWatered.png",renderer);
                break;
            case 2:
                stationTexture.loadFromFile("images/sprites/planterVegetativeWatered.png",renderer);
                break;
            case 3:
                stationTexture.loadFromFile("images/sprites/planterFloweringWatered.png",renderer);
                break;
            case 4:
                stationTexture.loadFromFile("images/sprites/planterRipeWatered.png",renderer);
                break;
        }
    }
    if(planterState == -1)
    {
        stationTexture.loadFromFile("images/sprites/planter.png",renderer);
    }

}
