#include "Proton.h"
#include <cmath>

// Apply EM force to other particles
void Proton::ApplyForce(Particle *other) {
	// F = k * (m1 * m2) / ||r||^3 * r
	if ( distance(other) > ( radius + other->radius ) ) {
		Vec3 r = pos - other->pos;
		Vec3 F = r * ( FORCE_K * radius * other->radius * ( 1 / pow(r.length(), 3) ) );
		if ( other->getType() == PART_PROTON ) {
			F *= -1;
		} else if ( other->getType() != PART_NEUTRON ) {
			F = 0;
		}
		other->accel += F * other->radius;
		accel -= F * radius;
	}
}

// Compute collision with other particles
Particle * Proton::collide(Particle *other, bool rec) {
	if ( collided(other) ) {
		if ( other->getType() == PART_PROTON || other->getType() == PART_NEUTRON ) {
			// flexible collision
			Vec3 new_vel = collideFlex(other);
			if ( rec ) {
				other->collide(this, false);
			}
			velocity = new_vel;
		} else if ( other->getType() == PART_PHOTON ) {
			other->collide(this, false);
			if ( radius < 1 ) {
				dispose = true;
			} else {
				// tear particle into two pieces
				Vec3 velocity_plus = ( velocity ^ Vec3(0, 0, 1) ) * 0.3;
				radius /= 2;
				Particle *p = new Proton(pos + Vec3(0, 0, 1000), velocity - velocity_plus, 0, radius);
				velocity += velocity_plus;
				return p;
			}
		}
	}
	return 0;
}