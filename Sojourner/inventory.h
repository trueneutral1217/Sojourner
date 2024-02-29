#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"

class inventory
{
    public:
		//constructor
		inventory();
		//deconstructor
        ~inventory();
        //initialize items
        item scrap,wood,plastic;
        //load inventory
        void loadInventory(SDL_Renderer* renderer, TTF_Font* font);

        void refreshInventory(SDL_Renderer* renderer, TTF_Font* font);

        private:

};

#endif // INVENTORY_H
