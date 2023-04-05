#ifndef PREGAMEUI_H
#define PREGAMEUI_H

#include "texture.h"
#include "button.h"
#include "particle.h"



class pregameui
{
public:
    //constructor
    pregameui();
    //destructor
    ~pregameui();

    //declaring textures (title, backgrounds, etc
    Texture title;
    Texture titleTexture;
    Texture creditsTexture;
    Texture optionsTexture;
    Texture loadGameTexture;
    Texture chapterSelectTexture;


    button buttons[TOTAL_PREGAME_BUTTONS];

    bool setPGUITextures(SDL_Renderer* renderer);
    void freePGUITextures();

    //sets up the textures by button name and sets positions of the pregame buttons.
    bool setPreGameButtonTextures(SDL_Renderer* renderer, bool success);
    //set button names
    void setButtonNames();
    //free the button textures at close.
    void freeButtons();

    void handleOptionsScreenRendering(SDL_Renderer* renderer);

    void handleCreditsScreenRendering(SDL_Renderer* renderer);

    void handleLoadGameScreenRendering(SDL_Renderer* renderer,bool chapter1Complete,bool chapter2Complete,bool chapter3Complete);

    void handleNewGameScreenRendering(SDL_Renderer* renderer);

    void handleTitleScreenRendering(SDL_Renderer* renderer);

    //particle objects
    Particle particles[ TOTAL_PARTICLES ];

    void renderParticles(SDL_Renderer* renderer);

    void createParticles(SDL_Renderer* renderer);

    bool loadPregameUI(SDL_Renderer* renderer,bool success);

    void free();

private:

};

#endif // PREGAMEUI_H
