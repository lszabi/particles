#include "Neutron.h"
#include "Photon.h"

// Apply Protons' force
void Neutron::ApplyForce(Particle *other) {
	if ( other->getType() == PART_PROTON ) {
		other->ApplyForce(this);
	}
}

// Compute collision with other particles
Particle * Neutron::collide(Particle *other, bool rec) {
	Particle *p = 0;
	if ( collided(other) ) {
		if ( other->getType() == PART_NEUTRON ) {
			// two neutrons create a photon
			p = new Photon(( pos + other->pos ) * 0.5 + Vec3(0, 0, 1000), velocity + other->velocity, 0);
		}
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
				p = new Neutron(pos + Vec3(0, 0, 1000), velocity - velocity_plus, 0, radius);
				velocity += velocity_plus;
			}
		}
	}
	return p;
}