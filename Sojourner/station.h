#ifndef STATION_H
#define STATION_H

#include "texture.h"

class station
{
    public:
        //constructor
        station();
        //destructor
        ~station();
        //bed (sleeping bag) coordinates
        int bedX, bedY;
        //watertank coordinates
        int waterTankX, waterTankY;
        //
        int planterX,planterY;
        //current number of stations
        const static int STATIONS = 3;
        //string for water level interaction of water tank station
        std::string waterLevel;
        std::string sleepyTime;
        std::string plantStatus;
        //the texture for the waterLevel stringstream
        Texture waterLevelTexture;
        Texture sleepyTimeTexture;
        Texture plantStatusTexture;
        //textures for stations
        Texture bedTexture;
        //idea for water tank / other upgrades: upgrades to stations = upgrades to UI,
        //ie: interact to gauge water before upgrade, after upgrade water level is part of UI.
        Texture waterTankTexture;
        Texture planterTexture;
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
        //loads textures for stations (sleepingbag image, water tank image)
        void loadStation(SDL_Renderer* renderer,TTF_Font* font);
        //when player walks around, the stations move with the background.
        void updatePosition(int y);
        //renders the textures
        void renderStation(SDL_Renderer* renderer);
        //frees the resources
        void free();

    private:

};

#endif // STATION_H
