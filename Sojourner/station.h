#ifndef STATION_H
#define STATION_H

#include "texture.h"
#include "button.h"
#include <vector>
#include <unordered_map>
#include <map>

class station
{
    public:
        //constructor
        station();
        //destructor
        ~station();

        int stationX,stationY,stationH,stationBot;
        //used when keeping the stations stationary while player moves up and down in module.
        int stationInitialY;

        int planterTimeWatered, planterDaysState, planterState;

        int stationTier;

        const static int STATIONS = 10;

        std::string stationDefaultInteractionText;

        //strings for interaction button text textures
        std::vector<std::string> buttonString;
        //flags for button availability (to player).  true = clickable,white.  false = not clickable/black.
        std::vector<bool> buttonAvailable;

        //the two bools below are to determine whether or not to load/render text texture buttons for planting, etc.
        //could possibly reduce to 1.
        bool stationOptionsLoaded;

        //this is currently only used for the waterTank I think, it's redundant, might delete.
        Texture stationDefaultInteractionTextTexture;

        Texture inventoryBG, researchBG;
        //text texture for bed research button
        Texture bedResearch;
        //text texture for upgrade description
        Texture tierOneDescription, tierOneDescription2;

        bool inventoryDisplaying,researchDisplaying;
        //each station has it's available research projects, the research desk is the sum of all of those.
        int availableResearchProjects;

        bool upgradeAvailable;
        //hash map of inventory items (by item name), and amount required to update a station.
        std::unordered_map<std::string, int> upgradeCost;

        //if the button is clickable, it shows up white, else black.
        SDL_Color available = {255,255,255};//white
        SDL_Color unavailable = {0,0,0};//black

        std::vector<Texture> buttonTextTexture;

        //idea for water tank / other upgrades: upgrades to stations = upgrades to UI,
        //ie: interact to gauge water before upgrade, after upgrade water level is part of UI.

        //this is the image of the station that is rendered to the module the player is in.
        Texture stationTexture;

        //the impassable area of the station
        SDL_Rect collidable;
        //the interactable area of the station
        SDL_Rect interactable;

        //when interacting with a station, these two set up the render color for text textures
        void loadStationButtonTextTextures(SDL_Renderer* renderer, TTF_Font* font,int need);
        void loadStationButtonTextTextures(SDL_Renderer* renderer, TTF_Font* font);
        //when loading stage, these functions set up each station
        //hab stations
        void loadHabExit(SDL_Renderer* renderer, TTF_Font* font);
        void loadRec(SDL_Renderer* renderer, TTF_Font* font,int need);
        void loadBike(SDL_Renderer* renderer, TTF_Font* font, int need);
        void loadInfirmary(SDL_Renderer* renderer, TTF_Font* font, int need);
        void loadWaterTank(SDL_Renderer* renderer,TTF_Font* font, int waterGauge);
        void loadBed(SDL_Renderer* renderer,TTF_Font* font, int need);
        void loadPlanter(SDL_Renderer* renderer,TTF_Font* font);
        void loadKitchen(SDL_Renderer* renderer, TTF_Font* font,int need);
        //engineering stations
        void loadEngExit(SDL_Renderer* renderer, TTF_Font* font);
        void loadBatteryArray(SDL_Renderer* renderer, TTF_Font* font, int powerGauge);
        void loadResearchDesk(SDL_Renderer* renderer, TTF_Font* font);
        void loadEngineStation(SDL_Renderer* renderer, TTF_Font* font, int fuelGauge);
        void loadCargoArea(SDL_Renderer* renderer, TTF_Font* font);
        void loadCommStation(SDL_Renderer* renderer, TTF_Font* font);
        //these two might not be used, considering deleting
        void renderInteractEngExit(SDL_Renderer* renderer, int x, int y);
        void renderInteractHabExit(SDL_Renderer* renderer, int x, int y);
        //functions for rendering interaction buttons like 'plant', 'sleep', etc.
        void renderInteractStation(SDL_Renderer* renderer, int x, int y);
        //renders the text textures for the stations' buttons, based on player coords sent in.
        void renderInteractStationButtons(SDL_Renderer* renderer, int x,int y);
        //when player walks around, the stations move with the background.
        void updateHabPosition(int y);
        //for the stations that are rendered on the second hab bg.
        void updateHabPosition2(int y);
        //updates first engineering background image to parallax as player walks up/down
        void updateEngPosition(int y);
        //updates the second background image
        void updateEngPosition2(int y);
        //renders the textures that belong behind player
        void renderHabStationBehindPlayer(SDL_Renderer* renderer,int playerBot);
        //renders the textures that belong in front of the player
        void renderHabStationFrontPlayer(SDL_Renderer* renderer, int playerBot);
        //renders stations behind player in engineering module
        void renderEngStationBehindPlayer(SDL_Renderer* renderer, int playerBot);
        //renders stations in front of player in engineering module
        void renderEngStationFrontPlayer(SDL_Renderer* renderer, int playerBot);
        //frees the resources
        void free();
        //update's plant's state based on time survived
        void updatePlant(SDL_Renderer* renderer, int timeSurvived);
        //update's plant's texture
        void updatePlantTexture(SDL_Renderer* renderer);
        //when the cargo area's inventory button is clicked, this displays the inventory
        void displayInventory(SDL_Renderer* renderer);
        //frees inventory background
        void freeInventory();
        //frees research background
        void freeResearch();
        //updates station Texture based on tier
        void updateStationTexture(SDL_Renderer* renderer);
        //makes upgrade available or unavailable
        void updateUpgradeAvailability();

    private:

};

#endif // STATION_H
