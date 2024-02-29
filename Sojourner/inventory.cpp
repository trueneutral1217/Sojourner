#include "inventory.h"

inventory::inventory()
{
    //this is a temporary value for scrap's itemCount
    //scrap.itemCount = 5;
    scrap.itemName = "scrap";
    wood.itemName = "wood";
    plastic.itemName = "plastic";

    scrap.itemDescription = "Most common station upgrade material.";
    wood.itemDescription = "Used as material in some stations.";
    plastic.itemDescription = "Occasionally used in station upgrades.";
}

inventory::~inventory()
{

}

void inventory::loadInventory(SDL_Renderer* renderer, TTF_Font* font)
{//creates text textures for inventory items.  rendered when player checks inventory at cargo station
    std::cout<<"\n running inventory::loadInventory(SDL_Renderer* renderer, TTF_Font* font)";
    //set text color for text texture
    SDL_Color textColor = {255,255,255};//font white

    //create string for text texture
    scrap.itemNameAndCount = std::to_string(scrap.itemCount) + " " + scrap.itemName;
    wood.itemNameAndCount = std::to_string(wood.itemCount) + " " + wood.itemName;
    plastic.itemNameAndCount = std::to_string(plastic.itemCount) + " " + plastic.itemName;
    //load string into text texture
    if(!scrap.itemTextTexture.loadFromRenderedText(scrap.itemNameAndCount,textColor,font,renderer))
    {
        std::cout<<"\n unable to load itemNameAndCount string to itemTextTexture (scrap)";
    }
    if(!wood.itemTextTexture.loadFromRenderedText(wood.itemNameAndCount,textColor,font,renderer))
    {
        std::cout<<"\n unable to load itemNameAndCount string to itemTextTexture (wood)";
    }
    if(!plastic.itemTextTexture.loadFromRenderedText(plastic.itemNameAndCount,textColor,font,renderer))
    {
        std::cout<<"\n unable to load itemNameAndCount string to itemTextTexture (plastic)";
    }
    if(!scrap.itemDescriptionTextTexture.loadFromRenderedText(scrap.itemDescription,textColor,font,renderer))
    {
        std::cout<<"\n unable to load scrap itemDescription to textTexture!";
    }
    if(!wood.itemDescriptionTextTexture.loadFromRenderedText(wood.itemDescription,textColor,font,renderer))
    {
        std::cout<<"\n unable to load wood itemDescription to textTexture!";
    }
    if(!plastic.itemDescriptionTextTexture.loadFromRenderedText(plastic.itemDescription,textColor,font,renderer))
    {
        std::cout<<"\n unable to load wood itemDescription to textTexture!";
    }
}

void inventory::refreshInventory(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running inventory::refreshInventory(SDL_Renderer* renderer,TTF_Font* font)";
    SDL_Color textColor = {255,255,255};//white
    scrap.itemNameAndCount = std::to_string(scrap.itemCount)+" "+scrap.itemName;
    if(!scrap.itemTextTexture.loadFromRenderedText(scrap.itemNameAndCount,textColor,font,renderer))
    {
        std::cout<<"\n unable to load itemNameAndCount string to itemTextTexture";
    }
}
