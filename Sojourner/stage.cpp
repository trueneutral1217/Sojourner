#include "stage.h"

stage::stage()
{
    internalView=false;
    externalView=true;
    showPlayer=false;
    habInternalY1=0;
    habInternalY2=-600;
    timeSurvived = 0;
}

stage::~stage()
{

}

void stage::freeButtons()
{
    std::cout<<"\n running stage::freeButtons()";
    //free button textures
    for(int i = 0; i < TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].buttonTexture.free();
        buttons[i].buttonMOTexture.free();
    }
}

bool stage::setStageButtonTextures(SDL_Renderer* renderer, bool success)
{
    std::cout<<"\n running stage::setStageButtonTextures(SDL_Renderer* renderer, bool success)";
    //stage button textures get loaded into array from array of string names, button positions set after.
    for( int i = 0; i < TOTAL_STAGE_BUTTONS; ++i )
    {
        if(i<1)
        {
            std::stringstream ss;
            std::stringstream ssMO;
            ss << "images/buttons/" << buttons[i].buttonName << ".png";
            ssMO << "images/buttons/" << buttons[i].buttonName << "MO.png";
            std::string str = ss.str();
            std::string str2 = ssMO.str();
            success = buttons[i].buttonTexture.loadFromFile( str,renderer );
            success = buttons[i].buttonMOTexture.loadFromFile( str2,renderer );
        }
    }
    //save and exit
    buttons[0].setPosition(600,80);

    return success;
}

void stage::setButtonNames()
{
    std::cout<<"\n running stage::setButtonNames()";
    //array of buttons filled by button names from function in button class.
    for(int i = 0; i < TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].setStageButtonName(i);
    }
}

bool stage::setStageTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running stage::setStageTextures(SDL_Renderer* renderer)";
    //stage background textures loaded from bgFileName array.
    bool success = true;
    setFileNames();
    for(int i = 0; i<TOTAL_STAGE_BACKGROUNDS;i++)
    {
        success = stage1BG[i].loadFromFile( bgFileName[i],renderer );
    }
    for(int i = 0; i < TOTAL_STAGE_UI; i++)
    {
        success = UI[i].loadFromFile(uiFileName[i],renderer);
    }
    success = starsFore.parallaxTexture.loadFromFile("images/starlaxfore.png",renderer);
    success = starsMid.parallaxTexture.loadFromFile("images/starlaxmid.png",renderer);
    success = starsBack.parallaxTexture.loadFromFile("images/starlaxback.png",renderer);

    courage = "Courage is freedom in practice.";
    //test if water tank interaction function is running
    std::cout<<"\n courage function executed";
    SDL_Color textColor = {255,255,255};//white
    if(!courageTexture.loadFromRenderedText(courage.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render courage string to courageTexture!";
    }

    return success;
}

void stage::setFileNames()
{
    std::cout<<"\n running stage::setFileNames()";
    //filenames being specified
    bgFileName[0] = "images/blackground.png";
    bgFileName[1] = "images/outerShip1.png";
    bgFileName[2] = "images/habitation1.png";
    bgFileName[3] = "images/habitation2.png";

    uiFileName[0] = "images/UI.png";

}

void stage::freeBGTextures()
{
    std::cout<<"\n running stage::freeBGTextures()";
    //free resources
    for(int i = 0; i<TOTAL_STAGE_BACKGROUNDS;i++)
    {
        stage1BG[i].free();
    }
    courageTexture.free();
    starsFore.freeParallaxTexture();
    starsMid.freeParallaxTexture();
    starsBack.freeParallaxTexture();
}

void stage::freeUITextures()
{
    std::cout<<"\n running stage::freeUITextures()";
    for(int i = 0; i < TOTAL_STAGE_UI; i++)
    {
        UI[i].free();
    }
}

void stage::loadFont()
{
    std::cout<<"\n running stage::loadFont()";
    //load the font
	font = TTF_OpenFont( "fonts/PublicPixel-z84yD.ttf", 12 );

}

