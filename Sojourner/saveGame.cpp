#include "saveGame.h"

void saveGame::readPrefsFile()
{
    std::cout<<"\n running saveGame::readPrefsFile()";
    //load's saved data, if it exists, else it creates a new file filled with default values for data.
    if( prefsFile == NULL )
    {
        printf( "\n Warning: Unable to open preferences file! SDL Error: %s\n", SDL_GetError() );
        //Create file for writing
        prefsFile = SDL_RWFromFile( "savegame/prefs.ssf", "w+b" );
        if( prefsFile != NULL )
        {
            printf( "\n New preferences file created!\n" );
            //write savegame defaults as 0.
            for( int i = 0; i < TOTAL_PREFS_DATA; ++i )
            {
                prefsData[ i ] = 0;//fullscreen default set to false
                if(i==1 || i==2)//music and voice toggles set to true (on)
                {
                    prefsData[i]=1;
                }
                SDL_RWwrite( prefsFile, &prefsData[ i ], sizeof(bool), 1 );
            }
            //Close file handler
            SDL_RWclose( prefsFile );
        }
        else
        {
            printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
            //success = false;
        }
    }//File exists
    else
    {
        printf( "\n Loading Saved Preferences Data...!\n" );
        for( int i = 0; i < TOTAL_PREFS_DATA; ++i )
        {
            SDL_RWread( prefsFile, &prefsData[ i ], sizeof(bool), 1 );
            std::cout<<"\n "<<prefsData[i];
        }

        //load data from file into savegame variables

        SDL_RWclose( prefsFile );
    }
}

void saveGame::readSaveFile(int fileNum)
{
    std::cout<<"\n running saveGame::readSaveFile(int fileNum)";
    //load's saved data, if it exists, else it creates a new file filled with default values for data.
    //data[0] is used in pregameui for the buttons in loadgame gamestate, data[1] is time that file was written.
    //data[2] through data[4] are currently stage variables (player coords, hab bg coords).
    std::cout<<"\n chosenSave/fileNum = "<<fileNum;
    saveFile = SDL_RWFromFile(saveLocation[fileNum], "r+b" );
    if( saveFile == NULL )
    {
        printf( "\n Warning: Unable to open save file %d! SDL Error: %s\n",fileNum, SDL_GetError() );


        //Create file for writing
        saveFile = SDL_RWFromFile( saveLocation[fileNum], "w+b" );
        if( saveFile != NULL )
        {
            printf( "\n New save file %d created!\n", fileNum );
            //write savegame defaults as 0.
            for( int i = 0; i < TOTAL_DATA; ++i )
            {
                data[ i ] = 0;
                SDL_RWwrite( saveFile, &data[ i ], sizeof(Sint32), 1 );
            }
            //Close file handler
            SDL_RWclose( saveFile );
        }
        else
        {
            printf( "Error: Unable to create save file %d! SDL Error: %s\n",fileNum, SDL_GetError() );
            //success = false;
        }
    }//File exists
    else
    {
        printf( "\n Loading Save Game file %d Data...!\n", fileNum );
        //load data from file into savegame variables
        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            SDL_RWread( saveFile, &data[ i ], sizeof(Sint32), 1 );
            std::cout<<"\n reading "<<data[i]<<" from fileNum "<<fileNum;
        }
        if(data[0])
        {
            savedDate[fileNum].str("");
            savedDate[fileNum].clear();
            time_t saved = data[1];
            char* sdt = ctime(&saved);
            savedDate[fileNum] << "Last Saved: " << sdt;
            std::cout<<"\n savedDate["<<fileNum<<"]: "<<savedDate[fileNum].str();

            int hours,minutes,seconds;
            if(data[2]/1000 < 0)
            {
                seconds = 0;
            }
            else
            {
                seconds = data[2]/1000;
            }

            if( (data[2]/1000)/60 < 0 )
            {
                minutes = 0;
            }
            else
            {
                minutes = (data[2]/1000)/60;
            }

            if( ( (data[2]/1000)/60 )/60 < 0 )
            {
                hours = 0;
            }
            else
            {
                hours = ((data[2]/1000)/60)/60;
            }

            savedPlayTime[fileNum].str("");
            savedPlayTime[fileNum].clear();
            savedPlayTime[fileNum] << "Time Played: " << hours << " hrs, "<<(minutes%60)<<" mins, "<<(seconds%60)<<" secs";

            std::cout<<"\n savedPlayTime["<<fileNum<<"]: "<<savedPlayTime[fileNum].str();
        }
        SDL_RWclose( saveFile );
    }
}

