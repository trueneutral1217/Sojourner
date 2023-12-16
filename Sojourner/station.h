#ifndef STATION_H
#define STATION_H

#include "texture.h"
#include "button.h"
#include <vector>

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

        const static int STATIONS = 9;

        std::string stationDefaultInteractionText;

        //strings for interaction button text textures
        //doing this to make the code more abstract.
        std::vector<std::string> buttonString;

        //strings to be used to determine interaction type for planter
        std::string plant;
        std::string waterPlants;
        std::string harvest;

        //for kitchen
        std::string eat;
        //for infirmary
        std::string heal;
        //for bike
        std::string exercise;



        //flags for planter options.  true sets font to white, false to black.
        bool plantOkay;
        bool waterPlantsOkay;
        bool harvestOkay;

        //the two bools below are to determine whether or not to load/render text texture buttons for planting, etc.
        //could possibly reduce to 1.
        bool stationOptionsLoaded;

        //tracks when 'plant' and 'watered' have been pressed,
        //bool interacted;

        Texture stationDefaultInteractionTextTexture;

        //if the button is clickable, it shows up white, else black.
        SDL_Color available = {255,255,255};//white
        SDL_Color unavailable = {0,0,0};//black

        std::vector<Texture> buttonTextTexture;

        //Text Textures for planter interaction buttons
        Texture plantTexture;
        Texture waterPlantsTexture;
        Texture harvestTexture;

        //idea for water tank / other upgrades: upgrades to stations = upgrades to UI,
        //ie: interact to gauge water before upgrade, after upgrade water level is part of UI.

        Texture stationTexture;

        //the impassable area of the station
        SDL_Rect collidable;
        //the interactable area of the station
        SDL_Rect interactable;

        //
        void loadStationButtonTextTextures(SDL_Renderer* renderer, TTF_Font* font,int need);

        void loadPlanterTextTextures(SDL_Renderer* renderer, TTF_Font* font);

        void loadEngExit(SDL_Renderer* renderer, TTF_Font* font);
        void loadHabExit(SDL_Renderer* renderer, TTF_Font* font);
        void loadRec(SDL_Renderer* renderer, TTF_Font* font,int need);
        void loadBike(SDL_Renderer* renderer, TTF_Font* font, int need);
        void loadInfirmary(SDL_Renderer* renderer, TTF_Font* font, int need);
        void loadWaterTank(SDL_Renderer* renderer,TTF_Font* font, int waterGauge);
        void loadBed(SDL_Renderer* renderer,TTF_Font* font, int need);
        void loadPlanter(SDL_Renderer* renderer,TTF_Font* font);
        void loadKitchen(SDL_Renderer* renderer, TTF_Font* font,int need);


        void renderInteractEngExit(SDL_Renderer* renderer, int x, int y);
        void renderInteractHabExit(SDL_Renderer* renderer, int x, int y);

        //functions for rendering interaction buttons like 'plant', 'sleep', etc.
        void renderInteractStation(SDL_Renderer* renderer, int x, int y);
        void renderInteractPlanter(SDL_Renderer* renderer,int x, int y);

        void renderInteractStationButtons(SDL_Renderer* renderer, int x,int y);


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
        //frees the resources
        void free();
        //update's plant's state based on time survived
        void updatePlant(SDL_Renderer* renderer, int timeSurvived);
        //update's plant's texture
        void updatePlantTexture(SDL_Renderer* renderer);


    private:

};

#endif // STATION_H
