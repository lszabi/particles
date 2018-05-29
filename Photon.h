#pragma once

#include "Particle.h"

// Class implementing Photon particle
class Photon : public Particle {
public:
	Photon(Vec3 p = 0, Vec3 v = 0, Vec3 a = 0, double r = 2) : Particle(p, v, a, r) {};
	Photon(const Photon &p) : Particle(p.pos, p.velocity, p.accel, p.radius) {};
	~Photon() {};
	
	Particle *collide(Particle *, bool = true);
	void ApplyForce(Particle *) { };
	
	int getColor() const { return 0xFFFFFFFF; };
	particle_type getType() const { return PART_PHOTON; };
};
