#ifndef PARTICLE_H
#define PARTICLE_H

#include "Texture.h"

//Particle count
const int TOTAL_PARTICLES = 200;


class Particle
{
	public:

		//Initialize position and animation
		void createParticle(SDL_Renderer* renderer);

		//~Particle();
		//Shows the particle
		void render(SDL_Renderer* renderer, int renderColor);

		//Checks if particle is dead
		bool isDead();

        int renderColor;


	private:
		//Offsets
		int partX, partY;

		//Current frame of animation
		int frame;

        //A rect to be filled
		SDL_Rect fillRect;


};

#endif // PARTICLE_H
