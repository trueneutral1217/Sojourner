#include "station.h"

station::station()
{
    planterTimeWatered=0;
    planterDaysState=0;
    planterState=-1;
    stationOptionsLoaded=false;
    //stationTier = 0;
    //availableResearchProjects = 1;
}

station::~station()
{

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

    stationID = "water";

    /*
    int waterGauge = shipGaugeValues;
    stationTexture.loadFromFile("images/sprites/WaterTank.png",renderer);
    stationDefaultInteractionText = std::to_string(waterGauge);
    stationDefaultInteractionText = stationDefaultInteractionText + " Liters";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render waterLevel string to waterLevelTexture!";
    }*/

    if(stationTier == 0)
    {
        upgradeCost.insert({"scrap", 3});
        stationTexture.loadFromFile("images/sprites/waterTank.png",renderer);
        SDL_Color textColor = {0,255,0};//green color
        if(!stationResearch.loadFromRenderedText("Tier 2 water tank", textColor,font,renderer))
        {
            std::cout<<"\n unable to render 'Tier 2 water tank' string to waterResearch Texture!";
        }
        textColor = {255,255,255};//white
        if(!tierOneDescription.loadFromRenderedText("Upgrades the water tank.",textColor,font,renderer))
        {
            std::cout<<"\n unable to render string to tierOneDescription!";
        }
        if(!tierOneDescription2.loadFromRenderedText("Increase water capacity. Requires 2 hours, 3 scrap.",textColor,font,renderer))
        {
            std::cout<<"\n unable to render string to tierOneDescription2!";
        }
        if(!upgradeAvailable)
        {
            //since bed is tier 0, research for tier 1 is available.
            availableResearchProjects = 1;
        }
    }
    else if(stationTier == 1)
    {
        stationTexture.loadFromFile("images/sprites/waterTank2.png",renderer);
    }
    if(buttonString.size()==0)
    {
        //buttonString.push_back("Sleep");
        buttonString.push_back("Upgrade");
        std::cout<<"\n buttonString[0]: "<<buttonString[0];
    }
    Texture tempTextTexture;
    if(buttonTextTexture.size()==0)
    {
        //buttonTextTexture.push_back(tempTextTexture);
        buttonTextTexture.push_back(tempTextTexture);
        std::cout<<"\n buttonTextTexture.size(): "<<buttonTextTexture.size();
    }
    if(buttonAvailable.size() == 0)
    {//
        /*
        if(shipGaugeValues < 100)
        {
            buttonAvailable.push_back(true);
        }
        else
        {
            buttonAvailable.push_back(false);
        }*/
        //upgrade button availability
        if(!upgradeAvailable)
        {
            buttonAvailable.push_back(false);
        }
        else
        {
            buttonAvailable.push_back(true);
        }
    }
    std::cout<<"\n buttonAvailable.size(): "<<buttonAvailable.size();
    std::cout<<"\n buttonAvailable[0] = "<<buttonAvailable[0];
    loadStationButtonTextTextures(renderer,font);
}

void station::reloadStationResearchTexture(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"running station::reloadStationResearchTexture(SDL_Renderer* renderer, TTF_Font* font)";
    SDL_Color textColor = {0,255,0};//green color
    if(stationID == "water")
    {
        if(!stationResearch.loadFromRenderedText("Tier 2 water tank", textColor,font,renderer))
        {
            std::cout<<"\n unable to render 'Tier 2 water tank' string to waterResearch Texture!";
        }
    }
    if(stationID == "bed")
    {
        if(!stationResearch.loadFromRenderedText("Single Bed", textColor,font,renderer))
        {
            std::cout<<"\n unable to render 'Single Bed' string to bedResearch Texture!";
        }
    }
    if(stationID == "rec")
    {
        if(!stationResearch.loadFromRenderedText("Record player", textColor,font,renderer))
        {
            std::cout<<"\n unable to render 'Record player' string to stationResearch Texture!";
        }
    }
}

