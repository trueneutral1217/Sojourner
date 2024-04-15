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
        //std::cout<<"\n gauge["<<i<<"] value: "<<gauge[i];
        shipGauges[i] = std::to_string(gauge[i]);// << need[i];
        /*
        if(!gaugesTexture[i].loadFromRenderedText(shipGauges[i], textColor,font,renderer))
        {
            std::cout<<"\n unable to load shipGauges["<<i<<"] string to gaugesTexture["<<i<<"]";
        }*/
    }
    if(!gaugesTexture[0].loadFromRenderedText(shipGauges[0], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[0] string to gaugesTexture[0]";
    }
    if(!gaugesTexture[1].loadFromRenderedText(shipGauges[1], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[1] string to gaugesTexture[1]";
    }
    if(!gaugesTexture[2].loadFromRenderedText(shipGauges[2], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[2] string to gaugesTexture[2]";
    }
    if(!gaugesTexture[3].loadFromRenderedText(shipGauges[3], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[3] string to gaugesTexture[3]";
    }
    if(!gaugesTexture[4].loadFromRenderedText(shipGauges[4], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[4] string to gaugesTexture[4]";
    }
    if(!gaugesTexture[5].loadFromRenderedText(shipGauges[5], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[5] string to gaugesTexture[5]";
    }
}

void ship::reloadGaugesTextures(SDL_Renderer* renderer,TTF_Font* font)
{
    freeGaugesTextures();
    //when something happens that affects the ship's gauges, the text texture for that
    //gauge needs to be reloaded before being rendered again
    std::cout<<"\n running ship::reloadGaugesTextures(SDL_Renderer* renderer,TTF_Font* font)";

    //the font color is more red when it's closer to 0, more blue when it's closer to 100
    Uint8 r,b,g;
    r = 0;
    g = 128;
    b = 200;
    SDL_Color textColor = {r,g,b};

    for (int i = 0; i< TOTAL_SHIP_GAUGES; i++)
    {
        r = 255 - (gauge[i]*2.55);
        g = gauge[i]*1.28;
        b = gauge[i]*2;
        textColor = {r,g,b};
        shipGauges[i] = std::to_string(gauge[i]);
/*
        if(!gaugesTexture[i].loadFromRenderedText(shipGauges[i], textColor,font,renderer))
        {
            std::cout<<"\n unable to load shipGauges["<<i<<"] string to gaugesTexture["<<i<<"]";
        }*/
    }
    if(!gaugesTexture[0].loadFromRenderedText(shipGauges[0], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[0] string to gaugesTexture[0]";
    }
    if(!gaugesTexture[1].loadFromRenderedText(shipGauges[1], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[1] string to gaugesTexture[1]";
    }
    if(!gaugesTexture[2].loadFromRenderedText(shipGauges[2], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[2] string to gaugesTexture[2]";
    }
    if(!gaugesTexture[3].loadFromRenderedText(shipGauges[3], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[3] string to gaugesTexture[3]";
    }
    if(!gaugesTexture[4].loadFromRenderedText(shipGauges[4], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[4] string to gaugesTexture[4]";
    }
    if(!gaugesTexture[5].loadFromRenderedText(shipGauges[5], textColor,font,renderer))
    {
        std::cout<<"\n unable to load shipGauges[5] string to gaugesTexture[5]";
    }
}

void ship::renderGaugesTextures(SDL_Renderer* renderer)
{//for loop was causing a problem with rendering sometimes.  best to just do them all individually.
    /*
    for(int i = 0; i<TOTAL_SHIP_GAUGES; i++)
    {
        gaugesTexture[i].render(450+(i*60),40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }*/
    gaugesTexture[0].render(450,40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    gaugesTexture[1].render(510,40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    gaugesTexture[2].render(570,40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    gaugesTexture[3].render(630,40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    gaugesTexture[4].render(700,40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    gaugesTexture[5].render(760,40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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
    habitation.freeHab();
    engineering.freeEng();
    freeGaugesTextures();
}

void ship::loadSavedShipData(Sint32 dataValues[])
{
    std::cout<<"\n running ship::loadSavedShipData(Sint32 dataValues[])";
    //load ship gauges from save
    for(int i = 0; i<TOTAL_SHIP_GAUGES; i++)
    {
        gauge[i] = dataValues[i];
        //std::cout<<"\n gauge["<<i<<"]: "<<gauge[i];
    }
}

void ship::loadHabitationModule(SDL_Renderer* renderer,TTF_Font* font, int need[])
{
    habitation.loadHabitation(renderer,font,gauge,need);
}

void ship::loadEngineeringModule(SDL_Renderer* renderer,TTF_Font* font, int need[])
{
    engineering.loadEngineering(renderer,font,gauge,need);
    //inventory may need to start being loaded with the habitation module later on
    inventory.loadInventory(renderer,font);
    updateTotalResearchProjects();
    std::cout<<"\n \n \n \n bed.available research projects: "<<habitation.bed.availableResearchProjects;
    std::cout<<"\n researchDesk.available research projects: "<<engineering.researchDesk.availableResearchProjects;
}

void ship::updateTotalResearchProjects()
{
    std::cout<<"\n running ship::updateTotalResearchProjects()";
    //total research projects for habitation
    int TRP = 0;
    //sums it up from each station
    TRP += habitation.waterTank.availableResearchProjects;
    TRP += habitation.kitchen.availableResearchProjects;
    TRP += habitation.infirmary.availableResearchProjects;
    TRP += habitation.bed.availableResearchProjects;
    TRP += habitation.bike.availableResearchProjects;
    TRP += habitation.planter.availableResearchProjects;
    TRP += habitation.recreation.availableResearchProjects;
    std::cout<<"\n total habitation module research projects: "<<TRP;

    //total engineering research projects
    int TRP2 = 0;
    //sum from the stations from that module, except the research station.
    TRP2 += engineering.batteryArray.availableResearchProjects;
    TRP2 += engineering.engineStation.availableResearchProjects;
    TRP2 += engineering.cargoArea.availableResearchProjects;
    TRP2 += engineering.commStation.availableResearchProjects;

    std::cout<<"\n total engineering module research projects: "<<TRP2;
    int total = TRP + TRP2;

    engineering.researchDesk.availableResearchProjects = total;
}
