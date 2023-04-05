#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "Texture.h"

//total save game data points
const int TOTAL_DATA = 6;

class saveGame
{
    public:

    //file read/write stuff
    Sint32 data[ TOTAL_DATA ];
    SDL_RWops* file = SDL_RWFromFile( "savegame/save.gsf", "r+b" );

    void readFile();
    void writeFile(int currentChapter,int currentPage,int currentScript, bool chapter1Complete, bool chapter2Complete, bool chapter3Complete);


    private:

};


#endif // SAVEGAME_H
