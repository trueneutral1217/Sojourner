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

        int bedX, bedY;

        Texture bedTexture;

        SDL_Rect collidable;

        void loadStation(SDL_Renderer* renderer);

        void updatePosition(int y);

        void renderStation(SDL_Renderer* renderer);

        void free();



    private:

};

#endif // STATION_H
