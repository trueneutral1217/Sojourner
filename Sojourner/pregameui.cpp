#include "pregameui.h"

pregameui::pregameui()
{
    for(int i = 0; i<TOTAL_SAVES;i++)
    {
        existingSave[i] = false;
    }
    promptDelete=false;
    triggerDelete = false;
    deleteCandidate = 0;
}

pregameui::~pregameui()
{

}

void pregameui::loadOptionsButtons(SDL_Renderer* renderer)
{
    optionsButtonNames[0]="back";
    optionsButtonNames[1]="fullScreenToggle";
    optionsButtonNames[2]="musicToggle";
    optionsButtonNames[3]="voiceToggle";
    //lines for mouseover are commented out until the textures are created
	for( int i = 0; i < TOTAL_OPTIONS_BUTTONS; ++i )
    {
        optionsButtons[i].buttonName = optionsButtonNames[i];
        std::stringstream ss;
        ss << "images/buttons/" << optionsButtons[i].buttonName << ".png";
        std::string str = ss.str();
        optionsButtons[i].buttonTexture.loadFromFile( str,renderer );
        //I only have one button on this screen with a mouseover texture
        if(i==0)
        {
            std::stringstream ssMO;
            ssMO << "images/buttons/" << optionsButtons[i].buttonName << "MO.png";
            std::string str2 = ssMO.str();
            optionsButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
        }
    }
    optionsButtons[1].fullScreenButtonTextureToggle(renderer);
    optionsButtons[2].musicButtonTextureToggle(renderer);
    optionsButtons[3].voiceButtonTextureToggle(renderer);

    optionsButtons[0].setPosition(600,20);
    optionsButtons[1].setPosition(20,100);
    optionsButtons[2].setPosition(20,200);
    optionsButtons[3].setPosition(20,300);

}

