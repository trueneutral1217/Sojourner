#include "Texture.h"

Texture::Texture()
{
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	//Deallocate

	free();
}
/*
bool Texture::initTexture(int SCREEN_WIDTH,int SCREEN_HEIGHT,SDL_Window* window,SDL_Renderer* renderer)
{
    //this may be able to be removed.  possible artifact.

    bool success = true;

		//Create window

			return success;
}*/

bool Texture::loadFromFile( std::string path,SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture = newTexture;
	return texture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText( std::string text, SDL_Color color,TTF_Font* font,SDL_Renderer* renderer)
{
	//clear old texture
	free();

	//Render text surface
	SDL_Surface* tSurface = TTF_RenderText_Solid( font, text.c_str(), color );
	if( tSurface != NULL )
	{
		//Create texture from surface
        texture = SDL_CreateTextureFromSurface( renderer, tSurface );
		if( texture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//set texture based on surface dimensions
			width = tSurface->w;
			height = tSurface->h;
		}

		//free temporary surface
		SDL_FreeSurface( tSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return texture != NULL;
}
#endif

void Texture::free()
{
	//Free texture if it exists
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( texture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( texture, blending );
}

void Texture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( texture, alpha );
}

void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* renderer )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

void Texture::timedRender(int ticks, int x, int y, Texture& tempTexture, SDL_Renderer* renderer)
{
    //still in progress
    timer tempTimer;
    tempTimer.start();
    if(ticks > tempTimer.getTicks())
    {
        tempTexture.render(x,y,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    else{
        tempTexture.free();
    }


}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}


SDL_Texture* loadTexture( std::string fileLocation,SDL_Renderer* renderer )
{
	SDL_Texture* texture = NULL;

	//Load image from fileLocation
	SDL_Surface* surface = IMG_Load( fileLocation.c_str() );
	if( surface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", fileLocation.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface
        texture = SDL_CreateTextureFromSurface( renderer, surface );
		if( texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", fileLocation.c_str(), SDL_GetError() );
		}

		//done with surface
		SDL_FreeSurface( surface );
	}

	return texture;
}
