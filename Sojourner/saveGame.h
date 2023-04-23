#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "Texture.h"
#include "pregameui.h"
#include "stage.h"

//total save game data points
const int TOTAL_DATA = 8;

class saveGame
{
    public:

    //file read/write stuff
    Sint32 data[ TOTAL_DATA ];
    SDL_RWops* file = SDL_RWFromFile( "savegame/save.ssf", "r+b" );

    void readFile();

    void writeFile(pregameui pregameui,stage stage);

    private:

};


#endif // SAVEGAME_H
