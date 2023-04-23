#include "saveGame.h"

void saveGame::readFile()
{
    if( file == NULL )
    {
        printf( "\n Warning: Unable to open file! SDL Error: %s\n", SDL_GetError() );
        //Create file for writing
        file = SDL_RWFromFile( "savegame/save.ssf", "w+b" );
        if( file != NULL )
        {
            printf( "\n New file created!\n" );
            //write savegame defaults as 0.
            for( int i = 0; i < TOTAL_DATA; ++i )
            {
                data[ i ] = 0;
                if(i==4 || i==5)//when new file is created setting defaults for music and voice to be on.
                {
                    data[i] = 1;
                }
                SDL_RWwrite( file, &data[ i ], sizeof(Sint32), 1 );
            }
            //Close file handler
            SDL_RWclose( file );
        }
        else
        {
            printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
            //success = false;
        }
    }//File exists
    else
    {
        printf( "Loading Save Game Data...!\n" );
        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            SDL_RWread( file, &data[ i ], sizeof(Sint32), 1 );
        }
        //load data from file into savegame variables

        SDL_RWclose( file );
    }
}

void saveGame::writeFile(pregameui pregameui,stage stage)
{

    SDL_RWops* file = SDL_RWFromFile( "savegame/save.ssf", "w+b" );
    if( file != NULL )
    {
        //Save data
        data[0] = pregameui.existingSave;
        data[1] = stage.player1.getX();
        data[2] = stage.player1.getY();
        data[3] = pregameui.optionsButtons[1].fullScreenToggle;
        data[4] = pregameui.optionsButtons[2].musicToggle;
        data[5] = pregameui.optionsButtons[3].voiceToggle;
        data[6] = stage.habInternalY1;
        data[7] = stage.habInternalY2;

        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            SDL_RWwrite( file, &data[ i ], sizeof(Sint32), 1 );
        }
        //Close file handler
        SDL_RWclose( file );
    }
    else
    {
        printf( "Error: Unable to save file! %s\n", SDL_GetError() );
    }

}
