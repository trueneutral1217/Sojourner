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

void stage::loadOpeningSequence(SDL_Renderer* renderer)
{
    std::cout<<"\n running stage::loadOpeningSequence(SDL_Renderer* renderer)";
    //going to need the font for the opening sequence
    loadFont();
    //loading images for opening sequence
    openingSequenceHouse.loadFromFile("images/openingSequenceHouse.png",renderer);
    openingSequenceNewspaper.loadFromFile("images/newsPaper.png",renderer);
    openingSequenceShip.loadFromFile("images/backyardShip.png",renderer);

    door.loadFromFile("images/door.png",renderer);
    obscure.loadFromFile("images/obscure.png",renderer);
    ramp.loadFromFile("images/ramp.png",renderer);

    ascension.loadFromFile("images/ascensionBG.png",renderer);
    cloud.loadFromFile("images/cloud.png",renderer);
    liftOffShip.loadFromFile("images/liftOffShip.png",renderer);


    inHab = false;
    inEng = false;

    SDL_Color textColor = {255,255,255};//white

    newspaper = "Maybe I should check the newspaper? (press 'e')";

    if(!newspaperTexture.loadFromRenderedText(newspaper.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render newspaper string to newspaperTexture!";
    }

    iDontWantToLiveOnThisPlanetAnymore = "I don't want to live on this planet anymore.";

    if(!iDontWantToLiveOnThisPlanetAnymoreTexture.loadFromRenderedText(iDontWantToLiveOnThisPlanetAnymore.c_str(), textColor,font,renderer))
    {
        std::cout<<"\n unable to render idontwanttoliveonthisplanetanymore string to idontwanttoliveonthisplanetanymoreTexture!";
    }

    backyard = "Time to head to the backyard.";

    if(!backyardTexture.loadFromRenderedText(backyard.c_str(),textColor,font,renderer))
    {
        std::cout<<"\n unable to render backyard string to backyardTexture!";
    }

    gtfo = "I'm getting the fuck out of here.";

    if(!gtfoTexture.loadFromRenderedText(gtfo.c_str(),textColor,font,renderer))
    {
        std::cout<<"\n unable to render gtfo string to gtfoTexture!";
    }

    //setting up interaction box for newspaper
    newspaperInteraction.x = 470;
    newspaperInteraction.y = 525;
    newspaperInteraction.w = 165;
    newspaperInteraction.h = 75;

    backdoorInteraction.x = 210;
    backdoorInteraction.y = 430;
    backdoorInteraction.w = 50;
    backdoorInteraction.h = 120;

    //X is hardcoded, so it can be removed (doorX, rampX)
    doorX = 331;
    doorY = 166;
    rampX = 338;
    rampY = 503;

    iterations = 62;
    iterations2 = 170;

    paperRead = false;
    inBackyard = false;
    backyardFree = false;

    paperOpen = false;
    //this tells loadPlayer below to load regular earth clothes
    player1.inSpace = false;
    //load player texture
    player1.loadPlayer(renderer);

    player1.setX(750);
    player1.setY(420);

    openingSequenceTimer.start();

    camera.x = 0;
    camera.y = 1200;
    camera.w = 800;
    camera.y = 600;

    ascensionY = -1200;

    cloudY = 200;
    cloudY2 = -300;

    complete = false;

}

bool stage::loadStage(SDL_Renderer* renderer, bool inHab, bool inEng, bool success)
{
    std::cout<<"\n running stage::loadStage(SDL_Renderer* renderer, bool inHab, bool inEng, bool success)";
    //stage file names get set and loaded into texture arrays, player gets loaded from player class.
    setButtonNames();
    //updates font to stage font.
    loadFont();
    //load stage button textures and positions
    success = setStageButtonTextures(renderer,success);
    //set stage bg texture
    success = setStageTextures(renderer);

    loadTimeSurvivedTextures(renderer);
    //loading the player might need an if statement based on whether a newgame is started or
    //user is loading a save file.

    //this tells loadplayer below to load the player's space clothes.
    player1.inSpace = true;
    //load player texture
    player1.loadPlayer(renderer);

    //loads needs text textures for UI.
    player1.loadNeedsTextures(renderer,font);
    //when loading from save, the colors of the text textures needs to be set, so reloadneedstextures needs to run
    player1.reloadNeedsTextures(renderer,font);
    if(inHab)
    {
        ship.loadHabitationModule(renderer,font,player1.need);
    }
    else if(inEng)
    {
        ship.loadEngineeringModule(renderer,font,player1.need);
    }

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

void stage::freeOpeningSequence()
{//only frees the house part of the opening sequence
    std::cout<<"\n running stage::freeOpeningSequence()";
    newspaperTexture.free();
    openingSequenceHouse.free();
    openingSequenceNewspaper.free();
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
        if(ship.habitation.planter.buttonAvailable[0])
        {
            ship.habitation.planter.buttonAvailable[1] = true;
            ship.habitation.planter.buttonAvailable[0] = false;
            ship.habitation.planter.loadStationButtonTextTextures(renderer,font);
            ship.habitation.planter.planterDaysState = 0;
            ship.habitation.planter.planterState = 0;
            ship.habitation.planter.updatePlantTexture(renderer);
            std::cout<<"\n plantOkay: "<<ship.habitation.planter.buttonAvailable[0];
            timeSurvived += 30;
            refreshTS(renderer);
            //see plant watering section below for notes about this.
            int plant[TOTAL_PLAYER_NEEDS] = {0,-5,-5,-5,-5};
            player1.modifyNeeds(plant);
            player1.reloadNeedsTextures(renderer,font);
        }
    }
    else if(buttonClicked == 4)
    {//player clicked water
        //if it's okay to water the plants now
        if(ship.habitation.planter.buttonAvailable[1])
        {
            ship.habitation.planter.buttonAvailable[1] = false;
            ship.habitation.planter.loadStationButtonTextTextures(renderer,font);
            ship.habitation.planter.updatePlantTexture(renderer);
            ship.habitation.planter.planterTimeWatered = timeSurvived;
            std::cout<<"\n waterPlantsOkay: "<<ship.habitation.planter.buttonAvailable[1];
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
        }
    }
    else if(buttonClicked == 5)
    {//player clicked harvest
        if(ship.habitation.planter.buttonAvailable[2])
        {//update flags.
            ship.habitation.planter.buttonAvailable[0]=true;
            ship.habitation.planter.buttonAvailable[1]=false;
            ship.habitation.planter.buttonAvailable[2]=false;
            //this updates the buttons based on the availability of the above options.
            ship.habitation.planter.loadStationButtonTextTextures(renderer,font);
            //-1 is a special state the planter returns to after harvest: not sown or watered.
            ship.habitation.planter.planterState = -1;
            //update the texture of the planter station to the unsown/unwatered texture
            ship.habitation.planter.updatePlantTexture(renderer);
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
            ship.habitation.bed.loadStationButtonTextTextures(renderer,font,player1.need[3]);
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
            ship.habitation.kitchen.loadStationButtonTextTextures(renderer,font,player1.need[2]);
            player1.reloadNeedsTextures(renderer,font);
            //half an hour passed from eating
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
            ship.habitation.infirmary.loadStationButtonTextTextures(renderer,font,player1.need[0]);
            player1.reloadNeedsTextures(renderer,font);
            //60 mis passed from healing
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
            ship.habitation.bike.loadStationButtonTextTextures(renderer,font,player1.need[1]);
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
            ship.habitation.recreation.loadStationButtonTextTextures(renderer,font,player1.need[4]);
            player1.reloadNeedsTextures(renderer,font);
            //1 hours passed from R&R
            timeSurvived +=60;
            ship.habitation.planter.updatePlant(renderer, timeSurvived);
            refreshTS(renderer);
        }
    }
    else if(buttonClicked == 11)
    {
        std::cout<<"\n research button action should happen here.";
    }
    else if(buttonClicked == 12)
    {//player clicked 'inventory' button at the cargo area station
        std::cout<<"\n should display ship's inventory";
        freeStationButtons();
        ship.engineering.cargoArea.loadStationButtonTextTextures(renderer,font);
        if(!ship.engineering.cargoArea.inventoryDisplaying)
        {
            ship.engineering.cargoArea.inventoryDisplaying = true;
            std::cout<<"\n creating close inventory button";
            buttons[11].buttonTexture.loadFromFile("images/buttons/inventoryClose.png",renderer);
            buttons[11].buttonName = "closeInventory";
            buttons[11].setPosition(710,165);
            buttonsFreed = false;
        }
        std::cout<<"\n inventory displaying: "<<ship.engineering.cargoArea.inventoryDisplaying;
        //ship.engineering.cargoArea.displayInventory(renderer);
    }
    else if(buttonClicked == 13)
    {
        std::cout<<"\n should close ship's inventory";
        if(ship.engineering.cargoArea.inventoryDisplaying)
        {
            ship.engineering.cargoArea.inventoryDisplaying = false;
        }
    }
    else if(buttonClicked == 14)
    {
        //user clicked upgrade button for the bed
        std::cout<<"\n user clicked upgrade button";
    }
}

int stage::handleButtons(SDL_Renderer* renderer, SDL_Event* e )
{
    //std::cout<<"\n running stage::handleButtons( SDL_Event* e )";
    //player clicks mouse inside stage
    int buttonClicked = 0;
    //here's where buttons are created based on player interacting with a station
    //if they haven't been freed, don't recreate
    if(player1.interact && buttonsFreed)
    {
        if(player1.interactPlanter)
        {
            std::cout<<"\n creating planter buttons";
            buttons[1].buttonTexture = ship.habitation.planter.buttonTextTexture[0];
            buttons[1].buttonName = "plant";
            buttons[1].setPosition(player1.getX()+50,player1.getY()-20);

            buttons[2].buttonTexture = ship.habitation.planter.buttonTextTexture[1];
            buttons[2].buttonName = "waterPlants";
            buttons[2].setPosition(player1.getX()+50,player1.getY());

            buttons[3].buttonTexture = ship.habitation.planter.buttonTextTexture[2];
            buttons[3].buttonName = "harvest";
            buttons[3].setPosition(player1.getX()+50,player1.getY()+20);

            buttonsFreed = false;
        }
        if(player1.interactBed)
        {
            std::cout<<"\n creating bed buttons";
            buttons[4].buttonTexture = ship.habitation.bed.buttonTextTexture[0];
            buttons[4].buttonName = "sleep";
            buttons[4].setPosition(player1.getX()+50,player1.getY()-20);
            buttons[12].buttonTexture = ship.habitation.bed.buttonTextTexture[1];
            buttons[12].buttonName = "upgrade";
            buttons[12].setPosition(player1.getX()+50,player1.getY());
            buttonsFreed = false;
        }
        if(player1.interactKitchen)
        {
            std::cout<<"\n creating kitchen buttons";
            buttons[5].buttonTexture = ship.habitation.kitchen.buttonTextTexture[0];
            buttons[5].buttonName = "eat";
            buttons[5].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }
        if(player1.interactInfirmary)
        {
            std::cout<<"\n creating infirmary buttons";
            buttons[6].buttonTexture = ship.habitation.infirmary.buttonTextTexture[0];
            buttons[6].buttonName = "heal";
            buttons[6].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }
        if(player1.interactBike)
        {
            std::cout<<"\n creating bike buttons";
            buttons[7].buttonTexture = ship.habitation.bike.buttonTextTexture[0];
            buttons[7].buttonName = "exercise";
            buttons[7].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed=false;
        }

        if(player1.interactRec)
        {
            std::cout<<"\n creating Rec buttons";
            buttons[8].buttonTexture = ship.habitation.recreation.buttonTextTexture[0];
            buttons[8].buttonName = "relax";
            buttons[8].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }
        if(player1.interactResearchDesk)
        {
            std::cout<<"\n creating researchDesk buttons";
            buttons[9].buttonTexture = ship.engineering.researchDesk.buttonTextTexture[0];
            buttons[9].buttonName = "research";
            buttons[9].setPosition(player1.getX()+50,player1.getY()-20);
            buttonsFreed = false;
        }
        if(player1.interactCargoArea)
        {
            std::cout<<"\n creating cargoArea buttons";
            buttons[10].buttonTexture = ship.engineering.cargoArea.buttonTextTexture[0];
            buttons[10].buttonName = "inventory";
            buttons[10].setPosition(player1.getX()+50,player1.getY()-20);
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
    ship.engineering.researchDesk.stationOptionsLoaded = false;
    ship.engineering.cargoArea.stationOptionsLoaded = false;
    buttonsFreed = true;
}

void stage::renderOpeningSequence(SDL_Renderer* renderer)
{
    //renders house background
    openingSequenceHouse.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    //renders player on top of house background
    if(!backdoorInteracted)
    {
        player1.render(renderer);
    }

    //renders text texture saying "maybe I should read the newspaper
    if(openingSequenceTimer.getTicks() < 3000 && openingSequenceTimer.isStarted() && !paperRead)
    {//this is just a text texture
        newspaperTexture.render(150,player1.getY()-20,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    else if(openingSequenceTimer.getTicks() >= 3000 && !paperRead)
    {
        openingSequenceTimer.stop();
    }

    //if user presses 'e' button
    if(player1.interact)
    {//newspaper renders
        if(paperRead)
        {
            if(player1.interactBackdoor)
            {
                //this is where the transition to the backyard happens.
                std::cout<<"\n backDoor interacted";
                freeHouse();
                backdoorInteracted = true;
                inBackyard = true;
                player1.setX(380);
                player1.setY(520);
            }
        }
        if(player1.interactNewspaper)
        {
            if(paperOpen)
            {
                paperOpen = false;
                paperRead = true;
                openingSequenceTimer.start();
                player1.interact = false;
            }
            else
            {
               paperOpen = true;
               player1.interact = false;
            }
            /*
            openingSequenceNewspaper.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            if(!paperRead)
            {
                paperRead = true;
                openingSequenceTimer.start();
            }*/
        }
    }
    if(paperOpen)
    {
        openingSequenceNewspaper.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(paperRead)
    {
        if(!player1.interact && !paperOpen)
        {
            if(openingSequenceTimer.getTicks() < 3000)
            {
                iDontWantToLiveOnThisPlanetAnymoreTexture.render(50,player1.getY() - 40,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
            if(openingSequenceTimer.getTicks() > 2000 && openingSequenceTimer.getTicks() < 5000)
            {
                backyardTexture.render(50,player1.getY()-20,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
    }
    if(backdoorInteracted)
    {

        openingSequenceShip.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        ramp.render(338,rampY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        obscure.render(338,405,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        if(!backyardFree)
        {
            player1.render(renderer);
        }
        door.render(doorX,doorY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        if(openingSequenceTimer.getTicks() < 3000)
        {
            gtfoTexture.render(50,player1.getY()-20,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        if(player1.getY() == 420)
        {//retract ramp, close door
            //make sure to re-enable movement later.
            player1.movementDisabled = true;
            if(openingSequenceTimer.getTicks() % 25 == 0 && iterations >= 0)
            {//raises the ramp until it's behind the obscure image (gives the illusion of the ramp being retracted)
                rampY--;
                iterations--;
            }
            if(openingSequenceTimer.getTicks() %25 == 0 && iterations2 >=0)
            {//lowers the door over the character
                doorY++;
                iterations2--;
            }
        }
        if(iterations <= 0 && iterations2 <= 0)
        {
            //time to fly
            if(!backyardFree)
            {
                freeBackyard();
                backyardFree = true;
                player1.movementDisabled = false;
                player1.inSpace = true;
            }

            ascension.render(0,ascensionY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(50,cloudY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(400,cloudY-25,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(450,cloudY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(100,cloudY2,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            liftOffShip.render(300,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(150,cloudY-600,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(250,cloudY-250,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(25,cloudY2-300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            cloud.render(500,cloudY2+150,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);


            if(openingSequenceTimer.getTicks() %10 == 0 && ascensionY <=0)
            {
                ascensionY++;
                cloudY++;
                cloudY2++;
            }
            if(ascensionY >= 0 && complete == false)
            {
                freeSky();
                complete = true;
                //set gamestate = 5 at this point.
            }
        }
    }
}

void stage::resetOpeningSequenceVariables()
{
    std::cout<<"\n running stage::resetOpeningSequenceVariables()";
    complete = false;
    backdoorInteracted = false;
    paperRead = false;
    inBackyard = false;
    openingSequenceTimer.stop();
    doorX = 331;
    doorY = 166;
    rampX = 338;
    rampY = 503;
    iterations = 62;
    iterations2 = 170;
    inHab = true;
}

void stage::freeHouse()
{
    std::cout<<"\n running stage::freeHouse()";
    //frees up the resources from the house portion of the opening sequence.
iDontWantToLiveOnThisPlanetAnymoreTexture.free();
openingSequenceTimer.restart();
openingSequenceNewspaper.free();
newspaperTexture.free();
openingSequenceHouse.free();
newspaperInteraction.x = 0;
newspaperInteraction.y = 0;
newspaperInteraction.w = 0;
newspaperInteraction.h = 0;
backdoorInteraction.x = 0;
backdoorInteraction.y = 0;
backdoorInteraction.w = 0;
backdoorInteraction.h = 0;

}

void stage::freeBackyard()
{
    std::cout<<"\n running stage::freeBackyard()";
    backyardTexture.free();
    openingSequenceShip.free();
    gtfoTexture.free();
    door.free();
    obscure.free();
    ramp.free();
}

void stage::freeSky()
{
    std::cout<<"\n running stage::freeSky()";
    ascension.free();
    cloud.free();
    liftOffShip.free();
}

void stage::renderStage1(SDL_Renderer* renderer)
{//while stage scene is running this displays bgs,buttons,stations,UI, and player with updated positions.
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
            //engExit is invisible, so the line below is just what should be added for visible stations.
            ship.engineering.batteryArray.renderEngStationBehindPlayer(renderer,player1.playerBot);
            ship.engineering.researchDesk.renderEngStationBehindPlayer(renderer,player1.playerBot);
            ship.engineering.engineStation.renderEngStationBehindPlayer(renderer,player1.playerBot);
            ship.engineering.cargoArea.renderEngStationBehindPlayer(renderer,player1.playerBot);
            ship.engineering.commStation.renderEngStationBehindPlayer(renderer,player1.playerBot);
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
                    ship.habitation.bed.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactRec)
                {
                    ship.habitation.recreation.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactBike)
                {
                    ship.habitation.bike.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactInfirmary)
                {
                    ship.habitation.infirmary.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactKitchen)
                {
                    ship.habitation.kitchen.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactPlanter)
                {
                    ship.habitation.planter.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactHabExit)
                {
                    if(inHab)
                    {
                        player1.interactHabExit = false;
                        player1.setX(60);
                        inHab = false;
                        inEng = true;
                        ship.habitation.freeHab();
                        ship.loadEngineeringModule(renderer,font,player1.need);
                        std::cout<<"\n player1.interactHabExit = "<<player1.interactHabExit;
                        std::cout<<"\n inHab = "<<inHab<<" inEng = "<<inEng;
                    }
                }
            }
        }
        if(inEng)
        {
            //engExit should be invisible, which means the line below is pointless.
            ship.engineering.batteryArray.renderEngStationFrontPlayer(renderer,player1.playerBot);
            ship.engineering.researchDesk.renderEngStationFrontPlayer(renderer,player1.playerBot);
            ship.engineering.engineStation.renderEngStationFrontPlayer(renderer,player1.playerBot);
            ship.engineering.cargoArea.renderEngStationFrontPlayer(renderer,player1.playerBot);
            ship.engineering.commStation.renderEngStationFrontPlayer(renderer,player1.playerBot);
            //interact is user pressed 'e', inRange is player collision with interactable station
            if(player1.interact)
            {
                if(player1.interactEngExit)
                {
                    player1.interactEngExit = false;
                    player1.setX(720);
                    inHab = true;
                    inEng = false;
                    ship.engineering.freeEng();
                    ship.loadHabitationModule(renderer,font,player1.need);
                    std::cout<<"\n player1.interactEngExit = "<<player1.interactEngExit;
                    std::cout<<"\n inHab = "<<inHab<<" inEng = "<<inEng;
                }
                if(player1.interactBatteryArray)
                {
                    ship.engineering.batteryArray.renderInteractStation(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactResearchDesk)
                {
                    ship.engineering.researchDesk.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactEngineStation)
                {
                    ship.engineering.engineStation.renderInteractStation(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactCargoArea)
                {
                    ship.engineering.cargoArea.renderInteractStationButtons(renderer,player1.getX(),player1.getY());
                }
                if(player1.interactCommStation)
                {
                    ship.engineering.commStation.renderInteractStation(renderer,player1.getX(),player1.getY());
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
        if(ship.engineering.cargoArea.inventoryDisplaying)
        {//there needs to be a button that displays on top of this image that toggles inventoryDisplaying
            ship.engineering.cargoArea.inventoryBG.render(50,150,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            //this is the button that closes the inventory
            buttons[11].buttonTexture.render(710,165,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            //display scrap text texture
            ship.inventory.scrap.itemTextTexture.render(100,200,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
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
    //SDL_Delay(10);
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
    if(inHab || inEng)
    {
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
        }
    }
    if(inHab || inEng)
    {
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
    }
    if(inHab || inEng)
    {
        player1.move(countedFrames,ship,inHab,inEng);
    }
    else
    {
        player1.move(countedFrames,newspaperInteraction,backdoorInteraction,inBackyard);
    }

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
        ship.engineering.batteryArray.updateEngPosition(engInternalY1);
        ship.engineering.researchDesk.updateEngPosition(engInternalY1);
        ship.engineering.engineStation.updateEngPosition(engInternalY1);
        ship.engineering.cargoArea.updateEngPosition(engInternalY1);
        ship.engineering.commStation.updateEngPosition(engInternalY1);
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
    //player1.interact is always true when this is running
    if(buttonsFreed)
    {
        if(player1.interactPlanter && !ship.habitation.planter.stationOptionsLoaded)
        {
            ship.habitation.planter.loadStationButtonTextTextures(renderer,font);
        }
        if(player1.interactBed && !ship.habitation.bed.stationOptionsLoaded)
        {
            ship.habitation.bed.loadStationButtonTextTextures(renderer,font,player1.need[3]);
        }
        if(player1.interactKitchen && !ship.habitation.kitchen.stationOptionsLoaded)
        {
            ship.habitation.kitchen.loadStationButtonTextTextures(renderer,font,player1.need[2]);
        }
        if(player1.interactInfirmary && !ship.habitation.infirmary.stationOptionsLoaded)
        {
            ship.habitation.infirmary.loadStationButtonTextTextures(renderer,font,player1.need[0]);
        }
        if(player1.interactBike && !ship.habitation.bike.stationOptionsLoaded)
        {
            ship.habitation.bike.loadStationButtonTextTextures(renderer,font,player1.need[1]);
        }
        if(player1.interactRec && !ship.habitation.recreation.stationOptionsLoaded)
        {
            ship.habitation.recreation.loadStationButtonTextTextures(renderer,font,player1.need[4]);
        }
        if(player1.interactResearchDesk && !ship.engineering.researchDesk.stationOptionsLoaded)
        {
            ship.engineering.researchDesk.loadStationButtonTextTextures(renderer,font);
        }
        if(player1.interactCargoArea && !ship.engineering.cargoArea.stationOptionsLoaded)
        {
            ship.engineering.cargoArea.loadStationButtonTextTextures(renderer,font);
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
