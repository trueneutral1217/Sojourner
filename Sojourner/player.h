#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"

//textures for character, soon to be broken up into different dimensions
//const int PLAYER_TEXTURES = 11;
const int IDLE_TEXTURES=1;
const int LR_TEXTURES=7;
const int DLDR_TEXTURES=7;
const int ULUR_TEXTURES=7;
const int D_TEXTURES=7;
const int U_TEXTURES=7;

const int SPACE_IDLE_TEXTURES=1;
const int SPACE_LR_TEXTURES=7;
const int SPACE_DLDR_TEXTURES=7;
const int SPACE_ULUR_TEXTURES=7;
const int SPACE_D_TEXTURES=7;
const int SPACE_U_TEXTURES=7;

//walk states is used to determine which dimension of the player textures array to display
//up, down, right, upright, downright, or idle.
const int MOVE_STATES = 6;

//idle is walk state 0, this consists of character standing in place
const int IDLE = 0;
//LR is walk state 1, this array has the textures of player moving left and right, although left walk is right flipped horizontally.
const int WALK_LR = 1;
//player is walking down right or down left when movestate is 2
const int WALK_DLDR = 2;
//movestate 3 is you guessed it, up left and up right walking.
const int WALK_ULUR = 3;
//movestate 4 is when player is walking down
const int WALK_D = 4;
//movestate 5 is player is walking up
const int WALK_U = 5;

class player
{
    public:

        player();
        ~player();
        //player's dimensions and velocity
        static const int PLAYER_WIDTH = 40;
        static const int PLAYER_HEIGHT = 80;
        static const int PLAYER_VEL = 5;
        //tracks current player movement state (idle, walkLR, soon to be other directions and possible other types of movement like floating or running)
        int moveState;
        //tracks current player animation frame
        int walkFrame;
        //used for player frame animation when walking left
        bool flipHorizontal;
        //is player is in space, load space outfit textures, else earth textures
        bool inSpace;
        //used for player walk animations
        Texture currentTexture;
        //second dimension must be size of move state with largest number of textures.
        Texture playerTexture[MOVE_STATES][LR_TEXTURES];
        //loads player resources
        void loadPlayer(SDL_Renderer* renderer);
        //if user presses wasd, this update's player velocity
        void handleEvent(SDL_Event& e);
        //updates player position, walk animation, wall collision
        void move(int tick);
        //renders player
        void render(SDL_Renderer* renderer);
        //frees player resources
        void freePlayer();
        //centers camera over player
        void setCamera(SDL_Rect& camera);
        //returns player's coordinates
        int getX();
        int getY();
        //returns player velocity by direction (x for horizontal, y for vert)
        int getPVelX();
        int getPVelY();
        //set's player's x/y coords
        void setX(int x);
        void setY(int y);
        //checks for collisions between a collidable object and player
        bool collisionDetector(SDL_Rect collidable);

    private:
        //player coordinates
        int playerX,playerY;
        //player velocity
        int pVelX,pVelY;
        //necessary for many operations, from walking to potentially fighting.
        SDL_Rect playerCollisionBox;
};
#endif // PLAYER_H

