#ifndef MODULE_H
#define MODULE_H

#include "station.h"

class module
{
    public:
        module();
        ~module();

        //declare habitation stations
        station waterTank,kitchen,infirmary,bed,bike,planter,recreation,habExit;

        //declare engineering stations
        station engExit;

        void loadHabitation(SDL_Renderer* renderer,TTF_Font* font, int gauge[]);

        void loadEngineering(SDL_Renderer* renderer,TTF_Font* font);

        void free();

    private:

};

#endif // MODULE_H
