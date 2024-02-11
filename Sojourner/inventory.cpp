#include "inventory.h"

inventory::inventory()
{

}

inventory::~inventory()
{

}

void inventory::loadInventory(SDL_Renderer* renderer, TTF_Font* font)
{
    std::cout<<"\n running inventory::loadInventory(SDL_Renderer* renderer, TTF_Font* font)";
    //set text color for text texture
    SDL_Color textColor = {255,255,255};//font white
    //this is a temporary value for scrap's itemCount
    scrap.itemCount = 5;
    scrap.itemName = "scrap";
    //create string for text texture
    scrap.itemNameAndCount = std::to_string(scrap.itemCount) + " " + scrap.itemName;
    //load string into text texture
    if(!scrap.itemTextTexture.loadFromRenderedText(scrap.itemNameAndCount,textColor,font,renderer))
    {
        std::cout<<"\n unable to load itemNameAndCount string to itemTextTexture";
    }
}