void saveGame::writeSaveFile(int fileNum,stage stage,Uint32 playedTime)
{
    std::cout<<"\n running saveGame::writeSaveFile(int fileNum,stage stage,Uint32 playedTime)";
    //saves the game, depending on fileNum to save1.ssf, save2.ssf, and save3.ssf

    SDL_RWops* saveFile = SDL_RWFromFile( saveLocation[fileNum], "w+b" );
    if( saveFile != NULL )
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        std::cout<<"\n now = "<<now;
        std::cout<<"\n current date & time: "<<dt;
        //Save data
        data[0] = true;
        data[1] = now;
        data[2] = playedTime;
        data[3] = stage.player1.getX();
        data[4] = stage.player1.getY();
        data[5] = stage.habInternalY1;
        data[6] = stage.habInternalY2;
        //iterates through the player's needs and records them.
        for(int i = 0; i < TOTAL_PLAYER_NEEDS; i++)
        {
            data[i+7] = stage.player1.need[i];
        }


        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            SDL_RWwrite( saveFile, &data[ i ], sizeof(Sint32), 1 );
            std::cout<<"\n writing "<<data[i]<<" to fileNum "<<fileNum;
        }
        //Close file handler
        SDL_RWclose( saveFile );
    }
    else
    {
        printf( "Error: Unable to save file %d! %s\n",fileNum, SDL_GetError() );
    }
}

void saveGame::deleteSave(int fileNum)
{
    std::cout<<"\n running saveGame::deleteSave(int fileNum)";
    //restores game data to default values, depending on fileNum: save1.ssf, save2.ssf, and save3.ssf
    saveFile = SDL_RWFromFile(saveLocation[fileNum], "r+b" );
    if( saveFile != NULL )
    {
        printf( "\n Reformatting savefile %d", fileNum );
        //write savegame defaults as 0.
        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            data[ i ] = 0;
            SDL_RWwrite( saveFile, &data[ i ], sizeof(Sint32), 1 );
        }
        //Close file handler
        SDL_RWclose( saveFile );
    }
    savedPlayTime[fileNum].str() = "";
    savedDate[fileNum].str() = "";
}

void saveGame::writePrefsFile(pregameui pregameui)
{
    std::cout<<"\n running saveGame::writePrefsFile(pregameui pregameui)";
    //save user preferences to prefs.ssf
    //Save data
    prefsData[0] = pregameui.optionsButtons[1].fullScreenToggle;
    prefsData[1] = pregameui.optionsButtons[2].musicToggle;
    prefsData[2] = pregameui.optionsButtons[3].voiceToggle;

    //SDL_Thread* writePrefsThread = SDL_CreateThread( threadFunction, "writePrefsThread", NULL );

    SDL_RWops* prefsFile = SDL_RWFromFile( "savegame/prefs.ssf", "w+b" );
    if( prefsFile != NULL )
    {

        for( int i = 0; i < TOTAL_PREFS_DATA; ++i )
        {
            SDL_RWwrite( prefsFile, &prefsData[ i ], sizeof(bool), 1 );
            std::cout<<"\n "<<prefsData[i];
        }

        //Close file handler
        SDL_RWclose( prefsFile );

    }
    else
    {
        printf( "Error: Unable to save file! %s\n", SDL_GetError() );
    }
    std::cout<<"\n write prefs function complete";

}

void saveGame::updateSaveData(int fileNum,stage stage,Uint32 playedTime)
{
    std::cout<<"\n running saveGame::updateSaveData(stage stage,Uint32 playedTime)";
    time_t now = time(0);
    char* dt = ctime(&now);
    std::cout<<"\n now = "<<now;
    std::cout<<"\n current date & time: "<<dt;
    //Save data
    data[0] = true;
    data[1] = now;
    data[2] = playedTime;
    std::cout<<"\n playedTime = "<<playedTime;
    data[3] = stage.player1.getX();
    std::cout<<"\n stage.player1.getX() = "<<stage.player1.getX();
    data[4] = stage.player1.getY();
    std::cout<<"\n stage.player1.getY() = "<<stage.player1.getY();
    data[5] = stage.habInternalY1;
    std::cout<<"\n stage.habInternalY1 = "<<stage.habInternalY1;
    data[6] = stage.habInternalY2;
    std::cout<<"\n stage.habInternalY2 = "<<stage.habInternalY2;

    //iterates through the player's needs and records them.
    for(int i = 0; i < TOTAL_PLAYER_NEEDS; i++)
    {
        data[i+7] = stage.player1.need[i];
    }

    SDL_RWops* saveFile = SDL_RWFromFile(saveLocation[fileNum], "w+b");
    for( int i = 0; i < TOTAL_DATA; ++i )
    {
        SDL_RWwrite( saveFile, &data[ i ], sizeof(Sint32), 1 );
        std::cout<<"\n writing "<<data[i]<<" to fileNum "<<fileNum;
    }
    //Close file handler
    SDL_RWclose( saveFile );
}

