#include "chapter.h"

chapter::chapter()
{
    currentChapter = 0;
    chapter1Complete = false;
    chapter2Complete = false;
    chapter3Complete = false;
    exitChapter = false;
    currentPage = 0;
    currentScript = 0;
    //loadedScript has to not equal currentScript in order to play first line of first chapter.
    loadedScript = -1;
    autoText = true;
    autoTextSpeed = 1;
    for(int j =0; j <TOTAL_PAGES; j++)
    {
        for(int i = 0; i<TOTAL_SCRIPTS; i++)
        {
            scriptString[j][i].str("");
        }
    }

    font = NULL;
    pageText.str( "" );
    lineText.str( "" );
}

chapter::~chapter()
{
    for(int i = 0; i < TOTAL_PAGES;i++)
    {
        for(int j = 0; j < TOTAL_SCRIPTS;j++)
        {
            scriptString[i][j].str("");
        }
    }
}

void chapter::scriptIncrement()
{//next line of script is prompted to show
    currentScript++;
}
void chapter::pageIncrement()
{//player finished previous page, starts at first script line of new page
    currentPage++;
    currentScript=0;
}
void chapter::backScript()
{//current line of script is removed if player is past first line
    if(0 < currentScript)
    {
        currentScript--;
    }
}
void chapter::backPage()
{//player clicks backPage button in menubar in chapter.
    if(0 < currentPage)
    {//player is sent to last line of previous page.
        currentPage--;
        currentScript=7;
    }
}

void chapter::nextPage()
{//player clicks nextPage button in menubar in chapter.
    if(currentPage < TOTAL_PAGES-1)
    {//player is sent to first line of next page.
        currentPage++;
        currentScript=0;
    }
}

