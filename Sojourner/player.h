#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"

class player
{
    public:

        player();
        ~player();
        static const int PLAYER_WIDTH = 40;
        static const int PLAYER_HEIGHT = 80;
        static const int PLAYER_VEL = 10;

        Texture playerTexture;

        void loadPlayer(SDL_Renderer* renderer);
        void handleEvent(SDL_Event& e);
        void move();
        void render(SDL_Renderer* renderer);

        void freePlayer();

        void setCamera(SDL_Rect& camera);

    private:
        //player coordinates
        int playerX,playerY;
        //player velocity
        int pVelX,pVelY;
        //necessary for many operations, from walking to potentially fighting.
        SDL_Rect playerCollisionBox;
};
#endif // PLAYER_H

