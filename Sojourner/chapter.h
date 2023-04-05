#ifndef CHAPTER_H
#define CHAPTER_H

//#include "Texture.h"
//texture.h is included in button.h, so maybe I'm okay to exclude the line.
#include "timer.h"
#include "button.h"
#include "parallax.h"
#include "audio.h"

//number of dialog lines for chapter 1.
const int TOTAL_SCRIPTS = 8;
//number of dialog pages for chapter 1.
const int TOTAL_PAGES = 8;
//number of dialogs
const int TOTAL_CHAPTERS=2;

class chapter
{
    public:
        //constructor
        chapter();
        //destructor
        ~chapter();
        //declare font
        TTF_Font *font;

        //timer for dialog for chapters
        timer chapterTimer;

        audio voice;

        button buttons[TOTAL_CHAPTER_BUTTONS];

        //tracks chapter progress.  used to save/load and display properly
        int currentScript;
        int currentPage;
        int currentChapter;
        bool chapter1Complete;
        bool chapter2Complete;
        bool chapter3Complete;
        //if player finished a chapter, need a flag independent of chapter completion status to exit chapter.
        bool exitChapter;

        bool autoText;
        int autoTextSpeed;

        //used to make sure text/voice is only loaded once.
        int loadedScript;

        //user presses 'h' to hide the dialogbox, or dialog box & text, or neither.
        bool hideDialogBox = false;
        bool hideDialogAndBox = false;
        bool fullScreen = false;

        Texture scriptTexture[TOTAL_PAGES][TOTAL_SCRIPTS];
        Texture chapter1BG[TOTAL_PAGES];
        Texture chapter2BG[TOTAL_PAGES];
        Texture chapter3BG[TOTAL_PAGES];
        Texture dialogBox;
        Texture menuBar;
        Texture tinCan;

        parallax ch2Pg7Fore;
        parallax ch2Pg7Mid;
        parallax ch2Pg7Back;

        parallax ch2Pg8Fore;
        parallax ch2Pg8AnteriorMid;
        parallax ch2Pg8Mid;
        parallax ch2Pg8Back;

        void ch2Pg7handleParallax(SDL_Renderer* renderer);
        void ch2Pg8handleParallax(SDL_Renderer* renderer);

        std::stringstream scriptString[TOTAL_PAGES][TOTAL_SCRIPTS];

        //Load Strings
        void loadChapterStrings(SDL_Renderer* renderer);

        void scriptIncrement();
        void pageIncrement();
        void backScript();
        void backPage();
        void completeChapter(SDL_Renderer* renderer);
        void resetChapters(SDL_Renderer* renderer);
        void resetPages();
        void resetScripts();
        void nextPage();

        void loadLineText(SDL_Renderer* renderer);
        void loadPageText(SDL_Renderer* renderer);

        //
        std::string bgFileName[TOTAL_PAGES];
        std::string bgFileName2[TOTAL_PAGES];
        std::string bgFileName3[TOTAL_PAGES];

        void freeBGTextures();
        //sets file names for page backgrounds
        void setFileNames();
        bool setScriptTextures(SDL_Renderer* renderer);
        bool setChapterTextures(SDL_Renderer* renderer);
        void loadFont();

        std::stringstream pageText;
        std::stringstream lineText;
        Texture curLineTextTexture;
        Texture curPageTextTexture;
        //tests savegame variables, usually when altered, saved, or loaded.
        void testSaveVariables();

        void setAutoScript();

        //player clicks mouse button outside of chapter buttons
        void progress(SDL_Renderer* renderer);
        //player presses spacebar
        void progress2(SDL_Renderer* renderer);
        //player presses h button
        void handleDialogVisability();
        //renders correct state of the visibility of dialog, dialog box.
        void handleDialogRendering(SDL_Renderer* renderer);
        //renders correct bg with it's corresponding page.
        void renderBackgrounds(SDL_Renderer* renderer,int j);
        //updates current page/script compensation
        void handleBackPagePress();
        //updates current line plus script compensation
        void handleBackLinePress();
        //sets buttonTexture by buttonName and position
        bool setChapterButtonTextures(SDL_Renderer* renderer, bool success);
        //set button names
        void setButtonNames();
        //free button textures at close time
        void freeButtons();
        //handles pretty much all rendering except animation in chapters
        void handleRendering(SDL_Renderer* renderer);
        //load savegame data into chapter variables
        void loadSavedVariables(Sint32 data0, Sint32 data1,Sint32 data2,Sint32 data3,Sint32 data4,Sint32 data5);

        void handleChapterButtonPresses(int gameState,SDL_Renderer* renderer);
        //loads chapter from savegame as well as sets up button names, the font, and textures
        bool loadChapters(Sint32 data0, Sint32 data1,Sint32 data2,Sint32 data3,Sint32 data4,Sint32 data5,SDL_Renderer* renderer, bool success);
        //loads an individual chapter into memory
        void loadChapter(SDL_Renderer* renderer);
        //frees up all the chapter resources
        void free();

    private:

};

#endif // CHAPTER_H
