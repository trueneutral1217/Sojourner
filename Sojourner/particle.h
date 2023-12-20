#ifndef PARTICLE_H
#define PARTICLE_H

#include "Texture.h"
#include "timer.h"

const int TOTAL_PARTICLES = 50;

const static int TOTAL_FRAMES = 5;

class Particle
{
	public:


        timer particleTimer;
		//Initialize position and animation
		void createParticle(SDL_Renderer* renderer);

		//~Particle();
		Texture star[TOTAL_FRAMES];

		//render particle textures to screen
		void render(SDL_Renderer* renderer, int renderColor, Texture star[]);

		//Checks if particle is dead
		bool isDead();

        int renderColor;

        void incrementFrame();


	private:
		//Offsets
		int partX, partY;

		//Current frame of animation
		int frame;

        //A rect to be filled
		//SDL_Rect fillRect;


};

#endif // PARTICLE_H