void pregameui::renderOptionsButtons(SDL_Renderer* renderer)
{
    for(int i =0; i<TOTAL_OPTIONS_BUTTONS;i++)
    {
        if(i==0)
        {
            if(optionsButtons[i].mouseOver == false)
            {
                optionsButtons[i].buttonTexture.render(optionsButtons[i].getPositionX(),optionsButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            else
            {
                optionsButtons[i].buttonMOTexture.render(optionsButtons[i].getPositionX(),optionsButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else
        {
            optionsButtons[i].buttonTexture.render(optionsButtons[i].getPositionX(),optionsButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }


    }
}

void pregameui::freeOptionsButtons()
{
    for(int i = 0; i<TOTAL_OPTIONS_BUTTONS;i++)
    {
        optionsButtons[i].buttonTexture.free();
        //the back button is the only one that has a mouseover texture
        if(i==0)
        {
            optionsButtons[i].buttonMOTexture.free();
        }
    }
}

void pregameui::handleOptionsScreenRendering(SDL_Renderer* renderer)
{
    //render background image
    optionsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //render buttons
    renderOptionsButtons(renderer);

    //add soundtoggle button
}


void pregameui::loadCreditsButtons(SDL_Renderer* renderer)
{
    //set button names
    creditsButtonNames[0]="back";
    creditsButtons[0].buttonName = creditsButtonNames[0];
    //load button images from file using button name (including mouseover image).
	for( int i = 0; i < TOTAL_CREDITS_BUTTONS; ++i )
    {
        creditsButtons[i].buttonName = creditsButtonNames[i];
        std::stringstream ss;
        std::stringstream ssMO;
        ss << "images/buttons/" << creditsButtons[i].buttonName << ".png";
        ssMO << "images/buttons/" << creditsButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        std::string str2 = ssMO.str();
        creditsButtons[i].buttonTexture.loadFromFile( str,renderer );
        creditsButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
    }
    //set position of button on credit's screen
    creditsButtons[0].setPosition(600,20);
}

void pregameui::renderCreditsButtons(SDL_Renderer* renderer)
{
    for(int i =0; i<TOTAL_CREDITS_BUTTONS;i++)
    {
        if(creditsButtons[i].mouseOver == false)
        {
            creditsButtons[i].buttonTexture.render(creditsButtons[i].getPositionX(),creditsButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            creditsButtons[i].buttonMOTexture.render(creditsButtons[i].getPositionX(),creditsButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
   }
}

void pregameui::freeCreditsButtons()
{
    std::cout<<"\n running pregameui::freeCreditsButtons()";
    for(int i = 0; i<TOTAL_CREDITS_BUTTONS;i++)
    {
        creditsButtons[i].buttonTexture.free();
        creditsButtons[i].buttonMOTexture.free();
    }
}

void pregameui::handleCreditsScreenRendering(SDL_Renderer* renderer)
{

    creditsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    renderCreditsButtons(renderer);
}

void pregameui::loadLoadgameButtons(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadLoadgameButtons(SDL_Renderer* renderer)";
    loadgameButtonNames[0]="back";
	loadgameButtonNames[1]="save1";
	loadgameButtonNames[2]="save2";
	loadgameButtonNames[3]="save3";
	loadgameButtonNames[4]="trash1";
	loadgameButtonNames[5]="trash2";
	loadgameButtonNames[6]="trash3";
	loadgameButtonNames[7]="yes";
	loadgameButtonNames[8]="no";
	for( int i = 0; i < TOTAL_LOADGAME_BUTTONS; ++i )
    {
        loadgameButtons[i].buttonName = loadgameButtonNames[i];
        std::stringstream ss;
        if(i<4)
        {
            std::stringstream ssMO;
            ssMO << "images/buttons/" << loadgameButtons[i].buttonName << "MO.png";
            std::string str2 = ssMO.str();
            loadgameButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
        }
        ss << "images/buttons/" << loadgameButtons[i].buttonName << ".png";
        std::string str = ss.str();
        if(i!= 7 && i!= 8)
        {
            /*success = */loadgameButtons[i].buttonTexture.loadFromFile( str,renderer );
        }

    }
    loadgameButtons[0].setPosition(600,20);
    loadgameButtons[1].setPosition(40,100);
    loadgameButtons[2].setPosition(40,200);
    loadgameButtons[3].setPosition(40,300);
    loadgameButtons[4].setPosition(14,125);
    loadgameButtons[5].setPosition(14,225);
    loadgameButtons[6].setPosition(14,325);
    loadgameButtons[7].setPosition(320,250);
    loadgameButtons[8].setPosition(420,250);
}

void pregameui::renderLoadgameButtons(SDL_Renderer* renderer)
{
    //first 4 loadgame buttons have mouseover textures, the last 3 are the trashcan image to delete a save.
    for(int i=0;i<TOTAL_LOADGAME_BUTTONS;i++)
    {
        if(i<4)
        {
            if(loadgameButtons[i].mouseOver == false)
            {
                loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            else
            {
                loadgameButtons[i].buttonMOTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(i<7)//load trashcan buttons
        {
            loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else//load yes/no buttons for prompting deletion of a save.
        {
            if(promptDelete)
            {
                if(loadgameButtons[i].mouseOver == false)
                {
                    loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else
                {
                    loadgameButtons[i].buttonMOTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
            }
        }

    }
}

void pregameui::freeLoadgameButtons()
{
    std::cout<<"\n running pregameui::freeLoadgameButtons()";
    for(int i = 0; i<TOTAL_LOADGAME_BUTTONS;i++)
    {
        if(i<4)
        {
            loadgameButtons[i].buttonTexture.free();
            loadgameButtons[i].buttonMOTexture.free();
            loadgameButtons[i].mouseOver = false;
        }
        else
        {
            loadgameButtons[i].buttonTexture.free();
            loadgameButtons[i].mouseOver = false;
        }
    }
}

void pregameui::handleLoadGameScreenRendering(SDL_Renderer* renderer)
{
    //this function renders the buttons and the prompt to delete a save
    if(promptDelete)
    {
        promptDeleteBG.render(300,200,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    renderLoadgameButtons(renderer);
}

void pregameui::loadNewgameButtons(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadNewgameButtons(SDL_Renderer* renderer)";
    newgameButtonNames[0]="back";
	newgameButtonNames[1]="save1";
	newgameButtonNames[2]="save2";
	newgameButtonNames[3]="save3";
	newgameButtonNames[4]="trash1";
	newgameButtonNames[5]="trash2";
	newgameButtonNames[6]="trash3";
	newgameButtonNames[7]="yes";
    newgameButtonNames[8]="no";
	for( int i = 0; i < TOTAL_NEWGAME_BUTTONS; ++i )
    {
        newgameButtons[i].buttonName = newgameButtonNames[i];
        std::stringstream ss;
        if(i<4)
        {
            std::stringstream ssMO;
            ssMO << "images/buttons/" << newgameButtons[i].buttonName << "MO.png";
            std::string str2 = ssMO.str();
            newgameButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
        }

        ss << "images/buttons/" << newgameButtons[i].buttonName << ".png";
        std::string str = ss.str();
        if(i!= 7 && i !=8)
        {
            /*success = */newgameButtons[i].buttonTexture.loadFromFile( str,renderer );
        }


    }
    newgameButtons[0].setPosition(600,20);
    newgameButtons[1].setPosition(40,100);
    newgameButtons[2].setPosition(40,200);
    newgameButtons[3].setPosition(40,300);
    newgameButtons[4].setPosition(14,125);
    newgameButtons[5].setPosition(14,225);
    newgameButtons[6].setPosition(14,325);
    newgameButtons[7].setPosition(320,250);
    newgameButtons[8].setPosition(420,250);
}

void pregameui::renderNewgameButtons(SDL_Renderer* renderer)
{
    for(int i=0;i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        if(i<4)//renders the mouseover or default version of the save1,2,3, and back buttons.
        {
            if(newgameButtons[i].mouseOver == false)
            {
                newgameButtons[i].buttonTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            else
            {
                newgameButtons[i].buttonMOTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
        else if(i<7)//render the trashcan buttons in the newgame screen
        {
            newgameButtons[i].buttonTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else//render yes/no buttons to delete a save
        {
            if(promptDelete)
            {
                if(!newgameButtons[i].mouseOver)
                {
                    newgameButtons[i].buttonTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else
                {
                    newgameButtons[i].buttonMOTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
            }
        }
    }
}

void pregameui::freeNewgameButtons()
{
    std::cout<<"\n running pregameui::freeNewgameButtons()";
    for(int i = 0; i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        if(i<4 || i == 7 || i == 8)
        {
            newgameButtons[i].buttonTexture.free();
            newgameButtons[i].buttonMOTexture.free();
            newgameButtons[i].mouseOver = false;
        }
        else
        {
            newgameButtons[i].buttonTexture.free();
            newgameButtons[i].mouseOver = false;
        }
    }
}

void pregameui::handleNewGameScreenRendering(SDL_Renderer* renderer)
{
    //this function renders the buttons and the prompt to delete a save
    if(promptDelete)
    {
        promptDeleteBG.render(300,200,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    renderNewgameButtons(renderer);
}

void pregameui::renderParticles(SDL_Renderer* renderer)
{//staged roll out for star particles
    //first 10 stars created and rendered
    for( int i = 0; i < TOTAL_PARTICLES/5; ++i )
    {
        if(particles[i].particleTimer.getTicks() > Uint32(rand() % 2000))
        {
            if( particles[i].isDead() )
            {
                particles[i].createParticle(renderer);
            }
        }
    }
    for( int i = 0; i < TOTAL_PARTICLES/5; ++i )
    {
        particles[i].render(renderer,particles[i].renderColor,star);
    }
    //next 15 stars created and rendered
    for( int i = TOTAL_PARTICLES/5; i < TOTAL_PARTICLES/2; ++i )
    {
        if(particles[i].particleTimer.getTicks() > Uint32(rand() % 2000))
        {
            if( particles[i].isDead() )
            {
                particles[i].createParticle(renderer);
            }
        }
    }
    for( int i = TOTAL_PARTICLES/5; i < TOTAL_PARTICLES/2; ++i )
    {
        particles[i].render(renderer,particles[i].renderColor,star);
    }
    //last 25 stars created and rendered.
    for( int i = TOTAL_PARTICLES/2; i < TOTAL_PARTICLES; ++i )
    {
        if(particles[i].particleTimer.getTicks() > Uint32(rand() % 2000))
        {
            if( particles[i].isDead() )
            {
                particles[i].createParticle(renderer);
            }
        }
    }
    for( int i = TOTAL_PARTICLES/2; i < TOTAL_PARTICLES; ++i )
    {
        particles[i].render(renderer,particles[i].renderColor,star);
    }
}

void pregameui::loadMainButtons(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadMainButtons(SDL_Renderer* renderer)";
    mainButtonNames[0]="new";
	mainButtonNames[1]="load";
	mainButtonNames[2]="options";
	mainButtonNames[3]="credits";

	for( int i = 0; i < TOTAL_MAIN_BUTTONS; ++i )
    {
        mainButtons[i].buttonName = mainButtonNames[i];
        std::stringstream ss;
        std::stringstream ssMO;
        ss << "images/buttons/" << mainButtons[i].buttonName << ".png";
        ssMO << "images/buttons/" << mainButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        std::string str2 = ssMO.str();
        /*success = */mainButtons[i].buttonTexture.loadFromFile( str,renderer );
        mainButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
        mainButtons[ i ].setPosition( (((i+1)*160)-80), SCREEN_HEIGHT - 140 );
    }
}

void pregameui::renderMainButtons(SDL_Renderer* renderer)
{

    for(int i=0;i<TOTAL_MAIN_BUTTONS;i++)
    {
        if(mainButtons[i].mouseOver == false){
            mainButtons[i].buttonTexture.render(mainButtons[i].getPositionX(),mainButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            mainButtons[i].buttonMOTexture.render(mainButtons[i].getPositionX(),mainButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }
}

void pregameui::freeMainButtons()
{
    std::cout<<"\n running pregameui::freeMainButtons()";
    for(int i = 0; i<TOTAL_MAIN_BUTTONS;i++)
    {
        mainButtons[i].buttonTexture.free();
        mainButtons[i].buttonMOTexture.free();
        mainButtons[i].mouseOver=false;
    }
}

void pregameui::handleTitleScreenRendering(SDL_Renderer* renderer)
{
    PGUIBlackGround.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    renderParticles(renderer);
    titleTexture.render( 0, 0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
    title.render(200, 100,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //render title screen buttons
    renderMainButtons(renderer);
}

void pregameui::createParticles(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::createParticles(SDL_Renderer* renderer)";
    /*for(int i=0;i<TOTAL_PARTICLES;i++){
        particles[i].createParticle(renderer);
    }*/

    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        if(particles[i].particleTimer.getTicks() > Uint32(rand() % 2000))
        {
            if( particles[i].isDead() )
            {
                particles[i].createParticle(renderer);
            }
        }
    }
}


bool pregameui::loadTitleScreenTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadTitleScreenTextures(SDL_Renderer* renderer)";
    bool success = true;
    //game title image
	success = title.loadFromFile( "images/title.png",renderer ); //used in main screen
	success = titleTexture.loadFromFile( "images/EarthMoon3.png",renderer );  //used in background of main screen
	success = PGUIBlackGround.loadFromFile("images/blackground.png",renderer); //used in main screen behind particles
	if(!success)
    {
        printf("\n \n there was a problem loading pregame UI textures. \n \n");
    }
	return success;
}

bool pregameui::loadLoadGameTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadLoadGameTextures(SDL_Renderer* renderer)";
    bool success = true;
    success = promptDeleteBG.loadFromFile("images/sprites/deleteSavePrompt.png",renderer);
    success = chapterSelectTexture.loadFromFile( "images/Cosmos.png",renderer ); //used in new/loadgame screens
    if(!success)
    {
        printf("\n \n there was a problem loading pregame UI textures. \n \n");
    }
	return success;
}

bool pregameui::loadNewGameTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadNewGameTextures(SDL_Renderer* renderer)";
    bool success = true;
    success = promptDeleteBG.loadFromFile("images/sprites/deleteSavePrompt.png",renderer);
    success = chapterSelectTexture.loadFromFile( "images/Cosmos.png",renderer ); //used in new/loadgame screens
    if(!success)
    {
        printf("\n \n there was a problem loading pregame UI textures. \n \n");
    }
	return success;
}

bool pregameui::loadCreditsTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadCreditsTextures(SDL_Renderer* renderer)";
    bool success = true;
    success = creditsTexture.loadFromFile( "images/cockpit.png",renderer ); //used in credits screen
    if(!success)
    {
        printf("\n \n there was a problem loading pregame UI textures. \n \n");
    }
	return success;
}

bool pregameui::loadOptionsTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadOptionsTextures(SDL_Renderer* renderer)";
    bool success = true;
    success = optionsTexture.loadFromFile("images/docking.png",renderer );  //used in options screen
    if(!success)
    {
        printf("\n \n there was a problem loading pregame UI textures. \n \n");
    }
	return success;
}

bool pregameui::loadPregameUI(SDL_Renderer* renderer,bool success)
{
    std::cout<<"\n running pregameui::loadPregameUI(SDL_Renderer* renderer,bool success)";
    //set button names and button positions & image textures
    loadMainButtons(renderer);
    success = loadTitleScreenTextures(renderer);

    for(int i = 0; i<TOTAL_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss << "images/animations/star/star" << a << ".png";
        std::string str = ss.str();
        star[i].loadFromFile(str,renderer);
    }

    return success;
}

void pregameui::free()
{
    std::cout<<"\n running pregameui::free()";
    //frees everything
    freeMainButtons();
    freeNewgameButtons();
    freeLoadgameButtons();
    freeOptionsButtons();
    freeCreditsButtons();
    //free pregame ui textures
    freeTitleScreenTextures();
    freeNewGameTextures();
    freeLoadGameTextures();
    freeOptionsTextures();
    freeCreditsTextures();
}

void pregameui::freeTitleScreenTextures()
{
    std::cout<<"\n running pregameui::freeTitleScreenTextures()";
    //title image "Sojourner"
    title.free();
    //free the background textures
	titleTexture.free();
	PGUIBlackGround.free();
}

void pregameui::freeNewGameTextures()
{
     std::cout<<"\n running pregameui::freeNewGameTextures()";
    chapterSelectTexture.free();
    promptDeleteBG.free();
}

void pregameui::freeLoadGameTextures()
{
    std::cout<<"\n running pregameui::freeLoadGameTextures()";
    chapterSelectTexture.free();
    promptDeleteBG.free();
}

void pregameui::freeOptionsTextures()
{
    std::cout<<"\n running pregameui::freeOptionsTextures()";
	optionsTexture.free();
}

void pregameui::freeCreditsTextures()
{
    std::cout<<"\n running pregameui::freeCreditsTextures()";
    creditsTexture.free();
}

int pregameui::handleButtons( int gameState, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer )
{
    //std::cout<<"\n running pregameui::handleButtons( int gameState, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer )";
    //user clicks a button in the pregameui scenes
    //backing up gamestate
    int oldGameState = gameState;
    //handles buttons by gamestate.
    if(gameState==0)
    {
        for( int i = 0; i < TOTAL_MAIN_BUTTONS; ++i )
        {//handlePGUIEvent needs to be broken up into 5 parts
            //polls the buttons on the mainscreen, returns the value of the gamestate the button points to.
            gameState = mainButtons[ i ].handlePGUIEvent(e, window,renderer );
            //user clicked a button, escape for loop.
            if(gameState!=-1)
            {
                i+=TOTAL_MAIN_BUTTONS;
            }
        }
    }
    else if(gameState==1)
    {
        for( int i = 0; i < TOTAL_NEWGAME_BUTTONS; ++i )
        {//handlePGUIEvent needs to be broken up into 5 parts
            gameState = newgameButtons[ i ].handlePGUIEvent(e, window,renderer );
            //user clicked a button, escape for loop.
            if(gameState!=-1)
            {
                if(gameState==0)
                { //user clicked back button, exit for loop.
                    i+=TOTAL_NEWGAME_BUTTONS;
                }
                if(gameState==5)
                {//user clicked either save1, 2 , or 3.
                    if(!existingSave[newgameButtons[i].chosenSave])
                    {//if there is not an existing save in that slot.
                       chosenSave = newgameButtons[i].chosenSave;
                       existingSave[chosenSave] = true;
                        i+=TOTAL_NEWGAME_BUTTONS;
                    }
                }
                if(gameState == 1 || gameState == 2 || gameState == 3)
                {
                    if(existingSave[gameState-1])
                    {
                        if(!promptDelete)
                        {
                            promptDelete = true;
                            std::cout<<"\n PromptDelete was false, now it's true (trashcan was clicked)";
                            promptDeleteBG.loadFromFile("images/sprites/deleteSavePrompt.png",renderer);
                            newgameButtons[7].buttonTexture.loadFromFile( "images/buttons/yes.png",renderer );
                            newgameButtons[8].buttonTexture.loadFromFile("images/buttons/no.png",renderer);
                            newgameButtons[7].buttonMOTexture.loadFromFile("images/buttons/yesMO.png",renderer);
                            newgameButtons[8].buttonMOTexture.loadFromFile("images/buttons/noMO.png",renderer);
                        }
                        deleteCandidate = gameState-1;//stores the number of the target savegame to potentially be deleted.
                        chosenSave = deleteCandidate;
                    }
                    gameState=-1;


                }
                if(gameState==4)
                {
                    //user clicked yes to delete save file
                    promptDelete=false;
                    std::cout<<"\n promptDelete was true, now it's false (yes was clicked)";
                    triggerDelete = true;
                    std::cout<<"\n trigger delete is now true";
                    gameState=-1;
                    promptDeleteBG.free();
                    newgameButtons[7].buttonTexture.free();
                    newgameButtons[8].buttonTexture.free();
                    newgameButtons[7].buttonMOTexture.free();
                    newgameButtons[8].buttonMOTexture.free();

                }
                if(gameState == 6)
                {//user clicked no to delete save file
                    promptDelete=false;
                    std::cout<<"\n promptDelete was true, now it's false (no was clicked)";
                    gameState=-1;
                    promptDeleteBG.free();
                    newgameButtons[7].buttonTexture.free();
                    newgameButtons[8].buttonTexture.free();
                    newgameButtons[7].buttonMOTexture.free();
                    newgameButtons[8].buttonMOTexture.free();
                }
            }
        }
        //this is added to make this function return 6 (opening sequence) instead of 5 (game proper).
        if(gameState == 5)
        {
            gameState = 6;
        }
    }
    else if(gameState==2)
    {//loadgame screen
        for( int i = 0; i < TOTAL_LOADGAME_BUTTONS; ++i )
        {//handlePGUIEvent needs to be broken up into 5 parts
            gameState = loadgameButtons[ i ].handlePGUIEvent(e, window,renderer );
            //user clicked a button, escape for loop.
            if(gameState!=-1)
            {
                if(gameState==0)
                {
                    i+=TOTAL_LOADGAME_BUTTONS;
                }
                if(gameState==5)
                {//user clicked either save1, 2 , or 3.
                    if(existingSave[loadgameButtons[i].chosenSave])
                    {//if there is an existing save in that slot.
                       chosenSave = loadgameButtons[i].chosenSave;
                        i+=TOTAL_LOADGAME_BUTTONS;
                    }
                }
                if(gameState == 1 || gameState == 2 || gameState == 3)
                {//choose file to delete
                    if(existingSave[gameState-1])
                    {
                        if(!promptDelete)
                        {
                            promptDelete = true;
                            std::cout<<"\n PromptDelete was false, now it's true (trashcan was clicked)";
                            promptDeleteBG.loadFromFile("images/sprites/deleteSavePrompt.png",renderer);
                            loadgameButtons[7].buttonTexture.loadFromFile( "images/buttons/yes.png",renderer );
                            loadgameButtons[8].buttonTexture.loadFromFile("images/buttons/no.png",renderer);
                            loadgameButtons[7].buttonMOTexture.loadFromFile("images/buttons/yesMO.png",renderer);
                            loadgameButtons[8].buttonMOTexture.loadFromFile("images/buttons/noMO.png",renderer);
                        }
                        deleteCandidate = gameState-1;//stores the number of the target savegame to potentially be deleted.
                        chosenSave = deleteCandidate;
                    }
                    gameState=-1;
                }
                if(gameState==4)
                {//user clicked yes to delete save file
                    promptDelete=false;
                    std::cout<<"\n promptDelete was true, now it's false (yes was clicked)";
                    triggerDelete = true;
                    std::cout<<"\n trigger delete is now true";
                    gameState=-1;
                    promptDeleteBG.free();
                    loadgameButtons[7].buttonTexture.free();
                    loadgameButtons[8].buttonTexture.free();
                    loadgameButtons[7].buttonMOTexture.free();
                    loadgameButtons[8].buttonMOTexture.free();
                }
                if(gameState == 6)
                {//user clicked no to delete save file
                    promptDelete=false;
                    std::cout<<"\n promptDelete was true, now it's false (no was clicked)";
                    gameState=-1;
                    promptDeleteBG.free();
                    loadgameButtons[7].buttonTexture.free();
                    loadgameButtons[8].buttonTexture.free();
                    loadgameButtons[7].buttonMOTexture.free();
                    loadgameButtons[8].buttonMOTexture.free();
                }
            }
        }
    }
    else if(gameState==3)
    {//options screen
        for( int i = 0; i < TOTAL_OPTIONS_BUTTONS; ++i )
        {//handlePGUIEvent needs to be broken up into 5 parts
            gameState = optionsButtons[ i ].handlePGUIEvent(e, window,renderer );
            //user clicked a button, escape for loop.
            if(gameState!=-1)
            {
                i+=TOTAL_OPTIONS_BUTTONS;
            }
        }
    }
    else if(gameState==4)
    {//credits screen
        for( int i = 0; i < TOTAL_CREDITS_BUTTONS; ++i )
        {//handlePGUIEvent needs to be broken up into 5 parts
            gameState = creditsButtons[ i ].handlePGUIEvent(e, window,renderer );
            //user clicked a button, escape for loop.
            if(gameState!=-1)
            {
                i+=TOTAL_CREDITS_BUTTONS;
            }
        }
    }
    if(gameState<0)
    {
        gameState=oldGameState;
    }
    int newGameState = gameState;
    //user pressed a button that changes gamestate.
    if(oldGameState != newGameState)
    {//free old state, load new state.
        loadState(oldGameState,newGameState,renderer);
    }
    return newGameState;
}

void pregameui::loadState(int oldGameState, int newGameState, SDL_Renderer* renderer)
{
    //when player changes state, this frees the old and loads the new
    std::cout<<"\n running pregameui::loadState(int oldGameState, int newGameState, SDL_Renderer* renderer)";
    std::cout<<"\n  oldGameState: "<<oldGameState<<" newGameState: "<<newGameState;
    switch( oldGameState )
    {
        case 0:  freeTitleScreenTextures();
            freeMainButtons();
            break;
        case 1: freeNewGameTextures();
            freeNewgameButtons();
            break;
        case 2: freeLoadGameTextures();
            freeLoadgameButtons();
            break;
        case 3: freeOptionsTextures();
            freeOptionsButtons();
            break;
        case 4: freeCreditsTextures();
            freeCreditsButtons();
            break;
    }
    switch( newGameState )
    {
        case 0: loadTitleScreenTextures(renderer);
            loadMainButtons(renderer);
            break;
        case 1: loadNewGameTextures(renderer);
            loadNewgameButtons(renderer);
            break;
        case 2: loadLoadGameTextures(renderer);
            loadLoadgameButtons(renderer);
            break;
        case 3: loadOptionsTextures(renderer);
            loadOptionsButtons(renderer);
            break;
        case 4: loadCreditsTextures(renderer);
            loadCreditsButtons(renderer);
        break;
    }
}