void chapter::completeChapter(SDL_Renderer* renderer)
{//when a player reaches the end of a chapter, page, script line need to be reset, chapter complete flagged, chapter is incremented.
    resetPages();
    //flag chapter complete
    if(currentChapter==0)
    {
        chapter1Complete=true;
    }
    else if(currentChapter==1)
    {
        chapter2Complete=true;
    }
    else if(currentChapter==2)
    {
        chapter3Complete=true;
    }

    exitChapter = true;

    //incrementing chapter may not be necessary.  might be better to set current chapter when player enters chapter.
    currentChapter += 1;
    //print currentpage, chapter, script line, and chapter completed flags to console.
    testSaveVariables();
}
void chapter::resetPages()
{//if a chapter is completed, or a new game is started, currentPage needs to be reset, as does script line on that page
    currentPage=0;
    resetScripts();
}
void chapter::resetScripts()
{//current line of script is returned to 0, effectively making next chapter page opened start from beginning
    currentScript=0;
}
void chapter::resetChapters(SDL_Renderer* renderer)
{  //when new game is clicked, reset chapter variables (page, script, chaptercomplete, and current chapter)
    currentChapter=0;
    resetPages();
    chapter1Complete = false;
    chapter2Complete = false;
    chapter3Complete = false;
    loadChapterStrings(renderer);
    testSaveVariables();
}
void chapter::loadChapterStrings(SDL_Renderer* renderer)
{
	if(currentChapter==0)
    {
        //chapter 1, page 1
        scriptString[0][0].str( "5 years ago, I stopped working regular jobs." );
        scriptString[0][1].str("Since then I've mostly begged for money on the street corner");
        scriptString[0][2].str("with cardboard signs that say things like 'Anything Helps'.");
        scriptString[0][3].str("I stopped working because I noticed a few major problems with");
        scriptString[0][4].str("our socio-economic system.  self-driving cars were commercially viable,");
        scriptString[0][5].str("but the state of California red-taped self driving cars.");
        scriptString[0][6].str("...It would greatly reduce the need for labor in the workforce.");
        scriptString[0][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 2
        scriptString[1][0].str("If the car is driving, the person behind the wheel [but why tf");
        scriptString[1][1].str("would there be a wheel?] can't be held liable, which makes the car driving");
        scriptString[1][2].str("system responsible, but their cars drive better than humans, so that");
        scriptString[1][3].str("won't be much of a problem.  They would probably insure their own");
        scriptString[1][4].str("cars, which would reduce need for auto insurance agents.  Besides that, ");
        scriptString[1][5].str("it's hard to find probable cause when the car is driving, ");
        scriptString[1][6].str("which reduces the need for police on the street.");
        scriptString[1][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 3
        scriptString[2][0].str("When self-driving cars are freely allowed, the need for cars drops.");
        scriptString[2][1].str("One car can be used by an entire family by summoning it as needed");
        scriptString[2][2].str("when not in active use.  But mainly, drivers would lose jobs: ");
        scriptString[2][3].str("taxi drivers, gig-economy transportation drivers, and big-rig truckers.");
        scriptString[2][4].str("Self-driving cars would require a black box like airplanes for liability,");
        scriptString[2][5].str("as well as bug fixes.  The goal should be 100% safety on the road. ");
        scriptString[2][6].str("30,000 automobile deaths yearly would be greatly reduced by self driving cars.");
        scriptString[2][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 4
        scriptString[3][0].str("The only problem with changing over to large scale automation in areas");
        scriptString[3][1].str("like driving is the job problem.  The only way to deal with a job market");
        scriptString[3][2].str("that is smaller than the labor force is to implement Universal Basic Income.");
        scriptString[3][3].str("Universal Basic Income is the idea that everyone, no matter their employment");
        scriptString[3][4].str("status receives a certain amount of money.  debtors can not garnish it, ");
        scriptString[3][5].str("and you still receive it if you are working...  ");
        scriptString[3][6].str("My mission is Universal basic income.");
        scriptString[3][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 5
        scriptString[4][0].str("You may be asking yourself: Won't people lose the incentive ");
        scriptString[4][1].str("to work if they receive UBI?  and yes, they will.  Millions of");
        scriptString[4][2].str("Americans are working minimum wage jobs that don't provide a ");
        scriptString[4][3].str("living wage.  The companies that provide these jobs fight against");
        scriptString[4][4].str("worker's rights, because nothing is more important to them than");
        scriptString[4][5].str("the bottom line.  In my last job I was working in a call center for");
        scriptString[4][6].str("a big telecom company.  Bedbugs and mandatory overtime for all.");
        scriptString[4][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 6
        scriptString[5][0].str("Since that job I've worked for myself mostly. Besides begging on");
        scriptString[5][1].str("street corners, I have knitted several scarves although I never made");
        scriptString[5][2].str("any money on them, only gave them away, except one that a friend");
        scriptString[5][3].str("tried on and walked off with... sigh.  I've painted a lot of paintings");
        scriptString[5][4].str("and sold a few of them.  acrylic + canvas.  I'm an avid gamer and");
        scriptString[5][5].str("since I'm basically retired, I play a lot of pc/android games.");
        scriptString[5][6].str("I have a bachelor's degree in computer science, so I'm programming this.");
        scriptString[5][7].str("                                Press LMB or Enter to continue...");
        //chapter1 page 7
        scriptString[6][0].str("If universal basic income is instated, the ultra rich know that");
        scriptString[6][1].str("eventually we will move toward income equality across the planet.");
        scriptString[6][2].str("That means people will be doing what they want to instead of what");
        scriptString[6][3].str("they must.  Since my last job I've been doing my part in keeping");
        scriptString[6][4].str("the demand for labor up by not working.  I want a future where");
        scriptString[6][5].str("employers don't low-ball employees on wages, and perhaps we");
        scriptString[6][6].str("can return to a time where employers search for employees.");
        scriptString[6][7].str("                                Press LMB or Enter to continue...");
        //chapter1 page8
        scriptString[7][0].str("I grew up playing PC and console videogames.  I knew I wanted");
        scriptString[7][1].str("to make videogames.  It's why I got into computer science.");
        scriptString[7][2].str("Unfortunately the market for game developers is too competitive,");
        scriptString[7][3].str("so I'm making this game independently in my spare time, with zero");
        scriptString[7][4].str("budget. The jobs in the computer science field are cut-throat and");
        scriptString[7][5].str("don't actually pay as much as I thought they would. I'm done making");
        scriptString[7][6].str("online surveys for market research.");
        scriptString[7][7].str(" *End of Chapter 1* Press LMB or Enter to return to select screen.");
    }
    if(currentChapter==1)
    {
        //chapter 2 page 1
        scriptString[0][0].str("Down with the oligarchy!");
        scriptString[0][1].str("The financially wealthy are entitled assholes.");
        scriptString[0][2].str("Cops enforce evil.");
        scriptString[0][3].str("Incumbent forces have too much influence.");
        scriptString[0][4].str("No capitalist future.");
        scriptString[0][5].str("Life is precious.");
        scriptString[0][6].str("Goodbye salamanders and coral reefs, goodbye large mammals.");
        scriptString[0][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 2
        scriptString[1][0].str("Blind obedience gets us nowhere.");
        scriptString[1][1].str("Where is the wisdom in holding back universal Basic Income?");
        scriptString[1][2].str("The planet is dying.");
        scriptString[1][3].str("The planet is dying and we're sticking to a socio-economic");
        scriptString[1][4].str("system that is killing it.");
        scriptString[1][5].str("jobs are currently more important than public health.");
        scriptString[1][6].str("The U.S. is Fascist Capitalist.");
        scriptString[1][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 3
        scriptString[2][0].str("You can't represent the financially poor unless you are");
        scriptString[2][1].str("financially poor yourself.");
        scriptString[2][2].str("The needs of the people outweigh maintaining capitalism.");
        scriptString[2][3].str("Universal basic income is necessary now.");
        scriptString[2][4].str("Political concessions to large corporations are killing the planet.");
        scriptString[2][5].str("My body runs on utilities, but I live in a car.");
        scriptString[2][6].str("Minimum wage should be a living wage.");
        scriptString[2][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 4
        scriptString[3][0].str("As inflation progresses, poverty grows.");
        scriptString[3][1].str("Universal basic income is a step forward for humanity.");
        scriptString[3][2].str("Dinosaurs can't lead the young.");
        scriptString[3][3].str("Coming soon: omega varient.");
        scriptString[3][4].str("We're all connected.");
        scriptString[3][5].str("You are a beacon of hope in this dark world.");
        scriptString[3][6].str("It's tough acting like you can operate at half mast.");
        scriptString[3][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 5
        scriptString[4][0].str("Tear down the mansions!");
        scriptString[4][1].str("Respect for authority is killing the planet.");
        scriptString[4][2].str("Homeless death means homelessness just became less of a problem.");
        scriptString[4][3].str("-Joe Biden");
        scriptString[4][4].str("Why don't you work? why aren't you vaccinated? I'm a millionaire!");
        scriptString[4][5].str("-Joe Biden");
        scriptString[4][6].str("Disobey when you know the orders are wrong.");
        scriptString[4][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 6
        scriptString[5][0].str("How many lies has the news media spun today?");
        scriptString[5][1].str("You know when your boss's orders are wrong, ");
        scriptString[5][2].str("disobey in those circumstances.");
        scriptString[5][3].str("You don't want me competing in the job market.");
        scriptString[5][4].str("Discontent is the first step to progress -Oscar Wilde");
        scriptString[5][5].str("Disinformation is a tool against socialist revolution!");
        scriptString[5][6].str("Automation means we compete with China, economically.");
        scriptString[5][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 7
        scriptString[6][0].str("Phase out human workers.");
        scriptString[6][1].str("Why are we prioritizing financially wealthy lives by having a");
        scriptString[6][2].str("tiered medical insurance system?");
        scriptString[6][3].str("I free up a job for you, friend.");
        scriptString[6][4].str("My big picture includes humanity's survival.");
        scriptString[6][5].str("Preventing mass extinctions is secondary, but important.");
        scriptString[6][6].str("Earth is a single point of failure for our species' survival.");
        scriptString[6][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 8
        scriptString[7][0].str("I may be a beggar on the street, ");
        scriptString[7][1].str("but don't I deserve utilities that aren't public?");
        scriptString[7][2].str("We all share the burden of the financially wealthy.");
        scriptString[7][3].str("How can I persuade you to demand universal basic income?");
        scriptString[7][4].str("I only have logic, and you're not like me at all.");
        scriptString[7][5].str("Why have I been treated less than equal?");
        scriptString[7][6].str("If I die tomorrow will it matter to you?");
        scriptString[7][7].str(" *End of Chapter 2* Press LMB or Enter to return to select screen.");
    }
    if(currentChapter==2) //chapter 3 title?  Logic over Common Sense.
    {
        //chapter 3, page 1
        scriptString[0][0].str("Oligarchs can't control their own greed,");
        scriptString[0][1].str("but they control our country;");
        scriptString[0][2].str("I can't control how bad this makes me feel.");
        scriptString[0][3].str("Your boss is always more right wing than you.");
        scriptString[0][4].str("If your boss is always more right wing than you,");
        scriptString[0][5].str("then working is bootlicking.");
        scriptString[0][6].str("It's better to be homeless.");
        scriptString[0][7].str("                                Press LMB or Enter to continue...");
        //chapter 3, page 2
        scriptString[1][0].str("I want you to up-cycle our future,");
        scriptString[1][1].str("by throwing away your job.");
        scriptString[1][2].str("The fear, propaganda, and disinformation that");
        scriptString[1][3].str("the media shares, impedes progress.");
        scriptString[1][4].str("Not working is brave.");
        scriptString[1][5].str("Stop devaluing labor.");
        scriptString[1][6].str("embrace robotic laborers, don't be them.");
        scriptString[1][7].str("                                Press LMB or Enter to continue...");
        //chapter 3, page 3
        scriptString[2][0].str("work is not freedom.");
        scriptString[2][1].str("cancel work.");
        scriptString[2][2].str("two thirds of Americans live paycheck to paycheck,");
        scriptString[2][3].str("but only one percent of American politicians are not capitalist.");
        scriptString[2][4].str("no more paycheck to paycheck slavery.");
        scriptString[2][5].str("you are over qualified, under appreciated, and expendable.");
        scriptString[2][6].str("The labor market is flooded.");
        scriptString[2][7].str("                                Press LMB or Enter to continue...");
        //chapter 3, page 4
        scriptString[3][0].str("Do you ever wonder where your employer' ethics are?");
        scriptString[3][1].str("Aren't you tired of being disrespected by your boss?");
        scriptString[3][2].str("Aren't you tired of being disrespected by customers/clients?");
        scriptString[3][3].str("You will always be a terrible worker.");
        scriptString[3][4].str("You should never start work for anyone but yourself.");
        scriptString[3][5].str("Money is making you do things that you don't want to do.");
        scriptString[3][6].str("Working when you don't want to work is slavery.");
        scriptString[3][7].str("                                Press LMB or Enter to continue...");
        //chapter 3, page 5
        scriptString[4][0].str("You can't have billionaires without homelessness.");
        scriptString[4][1].str("If you tax billionaires more, homelessness is reduced.");
        scriptString[4][2].str("As it is, you are paying for the billionaires to be billionaires,");
        scriptString[4][3].str("and for the public services and resources that the homeless are");
        scriptString[4][4].str("lucky enough to receive.");
        scriptString[4][5].str("Working under someone else is cowardly.");
        scriptString[4][6].str("Don't catch the same mental illness billionaires have: greed.");
        scriptString[4][7].str("                                Press LMB or Enter to continue...");
        //chapter 3, page 6
        scriptString[5][0].str("Federal minimum wage is $7.25 per hour.");
        scriptString[5][1].str("It's been the same since 2009,");
        scriptString[5][2].str("despite the fact that prices are 40% higher since then.");
        scriptString[5][3].str("currently, the consensus on a living wage is $24 per hour.");
        scriptString[5][4].str("Knowing this means that you know that politicians");
        scriptString[5][5].str("work for oligarchs, not the general population.");
        scriptString[5][6].str("That's not democracy.");
        scriptString[5][7].str("                                Press LMB or Enter to continue...");
        //chapter 3, page 7
        scriptString[6][0].str("Aim at nothing, and you will hit everything.");
        scriptString[6][1].str("If you care about the future,");
        scriptString[6][2].str("you have to do what's best for everyone.");
        scriptString[6][3].str("Working until you die ensures that your children,");
        scriptString[6][4].str("should you have them, will work until they die too.");
        scriptString[6][5].str("Do you want to perpetuate this broken system?");
        scriptString[6][6].str("Doing something with your life means not working.");
        scriptString[6][7].str("                                Press LMB or Enter to continue...");
        //chapter 3, page 8
        scriptString[7][0].str("Do you think big oil is going to stop lobbying against sustainability?");
        scriptString[7][1].str("What about big coal?  Do you think that having publicly owned");
        scriptString[7][2].str("utilities is going to incentivize fossil fuels?");
        scriptString[7][3].str("It will do the opposite.  Why keep people digging and drilling when");
        scriptString[7][4].str("solar panels, windmills, hydroelectric dams, and geothermal generators");
        scriptString[7][5].str("largely require little to no effort to maintain?");
        scriptString[7][6].str("Think about human survival, not just your own comfort.");
        scriptString[7][7].str(" *End of Chapter 3* Press LMB or Enter to return to select screen.");
    }
    //loads strings into textures
    setScriptTextures(renderer);
}

void chapter::freeBGTextures()
{
    //frees background textures for each chapter
    for(int i = 0; i < TOTAL_PAGES; i++)
    {
        chapter1BG[i].free();
        chapter2BG[i].free();
        chapter3BG[i].free();
    }
    //frees dialog box and menubar textures
    dialogBox.free();
    //menubar is background for backpage, backline, autotext speed/toggle buttons
	menuBar.free();
	//little tincan image.
	tinCan.free();
	//free the script textures
    for(int j = 0; j < TOTAL_PAGES; j++)
    {
        for(int i=0;i<TOTAL_SCRIPTS;i++)
        {
            scriptTexture[j][i].free();
        }
    }
    //frees ch2 pg 7 parallax background textures
    ch2Pg7Fore.freeParallaxTexture();
    ch2Pg7Mid.freeParallaxTexture();
    ch2Pg7Back.freeParallaxTexture();
    //free ch2 pg 8 parallax background textures
    ch2Pg8Fore.freeParallaxTexture();
    ch2Pg8Mid.freeParallaxTexture();
    ch2Pg8AnteriorMid.freeParallaxTexture();
    ch2Pg8Back.freeParallaxTexture();
}

void chapter::setFileNames()
{
    //chapter1 background file names
    bgFileName[0] = "images/signflying800x600.png";
    bgFileName[1] = "images/parkbench.png";
    bgFileName[2] = "images/bluewave.png";
    bgFileName[3] = "images/please.png";
    bgFileName[4] = "images/biblioteca.png";
    bgFileName[5] = "images/America2.png";
    bgFileName[6] = "images/darknight.png";
    bgFileName[7] = "images/forest.png";
    //chapter2 background file names
    bgFileName2[0] = "images/bubbleparty.png";
    bgFileName2[1] = "images/randomcolors.png";
    bgFileName2[2] = "images/angryright.png";
    bgFileName2[3] = "images/nondigitalpaperclip.png";
    bgFileName2[4] = "images/joblesspurpose.png";
    bgFileName2[5] = "images/treadonyou.png";
    bgFileName2[6] = "images/blackground.png";
    bgFileName2[7] = "images/blackground.png";
    //chapter 3 background file names
    bgFileName3[0] = "images/groundsleeper.png";
    bgFileName3[1] = "images/emptypockets.png";
    bgFileName3[2] = "images/kindnesshelps.png";
    bgFileName3[3] = "images/poorperson.png";
    bgFileName3[4] = "images/realdemocracy.png";
    bgFileName3[5] = "images/purepoverty.png";
    bgFileName3[6] = "images/trailer.png";
    bgFileName3[7] = "images/badsign.png";
}

bool chapter::setChapterTextures(SDL_Renderer* renderer)
{
    bool success = true;
    setFileNames();
    if(currentChapter==0)
    {
        for(int i = 0; i<TOTAL_PAGES;i++)
        {
            success = chapter1BG[i].loadFromFile( bgFileName[i],renderer );
        }
    }
    else if(currentChapter == 1)
    {
        for(int i = 0; i<TOTAL_PAGES;i++)
        {//load chapter 2 background images
            success = chapter2BG[i].loadFromFile( bgFileName2[i],renderer );
        }
        //load pg 7 parallax background textures
        success = ch2Pg7Fore.parallaxTexture.loadFromFile("images/starlaxfore.png",renderer);
        success = ch2Pg7Mid.parallaxTexture.loadFromFile("images/starlaxmid.png",renderer);
        success = ch2Pg7Back.parallaxTexture.loadFromFile("images/starlaxback.png",renderer);
        //load pg 8 parallax background textures
        success = ch2Pg8Fore.parallaxTexture.loadFromFile("images/dusk.png",renderer);
        success = ch2Pg8AnteriorMid.parallaxTexture.loadFromFile("images/road.png",renderer);
        success = ch2Pg8Mid.parallaxTexture.loadFromFile("images/cityscape.png",renderer);
        success = ch2Pg8Back.parallaxTexture.loadFromFile("images/citystars.png",renderer);
    }
    else if(currentChapter == 2)
    {

        for(int i = 0; i<TOTAL_PAGES;i++)
        {//load chapter 3 background images
            success = chapter3BG[i].loadFromFile( bgFileName3[i],renderer );
        }

    }
    //load dialog box image
	success = dialogBox.loadFromFile( "images/dialogbox1.png",renderer );
	success = menuBar.loadFromFile("images/menuBar.png",renderer);
	success = tinCan.loadFromFile("images/tincan.png",renderer);
    //set dialog box alpha (about 75% opaque @ 192)
    dialogBox.setAlpha(215);
    return success;
}

void chapter::loadLineText(SDL_Renderer* renderer)
{
    if(currentScript!=loadedScript)
    {
        voice.stopVoice();
        lineText.str( "" );
        lineText << currentScript + 1;
        SDL_Color textColor = {0,0,0};//black
        if( !curLineTextTexture.loadFromRenderedText( lineText.str().c_str(), textColor,font,renderer ) )
        {
            printf( "\n Unable to render current line text to texture!\n" );
        }
        if(currentPage < 8)
        {
            voice.loadVoice(currentChapter,currentPage,currentScript);
            voice.playVoice();
        }
        loadedScript=currentScript;
    }
}

void chapter::loadPageText(SDL_Renderer* renderer)
{
    pageText.str( "" );
    pageText << "" << currentPage + 1;
    SDL_Color textColor = {0,0,0};//black
    if( !curPageTextTexture.loadFromRenderedText( pageText.str().c_str(), textColor,font,renderer ) )
    {
        printf( "\n Unable to render current page text to texture!\n" );
    }
}

bool chapter::setScriptTextures(SDL_Renderer* renderer)
{
    bool success = true;
    //Render text
    SDL_Color textColor;
    //make sure loading current strings
    for(int j=0;j<TOTAL_PAGES;j++)
    {
        textColor = {55,55,55};
        if(j==0)//was testing page 1 dialog color here
        {
            //textColor = {0,255,0};//green
            //textColor = {255,0,255};//pink
        }
        if(j==3 || j==4 || j==6)//pages 4,5, and 7 have dialog color white.
        {
            textColor = {255,255,255};//white
        }
        if(j==5)//page 6 has red dialog
        {
            textColor = {255,0,0};//red
        }
        for(int i=0;i<TOTAL_SCRIPTS;i++){

            if( !scriptTexture[j][i].loadFromRenderedText( scriptString[j][i].str().c_str(), textColor,font, renderer ) )
            {
                printf( "Failed to render text texture!\n" );
                success = false;
            }
        }
    }
    return success;
}

void chapter::testSaveVariables()
{
    std::cout << "\n currentChapter: " << std::to_string( currentChapter );
    std::cout << "\n currentPage: " << std::to_string( currentPage );
    std::cout << "\n currentScript: " << std::to_string( currentScript );
    std::cout << "\n chapter1Complete: " << std::to_string(chapter1Complete);
    std::cout << "\n chapter2Complete: " << std::to_string(chapter2Complete);
    std::cout << "\n chapter3Complete: " << std::to_string(chapter3Complete);
}

void chapter::loadFont()
{
    //load the font
	font = TTF_OpenFont( "fonts/Tapeworm.ttf", 16 );
}

void chapter::progress(SDL_Renderer* renderer)
{
    //end of chapter, should send user back to load game screen
    if(currentPage==TOTAL_PAGES-1 && currentScript==TOTAL_SCRIPTS-1){
        completeChapter(renderer);
        chapterTimer.stop();
    }
    //increments line of script displayed
    else if (currentScript<TOTAL_SCRIPTS-1)
    {
        scriptIncrement();
        chapterTimer.restart();
    }
    //increments page displayed
    else if(currentPage<TOTAL_PAGES-1){
        pageIncrement();
        chapterTimer.restart();
    }
}

void chapter::progress2(SDL_Renderer* renderer)
{//increments script, page, chapter based on spacebar presses
    if(currentScript<TOTAL_SCRIPTS-1)
    {
        scriptIncrement();
        chapterTimer.restart();
    }
    else
    {
        if(currentPage<TOTAL_PAGES-1)
        {
            pageIncrement();
            chapterTimer.restart();
        }
        else
        {
            completeChapter(renderer);
        }
    }
}

void chapter::handleDialogVisability()
{
    if(!hideDialogBox && !hideDialogAndBox)
    {
        hideDialogBox = true;
        hideDialogAndBox = false;
    }
    else if(hideDialogBox && !hideDialogAndBox)
    {
        hideDialogAndBox = true;
        hideDialogBox = true;
    }else if(hideDialogBox && hideDialogAndBox)
    {
        hideDialogAndBox=false;
        hideDialogBox=false;
    }
    printf("\n h pressed \n");
    std::cout << "hideDialogBox: " << hideDialogBox;
}

void chapter::handleDialogRendering(SDL_Renderer* renderer)
{
    if(hideDialogBox == false)
    {
        dialogBox.render(0,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        tinCan.render(16,565,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(hideDialogAndBox==false){
        for(int i = 0; i<TOTAL_SCRIPTS;i++)
        {
            //render script lines
            if(i <= currentScript)
            {
                scriptTexture[currentPage][i].render(20,420 + (i*20),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
    }
}

void chapter::handleBackPagePress()
{
    if(currentPage>0)
    {
        currentPage--;
        currentScript=7;
    }
}

void chapter::setButtonNames()
{
    for(int i = 0; i < TOTAL_CHAPTER_BUTTONS; i++)
    {
        buttons[i].setChapterButtonName(i);
    }
}

void chapter::freeButtons()
{
    for(int i = 0; i<TOTAL_CHAPTER_BUTTONS;i++)
    {
        buttons[i].buttonTexture.free();
    }
}

void chapter::loadSavedVariables(Sint32 data0, Sint32 data1,Sint32 data2,Sint32 data3,Sint32 data4,Sint32 data5)
{
    currentChapter=data0;
    currentPage=data1;
    currentScript=data2;
    chapter1Complete=data3;
    chapter2Complete=data4;
    chapter3Complete=data5;
}

void chapter::handleChapterButtonPresses(int buttonClicked,SDL_Renderer* renderer)
{
    if(buttonClicked==1)
    {//player clicked save & exit
        voice.stopVoice();
    }
    if(buttonClicked==2)
    {
        handleBackPagePress();
    }
    else if(buttonClicked==3)
    {
        handleBackLinePress();
    }
    else if(buttonClicked==4)
    {
        autoText=true;
    }
    else if(buttonClicked==5)
    {
        autoText=false;
    }
    else if(buttonClicked==6)
    {
        autoTextSpeed = 0;
    }
    else if(buttonClicked==7)
    {
        autoTextSpeed = 1;
    }
    else if(buttonClicked==8)
    {
        autoTextSpeed = 2;
    }
    else if(buttonClicked==9)
    {
        nextPage();
    }
    else if(buttonClicked==0)
    {
        //mouse click was not on a button
        progress(renderer);
    }
}

void chapter::handleRendering(SDL_Renderer* renderer)
{
    if(!chapterTimer.isStarted())
    {
        chapterTimer.start();
    }
    for(int j = 0; j<TOTAL_PAGES;j++)
    {
        //render background & dialog box before script lines
        renderBackgrounds(renderer,j);
        if(autoText)
        {
            //render auto texture on button (hightlights auto text on in menubar)
            buttons[2].buttonTexture.render(buttons[2].getPositionX(),buttons[2].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            //render auto texture off button (hightlights auto text off in menubar)
            buttons[3].buttonTexture.render(buttons[3].getPositionX(),buttons[3].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        if(autoTextSpeed==0)
        {
            //highlights text speed 1
            buttons[4].buttonTexture.render(buttons[4].getPositionX(),buttons[4].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(autoTextSpeed==1)
        {
            //highlights text speed 2
            buttons[5].buttonTexture.render(buttons[5].getPositionX(),buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(autoTextSpeed==2)
        {
            //highlights text speed 3
            buttons[6].buttonTexture.render(buttons[6].getPositionX(),buttons[6].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        menuBar.render(0,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        //load page number into menubar
        loadPageText(renderer);
        curPageTextTexture.render(140,352,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        //load line number into menubar
        loadLineText(renderer);
        curLineTextTexture.render(130,374,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        //if the state of the dialog box visibility gets changed, this handles the rendering or not rendering.
        handleDialogRendering(renderer);
    }
    //render save & exit button
    buttons[7].buttonTexture.render(buttons[7].getPositionX(),buttons[7].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

bool chapter::setChapterButtonTextures(SDL_Renderer* renderer, bool success)
{
    for( int i = 0; i < TOTAL_CHAPTER_BUTTONS; ++i )
    {
        std::stringstream ss;
        ss << "images/buttons/" << buttons[i].buttonName << ".png";
        std::string str = ss.str();
        success = buttons[i].buttonTexture.loadFromFile( str,renderer );
        //buttons[ i ].setPosition( ((i*160)-80), SCREEN_HEIGHT - 140 );
    }
    //backpage and backline button positions
    buttons[0].setPosition(161,350);
    buttons[1].setPosition(195,350);
    //autoTextOn
    buttons[2].setPosition(270,385);
    buttons[3].setPosition(290,385);
    //autospeed
    buttons[4].setPosition(240,365);
    buttons[5].setPosition(266,365);
    buttons[6].setPosition(292,365);
    //save and exit
    buttons[7].setPosition(600,20);
    //next page
    buttons[8].setPosition(308,350);
    return success;
}

void chapter::handleBackLinePress()
{//player presses backline button in chapter menubar
    if(currentScript>0)
    {//if script line isn't first, line is reduced
       currentScript--;
    }
}

void chapter::renderBackgrounds(SDL_Renderer* renderer,int j)
{//depending on the chapter and the page, background is rendered.
    if(currentChapter == 0)
    {
        switch(currentPage %TOTAL_PAGES)
        {
        case 0:
            chapter1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 1:
            chapter1BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 2:
            chapter1BG[2].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 3:
            chapter1BG[3].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 4:
            chapter1BG[4].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 5:
            chapter1BG[5].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 6:
            chapter1BG[6].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 7:
            chapter1BG[7].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        }
    }
    else if(currentChapter == 1)
    {
        switch(currentPage %TOTAL_PAGES)
        {
        case 0:
            chapter2BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 1:
            chapter2BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 2:
            chapter2BG[2].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 3:
            chapter2BG[3].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 4:
            chapter2BG[4].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 5:
            chapter2BG[5].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 6:
            chapter2BG[6].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

            ch2Pg7handleParallax(renderer);

        break;
        case 7:
            //render images back to front for proper layering.
            chapter2BG[7].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

            ch2Pg8handleParallax(renderer);

        break;
        }
    }
    else if(currentChapter == 2)
    {
        switch(currentPage %TOTAL_PAGES)
        {
        case 0:
            chapter3BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 1:
            chapter3BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 2:
            chapter3BG[2].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 3:
            chapter3BG[3].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 4:
            chapter3BG[4].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 5:
            chapter3BG[5].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 6:
            //chapter3BG[6].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        case 7:
            chapter3BG[7].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
        }
    }
}

void chapter::setAutoScript()
{//after player presses autoscript speed buttons in chapter menubar, this code adjusts the speed at which script lines are incremented.
        if(chapterTimer.getTicks()/3000 > 1 && autoTextSpeed==0 && autoText)
        {//implement timer auto script option. Slow / default speed
            if(currentScript<TOTAL_SCRIPTS-1)
            {
                scriptIncrement();
                chapterTimer.restart();
            }
            if(currentScript == TOTAL_SCRIPTS-1)
            {
                chapterTimer.stop();
            }
        }
        else if(chapterTimer.getTicks()/2000 > 1 && autoTextSpeed==1 && autoText)
        {//implement timer auto script option. Medium Speed
            if(currentScript<TOTAL_SCRIPTS-1)
            {
                scriptIncrement();
                chapterTimer.restart();
            }
            if(currentScript == TOTAL_SCRIPTS-1)
            {
                chapterTimer.stop();
            }
        }
        else if(chapterTimer.getTicks()/1000 > 1 && autoTextSpeed==2 && autoText)
        {//implement timer auto script option.  Fast speed
            if(currentScript<TOTAL_SCRIPTS-1)
            {
                scriptIncrement();
                chapterTimer.restart();
            }
            if(currentScript == TOTAL_SCRIPTS-1)
            {
                chapterTimer.stop();
            }
        }
}


void chapter::ch2Pg7handleParallax(SDL_Renderer* renderer)
{//space parallax from chapter two
    //slows down the animation of the parallax backgrounds
    SDL_Delay(10);
    //pg 7 parallax rendering
    ch2Pg7Back.parallaxRender(renderer);
    ch2Pg7Mid.parallaxRender(renderer);
    ch2Pg7Fore.parallaxRender(renderer);
    //pg 7 parallax incrementation
    ch2Pg7Fore.incrementFore();
    ch2Pg7Mid.incrementMid();
    ch2Pg7Back.incrementBack();
}

void chapter::ch2Pg8handleParallax(SDL_Renderer* renderer)
{//car in the city parallax from chapter 2

    SDL_Delay(10);
    //pg 8 parallax rendering
    ch2Pg8Back.parallaxRender(renderer);
    ch2Pg8Mid.parallaxRender(renderer);
    ch2Pg8AnteriorMid.parallaxRender(renderer);
    ch2Pg8Fore.parallaxRender(renderer);
    //pg 8 parallax incrementation
    ch2Pg8Fore.specialIncrementFore();
    ch2Pg8AnteriorMid.incrementAnteriorMid();
    ch2Pg8Mid.incrementMid();
    ch2Pg8Back.incrementBack();
}

void chapter::loadChapter(SDL_Renderer* renderer)
{//loads chapter background textures/parallax backgrounds, also loads script strings / textures. also outputs currentScript, page, chapter, and chapter completed flags to console.
    setChapterTextures(renderer);
    loadChapterStrings(renderer);
    testSaveVariables();
}

bool chapter::loadChapters(Sint32 data0, Sint32 data1,Sint32 data2,Sint32 data3,Sint32 data4,Sint32 data5,SDL_Renderer* renderer,bool success)
{//when game loads, this handles a lot of the setup for chapters.
    setButtonNames();
	//set chapter variables based on savegame data.
	loadSavedVariables(data0,data1,data2,data3,data4,data5);
	//test the variables after loading
    testSaveVariables();
    //load font
	loadFont();
    //sets up button textures and positions for chapter buttons
    success = setChapterButtonTextures(renderer,success);
    //load chapter 1 background textures
    success = setChapterTextures(renderer);//this function is throwing a warning to console.
    //if textures were successfully created, returns true.  else a flag will be thrown to console.
    return success;
}

void chapter::free()
{
    //free the button textures
    freeButtons();
    //free the backgrounds, dialog box, menubar for chapters and script textures
	freeBGTextures();
	//free the font
	TTF_CloseFont( font );
    font = NULL;
}
