#include <iostream>
#include <ctime>
#include <cstdlib>
#include <list>
#include "Vec3.h"
#include "Particle.h"
#include "Neutron.h"
#include "Proton.h"
#include "Photon.h"
#include "SDLDriver.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PHOTON_SPEED 75

using namespace std;

typedef list<Particle *>::iterator ParticleIterator;

static SDLDriver *sdl;
static list<Particle *> particles;

// Main loop for the simulation
Uint32 timer_callback(Uint32 interval, void *param) {
	// Clear the screen and zero all acceleration (will be computed again)
	sdl->ClearScreen();
	for ( ParticleIterator it = particles.begin(); it != particles.end(); it++ ) {
		(*it)->accel = 0;
	}
	// Compute acceleration for each particle
	for ( ParticleIterator it1 = particles.begin(); it1 != particles.end(); it1++ ) {
		ParticleIterator it2 = it1;
		for ( it2++; it2 != particles.end(); it2++ ) {
			(*it1)->ApplyForce(*it2);
		}
	}
	// Calculate movement and draw particles
	for ( ParticleIterator it = particles.begin(); it != particles.end(); it++ ) {
		(*it)->move(0.001 * interval);
		(*it)->collide(0, 0, sdl->getWidth(), sdl->getHeight());
		// Calaculate collision with other particles
		ParticleIterator it2 = it;
		for ( it2++; it2 != particles.end(); it2++ ) {
			Particle *p = (*it)->collide(*it2);
			if ( p != 0 ) {
				particles.push_back(p);
			}
		}
		// Draw particle
		sdl->DrawParticle(*it);
	}
	// Get rid of destroyed particles
	for ( ParticleIterator it = particles.begin(); it != particles.end(); it++ ) {
		if ( (*it)->disposable() ) {
			Particle *p = *it;
			it = particles.erase(it);
			delete p;
		}
	}
	// Refresh canvas
	sdl->Draw();
	return interval;
}

int main(int argc, char **argv) {
	// Get number of particles from cmd line arg, default is 25
	int particles_n = 25;
	if ( argc > 1 ) {
		int x;
		if ( sscanf(argv[1], "%d", &x) == 1 ) {
			particles_n = x;
		}
	}
	// Inititalize field with random stationary particles (except photons, they have constant speed)
	srand(time(NULL));
	for ( int i = 0; i < particles_n; i++ ) {
		int a = rand() % 3;
		Vec3 pos = Vec3(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 0);
		Particle *p;
		if ( a == 0 ) {
			p = new Neutron(pos);
		} else if ( a == 1 ) {
			p = new Proton(pos);
		} else if ( a == 2 ) {
			int fi = rand();
			p = new Photon(pos, Vec3(PHOTON_SPEED * cos(fi), PHOTON_SPEED * sin(fi), 0));
		}
		particles.push_back(p);
	}
	// Initialize SDL and the main loop
	try {
		sdl = new SDLDriver(SCREEN_WIDTH, SCREEN_HEIGHT);
		sdl->AddTimer(1, timer_callback, NULL);
		sdl->WaitQuit();
		sdl->RemoveTimer();
	} catch ( char *error ) {
		cout << "Error: " << error << endl;
	}
	// Cleanup all objects
	for ( ParticleIterator it = particles.begin(); it != particles.end(); it++ ) {
		delete *it;
	}
	return 0;
}
