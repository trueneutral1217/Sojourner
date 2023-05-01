#include "pregameui.h"

pregameui::pregameui()
{
    existingSave = false;
}

pregameui::~pregameui()
{

}
/*
bool pregameui::setPreGameButtonTextures(SDL_Renderer* renderer, bool success)
{
    for( int i = 0; i < TOTAL_PREGAME_BUTTONS; ++i )
    {
        std::stringstream ss;
        ss << "images/buttons/" << buttons[i].buttonName << ".png";
        std::string str = ss.str();
        success = buttons[i].buttonTexture.loadFromFile( str,renderer );
        buttons[ i ].setPosition( ((i*160)-80), SCREEN_HEIGHT - 140 );
    }
    success = buttons[1].buttonMOTexture.loadFromFile("images/buttons/newMO.png",renderer);
    success = buttons[2].buttonMOTexture.loadFromFile("images/buttons/loadMO.png",renderer);
    success = buttons[3].buttonMOTexture.loadFromFile("images/buttons/optionsMO.png",renderer);
    success = buttons[4].buttonMOTexture.loadFromFile("images/buttons/creditsMO.png",renderer);
    buttons[0].setPosition(600,20);
    buttons[6].setPosition(20,20);//chapter 1 button
    buttons[5].setPosition(20,100);//fullscreentoggle button
    //buttons[7].setPosition(220,150);//stage 1 button
    //buttons[8].setPosition(20,200);//chapter 2 button
    //buttons[9].setPosition(20,300);//chapter 3 button
    buttons[7].setPosition(20,200);//musictoggle button
    buttons[8].setPosition(20,300);//voicetoggle button
    return success;
}*/

/*
void pregameui::setButtonNames()
{
    for(int i = 0; i<TOTAL_PREGAME_BUTTONS; i++)
    {
        buttons[i].setPregameButtonName(i);
    }
}*/
/*
void pregameui::freeButtons()
{
    for(int i = 0; i<TOTAL_PREGAME_BUTTONS;i++)
    {
        buttons[i].buttonTexture.free();
    }
}*/


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
        //std::stringstream ssMO;
        ss << "images/buttons/" << optionsButtons[i].buttonName << ".png";
        //ssMO << "images/buttons/" << mainButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        //std::string str2 = ssMO.str();
        optionsButtons[i].buttonTexture.loadFromFile( str,renderer );

        //mainButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
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
        optionsButtons[i].buttonTexture.render(optionsButtons[i].getPositionX(),optionsButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    //below is for when mouseover buttons are added to this screen
    /*
    for(int i=1;i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        if(loadgameButtons[i].mouseOver == false){
            loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            loadgameButtons[i].buttonMOTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }*/
}

void pregameui::freeOptionsButtons()
{
    for(int i = 0; i<TOTAL_OPTIONS_BUTTONS;i++)
    {
        optionsButtons[i].buttonTexture.free();
    }
}

void pregameui::handleOptionsScreenRendering(SDL_Renderer* renderer)
{
    optionsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    renderOptionsButtons(renderer);
    /*
    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    buttons[5].fullScreenButtonTextureToggle(renderer);
    buttons[7].musicButtonTextureToggle(renderer);
    buttons[8].voiceButtonTextureToggle(renderer);*/
    //add soundtoggle button
}


void pregameui::loadCreditsButtons(SDL_Renderer* renderer)
{
    creditsButtonNames[0]="back";
    creditsButtons[0].buttonName = creditsButtonNames[0];
    //lines for mouseover are commented out until the textures are created
	creditsButtons[0].buttonTexture.loadFromFile("images/buttons/back.png",renderer);
	/*
	for( int i = 0; i < TOTAL_LOADGAME_BUTTONS; ++i )
    {
        loadgameButtons[i].buttonName = loadgameButtonNames[i];
        std::stringstream ss;
        //std::stringstream ssMO;
        ss << "images/buttons/" << loadgameButtons[i].buttonName << ".png";
        //ssMO << "images/buttons/" << mainButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        //std::string str2 = ssMO.str();
        //loadgameButtons[i].buttonTexture.loadFromFile( str,renderer );
        //mainButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
    }*/
    creditsButtons[0].setPosition(600,20);

}

