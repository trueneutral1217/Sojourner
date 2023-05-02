#include "saveGame.h"

void saveGame::readPrefsFile()
{//load's saved data, if it exists, else it creates a new file filled with default values for data.
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
                SDL_RWwrite( prefsFile, &prefsData[ i ], sizeof(Sint32), 1 );
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
        printf( "Loading Saved Preferences Data...!\n" );
        for( int i = 0; i < TOTAL_PREFS_DATA; ++i )
        {
            SDL_RWread( prefsFile, &prefsData[ i ], sizeof(Sint32), 1 );
            std::cout<<"\n "<<prefsData[i];
        }



        //load data from file into savegame variables

        SDL_RWclose( prefsFile );
    }
}

void saveGame::readSaveFile(int fileNum)
{//load's saved data, if it exists, else it creates a new file filled with default values for data.
    //data[0] is used in pregameui for the buttons in loadgame gamestate, data[1] is time that file was written.
    //data[2] through data[4] are currently stage variables (player coords, hab bg coords).
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
        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            SDL_RWread( saveFile, &data[ i ], sizeof(Sint32), 1 );
            std::cout<<"\n reading "<<data[i]<<" from fileNum "<<fileNum;
        }
        //load data from file into savegame variables

        SDL_RWclose( saveFile );
    }
}

void saveGame::writeSaveFile(int fileNum,pregameui pregameui,stage stage)
{//saves the game, depending on fileNum to save1.ssf, save2.ssf, and save3.ssf

    SDL_RWops* saveFile = SDL_RWFromFile( saveLocation[fileNum], "w+b" );
    if( saveFile != NULL )
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        std::cout<<"\n now = "<<now;
        std::cout<<"\n current date & time: "<<dt;
        //Save data
        data[0] = pregameui.existingSave[0];
        data[1] = now;
        data[2] = stage.player1.getX();
        data[3] = stage.player1.getY();
        data[4] = stage.habInternalY1;
        data[5] = stage.habInternalY2;

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

void saveGame::writePrefsFile(pregameui pregameui)
{//save user preferences to prefs.ssf
    SDL_RWops* prefsFile = SDL_RWFromFile( "savegame/prefs.ssf", "w+b" );
    if( prefsFile != NULL )
    {
        //Save data
        prefsData[0] = pregameui.optionsButtons[1].fullScreenToggle;
        prefsData[1] = pregameui.optionsButtons[2].musicToggle;
        prefsData[2] = pregameui.optionsButtons[3].voiceToggle;

        for( int i = 0; i < TOTAL_PREFS_DATA; ++i )
        {
            SDL_RWwrite( prefsFile, &prefsData[ i ], sizeof(Sint32), 1 );
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

