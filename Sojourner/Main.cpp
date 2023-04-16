//local classes
#include "audio.h"
#include "button.h"
#include "Texture.h"
#include "timer.h"
#include "particle.h"
#include "chapter.h"
#include "saveGame.h"
#include "pregameui.h"
#include "animations.h"
#include "stage.h"
#include "text.h"

const int TOTAL_STATES = 8;

//gameStates
//gameState = 0 pregameui
//gameState = 1 new game chapter select
//gameState = 2 load game chapter select
//gameState = 3 options
//gameState = 4 credits
//gameState = 5 chapter 1
//gameState = 6 stage 1
//gameState = 7 chapter 2
//gameState = 8 chapter 3

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
saveGame savegame;
audio music;
std::vector<audio> sounds;
audio sound;
//declare chapter1
chapter chapter;
//declare stage
stage stage;
//declare instance of pregame user interface.
pregameui pregameui;
//declare instance of animations
animations animations;
//set up text input
text text;
//if player is not verified they wont progress to ch 3.
bool verified = false;
//declare sound vector & load sounds into it.
void loadSounds();
//render particles to screen
//tracks the state of the game for rendering etc.
int gameState;
//initializes audio,video, etc.
Texture blackGround;
bool fadeOut(int countedFrames, bool fade);

bool fadeIn(int countedFrames,bool fade);

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
    //load saved game
	savegame.readFile();
	//pre-game chapter set up.
	success = chapter.loadChapters(savegame.data[0],savegame.data[1],savegame.data[2],savegame.data[3],savegame.data[4],savegame.data[5],renderer,success);
    //load animations textures
    success = animations.setAnimationTextures(renderer);
    //sets up pregame ui button names, button textures, and bg textures.
    success = pregameui.loadPregameUI(renderer,success);
    //loads stage textures, button names, and button textures
    success = stage.loadStage(renderer,success);
	//load sound effects
	loadSounds();
    //fade to black background
    blackGround.loadFromFile("images/Blackground.png",renderer);
    //sets strings for verification page, loads those strings into their textures,loads verification page bg
    text.loadText(chapter.font,renderer);
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
    savegame.writeFile(chapter.currentChapter,chapter.currentPage,chapter.currentScript,chapter.chapter1Complete,chapter.chapter2Complete,chapter.chapter3Complete);
    //free chapter resources
    chapter.free();
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

                        if(gameState == 8)//chapter 3
                        {
                            if(!verified)
                            {
                                verified = text.verifyNoRobo();
                            }
                            else
                            {
                                int buttonClicked = 0;
                                for( int i = 0; i < TOTAL_CHAPTER_BUTTONS; ++i )
                                {
                                    buttonClicked += chapter.buttons[ i ].handleChapterEvent(chapter.buttons[i].buttonName, &e, window,renderer );
                                }
                                chapter.handleChapterButtonPresses(buttonClicked,renderer);
                                if( chapter.exitChapter || buttonClicked == 1)
                                {
                                    gameState=0;
                                    music.resetMusic();
                                    chapter.exitChapter = false;
                                }
                            }
                        }
                        if(gameState == 7)
                        {//player clicks mouse inside chapter 1 or 2
                            int buttonClicked = 0;
                            //buttonClicked takes the sum of all the button checks, 0 is outside of any buttons
                            for( int i = 0; i < TOTAL_CHAPTER_BUTTONS; ++i )
                            {
                                buttonClicked += chapter.buttons[ i ].handleChapterEvent(chapter.buttons[i].buttonName, &e, window,renderer );
                            }
                            chapter.handleChapterButtonPresses(buttonClicked,renderer);
                            if(chapter.exitChapter || buttonClicked == 1)
                            {//player clicked back button or player completed chapter 2
                                gameState=0;
                                music.resetMusic();
                                chapter.exitChapter = false;
                            }
                        }
                        if(gameState == 6){
                            //player clicks mouse inside stage
                            int buttonClicked = 0;
                            //buttonClicked takes the sum of all the button checks, 0 is outside of any buttons
                            for( int i = 0; i < TOTAL_STAGE_BUTTONS; ++i )
                            {
                                buttonClicked += stage.buttons[ i ].handleStageEvent(stage.buttons[i].buttonName, &e, window,renderer );
                            }
                            stage.handleStageButtonPresses(buttonClicked,renderer);
                            if(buttonClicked == 1)
                            {//player clicked exit button
                                gameState=0;
                                music.resetMusic();
                            }
                        }
                        if(gameState == 5)
                        {//player clicks mouse inside chapter 1 or 2
                            int buttonClicked = 0;
                            //buttonClicked takes the sum of all the button checks, 0 is outside of any buttons
                            for( int i = 0; i < TOTAL_CHAPTER_BUTTONS; ++i )
                            {
                                buttonClicked += chapter.buttons[ i ].handleChapterEvent(chapter.buttons[i].buttonName, &e, window,renderer );
                            }
                            chapter.handleChapterButtonPresses(buttonClicked,renderer);
                            if(chapter.exitChapter || buttonClicked == 1)
                            {//player clicked back button or player completed chapter 2
                                gameState=0;
                                music.resetMusic();
                                chapter.exitChapter=false;
                            }
                        }
                        //Handle button events when in pregame ui (opening, newgame, loadgame,options,and credits).
                        if(gameState <5)
                        {
                            //chapters get reset here, but I may have the actual chapter 1 button on this screen determine the reset.
                            //chapter.resetChapters(renderer);
                            int oldGameState = gameState;
                            for( int i = 0; i < TOTAL_PREGAME_BUTTONS; ++i )
                            {
                                gameState = pregameui.buttons[ i ].handlePGUIEvent(gameState,pregameui.buttons[i].buttonName, &e, window,renderer );
                            }
                            if(gameState==1)
                            {//user clicks the newGame button
                                chapter.resetChapters(renderer);
                            }
                            if(gameState==3)
                            {//user toggles music on or off
                                if(pregameui.buttons[10].musicOn)
                                {
                                    music.musicOn = true;
                                    if(!music.isPlaying())
                                    {
                                        music.playMusic();
                                    }
                                }
                                else
                                {
                                    music.musicOn = false;
                                    if(music.isPlaying())
                                    {
                                        music.stopMusic();
                                    }
                                }
                                if(pregameui.buttons[11].voiceOn)
                                {
                                    chapter.voice.voiceOn = true;
                                }
                                else
                                {
                                    chapter.voice.voiceOn = false;
                                }
                            }
                            if(gameState == 5)
                            {//user clicks chapter 1 button
                                if(chapter.currentChapter != 0)
                                {
                                    chapter.currentChapter = 0;
                                    chapter.resetPages();
                                }
                                music.resetChapter1Music();
                                chapter.loadChapter(renderer);
                            }
                            else if(gameState == 7)
                            {//user clicks chapter 2 button
                                if(chapter.currentChapter!=1)
                                {
                                    chapter.currentChapter =1;
                                    chapter.resetPages();
                                }
                                music.resetChapter2Music();
                                chapter.loadChapter(renderer);
                            }
                            else if(gameState == 8)
                            {//user clicks chapter 3 button
                                if(chapter.currentChapter!=2)
                                {
                                    chapter.currentChapter =2;
                                    chapter.resetPages();
                                }
                                music.resetChapter3Music();
                                chapter.loadChapter(renderer);
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
                    }
					//Handle key press
					if( e.type == SDL_KEYDOWN )
					{
					    if(gameState==8 && !verified)
                        {
                            //Handle backspace
                            if( e.key.keysym.sym == SDLK_BACKSPACE && text.inputText.str().length() > 0 )
                            {
                                text.inputText.str("");
                            }
                            //Handle copy
                            else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                            {
                                SDL_SetClipboardText( text.inputText.str().c_str() );
                            }
                            //Handle paste
                            else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                            {
                                text.inputText.str() = SDL_GetClipboardText();
                            }
                        }

						switch( e.key.keysym.sym )
						{
                            case SDLK_SPACE:
                                if(gameState ==8)
                                {
                                    //update script line, page, end chapter
                                    chapter.progress2(renderer);
                                    if(chapter.exitChapter)
                                    {
                                        gameState=0;
                                        chapter.exitChapter = false;
                                    }
                                }
                                else if(gameState==7)
                                {
                                    //update script line, page, end chapter
                                    chapter.progress2(renderer);
                                    if(chapter.exitChapter)
                                    {
                                        gameState=0;
                                        chapter.exitChapter = false;
                                    }
                                }
                                else if(gameState==5)
                                {
                                    //update script line, page, end chapter
                                    chapter.progress2(renderer);
                                    if(chapter.exitChapter)
                                    {
                                        gameState=0;
                                        chapter.exitChapter = false;
                                    }
                                }
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
							case SDLK_h:
							    //press h to cycle dialog visability
							    chapter.handleDialogVisability();
							break;
							case SDLK_9:
                                //press 9 to play / pause music
                                music.playMusic();
							break;
						}
					}
					else if( gameState == 8 && verified==false && e.type == SDL_TEXTINPUT )
                    {
                        //Not copy or pasting
						if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
						{
                            text.inputText << e.text.text;
						}
						verified = text.verifyNoRobo();
						if(verified)
                        {//somehow currentScript was greater than 0 without this
                            chapter.currentScript = 0;
                        }
                    }
					//if wasd are pressed player will be moved.
					stage.player1.handleEvent(e);
				}
				//process player movement
				stage.player1.move(countedFrames);
				//Clear screen
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );
                //Title Screen rendering
                if(gameState == 0)
                {
                    chapter.chapterTimer.stop();
                    //renders buttons, bg, title image, and handles particle effect.
                    pregameui.handleTitleScreenRendering(renderer);
                }
                else if(gameState == 1)
                {//new game chapter select screen
                    chapter.chapterTimer.stop();
                    pregameui.handleNewGameScreenRendering(renderer);
                }
                else if(gameState == 2)
                {//load game chapter/stage select screen
                    chapter.chapterTimer.stop();
                    //handles the buttons and background rendering
                    pregameui.handleLoadGameScreenRendering(renderer,chapter.chapter1Complete,chapter.chapter2Complete,chapter.chapter3Complete);
                }
                else if(gameState == 3)
                {
                    //options screen buttons/bg rendering
                    pregameui.handleOptionsScreenRendering(renderer);
                }
                //chapter 1 is in effect
                else if(gameState == 5)
                {
                    //Chapter rendering (buttons and backgrounds and text.
                    chapter.handleRendering(renderer);
                    //render tao animation
                    animations.renderTao(renderer);
                    //render rat animation
                    animations.renderRat(renderer);
                }
                //if chapter 2 is in effect
                else if(gameState == 7)
                {
                    chapter.handleRendering(renderer);
                    //rat animation rendered after chapter background, dialog box are rendered.
                    animations.renderRat(renderer);
                    if(chapter.currentPage == 3)
                    {
                        animations.renderToaster2(renderer);
                    }
                    else
                    {
                        animations.resetToaster2();
                    }
                    if(chapter.currentPage == 4)
                    {
                        animations.renderBlackstar(renderer);
                    }
                    if(chapter.currentPage == 5)
                    {
                        animations.renderPortal(renderer);
                    }
                    else
                    {
                        animations.resetPortal();
                    }
                }
                else if(gameState == 8)//render chapter 3 no robo verification, if passed, render chapter 3
                {
                    if(!verified)
                    {
                        text.renderVerification(chapter.font,renderer);
                    }
                    else
                    {
                        if(chapter.currentPage == 6)
                        {
                            animations.renderTrailer(renderer);
                        }
                        //Chapter rendering (buttons and backgrounds and text.
                        chapter.handleRendering(renderer);
                        //rat is rendered on top of dialog box in lower right hand corner. (after verification)
                        animations.renderRat(renderer);
                    }
                }
                else if(gameState == 4)
                {
                    //render background image and back button
                    pregameui.handleCreditsScreenRendering(renderer);
                    //robot animation
                    animations.renderToaster(renderer);
                    //animations.renderToaster2(renderer);
                }
                else if(gameState == 6)
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
                //set script line
                chapter.setAutoScript();
			}
			//Disable text input
			SDL_StopTextInput();
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
