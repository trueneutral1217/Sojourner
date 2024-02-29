#ifndef ITEM_H
#define ITEM_H

#include "texture.h"

class item
{
    public:
		//constructor
		item();
		//deconstructor
        ~item();
        //the item's name
        std::string itemName;
        //the item's name and count put together (ie:  5 scrap)
        std::string itemNameAndCount;
        //the text texture of the item name
        Texture itemTextTexture;
        //the amount of the item in the inventory
        int itemCount;
        //brief description for items, to be used in text textures at inventory screen
        std::string itemDescription;
        //textTextures for itemDescriptions
        Texture itemDescriptionTextTexture;

        private:


};

#endif // ITEM_H
