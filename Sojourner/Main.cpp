//local classes
#include "audio.h"
#include "button.h"
#include "Texture.h"
#include "timer.h"
#include "particle.h"
//#include "chapter.h"
#include "saveGame.h"
#include "pregameui.h"
#include "animations.h"
#include "stage.h"
#include "text.h"
//#include <SDL_thread.h>


const int TOTAL_STATES = 6;

//gameStates
//gameState = 0 pregameui
//gameState = 1 new game chapter select
//gameState = 2 load game chapter select
//gameState = 3 options
//gameState = 4 credits
//gameState = 5 stage 1

//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//The window renderer
SDL_Renderer* renderer = NULL;
//The window we'll be rendering to
SDL_Window* window = NULL;
//savegame handler
saveGame preferences;
saveGame savegame;
audio music;
std::vector<audio> sounds;
audio sound;
//declare stage
stage stage;
//declare instance of pregame user interface.
pregameui pregameui;
//declare instance of animations
animations animations;
//set up text input
text text;
//tracks the amount of time user has been in gameState 5
timer playedTime;
//declare sound vector & load sounds into it.
void loadSounds();
//render particles to screen
//tracks the state of the game for rendering etc.
int gameState;
//tracks which game the user loaded
int chosenSave;
//initializes audio,video, etc.
Texture blackGround;
bool fadeOut(int countedFrames, bool fade);

bool fadeIn(int countedFrames,bool fade);
/*
//write preferences semaphore
SDL_sem* writePrefsLock = NULL;

int threadFunction(void* data);

bool mainPrefsData[TOTAL_PREFS_DATA];

int threadFunction(void* data)
{

    //Lock
    SDL_SemWait( writePrefsLock );

    mainPrefsData[0]=pregameui.optionsButtons[1].fullScreenToggle;
    mainPrefsData[1]=pregameui.optionsButtons[2].musicToggle;
    mainPrefsData[2]=pregameui.optionsButtons[3].voiceToggle;

    SDL_RWops* prefsFile = SDL_RWFromFile( "savegame/prefs.ssf", "w+b" );
    if( prefsFile != NULL )
    {

        for( int i = 0; i < TOTAL_PREFS_DATA; ++i )
        {
            SDL_RWwrite( prefsFile, &mainPrefsData[ i ], sizeof(Sint32), 1 );
            std::cout<<"\n "<<mainPrefsData[i];
        }

        //Close file handler
        SDL_RWclose( prefsFile );

    }
    else
    {
        printf( "Error: Unable to save file! %s\n", SDL_GetError() );
    }
    std::cout<<"\n write prefs function complete";

    //Unlock
    SDL_SemPost( writePrefsLock );

    return 0;
}*/

bool fadeIn(int countedFrames, bool fade)
{
    Uint32 alpha = 255-(countedFrames%256);
    blackGround.setAlpha(alpha);
    if(countedFrames%256>254)
    {
        fade=false;
    }
    return fade;
}

bool fadeOut(int countedFrames, bool fade)
{
   if(countedFrames%256 < 255)
    {  //fades in the go homeless title
        blackGround.setAlpha(countedFrames);
    }
    if(countedFrames%256>=255)
    {
        fade=false;
    }
return fade;
}