bool stage::loadStage(SDL_Renderer* renderer, bool success)
{
    std::cout<<"\n running stage::loadStage(SDL_Renderer* renderer, bool success)";
    //stage file names get set and loaded into texture arrays, player gets loaded from player class.
    setButtonNames();
    //updates font to stage font.
    loadFont();
    //load stage button textures and positions
    success = setStageButtonTextures(renderer,success);
    //set stage bg texture
    success = setStageTextures(renderer);

    loadTimeSurvivedTextures(renderer);
    //load player texture
    player1.loadPlayer(renderer);
    //loads needs text textures for UI.
    player1.loadNeedsTextures(renderer,font);
    station.loadStation(renderer,font,ship.gauge);
    ship.loadGaugesTextures(renderer,font);
    return success;
}

void stage::free()
{
    std::cout<<"\n running stage::free()";
    //free resources
    freeTimeSurvivedTextures();
    freeButtons();
    freeBGTextures();
    freeUITextures();
    player1.freePlayer();
    station.free();
    ship.free();

}

void stage::handleStageButtonPresses(SDL_Renderer* renderer, int buttonClicked)
{
    //std::cout<<"\n running stage::handleStageButtonPresses(int buttonClicked)";
    if(buttonClicked==1)
    {//player clicked save & exit
        //voice.stopVoice();
        internalView = false;
        showPlayer = false;
        externalView = true;
    }
    else if(buttonClicked==2)
    {
        internalView=true;
        showPlayer=true;
        externalView=false;
    }
    else if(buttonClicked == 3)
    {//player clicked 'plant' under planter interactions
        //this is where the texture for the planter station should update to show plants have been planted
        //it should also take some time and lower players' needs (ie: player's slumber need)
        //std::cout<<"\n planter 'plant' button pressed";
        if(station.plantOkay)
        {
            //station.planterSown = true;
            station.waterPlantsOkay = true;
            station.plantOkay = false;
            station.interacted = true;
            std::cout<<"\n plantOkay: "<<station.plantOkay;
            timeSurvived += 30;
            refreshTS(renderer);
            //see plant watering section below for notes about this.
            int plant[TOTAL_PLAYER_NEEDS] = {0,-5,-5,-5,-5};
            player1.modifyNeeds(plant);
            player1.reloadNeedsTextures(renderer,font);
        }

        //station.planterTexture=station.planterSownTexture;
    }
    else if(buttonClicked == 4)
    {
        //if  player has already planted but not watered
        if(!station.plantOkay && station.waterPlantsOkay)
        {
            //station.planterWatered = true;
            station.waterPlantsOkay = false;
            station.interacted = true;
            std::cout<<"\n waterPlantsOkay: "<<station.waterPlantsOkay;
            //player watered the plants, which takes 30 minutes
            timeSurvived +=30;
            refreshTS(renderer);
            //update players needs to reflect the half hour they spent watering.
            //at some point, watering will have to track the how long it's been since last watering,
            //which I'll probably set up to need watering again after 24 hours.
            //health physique slumber hunger morale
            //it might be better to send a certain number of minutes to a function in player class
            //to modify the player's needs, but that would need to take into account strenuousness of an activity,
            //or other factors.
            //temporary numbers
            int water[TOTAL_PLAYER_NEEDS] = {0,-5,-5,-5,-5};
            player1.modifyNeeds(water);
            player1.reloadNeedsTextures(renderer,font);
            int waterDecrement[6] = {0,0,0,-2,0,0};
            ship.modifyGauges(waterDecrement);
            ship.reloadGaugesTextures(renderer,font);
            //reloading text texture for water tank level
            station.loadInteractWaterTank(renderer,font,ship.gauge[3]);
            //image needs to be refreshed with new texture.
            //station.planterTexture = station.planterSownWateredTexture;
        }
    }
}

int stage::handleButtons(SDL_Renderer* renderer, SDL_Event* e )
{
    //std::cout<<"\n running stage::handleButtons( SDL_Event* e )";
    //player clicks mouse inside stage
    int buttonClicked = 0;

    //planter's plant button needs to be updated based on the planter's X,Y coords
    //attempting to create a button using a textTexture. this might not work right if plant texture has moved.
    buttons[1].buttonTexture = station.plantTexture;
    buttons[1].setPosition(player1.getX()+50,player1.getY()-20);

    buttons[2].buttonTexture = station.waterPlantsTexture;
    buttons[2].setPosition(player1.getX()+50,player1.getY());

    //buttonClicked takes the sum of all the button checks, 0 is outside of any buttons
    for( int i = 0; i < TOTAL_STAGE_BUTTONS; ++i )
    {
        buttonClicked = buttons[ i ].handleStageEvent(internalView,buttons[i].buttonName, e );
        if(buttonClicked != 0)
        {
            i+=TOTAL_STAGE_BUTTONS;
        }
    }



    //std::cout<<"\n buttonClicked: "<<buttonClicked;

    handleStageButtonPresses(renderer,buttonClicked);

    if(buttonClicked == 1)
    {
        return 0;
    }
    else
    {
        return 5;
    }

}