void station::loadEngExit(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadEngExit(SDL_Renderer* renderer, TTF_Font* font)";
    stationX = 10;
    stationY = 390;
    stationInitialY = stationY;
    stationH = 10;
    stationBot = stationY + stationH;
    collidable.x = stationX;
    collidable.y = stationY + (stationH/2);
    collidable.w = 10;
    collidable.h = stationH/2;
    interactable.x = collidable.x-3;
    interactable.y = collidable.y - 3;
    interactable.w = collidable.w + 6;
    interactable.h = collidable.h + 6;

    stationID = "engExit";

    stationTexture.loadFromFile("images/sprites/engExit.png",renderer);
    stationDefaultInteractionText = "Leaving Engineering Module";
    SDL_Color textColor = {255,255,255};
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(),textColor,font,renderer))
    {
       std::cout<<"\n unable to render engExitDefault string to engExitDefaultTexture!";
    }
}

void station::loadBatteryArray(SDL_Renderer* renderer, TTF_Font* font, int shipGaugeValues)
{
    std::cout<<"\n running station::loadBatteryArray(SDL_Renderer* renderer, TTF_Font* font, int shipGaugeValues)";

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

    stationID = "battery";

    int batteryGauge = shipGaugeValues;
    stationTexture.loadFromFile("images/sprites/batteryArray.png",renderer);
    stationDefaultInteractionText = std::to_string(batteryGauge);
    stationDefaultInteractionText = stationDefaultInteractionText + " percent charge";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render stationDefaultInteractionText string to stationDefaultInteractionTextTexture!";
    }
}

void station::loadCargoArea(SDL_Renderer* renderer, TTF_Font* font)
{
    //this should be the ship's inventory management station.
    std::cout<<"\n running station::loadCargoArea(SDL_Renderer* renderer, TTF_Font* font)";

     //setup coords & collision box for cargo area
    stationX = 500;
    stationY = 250;
    stationInitialY = stationY;
    stationH = 100;
    stationBot = stationY + stationH;
    collidable.x = stationX+6;
    collidable.y = stationY+(stationH/2);
    collidable.w = 187;
    collidable.h = stationH/2;
    interactable.x=collidable.x-2;
    interactable.y=collidable.y-4;
    interactable.w=collidable.w+6;
    interactable.h=collidable.h+6;

    stationID = "cargo";

    stationTexture.loadFromFile("images/sprites/cargoArea.png",renderer);
    /*
    stationDefaultInteractionText = "inventory management screen still in development";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render stationDefaultInteractionText string to stationDefaultInteractionTextTexture!";
    }*/

    inventoryBG.loadFromFile("images/inventory.png",renderer);

    buttonString.push_back("inventory");
    std::cout<<"\n buttonString[0]: "<<buttonString[0];
    Texture tempTextTexture;
    buttonTextTexture.push_back(tempTextTexture);
    if(buttonAvailable.size() == 0)
    {
        buttonAvailable.push_back(true);
    }
    loadStationButtonTextTextures(renderer,font);
}

void station::loadCommStation(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadCommStation(SDL_Renderer* renderer, TTF_Font* font)";

     //setup coords & collision box for comm station
    stationX = 600;
    stationY = 25;
    stationInitialY = stationY;
    stationH = 40;
    stationBot = stationY + stationH;
    collidable.x = stationX+6;
    collidable.y = stationY+(stationH/2);
    collidable.w = 87;
    collidable.h = stationH/2;
    interactable.x=collidable.x-2;
    interactable.y=collidable.y-4;
    interactable.w=collidable.w+6;
    interactable.h=collidable.h+6;

    stationID = "comm";


    stationTexture.loadFromFile("images/sprites/commStation.png",renderer);
    stationDefaultInteractionText = "comm station still in development";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render stationDefaultInteractionText string to stationDefaultInteractionTextTexture!";
    }
}

