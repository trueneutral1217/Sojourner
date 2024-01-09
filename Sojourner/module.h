#ifndef MODULE_H
#define MODULE_H

#include "station.h"


class module
{
    public:
        module();
        ~module();

        //declare habitation stations
        station waterTank, kitchen, infirmary, bed, bike, planter, recreation, habExit;

        //declare engineering stations
        station engExit, batteryArray, researchDesk, engineStation;

        void loadHabitation(SDL_Renderer* renderer,TTF_Font* font, int gauge[], int need[]);

        void loadEngineering(SDL_Renderer* renderer,TTF_Font* font, int gauge[], int need[]);

        void freeHab();

        void freeEng();

    private:

};

#endif // MODULE_H
