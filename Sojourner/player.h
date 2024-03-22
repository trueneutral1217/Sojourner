#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

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
//used when iterating though the text textures displayed in the UI
const int TOTAL_PLAYER_NEEDS = 5;

class player
{
    public:

        player();
        ~player();
        //player's dimensions and velocity
        static const int PLAYER_WIDTH = 40;
        static const int PLAYER_HEIGHT = 80;
        float PLAYER_VEL = 1000.0f;
        //bottom of player sprite
        int playerBot;
        //tracks current player movement state (idle, walkLR, soon to be other directions and possible other types of movement like floating or running)
        int moveState;
        //tracks current player animation frame
        int walkFrame;
        //player needs (0-100 percent); health hunger physique slumber morale
        int need[TOTAL_PLAYER_NEEDS];
        //used for player frame animation when walking left
        bool flipHorizontal;
        //is player is in space, load space outfit textures, else earth textures
        bool inSpace;
        //player press 'E' button, signaling they want to interact.
        bool interact;
        //flag if player is collided with interaction box of a station.
        bool inRange;
        //the flag for rendering the water tank level.
        bool interactWaterTank;
        //the flag for rendering the bed text texture
        bool interactBed;
        //flag for rendering planter text texture
        bool interactPlanter;
        //flag for rendering kitchen text texture
        bool interactKitchen;
        //render infirmary text texture
        bool interactInfirmary;
        //render bike text texture?
        bool interactBike;
        //render recreation text texture
        bool interactRec;
        //flags interaction with a station in engineering module
        bool interactHabExit, interactEngExit, interactBatteryArray, interactResearchDesk, interactEngineStation, interactCargoArea, interactCommStation;
        //for opening sequence newspaper
        bool interactNewspaper,interactBackdoor;
        //needed for opening sequence
        bool movementDisabled;
        //the player's health is <= 0
        bool isDead;

        //used for player walk animations
        Texture currentTexture;
        //second dimension must be size of move state with largest number of textures.
        Texture playerTexture[MOVE_STATES][LR_TEXTURES];
        //strings for the player needs note: index 0 correlates with health, 1 = physique, 2 = hunger, 3 = slumber, 4 = morale
        std::string playerNeeds[TOTAL_PLAYER_NEEDS];
        //updates player's needs values (typically after interacting with a station)
        void modifyNeeds(int modNeedValues[]);
        //text textures for the UI, displays percent of health, hunger, physique, slumber, and morale.
        Texture needsTexture[TOTAL_PLAYER_NEEDS];
        //loads the needs textures
        void loadNeedsTextures(SDL_Renderer* renderer, TTF_Font* font);
        //reloads the needs textures (ideally after one of the values of needs changes)
        void reloadNeedsTextures(SDL_Renderer* renderer,TTF_Font* font);
        //renders the needs text textures
        void renderNeedsTextures(SDL_Renderer* renderer);
        //frees the text textures of the player's needs.
        void freeNeedsTextures();
        //loads player resources
        void loadPlayer(SDL_Renderer* renderer);
        //if user presses wasd, this update's player velocity
        void handleEvent(SDL_Event& e, float delta);
        //updates player position, walk animation, station collision box, station interaction box
        //void move(int tick, SDL_Rect collidable, SDL_Rect interactable,int STATIONS, bool inHab,bool inEng);

        void move(int tick, ship& ship,bool inhab, bool inEng, float delta);
        //this is the move function used in the opening sequence
        void move(int tick, SDL_Rect& newspaperInteraction, SDL_Rect& backdoorInteraction,bool inBackyard,float delta);
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
        //checks for collisions between collidable objects and player
        bool collisionDetector(SDL_Rect collidable);

        //loads needs from saved game file into working variables
        //void loadSavedPlayerData(Uint32 d1, Uint32 d2, Uint32 d3, Uint32 d4, Uint32 d5);
        void loadSavedPlayerData(Sint32 dataValues[]);


    private:
        //player coordinates
        int playerX,playerY;
        //player velocity
        float pVelX,pVelY;
        //necessary for many operations, from walking to potentially fighting.
        SDL_Rect playerCollisionBox;


};
#endif // PLAYER_H

