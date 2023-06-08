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
        int waterTankX, waterTankY;

        const static int STATIONS = 2;

        Texture bedTexture;
        Texture waterTankTexture;

        SDL_Rect collidable[STATIONS];

        void loadStation(SDL_Renderer* renderer);

        void updatePosition(int y);

        void renderStation(SDL_Renderer* renderer);

        void free();



    private:

};

#endif // STATION_H
