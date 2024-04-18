#ifndef DEBRIS_H
#define DEBRIS_H

#include "texture.h"


class debris
{
    public:
        debris();
        ~debris();
        //the debris object's texture (when player is collecting).
        Texture debrisTexture;
        //position and speed of the debris object.
        int debrisSpeed, debrisX, debrisY;
        //the things the player can harvest from the debris object.
        int debrisFuelDrop, debrisFoodDrop, debrisWaterDrop, debrisScrapDrop, debrisWoodDrop, debrisPlasticDrop;
        //is the debris an asteroid?
        bool asteroid;
        //is the debris a satellite? note, make sure only one flag is true.
        bool satellite;

    private:

};

#endif // DEBRIS_H