bool init()
{
	//Initialization flag
	bool success = true;
	gameState = 0;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0  )
	{
		printf( "\n SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "\n Warning: Linear texture filtering not enabled!" );
		}
		window = SDL_CreateWindow( "Sojourner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN  | SDL_WINDOW_RESIZABLE  );
		if( window == NULL )
		{
			printf( "\n Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "\n Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//create particles
				pregameui.createParticles(renderer);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "\n SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                printf( "\n SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                success = false;
            }
        if( TTF_Init() == -1 )
        {
            printf( "\n SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
	}
	return success;
}

void loadSounds()
{
    //prep the vector
    for(int i = 0; i < TOTAL_SOUNDS; i++)
    {
        sounds.push_back(sound);
    }
    //load the sounds for each point in the vector
    for(int i = 0; i < TOTAL_SOUNDS; i++)
    {
        sounds[i].loadSound(i);
    }
}

bool loadMedia()
{
	bool success = true;

	//Initialize semaphore
	//writePrefsLock = SDL_CreateSemaphore( 1 );

    //load saved game
    preferences.readPrefsFile();

    /* future way to read savegame files (the files themselves will have to be declared in main.cpp instead of savegame.h
    for(int i = 0; i < TOTAL_SAVES; i++)
    {
        savegame[i].readFile();
    }
    */
    for(int i = 0; i<TOTAL_SAVES;i++)//this should be done when loading stage
    {
        savegame.readSaveFile(i);
        pregameui.existingSave[i] = savegame.data[0];
        //time gets typecasted to an sint32 at save time (before converting it to string)
        //I typecast it back to time_t, then convert to string after loading, sdt (saved date time)
        //can be used at newgame/loadgame gamestates to show when that file was last saved, if at all.
        //I might also want to save the amount of time a user spent on any particular save game.
        time_t saved = savegame.data[1];
        char* sdt = ctime(&saved);
        std::cout<<"\n time of save: "<<sdt;

        std::cout<<"\n amount of time played: "<<savegame.data[2];


    }

	//savegame[0].readFile1();
	//savegame[1].readFile2();
	//savegame[2].readFile3();

    //has user clicked stage1 button from newgame screen, if so, loadgame will show stage1 button.
	//pregameui.existingSave=savegame.data[0];

	//load animations textures
    success = animations.setAnimationTextures(renderer);
    //sets up pregame ui button names, button textures, and bg textures.
    success = pregameui.loadPregameUI(renderer,success);
    //loads stage textures, button names, and button textures
    success = stage.loadStage(renderer,success);
    //load player x and y coords from savegame

    /* this will have to be called when user clicks a saved file button from load game screen
    stage.loadSavedGameData(savegame1);
    stage.loadSavedGameData(savegame2);
    stage.loadSavedGameData(savegame3);
    */

	//load sound effects
	loadSounds();
	//load user options preferences from save.
	pregameui.optionsButtons[1].fullScreenToggle = preferences.prefsData[0];
	pregameui.optionsButtons[2].musicToggle = preferences.prefsData[1];
	pregameui.optionsButtons[3].voiceToggle = preferences.prefsData[2];
	music.musicToggle=pregameui.optionsButtons[2].musicToggle;
    if(music.musicToggle)//if music is toggled on from save file, this plays it
    {
        music.playMusic();
    }
    if(pregameui.optionsButtons[1].fullScreenToggle)//if fullscreen is toggled on from save file, this updates the window
    {
        pregameui.optionsButtons[1].setFullScreenOn(window,renderer);
    }



    //fade to black background
    blackGround.loadFromFile("images/Blackground.png",renderer);
    //loads the font
    text.loadText(renderer);

    //creates text textures for new/load game screens to display time of save by filenumber
    savegame.loadSavedMetaData(renderer,text.font);

    //for debugging
    if(success == false)
    {
        printf("something didn't load right in loadmedia.");
    }
	return success;
}

void close()
{
    //save progress
    //this needs to be written when player exits stage1, probably needs to be multithread
    if(playedTime.getTicks() > 0)
    {
        savegame.writeSaveFile(chosenSave,pregameui,stage,playedTime.timePlayed);
    }
    //need to scale to 3.
    //savegame.writeSaveFile(1,pregameui,stage);
    //savegame.writeSaveFile(2,pregameui,stage);

    //save preferences
    preferences.writePrefsFile(pregameui);


    //free pregame ui resouces
    pregameui.free();
    //free stage resources
    stage.free();
    //free animation textures
    animations.freeAnimationTextures();
    //free the background used to fade in / out from black
	blackGround.free();
	//free text resources
	text.free();
	//audio destructor frees audio
	music.freeAudio();
	sound.freeAudio();
	while(!sounds.empty()){
        sounds.pop_back();
	}

	//Free semaphore
	//SDL_DestroySemaphore( writePrefsLock );
	//writePrefsLock = NULL;

	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;


	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
			bool fade=false;
			//load the bg music file
            music.loadMusic();
            music.playMusic();
			//The frames per second cap timer
			timer capTimer;
			//Start counting frames per second
			int countedFrames = 0;
			//Event handler
			SDL_Event e;


			//While application is running
			while( !quit )
			{
			    //Start cap timer
				capTimer.start();
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
                    {
                        if(gameState == 5){
                            //player clicks mouse inside stage
                            int buttonClicked = 0;
                            //buttonClicked takes the sum of all the button checks, 0 is outside of any buttons
                            for( int i = 0; i < TOTAL_STAGE_BUTTONS; ++i )
                            {
                                buttonClicked += stage.buttons[ i ].handleStageEvent(stage.buttons[i].buttonName, &e, window,renderer );
                            }
                            stage.handleStageButtonPresses(buttonClicked,renderer);
                            if(buttonClicked == 1)
                            {//player clicked save and exit button
                                gameState=0;
                                std::cout<<"\n playedTime: "<<playedTime.getTicks();
                                playedTime.timePlayed += playedTime.getTicks();
                                playedTime.pause();
                                pregameui.loadMainButtons(renderer);
                            }
                        }
                        //Handle button events when in main screen
                        if(gameState == 0)
                        {

                            int oldGameState = gameState;
                            for( int i = 0; i < TOTAL_MAIN_BUTTONS; ++i )
                            {//handlePGUIEvent needs to be broken up into 5 parts
                                gameState = pregameui.mainButtons[ i ].handlePGUIEvent(gameState,pregameui.mainButtons[i].buttonName, &e, window,renderer );
                            }
                            if(gameState != oldGameState)
                            {//user clicked a button
                                pregameui.loadState(oldGameState,gameState,renderer);
                                int newGameState = gameState;
                                gameState = oldGameState;
                                fade=true;
                                fade=fadeOut(countedFrames,fade);
                                gameState=newGameState;
                            }
                        }
                        if(gameState==1)
                        {//newgame screen - handles button clicks and gamestate change
                            int oldGameState = gameState;
                            bool clickedSave = false;
                            for( int i = 0; i < TOTAL_NEWGAME_BUTTONS; ++i )
                            {//poll for mouse clicks on buttons
                                gameState = pregameui.newgameButtons[ i ].handlePGUIEvent(gameState,pregameui.newgameButtons[i].buttonName, &e, window,renderer );
                                if(gameState==5 && !clickedSave)
                                {
                                    chosenSave = pregameui.newgameButtons[i].chosenSave;
                                    std::cout<<"\n main chosenSave: "<<chosenSave;
                                    clickedSave=true;
                                    playedTime.timePlayed=0;
                                    playedTime.start();
                                }
                            }
                            if(gameState==0)
                            {//user clicked back button
                                pregameui.loadState(oldGameState,gameState,renderer);
                            }
                            if(gameState==5)
                            {//user clicked stage 1 button
                                pregameui.freeNewgameButtons();
                                //pregameui.existingSave=true;
                                stage.setNewgameVars();
                            }
                            if(gameState != oldGameState)
                            {
                                int newGameState = gameState;
                                gameState = oldGameState;
                                fade=true;
                                fade=fadeOut(countedFrames,fade);
                                gameState=newGameState;
                            }
                        }
                        if(gameState==2)
                        {//loadgame gamestate button click / gamestate change handling
                            int oldGameState = gameState;
                            bool clickedSave = false;
                            for( int i = 0; i < TOTAL_LOADGAME_BUTTONS; ++i )
                            {//handlePGUIEvent needs to be broken up into 5 parts
                                gameState = pregameui.loadgameButtons[ i ].handlePGUIEvent(gameState,pregameui.loadgameButtons[i].buttonName, &e, window,renderer );
                                if(gameState==5 && !clickedSave)
                                {
                                    chosenSave = pregameui.loadgameButtons[i].chosenSave;
                                    std::cout<<"\n main chosenSave: "<<chosenSave;
                                    clickedSave=true;
                                    savegame.readSaveFile(chosenSave);
                                    playedTime.timePlayed=savegame.data[2];
                                    playedTime.start();

                                }
                            }
                            if(gameState==0)
                            {//user clicked back button
                                pregameui.loadState(oldGameState,gameState,renderer);
                            }
                            if(gameState==5)
                            {//user clicked stage 1 button
                                std::cout<<"\n chosenSave: "<<chosenSave;
                                savegame.readSaveFile(chosenSave);
                                stage.player1.setX(savegame.data[3]);
                                stage.player1.setY(savegame.data[4]);
                                stage.habInternalY1 = savegame.data[5];
                                stage.habInternalY2 = savegame.data[6];

                                pregameui.freeLoadgameButtons();
                                //pregameui.loadLoadgameButtons(renderer);
                            }
                            if(gameState != oldGameState)
                            {
                                int newGameState = gameState;
                                gameState = oldGameState;
                                fade=true;
                                fade=fadeOut(countedFrames,fade);
                                gameState=newGameState;
                            }
                        }
                        if(gameState==3)
                        {//options screen button handling /gamestate change handing
                            int oldGameState = gameState;
                            for( int i = 0; i < TOTAL_OPTIONS_BUTTONS; ++i )
                            {//handlePGUIEvent needs to be broken up into 5 parts
                                gameState = pregameui.optionsButtons[ i ].handlePGUIEvent(gameState,pregameui.optionsButtons[i].buttonName, &e, window,renderer );
                            }
                            if(gameState==0)
                            {//user clicked back button

                                //this is where I want preferences to be written to file, but I'll probably need
                                //to set up a thread for it.
                                //SDL_Thread* writePrefsThread = SDL_CreateThread( threadFunction, "writePrefsThread", NULL );

                                //Wait for thread to finish
                                //SDL_WaitThread( writePrefsThread, NULL );

                                pregameui.loadState(oldGameState,gameState,renderer);

                            }
                            if(gameState==3)
                            {//user clicked one of the toggle buttons
                                //refresh the buttons to reflect the new toggled status of the one clicked
                                pregameui.loadState(oldGameState,gameState,renderer);
                                //user toggles music on or off
                                if(pregameui.optionsButtons[2].musicToggle)
                                {
                                    music.musicToggle = true;
                                    if(!music.isPlaying())
                                    {
                                        music.playMusic();
                                    }
                                }
                                else
                                {
                                    music.musicToggle = false;
                                    if(music.isPlaying())
                                    {
                                        music.stopMusic();
                                    }
                                }
                                if(pregameui.optionsButtons[3].voiceToggle)
                                {
                                    //chapter.voice.voiceOn = true;
                                }
                                else
                                {
                                    //chapter.voice.voiceOn = false;
                                }
                            }
                            if(gameState != oldGameState)
                            {
                                int newGameState = gameState;
                                gameState = oldGameState;
                                fade=true;
                                fade=fadeOut(countedFrames,fade);
                                gameState=newGameState;
                            }
                        }
                        if(gameState==4)
                        {
                            int oldGameState = gameState;
                            for( int i = 0; i < TOTAL_CREDITS_BUTTONS; ++i )
                            {//handlePGUIEvent needs to be broken up into 5 parts
                                gameState = pregameui.creditsButtons[ i ].handlePGUIEvent(gameState,pregameui.creditsButtons[i].buttonName, &e, window,renderer );
                            }
                            if(gameState != oldGameState)
                            {
                                pregameui.loadState(oldGameState,gameState,renderer);
                                int newGameState = gameState;
                                gameState = oldGameState;
                                fade=true;
                                fade=fadeOut(countedFrames,fade);
                                gameState=newGameState;
                            }
                        }
                    }
					//Handle key press
					if( e.type == SDL_KEYDOWN )
					{
                        switch( e.key.keysym.sym )
						{
                            case SDLK_SPACE:
                                break;


                            case SDLK_ESCAPE:
                            if(gameState==0)
                            {
                                quit=true;
                            }
                            break;
							//sound tests
							case SDLK_1:
							    sounds[0].playSound();
							break;
							case SDLK_2:
                                sounds[1].playSound();
							break;
							case SDLK_3:
                                sounds[2].playSound();
							break;
							case SDLK_4:
                                sounds[3].playSound();
							break;
							case SDLK_9:
                                //press 9 to play / pause music
                                music.playMusic();
							break;
						}
					}

					//if wasd are pressed player will be moved.
					if(stage.internalView)
                    {
                        stage.player1.handleEvent(e);
					}
				}

				//process player movement, updates hab internal background as well
				if(stage.internalView)
                {
                    stage.move();
                    stage.player1.move(countedFrames);
                }

				//Clear screen
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );
                //Title Screen rendering
                if(gameState == 0)
                {
                    //renders buttons, bg, title image, and handles particle effect.
                    pregameui.handleTitleScreenRendering(renderer);
                }
                else if(gameState == 1)
                {//new game chapter select screen
                    pregameui.handleNewGameScreenRendering(renderer);
                    savegame.handleSavedMetaDataRendering(renderer);
                }
                else if(gameState == 2)
                {//load game chapter/stage select screen
                    //handles the buttons and background rendering
                    pregameui.handleLoadGameScreenRendering(renderer);
                    savegame.handleSavedMetaDataRendering(renderer);
                }
                else if(gameState == 3)
                {
                    //options screen buttons/bg rendering
                    pregameui.handleOptionsScreenRendering(renderer);
                }
                else if(gameState == 4)
                {
                    //render background image and back button
                    pregameui.handleCreditsScreenRendering(renderer);
                    //robot animation
                    animations.renderToaster(renderer);
                    //animations.renderToaster2(renderer);
                }
                else if(gameState == 5)
                {
                    //renders bg, stage ui buttons and player
                    stage.renderStage1(renderer);
                }
                if(fade)
                {
                    fade = fadeIn(countedFrames,fade);
                    blackGround.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
				//Update screen
				SDL_RenderPresent( renderer );
				++countedFrames;
				if(countedFrames>0 && countedFrames < 255 && gameState==0)
                {  //fades in the go homeless title
                    pregameui.title.setAlpha(countedFrames);
                }
				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
				//increments frames for animations
				animations.progress();


			}

			//Disable text input
			SDL_StopTextInput();
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
