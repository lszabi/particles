#include "Photon.h"

// Compute collision
Particle * Photon::collide(Particle *other, bool rec) {
	if ( ( other->getType() == PART_PROTON || other->getType() == PART_NEUTRON ) && collided(other) ) {
		// Photon gets destroyed
		dispose = true;
		if ( rec ) {
			return other->collide(this, false);
		}
	}
	return 0;
}