void station::loadEngineStation(SDL_Renderer* renderer, TTF_Font* font, int shipGaugeValues)
{
    std::cout<<"\n running station::loadEngineStation(SDL_Renderer* renderer, TTF_Font* font, int shipGaugeValues)";

     //setup coords & collision box for engine station
    stationX = 100;
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

    stationID = "engine";

    int fuelGauge = shipGaugeValues;
    stationTexture.loadFromFile("images/sprites/engineStation.png",renderer);
    stationDefaultInteractionText = std::to_string(fuelGauge);
    stationDefaultInteractionText = stationDefaultInteractionText + " percent fuel";
    SDL_Color textColor = {255,255,255};//white
    if(!stationDefaultInteractionTextTexture.loadFromRenderedText(stationDefaultInteractionText.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render stationDefaultInteractionText string to stationDefaultInteractionTextTexture!";
    }
}

void station::loadResearchDesk(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running station::loadResearchDesk(SDL_Renderer* renderer, TTF_Font* font)";

     //setup coords & collision box for research desk
    stationX = 100;
    stationY = 500;
    stationInitialY = stationY;
    stationH = 45;
    stationBot = stationY + stationH;
    collidable.x = stationX;
    collidable.y = stationY+(stationH/2);
    collidable.w = 90;
    collidable.h = stationH/2;
    interactable.x=collidable.x-3;
    interactable.y=collidable.y-3;
    interactable.w=collidable.w+6;
    interactable.h=collidable.h+6;

    stationID = "research";

    stationTexture.loadFromFile("images/sprites/researchDesk.png",renderer);

    researchBG.loadFromFile("images/research.png",renderer);

    buttonString.push_back("Research");
    std::cout<<"\n buttonString[0]: "<<buttonString[0];
    Texture tempTextTexture;
    if(buttonTextTexture.size() == 0)
    {
        buttonTextTexture.push_back(tempTextTexture);
    }

    if(buttonAvailable.size() == 0)
    {
        buttonAvailable.push_back(true);
    }
    loadStationButtonTextTextures(renderer,font);
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
    interactable.x = collidable.x - 3;
    interactable.y = collidable.y - 3;
    interactable.w = collidable.w + 6;
    interactable.h = collidable.h + 6;

    stationID = "habExit";

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

    stationID = "rec";


    if(stationTier == 0)
    {
        upgradeCost.insert({"scrap", 2});
        stationTexture.loadFromFile("images/sprites/recreation.png",renderer);
        SDL_Color textColor = {0,255,0};//green
        if(!stationResearch.loadFromRenderedText("Record player", textColor,font,renderer))
        {
            std::cout<<"\n unable to render 'Record player' string to stationResearch Texture!";
        }
        textColor = {255,255,255};//white
        if(!tierOneDescription.loadFromRenderedText("Upgrades the recreation station",textColor,font,renderer))
        {
            std::cout<<"\n unable to render string to tierOneDescription!";
        }
        if(!tierOneDescription2.loadFromRenderedText("Increase rec efficiency. Requires 2 hours, 2 scrap.",textColor,font,renderer))
        {
            std::cout<<"\n unable to render string to tierOneDescription2!";
        }
        if(!upgradeAvailable)
        {
            //since bed is tier 0, research for tier 1 is available.
            availableResearchProjects = 1;
        }
    }
    else if(stationTier == 1)
    {
        stationTexture.loadFromFile("images/sprites/recreationTier1.png",renderer);
    }
    if(buttonString.size()==0)
    {
        buttonString.push_back("Relax");
        buttonString.push_back("Upgrade");
        std::cout<<"\n buttonString[0]: "<<buttonString[0]<<"\n buttonString[1]: "<<buttonString[1];
    }
    Texture tempTextTexture;
    if(buttonTextTexture.size()==0)
    {
        buttonTextTexture.push_back(tempTextTexture);
        buttonTextTexture.push_back(tempTextTexture);
    }
    if(buttonAvailable.size() == 0)
    {//relax button availability
        if(need < 100)
        {
            buttonAvailable.push_back(true);
        }
        else
        {
            buttonAvailable.push_back(false);
        }
        //upgrade button availability
        if(!upgradeAvailable)
        {
            buttonAvailable.push_back(false);
        }
        else
        {
            buttonAvailable.push_back(true);
        }

    }
}

void station::loadStationButtonTextTextures(SDL_Renderer* renderer,TTF_Font* font,int need)
{//renders the color of the font of the button black for unavailable, white for available, based on player needs
    std::cout<<"\n running station::loadStationButtonTextTextures(SDL_Renderer* renderer,TTF_Font* font,int need)";
    std::cout<<"\n buttonTextTexture.size() = "<<buttonTextTexture.size();
    if(buttonTextTexture.size()>0)
    {
        for(Uint32 i = 0; i<buttonTextTexture.size(); i++)
        {//this will make the first text texture available if need <100, buttons after the first are not checked.
            if(i == 0)
            {
                if(need == 100)
                {
                    std::cout<<"\n unavailable";
                    if(!buttonTextTexture[i].loadFromRenderedText(buttonString[i],unavailable,font,renderer))
                    {
                        std::cout<<"\n unable to render station button text to station button text texture!";
                    }
                }
                else
                {
                    std::cout<<"\n available";
                    if(!buttonTextTexture[i].loadFromRenderedText(buttonString[i],available,font,renderer))
                    {
                        std::cout<<"\n unable to render station button text to station button text texture!";
                    }
                }
            }
            else
            {
                if(!buttonAvailable[i])
                {
                    std::cout<<"\n unavailable";
                    if(!buttonTextTexture[i].loadFromRenderedText(buttonString[i],unavailable,font,renderer))
                    {
                        std::cout<<"\n unable to render station button text to station button text texture!";
                    }
                }
                else
                {
                    std::cout<<"\n available";
                    if(!buttonTextTexture[i].loadFromRenderedText(buttonString[i],available,font,renderer))
                    {
                        std::cout<<"\n unable to render station button text to station button text texture!";
                    }
                }
            }
        }
    }
    //tells the stage.handleStation function not to keep running this function.
    stationOptionsLoaded = true;
}

void station::loadStationButtonTextTextures(SDL_Renderer* renderer,TTF_Font* font)
{//renders the color of the font of the button black for unavailable, white for available
    std::cout<<"\n running station::loadStationButtonTextTextures(SDL_Renderer* renderer,TTF_Font* font)";
    std::cout<<"\n buttonTextTexture.size() = "<<buttonTextTexture.size();
    if(buttonTextTexture.size()>0)
    {
        for(Uint32 i = 0; i<buttonTextTexture.size(); i++)
        {
            if(!buttonAvailable[i])
            {
                std::cout<<"\n unavailable";
                if(!buttonTextTexture[i].loadFromRenderedText(buttonString[i],unavailable,font,renderer))
                {
                    std::cout<<"\n unable to render station button text to station button text texture!";
                }
            }
            else
            {
                std::cout<<"\n available";
                if(!buttonTextTexture[i].loadFromRenderedText(buttonString[i],available,font,renderer))
                {
                    std::cout<<"\n unable to render station button text to station button text texture!";
                }
            }
        }
    }
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

    stationID = "bike";
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
    stationH = 80;
    stationBot = stationY+stationH;
    collidable.x = stationX+40;
    collidable.y = stationY+(stationH/2);
    collidable.w = 105;
    collidable.h = stationH/2;
    interactable.x = collidable.x-2;
    interactable.y = collidable.y-3;
    interactable.w = collidable.w+4;
    interactable.h = collidable.h+6;

    stationID = "infirmary";

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

    stationID = "kitchen";

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

    stationID = "planter";

    if(planterState == -1)
    {
        stationTexture.loadFromFile("images/sprites/planter.png",renderer);
    }
    if(buttonString.size() == 0)
    {
        buttonString.push_back("Plant");
        std::cout<<"\n buttonString[0]: "<<buttonString[0];
    }
    if(buttonString.size()==1)
    {
        buttonString.push_back("Water Plants");
        std::cout<<"\n buttonString[1]: "<<buttonString[1];
    }
    if(buttonString.size()==2)
    {
        buttonString.push_back("Harvest");
        std::cout<<"\n buttonString[2]: "<<buttonString[2];
    }
    Texture tempTextTexture;
    if(buttonTextTexture.size()==0)
    {
        buttonTextTexture.push_back(tempTextTexture);
        buttonTextTexture.push_back(tempTextTexture);
        buttonTextTexture.push_back(tempTextTexture);
    }
    std::cout<<"\n buttonTextTexture.size() = "<<buttonTextTexture.size();
    if(buttonAvailable.size() == 0)
    {
        buttonAvailable.push_back(true); //plant
        buttonAvailable.push_back(false); //water
        buttonAvailable.push_back(false); //harvest
    }
    loadStationButtonTextTextures(renderer,font);
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

    stationID = "bed";

    if(stationTier == 0)
    {
        upgradeCost.insert({"scrap", 3});
        stationTexture.loadFromFile("images/sprites/sleepingbag.png",renderer);
        SDL_Color textColor = {0,255,0};//unknown color
        if(!stationResearch.loadFromRenderedText("Single Bed", textColor,font,renderer))
        {
            std::cout<<"\n unable to render 'Single Bed' string to bedResearch Texture!";
        }
        textColor = {255,255,255};//white
        if(!tierOneDescription.loadFromRenderedText("Upgrades the sleeping bag to a single bed",textColor,font,renderer))
        {
            std::cout<<"\n unable to render string to tierOneDescription!";
        }
        if(!tierOneDescription2.loadFromRenderedText("Increase sleep efficiency. Requires 2 hours, 3 scrap.",textColor,font,renderer))
        {
            std::cout<<"\n unable to render string to tierOneDescription2!";
        }
        if(!upgradeAvailable)
        {
            //since bed is tier 0, research for tier 1 is available.
            availableResearchProjects = 1;
        }
    }
    else if(stationTier == 1)
    {
        stationTexture.loadFromFile("images/sprites/singleBed.png",renderer);
    }
    if(buttonString.size()==0)
    {
        buttonString.push_back("Sleep");
        buttonString.push_back("Upgrade");
        std::cout<<"\n buttonString[1]: "<<buttonString[1];
    }
    Texture tempTextTexture;
    if(buttonTextTexture.size()==0)
    {
        buttonTextTexture.push_back(tempTextTexture);
        buttonTextTexture.push_back(tempTextTexture);
    }
    if(buttonAvailable.size() == 0)
    {//sleep button availability
        if(need < 100)
        {
            buttonAvailable.push_back(true);
        }
        else
        {
            buttonAvailable.push_back(false);
        }
        //upgrade button availability
        if(!upgradeAvailable)
        {
            buttonAvailable.push_back(false);
        }
        else
        {
            buttonAvailable.push_back(true);
        }

    }
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
//    std::cout<<"\n"<<stationDefaultInteractionText;
    y-=20;
    //if the right half of the default text texture is on the screen, just render it.
    if(x+stationDefaultInteractionTextTexture.getWidth() < 800)
    {
        stationDefaultInteractionTextTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    else
    {//if the right half of the default text texture is off the screen, shift it left.
        if(stationDefaultInteractionTextTexture.getWidth() < x)
        {
            int temp = x - stationDefaultInteractionTextTexture.getWidth();
            stationDefaultInteractionTextTexture.render(temp,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {//if the default text texture width is larger than x, there may be some text cut off at the right, but
            //this aligns the text as far left as possible.
            int temp2 = 800 - stationDefaultInteractionTextTexture.getWidth();
            if(temp2<0)
            {
                temp2 = 0;
            }
            stationDefaultInteractionTextTexture.render(temp2,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }


}

void station::renderInteractStationButtons(SDL_Renderer* renderer, int x, int y)
{
    if(buttonTextTexture.size() > 0)
    {
        x+=50;
        y-=20;
        buttonTextTexture[0].render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        if(buttonTextTexture.size() > 1)
        {
            for(Uint32 i = 1; i<buttonTextTexture.size(); i++)
            {
                y+=20;
                buttonTextTexture[i].render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
    }
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
    while(buttonString.size()>0)
    {
        buttonString.pop_back();
    }
    while(buttonTextTexture.size()>0)
    {
        buttonTextTexture.pop_back();
    }
    while(buttonAvailable.size()>0)
    {
        buttonAvailable.pop_back();
    }
}

void station::updatePlant(SDL_Renderer* renderer, int timeSurvived)
{
    std::cout<<"\n running station::updatePlant(int timeSurvived)";
    if(planterState<4)
    {
        if(timeSurvived-planterTimeWatered > 1440 && !buttonAvailable[1] && !buttonAvailable[2])
        {
            //1440 minutes is 24 hours... if at least that much time has passed, the plant is ready to be
            //watered again.  If the plant is harvestable, no need to water, so let's save the player from
            //accidentally wasting time watering.
            buttonAvailable[1] = true;
            planterDaysState++;
            if(planterDaysState >= 5)
            {
                //if the plant has been at it's current state for 5+ days and isn't harvestable yet, increment the
                //state, then reset days at state to 0.
                planterState++;
                planterDaysState = 0;
                if(planterState == 4)
                {//if plant is old enough, it is harvestable.
                    buttonAvailable[2] = true;
                    buttonAvailable[1] = false;
                }
            }
        }
    }
    std::cout<<"\n waterPlantsOkay: "<<buttonAvailable[1];
    std::cout<<"\n planterDaysState: "<<planterDaysState;
    std::cout<<"\n planterState: "<<planterState;
    std::cout<<"\n harvestOkay: "<<buttonAvailable[2];
    updatePlantTexture(renderer);
}

void station::updatePlantTexture(SDL_Renderer* renderer)
{
    std::cout<<"\n running station::updatePlantTexture(SDL_Renderer* renderer)";
    stationTexture.free();
    std::cout<<"\n waterPlantsOkay: "<<buttonAvailable[1];
    std::cout<<"\n planterState: "<<planterState;
    if(buttonAvailable[1])
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
    {//if plant is not sown
        stationTexture.loadFromFile("images/sprites/planter.png",renderer);
    }
}

void station::displayInventory(SDL_Renderer* renderer)
{//currently not in use
    //std::cout<<"\n running station::displayInventory()";
    if(inventoryDisplaying)
    {
        inventoryBG.render(50,150,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void station::freeInventory()
{
    std::cout<<"\n running station::freeInventory()";
    inventoryBG.free();
}

void station::freeResearch()
{
    std::cout<<"\n running station::freeResearch()";
    researchBG.free();
}

void station::updateStationTexture(SDL_Renderer* renderer)
{
    std::cout<<"\n running station::updateStationTexture";
    if(stationID == "bed")
    {
        if(stationTier == 1)
        {
            stationTexture.loadFromFile("images/sprites/singleBed.png",renderer);
        }
    }
    else if(stationID == "rec")
    {
        if(stationTier == 1)
        {
            stationTexture.loadFromFile("images/sprites/recreationTier1.png",renderer);
        }
    }
    else if(stationID == "water")
    {
        if(stationTier == 1)
        {
            stationTexture.loadFromFile("images/sprites/waterTank2.png",renderer);
        }
    }
}

void station::updateUpgradeAvailability()
{//this only works for bed right now, will have to make sure the last button is always the upgrade button for this to work correctly.
    std::cout<<"\n running station::updateUpgradeAvailability()";
    std::cout<<"\n upgradeAvailable: "<<upgradeAvailable;
    std::cout<<"\n buttonAvailable.size(): "<<buttonAvailable.size();
    buttonAvailable[(buttonAvailable.size()-1)] = upgradeAvailable;
}
