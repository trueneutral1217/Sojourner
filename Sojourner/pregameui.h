#ifndef PREGAMEUI_H
#define PREGAMEUI_H

#include "texture.h"
#include "button.h"
#include "particle.h"

const static int TOTAL_SAVES = 3;

class pregameui
{
public:
    //constructor
    pregameui();
    //destructor
    ~pregameui();

    bool existingSave[TOTAL_SAVES];
    bool promptDelete;
    int deleteCandidate;
    bool triggerDelete;

    //declaring textures (title, backgrounds, etc
    Texture title;
    Texture titleTexture;
    Texture creditsTexture;
    Texture optionsTexture;
    Texture loadGameTexture;
    Texture chapterSelectTexture;
    Texture promptDeleteBG;
    //behind background images that have transparency and need black background instead of default white.
    Texture PGUIBlackGround;

    //phasing this setup out
    //button buttons[TOTAL_PREGAME_BUTTONS];

    //new button setup
    button mainButtons[TOTAL_MAIN_BUTTONS];
    button newgameButtons[TOTAL_NEWGAME_BUTTONS];
    button loadgameButtons[TOTAL_LOADGAME_BUTTONS];
    button optionsButtons[TOTAL_OPTIONS_BUTTONS];
    button creditsButtons[TOTAL_CREDITS_BUTTONS];

    //this is the new set of string arrays
    std::string mainButtonNames[TOTAL_MAIN_BUTTONS];
    std::string newgameButtonNames[TOTAL_NEWGAME_BUTTONS];
    std::string loadgameButtonNames[TOTAL_LOADGAME_BUTTONS];
    std::string optionsButtonNames[TOTAL_OPTIONS_BUTTONS];
    std::string creditsButtonNames[TOTAL_CREDITS_BUTTONS];

    //loads each scene's buttons
    void loadMainButtons(SDL_Renderer* renderer);
    void loadNewgameButtons(SDL_Renderer* renderer);
    void loadLoadgameButtons(SDL_Renderer* renderer);
    void loadOptionsButtons(SDL_Renderer* renderer);
    void loadCreditsButtons(SDL_Renderer* renderer);

    //renders the buttons for each scene
    void renderMainButtons(SDL_Renderer* renderer);
    void renderNewgameButtons(SDL_Renderer* renderer);
    void renderLoadgameButtons(SDL_Renderer* renderer);
    void renderOptionsButtons(SDL_Renderer* renderer);
    void renderCreditsButtons(SDL_Renderer* renderer);

    //these free up set of buttons depending on the scene the user is in.
    void freeMainButtons();
    void freeNewgameButtons();
    void freeLoadgameButtons();
    void freeOptionsButtons();
    void freeCreditsButtons();

    int chosenSave;
    //handles button presses/mouseover
    int handleButtons( int gameState, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );

    //this function uses old gamestate to choose which gamestate to free and newgamestate to choose which gamestate to load.
    void loadState(int oldGameState, int newGameState, SDL_Renderer* renderer);


    //bool setPGUITextures(SDL_Renderer* renderer); //deprecated

    bool loadTitleScreenTextures(SDL_Renderer* renderer);
    bool loadLoadGameTextures(SDL_Renderer* renderer);
    bool loadNewGameTextures(SDL_Renderer* renderer);
    bool loadOptionsTextures(SDL_Renderer* renderer);
    bool loadCreditsTextures(SDL_Renderer* renderer);

    //void freePGUITextures(); //deprecated

    void freeTitleScreenTextures();
    void freeNewGameTextures();
    void freeLoadGameTextures();
    void freeOptionsTextures();
    void freeCreditsTextures();

    //sets up the textures by button name and sets positions of the pregame buttons.
    bool setPreGameButtonTextures(SDL_Renderer* renderer, bool success);
    //set button names
    void setButtonNames();
    //free the button textures at close.
    void freeButtons();

    void handleOptionsScreenRendering(SDL_Renderer* renderer);

    void handleCreditsScreenRendering(SDL_Renderer* renderer);

    void handleLoadGameScreenRendering(SDL_Renderer* renderer);

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
