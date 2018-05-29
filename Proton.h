#pragma once

#include "Particle.h"

#define FORCE_K 300

// Class impementing Proton particle
class Proton : public Particle {
public:
	Proton(Vec3 p = 0, Vec3 v = 0, Vec3 a = 0, double r = 5) : Particle(p, v, a, r) {};
	Proton(const Proton &p) : Particle(p.pos, p.velocity, p.accel, p.radius) {};
	~Proton() {};
	
	void ApplyForce(Particle *);
	Particle *collide(Particle *, bool = true);
	
	int getColor() const { return 0xFF0000FF; };
	particle_type getType() const { return PART_PROTON; };
};
