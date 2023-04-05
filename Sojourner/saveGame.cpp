#include "saveGame.h"

void saveGame::readFile()
{
    if( file == NULL )
    {
        printf( "\n Warning: Unable to open file! SDL Error: %s\n", SDL_GetError() );
        //Create file for writing
        file = SDL_RWFromFile( "savegame/save.gsf", "w+b" );
        if( file != NULL )
        {
            printf( "\n New file created!\n" );
            //write savegame defaults as 0.
            for( int i = 0; i < TOTAL_DATA; ++i )
            {
                data[ i ] = 0;
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

void saveGame::writeFile(int currentChapter,int currentPage, int currentScript,bool chapter1Complete,bool chapter2Complete,bool chapter3Complete)
{

    SDL_RWops* file = SDL_RWFromFile( "savegame/save.gsf", "w+b" );
    if( file != NULL )
    {
        //Save data
        data[0] = currentChapter;
        data[1] = currentPage;
        data[2] = currentScript;
        data[3] = chapter1Complete;
        data[4] = chapter2Complete;
        data[5] = chapter3Complete;
        //testSaveVariables();
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
