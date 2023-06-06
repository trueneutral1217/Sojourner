#ifndef TEXT_H
#define TEXT_H

#include "texture.h"

class text
{
    public:
        //constructor
        text();
        //destructor
        ~text();

        TTF_Font* font;

        void loadText(SDL_Renderer* renderer);

        void free();


    private:

};

#endif // TEXT_H
