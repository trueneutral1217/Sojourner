#ifndef MODULE_H
#define MODULE_H

#include "station.h"

class module
{
    public:
        module();
        ~module();

        station station;

        void loadModule(SDL_Renderer* renderer,TTF_Font* font, int gauge[]);

        void free();

    private:

};

#endif // MODULE_H
