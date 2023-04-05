#include "text.h"

text::text()
{
    verified = false;
    inputText.str( "" );
    noRobo.str("");
}

text::~text()
{

}

bool text::verifyNoRobo()
{
    if (inputText.str() == noRobo.str())
    {
        verified = true;
    }
    return verified;
}

void text::loadText(TTF_Font* font,SDL_Renderer* renderer)
{
    //verification background at beginning of chapter 3
    verify.loadFromFile("images/verify.png",renderer);
    //Set text color as black
    SDL_Color textColor = { 255, 255, 255, 0xFF };
    //the text to be verified
    noRobo.str("fuck capitalism");
    noRoboTextTexture.loadFromRenderedText( noRobo.str().c_str(),textColor,font,renderer );
    //Enable text input
    SDL_StartTextInput();
}

void text::renderVerification(TTF_Font* font,SDL_Renderer* renderer)
{
    verify.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    SDL_Color textColor = { 255, 255, 255 };
    if(inputText.str()!="")
    {
        inputTextTexture.loadFromRenderedText( inputText.str().c_str(), textColor,font,renderer );
    }
    noRoboTextTexture.render(150,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    if(inputText.str() != "")
    {
        inputTextTexture.render(150,370,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
}

void text::free()
{
    //free text background
    verify.free();
    //Free Text images
	noRoboTextTexture.free();
	inputTextTexture.free();
}
