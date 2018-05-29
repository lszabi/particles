#pragma once

#include "Particle.h"

// Class implemementing Neutron particle
class Neutron : public Particle {
public:
	Neutron(Vec3 p = 0, Vec3 v = 0, Vec3 a = 0, double r = 5) : Particle(p, v, a, r) {};
	Neutron(const Neutron &p) : Particle(p.pos, p.velocity, p.accel, p.radius) {};
	~Neutron() {};
	
	Particle *collide(Particle *, bool = true);
	void ApplyForce(Particle *);
	
	int getColor() const { return 0x00FF00FF; };
	particle_type getType() const { return PART_NEUTRON; };
};
