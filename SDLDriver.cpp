#include "SDLDriver.h"

SDLDriver::SDLDriver(int w, int h) {
	sdlTimer = NULL;
	width = w;
	height = h;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	sdlScreen = SDL_SetVideoMode(width, height, 0, SDL_ANYFORMAT);
	if ( !sdlScreen ) {
		throw "SDL screen error!";
	}
	SDL_WM_SetCaption("SDL particle simulator", "SDL particle simulator");
}

SDLDriver::~SDLDriver() {
	SDL_Quit();
}

void SDLDriver::AddTimer(int interval, SDL_NewTimerCallback callback, void *param) {
	RemoveTimer();
	sdlTimer = SDL_AddTimer(interval, callback, param);
}

void SDLDriver::RemoveTimer() {
	if ( sdlTimer != NULL ) {
		SDL_RemoveTimer(sdlTimer);
		sdlTimer = NULL;
	}
}

void SDLDriver::DrawParticle(const Particle *p) {
	filledCircleColor(sdlScreen, p->pos.x, p->pos.y, p->radius, p->getColor());
}

void SDLDriver::ClearScreen() {
	boxRGBA(sdlScreen, 0, 0, width, height, 0, 0, 0, 255);
}

void SDLDriver::Draw() {
	SDL_Flip(sdlScreen);
}

void SDLDriver::WaitQuit() {
	SDL_Event sdlEvent;
	while ( SDL_WaitEvent(&sdlEvent) && sdlEvent.type!=SDL_QUIT );
}
