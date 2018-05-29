#pragma once

#include "Vec3.h"

typedef enum { PART_NEUTRON, PART_PROTON, PART_PHOTON } particle_type;

// Class implementing Particle abstract base class
class Particle {
protected:
	bool dispose;
	Vec3 collideFlex(Particle *);
public:
	Vec3 pos, velocity, accel;
	double radius;
	
	Particle(Vec3 p = 0, Vec3 v = 0, Vec3 a = 0, double r = 0) : dispose(false), pos(p), velocity(v), accel(a), radius(r) { };
	virtual ~Particle() {};

	void collide(int, int, int, int);
	void move(double dt);
	double distance(const Particle *) const;
	
	bool collided(Particle *other) const { return distance(other) <= ( radius + other->radius ); };
	
	virtual Particle *collide(Particle *, bool = true);
	virtual void ApplyForce(Particle *) = 0;
	
	virtual int getColor() const = 0; 
	virtual particle_type getType() const = 0;
	
	bool disposable() { return dispose; }
};