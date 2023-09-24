#include "pregameui.h"

pregameui::pregameui()
{
    for(int i = 0; i<TOTAL_SAVES;i++)
    {
        existingSave[i] = false;
    }
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
	for( int i = 0; i < TOTAL_LOADGAME_BUTTONS; ++i )
    {
        loadgameButtons[i].buttonName = loadgameButtonNames[i];
        std::stringstream ss;
        std::stringstream ssMO;
        ss << "images/buttons/" << loadgameButtons[i].buttonName << ".png";
        ssMO << "images/buttons/" << loadgameButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        std::string str2 = ssMO.str();
        /*success = */loadgameButtons[i].buttonTexture.loadFromFile( str,renderer );
        loadgameButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
    }
    loadgameButtons[0].setPosition(600,20);
    loadgameButtons[1].setPosition(40,100);
    loadgameButtons[2].setPosition(40,200);
    loadgameButtons[3].setPosition(40,300);
}

void pregameui::renderLoadgameButtons(SDL_Renderer* renderer)
{
    //std::cout<<"\n running pregameui::renderLoadgameButtons(SDL_Renderer* renderer)";
    /*
    for(int i =0; i<TOTAL_LOADGAME_BUTTONS;i++)
    {
        loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    */
    //below is for when mouseover buttons are added to this screen

    for(int i=0;i<TOTAL_LOADGAME_BUTTONS;i++)
    {
        if(loadgameButtons[i].mouseOver == false){
            loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            loadgameButtons[i].buttonMOTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }
}

void pregameui::freeLoadgameButtons()
{
    std::cout<<"\n running pregameui::freeLoadgameButtons()";
    for(int i = 0; i<TOTAL_LOADGAME_BUTTONS;i++)
    {
        loadgameButtons[i].buttonTexture.free();
        loadgameButtons[i].buttonMOTexture.free();
        loadgameButtons[i].mouseOver = false;
    }
}

void pregameui::handleLoadGameScreenRendering(SDL_Renderer* renderer)
{

    //chapter select screen
    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    renderLoadgameButtons(renderer);
}

void pregameui::loadNewgameButtons(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::loadNewgameButtons(SDL_Renderer* renderer)";
    newgameButtonNames[0]="back";
	newgameButtonNames[1]="save1";
	newgameButtonNames[2]="save2";
	newgameButtonNames[3]="save3";

	for( int i = 0; i < TOTAL_NEWGAME_BUTTONS; ++i )
    {
        newgameButtons[i].buttonName = newgameButtonNames[i];
        std::stringstream ss;
        std::stringstream ssMO;
        ss << "images/buttons/" << newgameButtons[i].buttonName << ".png";
        ssMO << "images/buttons/" << newgameButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        std::string str2 = ssMO.str();
        /*success = */newgameButtons[i].buttonTexture.loadFromFile( str,renderer );
        newgameButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
    }
    newgameButtons[0].setPosition(600,20);
    newgameButtons[1].setPosition(40,100);
    newgameButtons[2].setPosition(40,200);
    newgameButtons[3].setPosition(40,300);
}

void pregameui::renderNewgameButtons(SDL_Renderer* renderer)
{
    //std::cout<<"\n running pregameui::renderNewgameButtons(SDL_Renderer* renderer)";
    for(int i =0; i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        newgameButtons[i].buttonTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    //below is for when mouseover buttons are added to this screen

    for(int i=0;i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        if(newgameButtons[i].mouseOver == false){
            newgameButtons[i].buttonTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            newgameButtons[i].buttonMOTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }
}

void pregameui::freeNewgameButtons()
{
    std::cout<<"\n running pregameui::freeNewgameButtons()";
    for(int i = 0; i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        newgameButtons[i].buttonTexture.free();
        newgameButtons[i].buttonMOTexture.free();
        newgameButtons[i].mouseOver = false;
    }
}

void pregameui::handleNewGameScreenRendering(SDL_Renderer* renderer)
{

    //rendering bg for newgame screen
    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
    renderNewgameButtons(renderer);
}

void pregameui::renderParticles(SDL_Renderer* renderer)
{

    //Go through particles
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        //Delete and replace dead particles
        if( particles[i].isDead() )
        {
            particles[i].createParticle(renderer);
        }
    }
    //Show particles
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[i].render(renderer,particles[i].renderColor);
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
    for(int i=0;i<TOTAL_PARTICLES;i++){
        particles[i].createParticle(renderer);
    }
}

bool pregameui::setPGUITextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running pregameui::setPGUITextures(SDL_Renderer* renderer)";
    bool success = true;
    //game title image
	success = title.loadFromFile( "images/title.png",renderer );
	//load background image files for non-chapter1 backgrounds
	success = titleTexture.loadFromFile( "images/EarthMoon2.png",renderer );
	success = loadGameTexture.loadFromFile( "images/AsteroidMoon.png",renderer );
	success = chapterSelectTexture.loadFromFile( "images/Cosmos.png",renderer );
	success = creditsTexture.loadFromFile( "images/cockpit.png",renderer );
	success = optionsTexture.loadFromFile("images/docking.png",renderer );
	success = PGUIBlackGround.loadFromFile("images/blackground.png",renderer);
	//success = thanksTexture.loadFromFile("images/thanks.png",renderer);

	if(!success)
    {
        printf("\n \n there was a problem loading pregame UI textures. \n \n");
    }

	return success;
}

void pregameui::freePGUITextures()
{
    std::cout<<"\n running pregameui::freePGUITextures()";
    //frees background images
     //free the title image
    title.free();
    //free the background textures
	titleTexture.free();
	chapterSelectTexture.free();
	loadGameTexture.free();
	optionsTexture.free();
	creditsTexture.free();
	PGUIBlackGround.free();
    //thanksTexture.free();
}

bool pregameui::loadPregameUI(SDL_Renderer* renderer,bool success)
{
    std::cout<<"\n running pregameui::loadPregameUI(SDL_Renderer* renderer,bool success)";
    //set button names
    //setButtonNames();
    loadMainButtons(renderer);
    //set button positions & image textures
    //success = setPreGameButtonTextures(renderer, success);
    //load titlescreen textures, credit screen textures, etc.
    success = setPGUITextures(renderer);
    return success;
}

void pregameui::free()
{
    std::cout<<"\n running pregameui::free()";
    //frees everything
    //freeButtons();
    freeMainButtons();
    freeNewgameButtons();
    freeLoadgameButtons();
    freeOptionsButtons();
    freeCreditsButtons();
    //free pregame ui textures
    freePGUITextures();
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
                chosenSave = newgameButtons[i].chosenSave;
                i+=TOTAL_NEWGAME_BUTTONS;
            }
        }
    }
    else if(gameState==2)
    {
        for( int i = 0; i < TOTAL_LOADGAME_BUTTONS; ++i )
        {//handlePGUIEvent needs to be broken up into 5 parts
            gameState = loadgameButtons[ i ].handlePGUIEvent(e, window,renderer );
            //user clicked a button, escape for loop.
            if(gameState!=-1)
            {
                i+=TOTAL_LOADGAME_BUTTONS;
            }
        }
    }
    else if(gameState==3)
    {
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
    {
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
    std::cout<<"\n running pregameui::loadState(int oldGameState, int newGameState, SDL_Renderer* renderer)";
    std::cout<<"\n  oldGameState: "<<oldGameState<<" newGameState: "<<newGameState;
    switch( oldGameState )
    {
        case 0: freeMainButtons();
            break;
        case 1: freeNewgameButtons();
            break;
        case 2: freeLoadgameButtons();
            break;
        case 3: freeOptionsButtons();
            break;
        case 4: freeCreditsButtons();
            break;
    }
    switch( newGameState )
    {
        case 0: loadMainButtons(renderer);
            break;
        case 1: loadNewgameButtons(renderer);
            break;
        case 2: loadLoadgameButtons(renderer);
            break;
        case 3: loadOptionsButtons(renderer);
            break;
        case 4: loadCreditsButtons(renderer);
            break;
    }
}
