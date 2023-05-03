#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "Texture.h"
#include "pregameui.h"
#include "stage.h"
#include <ctime>


//total save game data points
const int TOTAL_DATA = 6;
//total preferences data points
const int TOTAL_PREFS_DATA = 3;

class saveGame
{
    public:

    //file read/write stuff
    Sint32 data[ TOTAL_DATA ];
    Sint32 prefsData[ TOTAL_PREFS_DATA ];

    std::stringstream savedDate[TOTAL_SAVES];
    Texture savedDateTexture[TOTAL_SAVES];

    void loadSavedDate(SDL_Renderer* renderer,TTF_Font* font);

    int fileNum;

    const char *saveLocation[TOTAL_SAVES] = {"savegame/save1.ssf","savegame/save2.ssf","savegame/save3.ssf"};

    SDL_RWops* prefsFile = SDL_RWFromFile( "savegame/prefs.ssf", "r+b" );

    SDL_RWops* saveFile;

    //int threadFunction(void* data);

    void readPrefsFile();

    //reads save file, specified by fileNum, creates a new one if none exists.
    void readSaveFile(int fileNum);

    void writePrefsFile(pregameui pregameui);

    void writeSaveFile(int fileNum,pregameui pregameui,stage stage);

    //thinking about having multiple save files, one with preferences, 3 with game progress.
    //considering adding time played to saved game progress variables.



    private:

};


#endif // SAVEGAME_H