void pregameui::renderCreditsButtons(SDL_Renderer* renderer)
{
    for(int i =0; i<TOTAL_CREDITS_BUTTONS;i++)
    {
        creditsButtons[i].buttonTexture.render(creditsButtons[i].getPositionX(),creditsButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    //below is for when mouseover buttons are added to this screen
    /*
    for(int i=1;i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        if(loadgameButtons[i].mouseOver == false){
            loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            loadgameButtons[i].buttonMOTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }*/
}

void pregameui::freeCreditsButtons()
{
    for(int i = 0; i<TOTAL_CREDITS_BUTTONS;i++)
    {
        creditsButtons[i].buttonTexture.free();
    }
}

void pregameui::handleCreditsScreenRendering(SDL_Renderer* renderer)
{
    creditsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    renderCreditsButtons(renderer);
}

void pregameui::loadLoadgameButtons(SDL_Renderer* renderer)
{
    loadgameButtonNames[0]="back";
    loadgameButtons[0].buttonName = loadgameButtonNames[0];
    //lines for mouseover are commented out until the textures are created
	loadgameButtons[0].buttonTexture.loadFromFile("images/buttons/back.png",renderer);
	/*
	for( int i = 0; i < TOTAL_LOADGAME_BUTTONS; ++i )
    {
        loadgameButtons[i].buttonName = loadgameButtonNames[i];
        std::stringstream ss;
        //std::stringstream ssMO;
        ss << "images/buttons/" << loadgameButtons[i].buttonName << ".png";
        //ssMO << "images/buttons/" << mainButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        //std::string str2 = ssMO.str();
        //loadgameButtons[i].buttonTexture.loadFromFile( str,renderer );
        //mainButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
    }*/
    loadgameButtons[0].setPosition(600,20);

    if(existingSave)
    {
        loadgameButtonNames[1]="stage1";
        loadgameButtons[1].buttonName = loadgameButtonNames[1];
        loadgameButtons[1].buttonTexture.loadFromFile("images/buttons/stage1.png",renderer);
        loadgameButtons[1].setPosition(20,20);
    }
}

void pregameui::renderLoadgameButtons(SDL_Renderer* renderer)
{
    for(int i =0; i<TOTAL_LOADGAME_BUTTONS;i++)
    {
        loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    //below is for when mouseover buttons are added to this screen
    /*
    for(int i=1;i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        if(loadgameButtons[i].mouseOver == false){
            loadgameButtons[i].buttonTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            loadgameButtons[i].buttonMOTexture.render(loadgameButtons[i].getPositionX(),loadgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }*/
}

void pregameui::freeLoadgameButtons()
{
    for(int i = 0; i<TOTAL_LOADGAME_BUTTONS;i++)
    {
        loadgameButtons[i].buttonTexture.free();
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
    newgameButtonNames[0]="back";
	newgameButtonNames[1]="stage1";
    //lines for mouseover are commented out until the textures are created
	for( int i = 0; i < TOTAL_NEWGAME_BUTTONS; ++i )
    {
        newgameButtons[i].buttonName = newgameButtonNames[i];
        std::stringstream ss;
        //std::stringstream ssMO;
        ss << "images/buttons/" << newgameButtons[i].buttonName << ".png";
        //ssMO << "images/buttons/" << mainButtons[i].buttonName << "MO.png";
        std::string str = ss.str();
        //std::string str2 = ssMO.str();
        /*success = */newgameButtons[i].buttonTexture.loadFromFile( str,renderer );
        //mainButtons[i].buttonMOTexture.loadFromFile(str2,renderer);
    }
    newgameButtons[0].setPosition(600,20);
    newgameButtons[1].setPosition(20,20);
}

void pregameui::renderNewgameButtons(SDL_Renderer* renderer)
{
    for(int i =0; i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        newgameButtons[i].buttonTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    //below is for when mouseover buttons are added to this screen
    /*
    for(int i=1;i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        if(newgameButtons[i].mouseOver == false){
            newgameButtons[i].buttonTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            newgameButtons[i].buttonMOTexture.render(newgameButtons[i].getPositionX(),newgameButtons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
    }*/
}

void pregameui::freeNewgameButtons()
{
    for(int i = 0; i<TOTAL_NEWGAME_BUTTONS;i++)
    {
        newgameButtons[i].buttonTexture.free();
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
    for(int i=0;i<TOTAL_PARTICLES;i++){
        particles[i].createParticle(renderer);
    }
}

bool pregameui::setPGUITextures(SDL_Renderer* renderer)
{
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
    //freeButtons();
    freeMainButtons();
    freeNewgameButtons();
    freeLoadgameButtons();
    freeOptionsButtons();
    freeCreditsButtons();
    //free pregame ui textures
    freePGUITextures();
}

void pregameui::loadState(int oldGameState, int newGameState, SDL_Renderer* renderer)
{
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
