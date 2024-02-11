#ifndef SHIP_H
#define SHIP_H

#include "module.h"


const int TOTAL_SHIP_GAUGES = 6;

class ship
{
    public:

    ship();
    ~ship();

    module habitation;
    module engineering;

    //first inventory item
    int scrap;
    //string used to insert into scrap text texture
    std::string scrapString;
    //text texture for inventory
    Texture scrapTT;

    //ship guages (0-100 percent); hull, fuel, power, water, oxygen, temperature
    int gauge[TOTAL_SHIP_GAUGES];
    //strings for the ship's gauges
    std::string shipGauges[TOTAL_SHIP_GAUGES];
    //updates player's needs values (typically after interacting with a station)
    void modifyGauges(int modGaugeValues[]);
    //text textures for the UI, displays percentages of gauges
    Texture gaugesTexture[TOTAL_SHIP_GAUGES];
    //loads the gauges textures
    void loadGaugesTextures(SDL_Renderer* renderer, TTF_Font* font);
    //reloads the gauges textures (ideally after one of the values of gauges changes)
    void reloadGaugesTextures(SDL_Renderer* renderer,TTF_Font* font);
    //renders the gauges text textures
    void renderGaugesTextures(SDL_Renderer* renderer);
    //frees the text textures of the ship's gauges.
    void freeGaugesTextures();
    //free ship resources
    void free();
    //load ship saved data from file
    void loadSavedShipData(Uint32 dataValues[]);

    void loadHabitationModule(SDL_Renderer* renderer,TTF_Font* font, int need[]);

    void loadEngineeringModule(SDL_Renderer* renderer,TTF_Font* font, int need[]);
    //creates text texture for inventory
    void loadInventory(SDL_Renderer* renderer, TTF_Font* font);

    private:

};
#endif // SHIP_H
