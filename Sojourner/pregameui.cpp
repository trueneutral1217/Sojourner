#include "pregameui.h"

pregameui::pregameui()
{

}

pregameui::~pregameui()
{

}

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
    buttons[0].setPosition(600,20);
    buttons[5].setPosition(20,20);//chapter 1 button
    buttons[6].setPosition(20,100);//fullscreen button
    buttons[7].setPosition(220,150);//stage 1 button
    buttons[8].setPosition(20,200);//chapter 2 button
    buttons[9].setPosition(20,300);//chapter 3 button
    buttons[10].setPosition(20,200);//musicOn button
    buttons[11].setPosition(20,300);//voiceOn button
    return success;
}

void pregameui::setButtonNames()
{
    for(int i = 0; i<TOTAL_PREGAME_BUTTONS; i++)
    {
        buttons[i].setPregameButtonName(i);
    }
}

void pregameui::freeButtons()
{
    for(int i = 0; i<TOTAL_PREGAME_BUTTONS;i++)
    {
        buttons[i].buttonTexture.free();
    }
}

void pregameui::handleOptionsScreenRendering(SDL_Renderer* renderer)
{
    optionsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    buttons[6].fullScreenButtonTextureToggle(renderer);
    buttons[10].musicButtonTextureToggle(renderer);
    buttons[11].voiceButtonTextureToggle(renderer);
}

void pregameui::handleCreditsScreenRendering(SDL_Renderer* renderer)
{
    creditsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void pregameui::handleLoadGameScreenRendering(SDL_Renderer* renderer, bool chapter1Complete,bool chapter2Complete, bool chapter3Complete)
{
    //chapter select screen
    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

    //if chapter 1 is complete, render stage 1 button
    if(chapter1Complete)
    {
        //render chapter 2 button
        buttons[8].buttonTexture.render(buttons[8].getPositionX(),buttons[8].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(chapter2Complete)
    {
        //render chapter 2 button
        buttons[9].buttonTexture.render(buttons[9].getPositionX(),buttons[9].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(chapter3Complete)
    {
        //render stage 1 button
        buttons[7].buttonTexture.render(buttons[7].getPositionX(),buttons[7].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    //chapter 1 button
    buttons[5].buttonTexture.render(buttons[5].getPositionX(),buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //back button
    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void pregameui::handleNewGameScreenRendering(SDL_Renderer* renderer)
{
    //rendering bg for newgame screen
    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
    //chapter 1 button
    buttons[5].buttonTexture.render(buttons[5].getPositionX(),buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //back button
    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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

void pregameui::handleTitleScreenRendering(SDL_Renderer* renderer)
{
    titleTexture.render( 0, 0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
    renderParticles(renderer);
    title.render(200, 100,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //render title screen buttons
    //5 is back button 6 is fullscreen button
    for(int i=1;i<5;i++)
    {
        buttons[i].buttonTexture.render(buttons[i].getPositionX(),buttons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
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
	success = titleTexture.loadFromFile( "images/skidrow.png",renderer );
	success = loadGameTexture.loadFromFile( "images/loadgamescreen.png",renderer );
	success = chapterSelectTexture.loadFromFile( "images/busstop.png",renderer );
	success = creditsTexture.loadFromFile( "images/brickwall.png",renderer );
	success = optionsTexture.loadFromFile("images/maritime.png",renderer );
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
    //thanksTexture.free();
}

bool pregameui::loadPregameUI(SDL_Renderer* renderer,bool success)
{
    //set button names
    setButtonNames();
    //set button positions & image textures
    success = setPreGameButtonTextures(renderer, success);
    //load titlescreen textures, credit screen textures, etc.
    success = setPGUITextures(renderer);
    return success;
}

void pregameui::free()
{
    freeButtons();
    //free pregame ui textures
    freePGUITextures();
}
