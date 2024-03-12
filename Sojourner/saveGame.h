#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "Texture.h"
#include "pregameui.h"
#include "stage.h"
#include <ctime>


//total save game data points
const int TOTAL_DATA = 36;
//total preferences data points
const int TOTAL_PREFS_DATA = 3;

class saveGame
{
    public:

    //file read/write stuff
    Sint32 data[ TOTAL_DATA ];
    Sint32 prefsData[ TOTAL_PREFS_DATA ];

    std::string dataDescription[TOTAL_DATA] = {"save exists","current time","played time","player1.getX","player1.getY","habInternalY1","habInternalY2","player health","player hunger","player physique","player slumber","player morale","ship hull","ship fuel","ship power","ship water","ship oxygen","ship temperature","planter.buttonAvailable[0]","planter.buttonAvailable[1]","timeSurvived","planterState","planterDaysState","planterTimeWatered","engInternalY1","engInternalY2","planter.buttonAvailable[2]","inHab","inEng","bed.stationTier","scrap.itemCount","bed.upgradeAvailable","recreation.upgradeAvailable","recreation.stationTier","waterTank.upgradeAvailable","waterTank.stationTier"};

    std::stringstream savedDate[TOTAL_SAVES];
    std::stringstream savedPlayTime[TOTAL_SAVES];
    Texture savedDateTexture[TOTAL_SAVES];
    Texture savedPlayTimeTexture[TOTAL_SAVES];

    bool exists[TOTAL_SAVES];

    //void loadSavedMetaData(SDL_Renderer* renderer,TTF_Font* font);

    int fileNum;

    const char *saveLocation[TOTAL_SAVES] = {"savegame/save1.ssf","savegame/save2.ssf","savegame/save3.ssf"};

    SDL_RWops* prefsFile = SDL_RWFromFile( "savegame/prefs.ssf", "r+b" );

    SDL_RWops* saveFile;

    void readPrefsFile();

    //reads save file, specified by fileNum, creates a new one if none exists.
    void readSaveFile(int fileNum);


    //*********************************
    //Objects may need to be sent in by reference (&) in order for proper functioning.
    //*********************************
    void writePrefsFile(pregameui& pregameui);

    void writeSaveFile(int fileNum,stage& stage,Uint32 playedTime);
    //just updates data of a save file, writing happens at program close.
    void updateSaveData(int fileNum,stage& stage, Uint32 playedTime);
    //updates the text textures of after the data has been updated.
    void updateSavedMetaData(int fileNum,SDL_Renderer* renderer,TTF_Font* font);

    void handleSavedMetaDataRendering(SDL_Renderer* renderer);

    void loadSaveTextTextures(SDL_Renderer* renderer,TTF_Font* font);

    void freeTextTextures();

    void deleteSave(int fileNum);
    //thinking about having multiple save files, one with preferences, 3 with game progress.
    //considering adding time played to saved game progress variables.

    //stage/player variables
    Uint32 dataValues1[6];
    //player needs
    Uint32 dataValues2[5];
    //ship gauges
    Uint32 dataValues3[6];

    void setDataValues();


    private:

};


#endif // SAVEGAME_H
