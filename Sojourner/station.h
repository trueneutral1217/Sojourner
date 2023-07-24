#ifndef STATION_H
#define STATION_H

#include "texture.h"
#include "button.h"

class station
{
    public:
        //constructor
        station();
        //destructor
        ~station();
        //bed (sleeping bag) coordinates
        int bedX, bedY,bedH,bedBot;
        //watertank coordinates
        int waterTankX, waterTankY,waterTankH,waterTankBot;
        //planter coords
        int planterX,planterY,planterH,planterBot;
        //kitchen coords
        int kitchenX,kitchenY,kitchenH,kitchenBot;
        //current number of stations
        const static int STATIONS = 4;
        //string for water level interaction of water tank station
        std::string waterLevel;
        std::string sleepyTime;
        std::string plantStatus;
        std::string foodTime;
        //strings to be used to determine interaction type for planter
        std::string plant;
        std::string waterPlants;
        std::string harvest;
        //std::string cancel;
        //flags for planter options
        bool plantOkay;
        bool waterPlantsOkay;
        bool harvestOkay;
        //the texture for the waterLevel stringstream
        Texture waterLevelTexture;
        Texture sleepyTimeTexture;
        //Texture plantStatusTexture;
        Texture foodTimeTexture;
        //Textures for planter interaction
        Texture plantTexture;
        Texture waterPlantsTexture;
        Texture harvestTexture;
        //Texture cancelTexture;
        //textures for stations
        Texture bedTexture;
        //idea for water tank / other upgrades: upgrades to stations = upgrades to UI,
        //ie: interact to gauge water before upgrade, after upgrade water level is part of UI.
        Texture waterTankTexture;
        Texture planterTexture;
        Texture kitchenTexture;
        //the impassable area of the station
        SDL_Rect collidable[STATIONS];
        //the interactable area of the station
        SDL_Rect interactable[STATIONS];
        //loads the water tank interaction text texture with the current waterlevel (currently just using a
        //stringstream hard coded with "100L"
        void loadInteractWaterTank(SDL_Renderer* renderer,TTF_Font* font);
        //renders the water tank level text texture to screen
        void renderInteractWaterTank(SDL_Renderer* renderer,int x, int y);
        //loads bed interaction string and texture
        void loadInteractBed(SDL_Renderer* renderer,TTF_Font* font);
        //renders bed interaction text texture
        void renderInteractBed(SDL_Renderer* renderer,int x, int y);
        //loads Planter interaction string and text texture
        void loadInteractPlanter(SDL_Renderer* renderer,TTF_Font* font);
        //renders planter interaction text texture
        void renderInteractPlanter(SDL_Renderer* renderer,int x, int y);
        //load kitchen interaction string and text texture
        void loadInteractKitchen(SDL_Renderer* renderer, TTF_Font* font);
        //render kitchen interaction text texture
        void renderInteractKitchen(SDL_Renderer* renderer,int x, int y);
        //loads textures for stations (sleepingbag image, water tank image)
        void loadStation(SDL_Renderer* renderer,TTF_Font* font);
        //when player walks around, the stations move with the background.
        void updatePosition(int y);
        //renders the textures that belong behind player
        void renderStationBehindPlayer(SDL_Renderer* renderer,int playerBot);
        //renders the textures that belong in front of the player
        void renderStationFrontPlayer(SDL_Renderer* renderer, int playerBot);
        //frees the resources
        void free();

    private:

};

#endif // STATION_H
