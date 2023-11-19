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
        int infirmX, infirmY,infirmH,infirmBot;

        int bikeX,bikeY,bikeH,bikeBot;

        int recX,recY,recH,recBot;

        int habExitX, habExitY,habExitH,habExitBot;

        int engExitX, engExitY,engExitH,engExitBot;

        int planterTimeWatered, planterDaysState, planterState;

        const static int STATIONS = 9;


        std::string engExitDefault;

        std::string habExitDefault;

        std::string recDefault;

        std::string bikeDefault;
        std::string infirmDefault;
        //string for water level interaction of water tank station
        std::string waterLevel;
        //currently 'not tired'
        std::string sleepyTime;

        std::string plantStatus;
        std::string foodTime;
        //strings to be used to determine interaction type for planter
        std::string plant;
        std::string waterPlants;
        std::string harvest;
        //std::string cancel;
        //flags for planter options.  true sets font to white, false to black.
        bool plantOkay;
        bool waterPlantsOkay;
        bool harvestOkay;
        //the two bools below are to determine whether or not to load/render text texture buttons for planting, etc.
        //could possibly reduce to 1.
        bool planterOptionsLoaded;
        bool planterOptionsFreed;
        //these two could probably be removed as plantOkay and waterPlantsOkay probably equal opposite of these always
//        bool planterSown;
       // bool planterWatered;
        //need to track time that the plants have been growing to update plant texture to show lifecycle of plant,
        //and eventually set harvestOkay to true when the plant is fully grown.

        bool interacted;

        Texture engExitDefaultTexture;

        Texture habExitDefaultTexture;

        Texture recDefaultTexture;

        Texture bikeDefaultTexture;
        Texture infirmDefaultTexture;
        //the texture for the waterLevel string
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
        Texture recTexture;
        Texture bikeTexture;
        Texture infirmaryTexture;
        Texture waterTankTexture;
        Texture planterTexture;
        Texture planterSownTexture;
        Texture planterSownWateredTexture;
        Texture planterSeedlingTexture;
        Texture planterSeedlingWateredTexture;
        Texture planterVegetativeTexture;
        Texture planterVegatativeWateredTexture;
        Texture planterFloweringTexture;
        Texture planterFloweringWateredTexture;
        Texture planterRipeTexture;
        Texture planterRipeWateredTexture;

        Texture habExitTexture;//currently no texture for this, might just do a 10x10 fully transparent square/rect
        Texture engExitTexture;

        Texture kitchenTexture;
        //the impassable area of the station
        SDL_Rect collidable[STATIONS];
        //the interactable area of the station
        SDL_Rect interactable[STATIONS];

        void loadInteractEngExit(SDL_Renderer* renderer, TTF_Font* font);
        void renderInteractEngExit(SDL_Renderer* renderer, int x, int y);

        void loadInteractHabExit(SDL_Renderer* renderer, TTF_Font* font);
        void renderInteractHabExit(SDL_Renderer* renderer, int x, int y);

        void loadInteractRec(SDL_Renderer* renderer, TTF_Font* font);
        void renderInteractRec(SDL_Renderer* renderer, int x, int y);

        void loadInteractBike(SDL_Renderer* renderer, TTF_Font* font);
        void renderInteractBike(SDL_Renderer* renderer, int x, int y);

        void loadInteractInfirmary(SDL_Renderer* renderer, TTF_Font* font);
        void renderInteractInfirmary(SDL_Renderer* renderer, int x, int y);
        //loads the water tank interaction text texture with the current waterlevel (currently just using a
        //stringstream hard coded with "100L"
        void loadInteractWaterTank(SDL_Renderer* renderer,TTF_Font* font, int waterGauge);
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
        void loadStation(SDL_Renderer* renderer,TTF_Font* font, int shipGaugeValues[]);
        //when player walks around, the stations move with the background.
        void updateHabPosition(int y);
        //for the stations that are rendered on the second hab bg.
        void updateHabPosition2(int y);
        //
        void updateEngPosition(int y);
        //
        void updateEngPosition2(int y);
        //renders the textures that belong behind player
        void renderHabStationBehindPlayer(SDL_Renderer* renderer,int playerBot);
        //renders the textures that belong in front of the player
        void renderHabStationFrontPlayer(SDL_Renderer* renderer, int playerBot);
        //
        void renderEngStationBehindPlayer(SDL_Renderer* renderer, int playerBot);
        //
        void renderEngStationFrontPlayer(SDL_Renderer* renderer, int playerBot);
        //player is no longer interacting with the planter.
        void freePlanterOptions();
        //frees the resources
        void free();
        //
        void updatePlant(int timeSurvived);

    private:

};

#endif // STATION_H
