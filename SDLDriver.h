#pragma once

#include "Particle.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

class SDLDriver {
	SDL_Surface *sdlScreen;
	SDL_TimerID sdlTimer;
	int width, height;
public:
	SDLDriver(int, int);
	~SDLDriver();
	void AddTimer(int, SDL_NewTimerCallback, void *);
	void RemoveTimer();
	void DrawParticle(const Particle *);
	void ClearScreen();
	void Draw();
	void WaitQuit();
	int getWidth() const { return width; };
	int getHeight() const { return height; }
};