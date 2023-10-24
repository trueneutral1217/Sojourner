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

        //16pt public pixel
        TTF_Font* font;
        //12pt public pixel
        TTF_Font* font2;

        void loadText(SDL_Renderer* renderer);

        void loadNemoy(SDL_Renderer* renderer);

        void free();


    private:

};

#endif // TEXT_H
