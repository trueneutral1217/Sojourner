#include "stage.h"

stage::stage()
{
    internalView=false;
    externalView=true;
    showPlayer=false;
    habInternalY1=0;
    habInternalY2=-600;
    engInternalY1 = 0;
    engInternalY2 = -600;
    timeSurvived = 0;
    //player starts in habitation module
    inHab = true;
    //player does not start in engineering module
    inEng = false;

    buttonsFreed = true;

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
    bgFileName[4] = "images/engineering1.png";
    bgFileName[5] = "images/engineering2.png";

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
    ship.loadShip(renderer,font,player1.need);
    //ship.loadModule(renderer,font,ship.gauge);
    //station.loadStation(renderer,font,ship.gauge);
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
    //station.free();
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
        if(ship.habitation.planter.plantOkay)
        {
            //station.planterSown = true;
            ship.habitation.planter.waterPlantsOkay = true;
            ship.habitation.planter.plantOkay = false;
            ship.habitation.planter.loadPlanterTextTextures(renderer,font);

            ship.habitation.planter.planterDaysState = 0;
            ship.habitation.planter.planterState = 0;
            ship.habitation.planter.updatePlantTexture(renderer);
            //ship.habitation.planter.interacted = true;


            std::cout<<"\n plantOkay: "<<ship.habitation.planter.plantOkay;
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
    {//player clicked water
        //if it's okay to water the plants now
        if(ship.habitation.planter.waterPlantsOkay)
        {
            ship.habitation.planter.waterPlantsOkay = false;
            ship.habitation.planter.loadPlanterTextTextures(renderer,font);
            ship.habitation.planter.updatePlantTexture(renderer);
            ship.habitation.planter.planterTimeWatered = timeSurvived;
            //ship.habitation.planter.interacted = true;
            std::cout<<"\n waterPlantsOkay: "<<ship.habitation.planter.waterPlantsOkay;
            //player watered the plants, which takes 30 minutes
            timeSurvived +=30;
            refreshTS(renderer);
            //health physique hunger slumber morale
            //temporary numbers (need balancing later)
            int water[TOTAL_PLAYER_NEEDS] = {0,-5,-5,-5,-5};
            player1.modifyNeeds(water);
            player1.reloadNeedsTextures(renderer,font);
            int waterDecrement[6] = {0,0,0,-2,0,0};
            ship.modifyGauges(waterDecrement);
            ship.reloadGaugesTextures(renderer,font);
            //reloading text texture for water tank level
            ship.habitation.waterTank.loadWaterTank(renderer,font,ship.gauge[3]);
            //image needs to be refreshed with new texture.
            //station.planterTexture = station.planterSownWateredTexture;
        }
    }
    else if(buttonClicked == 5)
    {//player clicked harvest
        if(ship.habitation.planter.harvestOkay)
        {//update flags.
            ship.habitation.planter.plantOkay = true;
            ship.habitation.planter.waterPlantsOkay = false;
            ship.habitation.planter.harvestOkay = false;
            //this updates the buttons based on the availability of the above options.
            ship.habitation.planter.loadPlanterTextTextures(renderer,font);
            //-1 is a special state the planter returns to after harvest: not sown or watered.
            ship.habitation.planter.planterState = -1;
            //update the texture of the planter station to the unsown/unwatered texture
            ship.habitation.planter.updatePlantTexture(renderer);
            //interacted variable may be deprecated... remove?
            //ship.habitation.planter.interacted = true;
            //takes 1 hour to harvest the plants.  update the TimeSurvived text texture to reflect this.
            timeSurvived +=60;
            refreshTS(renderer);
            //health physique hunger slumber morale
            //temporary numbers (need balancing later)
            int harvest[TOTAL_PLAYER_NEEDS] = {0,-10,-10,-10,-10};
            player1.modifyNeeds(harvest);
            player1.reloadNeedsTextures(renderer,font);

        }

    }
    else if(buttonClicked == 6)
    {//player clicked sleep
        if(player1.need[3] != 100)
        {
            //if player's slumber value is less than 100, modify and refresh needs from bed use.
            int slumberBag[TOTAL_PLAYER_NEEDS] = {0,-33,-33,100,-33};
            player1.modifyNeeds(slumberBag);
            ship.habitation.bed.loadBedTextTextures(renderer,font,player1.need[3]);
            player1.reloadNeedsTextures(renderer,font);
            //8 hours passed from sleeping
            timeSurvived +=480;
            ship.habitation.planter.updatePlant(renderer,timeSurvived);

            refreshTS(renderer);
        }
    }
    else if(buttonClicked == 7)
    {
        if(player1.need[2] != 100)
        {
            //if player's hunger value is less than 100, modify and refresh needs from kitchen use.
            int kitchen[TOTAL_PLAYER_NEEDS] = {0,-5,100,-2,0};
            player1.modifyNeeds(kitchen);
            ship.habitation.kitchen.loadKitchenTextTextures(renderer,font,player1.need[2]);
            player1.reloadNeedsTextures(renderer,font);
            //8 hours passed from sleeping
            timeSurvived +=30;
            ship.habitation.planter.updatePlant(renderer, timeSurvived);
            refreshTS(renderer);
        }
    }
    else if(buttonClicked == 8)
    {//heal button clicked
        if(player1.need[0] != 100)
        {
            //if player's hunger value is less than 100, modify and refresh needs from kitchen use.
            int infirm[TOTAL_PLAYER_NEEDS] = {100,-5,-5,-5,-5};
            player1.modifyNeeds(infirm);
            ship.habitation.infirmary.loadInfirmaryTextTextures(renderer,font,player1.need[0]);
            player1.reloadNeedsTextures(renderer,font);
            //8 hours passed from sleeping
            timeSurvived +=60;
            ship.habitation.planter.updatePlant(renderer, timeSurvived);
            refreshTS(renderer);
        }
    }
    else if(buttonClicked == 9)
    {//exercise button clicked
        if(player1.need[1] != 100)
        {
            //if player's physique value is less than 100, modify and refresh needs from bike use.
            int bike[TOTAL_PLAYER_NEEDS] = {0,100,-5,-5,-5};
            player1.modifyNeeds(bike);
            ship.habitation.bike.loadBikeTextTextures(renderer,font,player1.need[1]);
            player1.reloadNeedsTextures(renderer,font);
            //2 hours passed from exercising
            timeSurvived +=120;
            ship.habitation.planter.updatePlant(renderer, timeSurvived);
            refreshTS(renderer);
        }
    }
    else if(buttonClicked == 10)
    {//relax button clicked
        if(player1.need[4] != 100)
        {
            //if player's hunger value is less than 100, modify and refresh needs from kitchen use.
            int recreation[TOTAL_PLAYER_NEEDS] = {0,-5,-5,-5,100};
            player1.modifyNeeds(recreation);
            ship.habitation.recreation.loadRecTextTextures(renderer,font,player1.need[4]);
            player1.reloadNeedsTextures(renderer,font);
            //1 hours passed from R&R
            timeSurvived +=60;
            ship.habitation.planter.updatePlant(renderer, timeSurvived);
            refreshTS(renderer);
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
    //std::cout<<"\n interactPlanter: "<<player1.interactPlanter;
    if(player1.interact && buttonsFreed)
    {
        if(player1.interactPlanter)
        {
            std::cout<<"\n creating planter buttons";
            buttons[1].buttonTexture = ship.habitation.planter.plantTexture;
            buttons[1].buttonName = "plant";
            buttons[1].setPosition(player1.getX()+50,player1.getY()-20);

            buttons[2].buttonTexture = ship.habitation.planter.waterPlantsTexture;
            buttons[2].buttonName = "waterPlants";
            buttons[2].setPosition(player1.getX()+50,player1.getY());

            buttons[3].buttonTexture = ship.habitation.planter.harvestTexture;
            buttons[3].buttonName = "harvest";
            buttons[3].setPosition(player1.getX()+50,player1.getY()+20);

            buttonsFreed = false;
        }
        //std::cout<<"\n interactBed: "<<player1.interactBed;
        if(player1.interactBed)
        {
            std::cout<<"\n creating bed buttons";
            buttons[4].buttonTexture = ship.habitation.bed.sleepTexture;
            buttons[4].buttonName = "sleep";
            buttons[4].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }

        if(player1.interactKitchen)
        {
            std::cout<<"\n creating kitchen buttons";
            buttons[5].buttonTexture = ship.habitation.kitchen.eatTexture;
            buttons[5].buttonName = "eat";
            buttons[5].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }

        if(player1.interactInfirmary)
        {
            std::cout<<"\n creating infirmary buttons";
            buttons[6].buttonTexture = ship.habitation.infirmary.healTexture;
            buttons[6].buttonName = "heal";
            buttons[6].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }

        if(player1.interactBike)
        {
            std::cout<<"\n creating bike buttons";
            buttons[7].buttonTexture = ship.habitation.bike.exerciseTexture;
            buttons[7].buttonName = "exercise";
            buttons[7].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed=false;
        }

        if(player1.interactRec)
        {
            std::cout<<"\n creating Rec buttons";
            buttons[8].buttonTexture = ship.habitation.recreation.relaxTexture;
            buttons[8].buttonName = "relax";
            buttons[8].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }
    }

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

void stage::freeStationButtons()
{
    std::cout<<"\n running stage::freeStationButtons()";
    for(int i = 1; i<TOTAL_STAGE_BUTTONS; i++)
    {
        buttons[i].free();
    }
    ship.habitation.planter.stationOptionsLoaded = false;
    ship.habitation.bed.stationOptionsLoaded = false;
    ship.habitation.kitchen.stationOptionsLoaded = false;
    ship.habitation.infirmary.stationOptionsLoaded = false;
    ship.habitation.bike.stationOptionsLoaded = false;
    ship.habitation.recreation.stationOptionsLoaded =false;
    buttonsFreed = true;
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
        if(inHab)
        {
            habInternalHandleParallax(renderer);
        }
        else if(inEng)
        {
            engInternalHandleParallax(renderer);
        }
    }
    //renders station, then renders player, because station is in front of player (station closer to bottom screen)
    if(internalView)
    {//this will have to be broken up a little, it should probably be renderHabStationBehindPlayer, but maybe I will
        //alter it in the function.
        if(inHab)
        {
            ship.habitation.waterTank.renderHabStationBehindPlayer(renderer,player1.playerBot);
            ship.habitation.planter.renderHabStationBehindPlayer(renderer,player1.playerBot);
            ship.habitation.infirmary.renderHabStationBehindPlayer(renderer,player1.playerBot);
            ship.habitation.kitchen.renderHabStationBehindPlayer(renderer,player1.playerBot);
            ship.habitation.recreation.renderHabStationBehindPlayer(renderer,player1.playerBot);
            ship.habitation.bike.renderHabStationBehindPlayer(renderer,player1.playerBot);
            ship.habitation.bed.renderHabStationBehindPlayer(renderer,player1.playerBot);

        }
        if(inEng)
        {
            ship.engineering.engExit.renderEngStationBehindPlayer(renderer,player1.playerBot);
        }
    }
    if(showPlayer)
    {//player is shown if internalView is on.
        player1.render(renderer);
        if(inHab)
        {
            ship.habitation.waterTank.renderHabStationFrontPlayer(renderer,player1.playerBot);
            ship.habitation.planter.renderHabStationFrontPlayer(renderer,player1.playerBot);
            ship.habitation.infirmary.renderHabStationFrontPlayer(renderer,player1.playerBot);
            ship.habitation.kitchen.renderHabStationFrontPlayer(renderer,player1.playerBot);
            ship.habitation.recreation.renderHabStationFrontPlayer(renderer,player1.playerBot);
            ship.habitation.bike.renderHabStationFrontPlayer(renderer,player1.playerBot);
            ship.habitation.bed.renderHabStationFrontPlayer(renderer,player1.playerBot);
            //interact is user pressed 'e', inRange is player collision with interactable station
            if(player1.interact)
            {
                if(player1.interactWaterTank)
                {
                    ship.habitation.waterTank.renderInteractStation(renderer,player1.getX(),player1.getY());
                }

                if(player1.interactBed)
                {
                    ship.habitation.bed.renderInteractBed(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactPlanter)
                {
                    ship.habitation.planter.renderInteractPlanter(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactKitchen)
                {
                    ship.habitation.kitchen.renderInteractKitchen(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactInfirmary)
                {
                    ship.habitation.infirmary.renderInteractInfirmary(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactBike)
                {
                    ship.habitation.bike.renderInteractBike(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactRec)
                {
                    ship.habitation.recreation.renderInteractRec(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactHabExit)
                {
                    if(inHab)
                    {
                        player1.setX(0);
                        inHab = false;
                        inEng = true;
                        std::cout<<"\n player1.interactHabExit = "<<player1.interactHabExit;
                        std::cout<<"\n inHab = "<<inHab<<" inEng = "<<inEng;
                    }
                }
            }
        }
        if(inEng)
        {
            ship.engineering.engExit.renderEngStationFrontPlayer(renderer,player1.playerBot);

            //interact is user pressed 'e', inRange is player collision with interactable station
            if(player1.interact)
            {
                if(player1.interactEngExit)
                {
                    if(inEng)
                    {
                        player1.setX(750);
                        inHab = true;
                        inEng = false;
                        std::cout<<"\n player1.interactEngExit = "<<player1.interactEngExit;
                        std::cout<<"\n inHab = "<<inHab<<" inEng = "<<inEng;
                    }
                }
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

void stage::engInternalHandleParallax(SDL_Renderer* renderer)
{
    stage1BG[4].render(0,engInternalY1,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    stage1BG[5].render(0,engInternalY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void stage::move(int countedFrames)
{
    //std::cout<<"\n running stage::move(int countedFrames)";
    if( player1.getY() == 360 && player1.getPVelY() > 0 )
    {//player is heading down after hitting lower threshold.
        if(inHab)
        {
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
        }
        else if(inEng)
        {
            //y value of hab background continues to decrease as it moves up the screen
            if(engInternalY1 < -599)//if hab y value is -600 or less, reset hab background position to bottom of screen
            {
                engInternalY1 = 600;
            }
            if(engInternalY2 < -599)
            {
                engInternalY2 = 600;
            }

            engInternalY1-=player1.getPVelY();
            engInternalY2-=player1.getPVelY();
        }

        //std::cout<<"\n habY1: "<<habInternalY1<<", habY2: "<<habInternalY2;
    }
    if(player1.getY()==160 && player1.getPVelY()<0)//player is heading up,bg scrolling down
    {

        if(inHab)
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
        }
        else if(inEng)
        {
            if(engInternalY1 > 599)
            {
                engInternalY1 = -600;
            }
            if(engInternalY2 > 599)
            {
                engInternalY2 = -600;
            }

            engInternalY1-=player1.getPVelY();
            engInternalY2-=player1.getPVelY();
        }
    }

    player1.move(countedFrames,ship,inHab,inEng);
    if(inHab)
    {
        //first habitat background
        ship.habitation.waterTank.updateHabPosition(habInternalY1);
        ship.habitation.kitchen.updateHabPosition(habInternalY1);
        ship.habitation.infirmary.updateHabPosition(habInternalY1);
        ship.habitation.planter.updateHabPosition(habInternalY1);
        ship.habitation.bed.updateHabPosition(habInternalY1);
        ship.habitation.habExit.updateHabPosition(habInternalY1);
        //second habitat background
        ship.habitation.bike.updateHabPosition2(habInternalY2);
        ship.habitation.recreation.updateHabPosition2(habInternalY2);
    }
    else if(inEng)
    {
        ship.engineering.engExit.updateEngPosition(engInternalY1);
        //going to keep the line below for reference when I start creating the engineering stations
        //ship.engineering.engExit.updateEngPosition2(engInternalY2);
    }
}

void stage::setNewgameVars()
{
    std::cout<<"\n running stage::setNewgameVars()";
    player1.setX(380);
    player1.setY(260);
    habInternalY1 = 0;
    habInternalY2 = -600;
    engInternalY1 = 0;
    engInternalY2 = -600;
    //sets players starting needs at 100
    for(int i = 0; i < TOTAL_PLAYER_NEEDS; i++)
    {
        player1.need[i] = 100;
    }
    //set ship's starting gauges at 100
    for(int i=0; i<TOTAL_SHIP_GAUGES; i++)
    {
        ship.gauge[i] = 100;
    }
}


void stage::loadSavedGameData(Uint32 dataValues[])
{
    std::cout<<"\n running stage::loadSavedGameData(Uint32 dataValues[])";
    player1.setX(dataValues[0]);
    player1.setY(dataValues[1]);
    //load habitat Y1 and Y2 coords from save file
    habInternalY1 = dataValues[2];
    habInternalY2 = dataValues[3];
    //load engineering Y1 & Y2 values from save file
    engInternalY1 = dataValues[4];
    engInternalY2 = dataValues[5];
}

void stage::handleStation(SDL_Renderer* renderer, TTF_Font* font)
{
    //I want more abstraction
    //buttons aren't rendering again after being freed then recreated... sometimes
    //player1.interact is always true when this is running
    if(buttonsFreed)
    {
        if(player1.interactPlanter && !ship.habitation.planter.stationOptionsLoaded)
        {
            ship.habitation.planter.loadPlanterTextTextures(renderer,font);
        }
        if(player1.interactBed && !ship.habitation.bed.stationOptionsLoaded)
        {
            ship.habitation.bed.loadBedTextTextures(renderer,font,player1.need[3]);
        }
        if(player1.interactKitchen && !ship.habitation.kitchen.stationOptionsLoaded)
        {
            ship.habitation.kitchen.loadKitchenTextTextures(renderer,font,player1.need[2]);
        }
        if(player1.interactInfirmary && !ship.habitation.infirmary.stationOptionsLoaded)
        {
            ship.habitation.infirmary.loadInfirmaryTextTextures(renderer,font,player1.need[0]);
        }
        if(player1.interactBike && !ship.habitation.bike.stationOptionsLoaded)
        {
            ship.habitation.bike.loadBikeTextTextures(renderer,font,player1.need[1]);
        }
        if(player1.interactRec && !ship.habitation.recreation.stationOptionsLoaded)
        {
            ship.habitation.recreation.loadRecTextTextures(renderer,font,player1.need[4]);
        }
    }

}

void stage::loadTimeSurvivedTextures(SDL_Renderer* renderer)
{
    std::cout<<"\n running stage::loadTimeSurvivedTextures(SDL_Renderer* renderer)";
    //minutes, hours, days survived
    int mS,hS,dS;
    //time survived is an int that keeps getting increased by minutes
    mS = timeSurvived%60;
    hS = (timeSurvived/60)%24;
    dS = ((timeSurvived/60)/24);

    //strings created for the UI at the top center of stage screen
    std::string mSurvived = std::to_string(mS);
    std::string hSurvived = std::to_string(hS);
    std::string dSurvived = std::to_string(dS);

    //the text textures for mins, hrs, & days survived
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
{//renders the text textures for the mins,hrs, and days survived
    daysSurvived.render(420,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    hoursSurvived.render(420,25,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    minutesSurvived.render(420,50,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

void stage::freeTimeSurvivedTextures()
{//frees the text textures for mins, hrs, and days survived
    daysSurvived.free();
    hoursSurvived.free();
    minutesSurvived.free();
}

void stage::refreshTS(SDL_Renderer* renderer)
{//if time survived is increased, the new values for mins,hrs, and days need to be reloaded from ints to strings
    //to textures
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
