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

        bool verified;
        //verification passphrase & inputted text texture
        Texture noRoboTextTexture;
        Texture inputTextTexture;
        //verification bg texture
        Texture verify;

        std::string foo;

        std::stringstream inputText;

        std::stringstream noRobo;

        void loadText(TTF_Font* font,SDL_Renderer* renderer);

        bool verifyNoRobo();

        void renderVerification(TTF_Font* font,SDL_Renderer* renderer);

        void free();


    private:

};

#endif // TEXT_H
