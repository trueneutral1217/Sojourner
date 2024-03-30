//local classes
#include "audio.h"
#include "button.h"
#include "Texture.h"
#include "particle.h"
#include "saveGame.h"
#include "pregameui.h"
#include "animations.h"
#include "stage.h"
#include "text.h"

//total gamestates
const int TOTAL_STATES = 6;
//gameStates
//gameState = 0 pregameui
//gameState = 1 new game chapter select
//gameState = 2 load game chapter select
//gameState = 3 options
//gameState = 4 credits
//gameState = 5 stage 1
//gameState = 6 opening sequence gamestate, goes to gamestate 5
//gameState = 7 gameover


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
//declare user preferences
saveGame preferences;
//declare user savegame
saveGame savegame;
//declare music
audio music;
//declare sounds vector
std::vector<audio> sounds;
//declare sound
audio sound;
//declare stage
stage stage,openingSequence,gameOver;
//declare opening sequence stage (used when new game is created)
//stage openingSequence;
//declare instance of pregame user interface.
pregameui pregameui;
//declare instance of animations
animations animations;
//set up text input
text text;
//tracks the amount of time user has been in gameState 5
timer playedTime;

int currentTime =0;
int previousTime = 0;
float delta = 0.0f;


//declare sound vector & load sounds into it.
bool loadSounds();
//render particles to screen
//tracks the state of the game for rendering etc.
int gameState;
//tracks which game the user loaded
int chosenSave;
//initializes audio,video, etc.
Texture blackGround;
//fadeout function for old gamestate
bool fadeOut(int countedFrames, bool fade);
//fadein function for current gamestate
bool fadeIn(int countedFrames,bool fade);
//reduces opacity of blackground texture (blackground is a foreground texture)
bool fadeIn(int countedFrames, bool fade)
{
    std::cout<<"\n running fadeIn(int countedFrames, bool fade)";
    Uint32 alpha = 255-(countedFrames%256);
    blackGround.setAlpha(alpha);
    if(countedFrames%256>254)
    {
        fade=false;
    }
    return fade;
}
//increases opacity of blackground texture
bool fadeOut(int countedFrames, bool fade)
{
    std::cout<<"\n running fadeOut(int countedFrames, bool fade)";
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
    std::cout<<"\n running init()";
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

bool loadSounds()
{
    std::cout<<"\n running loadSounds()";
    bool success = true;
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
    return success;
}

bool loadMedia()
{
    std::cout<<"\n running loadMedia()";
	bool success = true;
    //load saved preferences
    preferences.readPrefsFile();
    //reads save data, if a save exists, shows the time saved and played
    for(int i = 0; i<TOTAL_SAVES;i++)
    {
        savegame.readSaveFile(i);

        pregameui.existingSave[i] = savegame.data[0];
        //time gets typecasted to an sint32 at save time (before converting it to string)
        //I typecast it back to time_t, then convert to string after loading, sdt (saved date time)
        //can be used at newgame/loadgame gamestates to show when that file was last saved, if at all.
        //I also save the amount of time a user spent on any particular save game.
        time_t saved = savegame.data[1];
        char* sdt = ctime(&saved);
        std::cout<<"\n time of save: "<<sdt;
        std::cout<<"\n amount of time played: "<<savegame.data[2];
    }
	//load animations textures
    //success = animations.setAnimationTextures(renderer); //loading by scene now.

    //sets up pregame ui button names, button textures, and bg textures.
    success = pregameui.loadPregameUI(renderer,success);
    //loads stage textures, button names, and button textures
    //success = stage.loadStage(renderer,success);


	//load sound effects
	success = loadSounds();
	//loadSounds();
	//load user options preferences from save.
	pregameui.optionsButtons[1].fullScreenToggle = preferences.prefsData[0];
	pregameui.optionsButtons[2].musicToggle = preferences.prefsData[1];
	pregameui.optionsButtons[3].voiceToggle = preferences.prefsData[2];
	//sets music on/off based on saved data
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
    //creates text textures for new/load game screens to display time of save by filenumber, as well as time played
//    savegame.loadSavedMetaData(renderer,text.font);
    //for debugging
    if(success == false)
    {
        printf("something didn't load right in loadmedia.");
    }
	return success;
}

void close()
{
    std::cout<<"\n running close()";
    //save progress
    //this needs to be written when player exits stage1, probably needs to be multithread
    std::cout<<"\n playedTime.getTicks(): "<<playedTime.getTicks();
    std::cout<<"\n playedTime.timePlayed: "<<playedTime.timePlayed;
//    if(playedTime.getTicks() > 0)
  //  {
        //savegame.writeSaveFile(chosenSave,stage,playedTime.timePlayed);
  //  }
    //save preferences
    preferences.writePrefsFile(pregameui);
    //free pregame ui resouces
    pregameui.free();

    //since the opening sequence stage doesn't have it's free function get called yet, I'm putting it here, temporarily.
    openingSequence.free();
    //free stage resources
    //stage.free();
    //free animation textures
//    animations.freeAnimationTextures();
    //free the background used to fade in / out from black
	blackGround.free();
	//free text resources
	text.free();
	//audio destructor frees audio
	music.freeAudio();

	//frees the sound resources
	//sound.freeAudio();
	//freeAudio only needs to be called once.

	//frees the elements in the sounds vector
	while(!sounds.empty()){
        sounds.pop_back();
	}
	//Destroy window and renderer
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
    std::cout<<"\n running main( int argc, char* args[] )";
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
            //Start cap timer
            capTimer.start();
			//While application is running
			while( !quit )
			{

			    previousTime = currentTime;
			    currentTime = SDL_GetTicks();
			    delta = (currentTime - previousTime) / 1000.0f;

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					if(stage.player1.isDead)
                    {
                        std::cout<<"\n stage.player1.isDead == true";
                        //loads bg image
                        gameOver.loadGameOver(renderer);
                        //frees stage resources, resets stage variables to default.
                        stage.free();
                        //delete the savegame haha
                        savegame.deleteSave(chosenSave);
                        //flag that a save does not exist so that new game can be created in that slot.
                        pregameui.existingSave[chosenSave] = false;
                        //clear saved date & time of deleted save (may be redundant).
                        savegame.updateSavedMetaData(chosenSave,renderer,text.font);
                        savegame.savedDate[chosenSave].str("");
                        savegame.savedPlayTime[chosenSave].str("");
                        //pgui used for button handling
                        pregameui.loadState(5,7,renderer);
                        gameState = 7;
                        stage.player1.isDead = false;
                    }
                    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION || openingSequence.complete)
                    {
                        if(gameState == 5)
                        {
                            gameState = stage.handleButtons(renderer,&e);
                            if(gameState!= 5)
                            {//player clicked save and exit button
                                //player is going back to the main scene
                                //playedTime needs to be updated because player was in game
                                std::cout<<"\n playedTime.timePlayed before running playedTime.updatePlayedTime(): "<<playedTime.timePlayed;
                                playedTime.updatePlayedTime();
                                std::cout<<"\n playedTime.timePlayed after running playedTime.updatePlayedTime(): "<<playedTime.timePlayed;
                                playedTime.pause();
                                std::cout<<"\n playedTime started: "<<playedTime.isStarted()<<", playedTime paused: "<<playedTime.isPaused();
                                std::cout<<"\n SDL_getTicks(): "<<SDL_GetTicks()<<", playedTime.getTicks(): "<<playedTime.getTicks();
                                //player position, background y, and played amount of time, and the date of last save
                                //are updated by these two functions
                                savegame.updateSaveData(chosenSave,stage,playedTime.timePlayed);
                                savegame.updateSavedMetaData(chosenSave,renderer,text.font);
                                //free stage resources!
                                stage.free();
                                pregameui.loadTitleScreenTextures(renderer);
                                pregameui.loadMainButtons(renderer);

                            }
                        }
                        //Handle button events when in main screen
                        if(gameState == 0)
                        {
                            //handles button presses / mouseover from pregame scenes.

                            gameState = pregameui.handleButtons(gameState,&e, window,renderer);

                            if(gameState==4)
                            {
                                animations.loadCreditsAnimationTextures(renderer);
                            }

                            if(gameState==1 || gameState == 2)
                            {
                                savegame.loadSaveTextTextures(renderer,text.font);
                            }

                        }
                        if(gameState==1)
                        {//newgame screen - handles button clicks and gamestate change
                            gameState = pregameui.handleButtons(gameState,&e, window,renderer);

                            if(gameState==6)
                            {
                                chosenSave = pregameui.chosenSave;
                                playedTime.timePlayed = 0;
                                playedTime.restart();
                                animations.loadBushAnimationTextures(renderer);
                                animations.loadLeftCurtainAnimationTextures(renderer);
                                animations.loadRightCurtainAnimationTextures(renderer);
                                openingSequence.loadOpeningSequence(renderer);
                            }
                            if(gameState==5)
                            {//user loadeded a saved game
                                std::cout<<"\n not from opening sequence";
                                //I don't think this code ever runs.
                                chosenSave = pregameui.chosenSave;
                                stage.setNewgameVars();
                                playedTime.timePlayed = 0;
                                playedTime.restart();
                                stage.loadStage(renderer,stage.inHab, stage.inEng,true);
                                //savegame.freeTextTextures();
                            }
                            if(pregameui.triggerDelete)
                            {
                                pregameui.triggerDelete = false;
                                savegame.deleteSave(pregameui.deleteCandidate);
                                //savegame.readSaveFile(pregameui.deleteCandidate);
                                std::cout<<"\n deleteSave called from newgame screen";
                                pregameui.existingSave[pregameui.deleteCandidate] = false;
                                savegame.updateSavedMetaData(pregameui.deleteCandidate,renderer,text.font);
                                savegame.savedDate[pregameui.deleteCandidate].str("");
                                savegame.savedPlayTime[pregameui.deleteCandidate].str("");
                                //savegame.readSaveFile(pregameui.deleteCandidate);
                                savegame.loadSaveTextTextures(renderer, text.font);
                            }
                        }
                        if(gameState==2)
                        {//loadgame gamestate button click / gamestate change handling

                            gameState = pregameui.handleButtons(gameState,&e, window,renderer);

                            if(gameState==5)
                            {//user clicked a load saved game button (1, 2, or 3)
                                std::cout<<"\n chosenSave: "<<chosenSave<<"\n pregameui.chosenSave: "<<pregameui.chosenSave<<"\n pregameui.deleteCandidate: "<<pregameui.deleteCandidate;
                                chosenSave = pregameui.chosenSave;
                                std::cout<<"\n chosenSave: "<<chosenSave;
                                savegame.readSaveFile(chosenSave);
                                //if the save exists load the saved data
                                if(savegame.data[0])
                                {
                                    //set player coords on screen and location in habitat (since it parallaxes vertically)
                                    savegame.setDataValues();
                                    stage.loadSavedGameData(savegame.dataValues1);
                                    stage.player1.loadSavedPlayerData(savegame.dataValues2);
                                    //load ship gauge data from save file
                                    stage.ship.loadSavedShipData(savegame.dataValues3);
                                    if(stage.ship.habitation.planter.buttonAvailable.size() == 0)
                                    {
                                        stage.ship.habitation.planter.buttonAvailable.push_back(savegame.data[18]);
                                        stage.ship.habitation.planter.buttonAvailable.push_back(savegame.data[19]);
                                        stage.ship.habitation.planter.buttonAvailable.push_back(savegame.data[26]);
                                    }
                                    stage.timeSurvived = savegame.data[20];
                                    stage.ship.habitation.planter.planterState = savegame.data[21];
                                    stage.ship.habitation.planter.planterDaysState = savegame.data[22];
                                    stage.ship.habitation.planter.planterTimeWatered = savegame.data[23];
                                    stage.inHab = savegame.data[27];
                                    stage.inEng = savegame.data[28];
                                    stage.ship.habitation.bed.stationTier = savegame.data[29];
                                    std::cout<<"\n *** \n before loading scrap.itemCount = "<<stage.ship.inventory.scrap.itemCount;
                                    stage.ship.inventory.scrap.itemCount = savegame.data[30];
                                    std::cout<<"\n *** \n after loading scrap.itemCount = "<<stage.ship.inventory.scrap.itemCount;
                                    stage.ship.habitation.bed.upgradeAvailable = savegame.data[31];
                                    stage.ship.habitation.recreation.upgradeAvailable = savegame.data[32];
                                    stage.ship.habitation.recreation.stationTier = savegame.data[33];
                                    stage.ship.habitation.waterTank.upgradeAvailable = savegame.data[34];
                                    stage.ship.habitation.waterTank.stationTier = savegame.data[35];
                                    stage.ship.engineering.batteryArray.upgradeAvailable = savegame.data[36];
                                    stage.ship.engineering.batteryArray.stationTier = savegame.data[37];

                                    //data needs to be loaded from save before stage loads.
                                    stage.loadStage(renderer, stage.inHab, stage.inEng, true);
                                    //previouslyPlayed is probably deprecated by timePlayed.
                                    std::cout<<"\n savegame.data[2]: "<<savegame.data[2];
                                    Uint32 previouslyPlayed = savegame.data[2];
                                    std::cout<<"\n previouslyPlayed: "<<previouslyPlayed;
                                    playedTime.timePlayed = savegame.data[2];
                                    //savegame.freeTextTextures();
                                    playedTime.restart();
                                }
                                //if the save doesn't exist, gameState goes back to 2
                                if(gameState==0)
                                {
                                    pregameui.loadLoadGameTextures(renderer);
                                    pregameui.loadLoadgameButtons(renderer);
                                    gameState = 2;
                                }
                            }
                            if(pregameui.triggerDelete)//going to need to refresh new/loadgame screens & text textures
                            {//after a save deletion.
                                pregameui.triggerDelete = false;
                                savegame.deleteSave(pregameui.deleteCandidate);

                                //savegame.readSaveFile(pregameui.deleteCandidate);

                                std::cout<<"\n deleteSave called from loadgame screen";
                                pregameui.existingSave[pregameui.deleteCandidate] = false;
                                savegame.updateSavedMetaData(pregameui.deleteCandidate,renderer,text.font);
                                savegame.savedDate[pregameui.deleteCandidate].str("");
                                savegame.savedPlayTime[pregameui.deleteCandidate].str("");
                                //savegame.readSaveFile(pregameui.deleteCandidate);
                                savegame.loadSaveTextTextures(renderer, text.font);
                            }
                        }
                        if(gameState==3)
                        {//options screen button handling /gamestate change handing
                            gameState = pregameui.handleButtons(gameState,&e, window,renderer);
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
                        if(gameState==4)
                        { // credits screen
                            gameState = pregameui.handleButtons(gameState,&e, window,renderer);

                            if(!animations.animationTimer2.isStarted())
                            {
                                animations.animationTimer2.start();
                            }
                            if(gameState == 0)
                            {
                                animations.freeCreditsAnimationTextures();
                            }
                        }
                        if(gameState == 6)
                        {
                            //this is the opening sequence of a new game.
                            //should allow player movement etc.
                            openingSequence.handleButtons(renderer,&e);
                            //frees animations between house and backyard scene in opening sequence
                            if(openingSequence.backdoorInteracted & !animations.bushFree)
                            {
                                animations.freeBushAnimationTextures();
                                animations.freeLeftCurtainAnimationTextures();
                                animations.freeRightCurtainAnimationTextures();
                                animations.bushFree = true;
                            }
                        }
                        if(gameState == 7)
                        {
                            //gameover scene of the game
                            gameState = pregameui.handleButtons(gameState,&e, window,renderer);
                            if(gameState == 0)
                            {
                                gameOver.freeGameOver();
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
                            else if(gameState == 1 || gameState == 2 || gameState == 3 || gameState == 4 || gameState == 7)
                            {//if player presses escape in newgame,loadgame,options,credits, or gameOver screen, return to title screen
                                pregameui.loadState(gameState,0,renderer);
                                if(gameState == 4)
                                {
                                    animations.freeCreditsAnimationTextures();
                                }
                                gameState=0;
                            }
                            else if(gameState==6)
                            {
                                openingSequence.complete = true;
                            }
                            else if(gameState==5)
                            {
                                if(stage.ship.engineering.cargoArea.inventoryDisplaying)
                                {
                                    std::cout<<"\n should close ship's inventory";
                                    stage.ship.engineering.cargoArea.inventoryDisplaying = false;
                                }
                                if(stage.ship.engineering.researchDesk.researchDisplaying)
                                {
                                    std::cout<<"\n should close research";
                                    stage.ship.engineering.researchDesk.researchDisplaying = false;
                                }
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
					//if wasd are pressed player will be moved. 'e' to interact with stations
					if(stage.internalView)
                    {
                        stage.player1.handleEvent(e,delta);
					}
                    //handles the interactions with the stations.
                    if(stage.player1.interact)
                    {
                        stage.handleStation(renderer,text.font2);
                    }
                    if(!stage.buttonsFreed && !stage.player1.interact && !stage.ship.engineering.cargoArea.inventoryDisplaying && !stage.ship.engineering.researchDesk.researchDisplaying)
                    {
                        stage.freeStationButtons();
                    }
                    if(gameState == 6)
                    {
                        openingSequence.player1.handleEvent(e,delta);
                    }
				}
				//process player movement, updates hab internal background as well
				if(stage.internalView)
                {//updates player and habitat coords
                    stage.move(countedFrames,delta);
                }
                if(gameState == 6)
                {
                    openingSequence.move(countedFrames,delta);
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
                {//new game screen
                    //new/loadgame bg screen
                    pregameui.chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //weirdly, bg image renders after savedmetadata without this delay.
                    SDL_Delay(1);
                    //renders the text textures of existing saves' saved date and playedtime
                    savegame.handleSavedMetaDataRendering(renderer);
                    //renders the delete save prompt if conditions call for it, and the buttons.
                    pregameui.handleNewGameScreenRendering(renderer);

                }
                else if(gameState == 2)
                {//load game save select screen
                    //new/loadgame bg screen
                    pregameui.chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //weirdly, bg image renders after savedmetadata without this delay.
                    SDL_Delay(1);
                    //renders the text textures of existing saves' saved date and playedtime
                    savegame.handleSavedMetaDataRendering(renderer);
                    //renders the delete save prompt if conditions call for it, and the buttons.
                    pregameui.handleLoadGameScreenRendering(renderer);
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
                    animations.toasterAnimationProgress();
                    animations.cycleAnimations();
                    //animations.renderToaster2(renderer);
                }
                else if(gameState == 5)
                {
                    //renders bg, stage ui buttons and player
                    stage.renderStage1(renderer);
                }
                else if(gameState == 6)
                {
                    openingSequence.renderOpeningSequence(renderer,animations);
                    if(!openingSequence.backdoorInteracted)
                    {
                        animations.cycleAnimations();
                        animations.bushAnimationProgress();
                        animations.leftCurtainAnimationProgress();
                        animations.rightCurtainAnimationProgress();

                    }
                }
                else if(gameState == 7)
                {
                    //this is where gameover scene will be rendered.
                    gameOver.gameOverBG.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    pregameui.renderGameOverButton(renderer);
                    //pregameui.handleGameOverScreenRendering(renderer);
                }
                if(fade)
                {
                    fade = fadeIn(countedFrames,fade);
                    blackGround.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                if(openingSequence.complete)
                {
                    std::cout<<"\n changing gamestate from 6 to 5";
                    openingSequence.resetOpeningSequenceVariables();
                    gameState = 5;
                    //taken from the gamestate == 1 old way of transitioning to gamestate 5
                    //chosenSave = pregameui.chosenSave;
                    std::cout<<"\n from opening sequence";
                    stage.setNewgameVars();
                    //playedTime.timePlayed = 0;
                    //playedTime.restart();
                    stage.loadStage(renderer,stage.inHab, stage.inEng,true);
                }
				//Update screen
				SDL_RenderPresent( renderer );
				++countedFrames;
				if(countedFrames>0 && countedFrames < 255 && gameState==0)
                {  //fades in the title
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
				//animations.progress();
			}
			//Disable text input
			SDL_StopTextInput();
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