void saveGame::updateSavedMetaData(int fileNum, SDL_Renderer* renderer,TTF_Font* font)
{//this function updates the savedDate & playtime of a savefile (fileNum) after player exits stage.
    //by using filenum instead of iterating through all the save files some efficiency might be gained.
    std::cout<<"\n running saveGame::updateSavedMetaData(int fileNum, SDL_Renderer* renderer,TTF_Font* font)";
    savedDate[fileNum].str("");
    savedDate[fileNum].clear();
    time_t saved = data[1];
    char* sdt = ctime(&saved);
    std::cout<<"\n sdt: "<<sdt;
    savedDate[fileNum] << "Last Saved: " << sdt;
    //in order to strip out the extra couple characters that come with ctime, I pull the string out of
    //the stringstream and do the operation to concatenate the extra couple characters.
    std::string s = savedDate[fileNum].str();
    s.erase(36,2);
    savedDate[fileNum].str(s);
    std::cout<<"\n savedDate["<<fileNum<<"]: "<<savedDate[fileNum].str();
    std::cout<<"\n data[2] (playedTime) = "<<data[2];
    int hours,minutes,seconds;
    if(data[2]/1000 < 0)
    {
        seconds = 0;
    }
    else
    {
        seconds = data[2]/1000;
    }
    if( (data[2]/1000)/60 < 0 )
    {
        minutes = 0;
    }
    else
    {
        minutes = (data[2]/1000)/60;
    }
    if( ( (data[2]/1000)/60 )/60 < 0 )
    {
        hours = 0;
    }
    else
    {
        hours = ((data[2]/1000)/60)/60;
    }
    savedPlayTime[fileNum].str("");
    savedPlayTime[fileNum].clear();
    savedPlayTime[fileNum] << "Time Played: " << hours << " hrs, "<<(minutes%60)<<" mins, "<<(seconds%60)<<" secs";
    std::cout<<"\n savedPlayTime["<<fileNum<<"]: "<<savedPlayTime[fileNum].str();
    std::cout<<"\n";
    SDL_Color textColor = {0,0,0};//black
    //textColor = {255,255,0};//ochre?
    //textColor = {0,255,0};//green
    //textColor = {255,0,255};//pink
    //textColor = {255,0,0};//red
    textColor = {0,128,200};
}

void saveGame::loadSaveTextTextures(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running saveGame::loadSaveTextTextures(SDL_Renderer* renderer, TTF_Font* font)";
    for(int i =0; i<TOTAL_SAVES;i++)
    {
        //freeing textures before reloading them.
        savedDateTexture[i].free();
        savedPlayTimeTexture[i].free();
    }

    SDL_Color textColor = {0,128,200};
    for(int i=0; i<TOTAL_SAVES;i++)
    {
        std::cout<<"\n savedDate["<<i<<"]: "<<savedDate[i].str().c_str();
        if(savedDate[i].str() == "")
        {
            std::cout<<"\n savedDate["<<i<<".str() = \"\"";
            savedDate[i].str("Empty");
        }
        if(!savedDateTexture[i].loadFromRenderedText(savedDate[i].str().c_str(), textColor,font,renderer))
        {
            std::cout<<"\n unable to load savedDate["<<i<<"] streamstring to savedDateTexture["<<i<<"]";
        }
        else
        {
            std::cout<<"\n savedDateTexture["<<i<<"] is loaded from streamstring";
            std::cout<<"\n savedDate["<<i<<"]: "<<savedDate[i].str();
        }
        if(savedPlayTime[i].str() == "")
        {
            savedPlayTime[i].str("Empty");
        }
        if(!savedPlayTimeTexture[i].loadFromRenderedText(savedPlayTime[i].str().c_str(), textColor,font,renderer))
        {
            std::cout<<"\n unable to render savedPlayTime["<<i<<"] streamstring to savedPlayTimeTexture["<<i<<"]";
        }
        else
        {
            std::cout<<"\n savedPlayTimeTexture["<<i<<"] is loaded from streamstring";
            std::cout<<"\n savedPlayTime["<<i<<"]: "<<savedPlayTime[i].str();
        }
    }
}

void saveGame::handleSavedMetaDataRendering(SDL_Renderer* renderer)
{
    for(int i; i<TOTAL_SAVES;i++)
    {
        savedPlayTimeTexture[i].render(160,(110+(i*100)),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        savedDateTexture[i].render(160,(130+(i*100)),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void saveGame::freeTextTextures()
{
    std::cout<<"\n freeing savedMetaDataTextTextures";
    for(int i; i<TOTAL_SAVES; i++)
    {
        savedPlayTimeTexture[i].free();
        savedDateTexture[i].free();
    }
}

void saveGame::setDataValues()
{//used for loading saved data values for saved games
    //player coords / parallax bg coords
    for(int i = 0; i < 4; i++)
    {
        dataValues1[i] = data[i+3];
    }
    //player needs values
    for(int j = 0; j < TOTAL_PLAYER_NEEDS; j++)
    {
        dataValues2[j] = data[j+7];
    }
}
