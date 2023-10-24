#include "text.h"

text::text()
{
  //  verified = false;
    //inputText.str( "" );
    //noRobo.str("");
}

text::~text()
{

}

void text::loadText(SDL_Renderer* renderer)
{
    font = TTF_OpenFont( "fonts/PublicPixel-z84yD.ttf", 16 );
    font2 = TTF_OpenFont( "fonts/PublicPixel-z84yD.ttf", 12 );
    //Set text color as black
    //SDL_Color textColor = { 255, 255, 255, 0xFF };

    //Enable text input
    SDL_StartTextInput();
}

void text::loadNemoy(SDL_Renderer* renderer)
{
font = TTF_OpenFont( "fonts/", 12);
SDL_StartTextInput();
}

void text::free()
{
	TTF_CloseFont( font );
    font = NULL;
}
