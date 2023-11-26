#include "module.h"

module::module()
{

}

module::~module()
{

}

void module::loadModule(SDL_Renderer* renderer,TTF_Font* font,int gauge[])
{
    station.loadStation(renderer,font,gauge);
}

void module::free()
{
    station.free();
}