void stage::renderStage1(SDL_Renderer* renderer)
{//while stage scene is running this displays bgs,buttons, and player with updated positions.
    stage1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    starsHandleParallax(renderer);
    if(externalView)
    {//renders the exterior of the ship
        stage1BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        courageTexture.render(10,580,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    else if(internalView)
    {//renders the interior of the ship (supposed to parallax as player walks up or down.
        habInternalHandleParallax(renderer);
    }

    //renders station, then renders player, because station is in front of player (station closer to bottom screen)
    if(internalView)
    {
        station.renderStationBehindPlayer(renderer,player1.playerBot);
    }
    if(showPlayer)
    {//player is shown if internalView is on.
        player1.render(renderer);
        station.renderStationFrontPlayer(renderer,player1.playerBot);

        //interact is user pressed 'e', inRange is player collision with interactable station
        if(player1.interact)
        {
            if(player1.interactWaterTank)
            {
                station.renderInteractWaterTank(renderer,player1.getX(),player1.getY());
            }
            if(player1.interactBed)
            {
                if(player1.need[3]<100)
                {
                    //if player's slumber value is less than 100, modify and refresh needs from bed use.
                    int slumberBag[TOTAL_PLAYER_NEEDS] = {0,-33,-33,100,-33};
                    player1.modifyNeeds(slumberBag);
                    player1.reloadNeedsTextures(renderer,font);
                    //8 hours passed from sleeping
                    timeSurvived +=480;
                    refreshTS(renderer);
                }
                else
                {//else just render 'not tired'
                    station.renderInteractBed(renderer,player1.getX(),player1.getY());
                }
            }
            if(player1.interactPlanter)
            {
                /*if(!station.planterOptionsLoaded)
                {
                    station.planterOptionsLoaded = true;
                    station.loadInteractPlanter(renderer,text.font2);
                }*/

                station.renderInteractPlanter(renderer,player1.getX(),player1.getY());
            }
            if(player1.interactKitchen)
            {
                station.renderInteractKitchen(renderer,player1.getX(),player1.getY());
            }
            if(player1.interactInfirmary)
            {
                station.renderInteractInfirmary(renderer,player1.getX(),player1.getY());
            }
            if(player1.interactBike)
            {
                station.renderInteractBike(renderer,player1.getX(),player1.getY());
            }
        }
    }
    if(internalView)
    {
        UI[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        renderTimeSurvivedTextTextures(renderer);
        player1.renderNeedsTextures(renderer);
        ship.renderGaugesTextures(renderer);
    }
    if(buttons[0].mouseOver==false)
    {
        buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    else
    {
        buttons[0].buttonMOTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void stage::starsHandleParallax(SDL_Renderer* renderer)
{//space parallax
    //slows down the animation of the parallax backgrounds
    SDL_Delay(10);
    //parallax rendering
    starsBack.parallaxRender(renderer);
    starsMid.parallaxRender(renderer);
    starsFore.parallaxRender(renderer);
    // parallax incrementation
    starsFore.incrementFore();
    starsMid.incrementMid();
    starsBack.incrementBack();
}

void stage::habInternalHandleParallax(SDL_Renderer* renderer)
{
    stage1BG[2].render(0,habInternalY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    stage1BG[3].render(0,habInternalY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void stage::move(int countedFrames)
{
    //std::cout<<"\n running stage::move(int countedFrames)";
    if( player1.getY() == 360 && player1.getPVelY() > 0 )
    {//player is heading down after hitting lower threshold.

        //y value of hab background continues to decrease as it moves up the screen
        if(habInternalY1 < -599)//if hab y value is -600 or less, reset hab background position to bottom of screen
        {
            habInternalY1 = 600;
        }
        if(habInternalY2 < -599)
        {
            habInternalY2 = 600;
        }

        habInternalY1-=player1.getPVelY();
        habInternalY2-=player1.getPVelY();

        std::cout<<"\n habY1: "<<habInternalY1<<", habY2: "<<habInternalY2;
    }
    if(player1.getY()==160 && player1.getPVelY()<0)//player is heading up,bg scrolling down
    {


        if(habInternalY1 > 599)
        {
            habInternalY1 = -600;
        }
        if(habInternalY2 > 599)
        {
            habInternalY2 = -600;
        }

        habInternalY1-=player1.getPVelY();
        habInternalY2-=player1.getPVelY();
        std::cout<<"\n habY1: "<<habInternalY1<<", habY2: "<<habInternalY2;
        //std::cout<<"\n bikeBot: "<<station.bikeBot;
    }
    player1.move(countedFrames,station.collidable,station.interactable,station.STATIONS);
    station.updatePosition(habInternalY1);
    station.updatePositionHab2(habInternalY2);
}

void stage::setNewgameVars()
{
    std::cout<<"\n running stage::setNewgameVars()";
    player1.setX(380);
    player1.setY(260);
    habInternalY1 = 0;
    habInternalY2 = -600;
    //sets players starting needs at 100
    for(int i = 0; i < TOTAL_PLAYER_NEEDS; i++)
    {
        player1.need[i] = 100;
    }
    //externalView=true;
}


void stage::loadSavedGameData(Uint32 dataValues[])
{
    std::cout<<"\n running stage::loadSavedGameData(Uint32 dataValues[])";
    player1.setX(dataValues[0]);
    player1.setY(dataValues[1]);
    //load habitat Y1 and Y2 coords from safe file
    habInternalY1 = dataValues[2];
    habInternalY2 = dataValues[3];
}

void stage::handlePlanter(SDL_Renderer* renderer, TTF_Font* font)
{
    if(station.planterOptionsLoaded && !player1.interact)
    {//the player is no longer interacting with the planter,freeing the buttons
        station.freePlanterOptions();
    }
    if(!station.planterOptionsLoaded && player1.interact)
    {//player is interacting with the planter, loading the buttons
        station.loadInteractPlanter(renderer,font);
    }
    if(station.planterOptionsLoaded && player1.interact && station.interacted)
    {//player interacted with the planter, update the available options, planter texture.
        station.freePlanterOptions();
        station.loadInteractPlanter(renderer,font);
        station.interacted = false;
    }
}

void stage::loadTimeSurvivedTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running stage::loadTimeSurvivedTextures(SDL_Renderer* renderer)";

    int mS,hS,dS;
    mS = timeSurvived%60;
    hS = (timeSurvived/60)%24;
    dS = ((timeSurvived/60)/24);

    std::string mSurvived = std::to_string(mS);
    std::string hSurvived = std::to_string(hS);
    std::string dSurvived = std::to_string(dS);

    SDL_Color textColor = {255,255,255};//white
    if(!minutesSurvived.loadFromRenderedText(mSurvived.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render mSurvived string to minutesSurvived Texture!";
    }
    if(!hoursSurvived.loadFromRenderedText(hSurvived.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render hSurvived string to hoursSurvived Texture!";
    }
    if(!daysSurvived.loadFromRenderedText(dSurvived.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render dSurvived string to daysSurvived Texture!";
    }
}

void stage::renderTimeSurvivedTextTextures(SDL_Renderer* renderer)
{
    daysSurvived.render(420,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    hoursSurvived.render(420,25,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    minutesSurvived.render(420,50,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void stage::freeTimeSurvivedTextures()
{
    daysSurvived.free();
    hoursSurvived.free();
    minutesSurvived.free();
}

void stage::refreshTS(SDL_Renderer* renderer)
{
    freeTimeSurvivedTextures();
    std::cout<<"\n running stage::refreshTS(SDL_Renderer* renderer)";

    int mS,hS,dS;
    mS = timeSurvived%60;
    hS = (timeSurvived/60)%24;
    dS = ((timeSurvived/60)/24);

    std::string mSurvived = std::to_string(mS);
    std::string hSurvived = std::to_string(hS);
    std::string dSurvived = std::to_string(dS);

    SDL_Color textColor = {255,255,255};//white
    if(!minutesSurvived.loadFromRenderedText(mSurvived.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render mSurvived string to minutesSurvived Texture!";
    }
    if(!hoursSurvived.loadFromRenderedText(hSurvived.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render hSurvived string to hoursSurvived Texture!";
    }
    if(!daysSurvived.loadFromRenderedText(dSurvived.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render dSurvived string to daysSurvived Texture!";
    }
}
