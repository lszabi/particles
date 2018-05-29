#include "Vec3.h"
#include "Particle.h"

// Distance between particles
double Particle::distance(const Particle *other) const {
	// d = ||a - b||
	return (pos - other->pos).length();
}

// Calculate movement
void Particle::move(double dt) {
	// x = 0.5 * a * dt^2 + v0 * dt * x0
	// v = a * dt + v0
	pos += accel * 0.5 * dt * dt + velocity * dt;
	velocity += accel * dt;
	// Delay after creation
	if ( pos.z > 0 ) {
		pos -= Vec3(0, 0, 1000 * dt);
	} else {
		pos.z = 0;
	}
}

// Flexible collision
Vec3 Particle::collideFlex(Particle *other) {
	// u1 = ( v1 * ( m1 - m2 ) + 2 * v2 * m2 ) / ( m1 + m2 )
	return ( velocity * ( radius - other->radius ) + other->velocity * ( 2 * other->radius ) ) * ( 1 / ( radius + other->radius ) );
}

// Calculate collision
Particle * Particle::collide(Particle *other, bool rec) {
	if ( collided(other) ) {
		Vec3 new_velocity = collideFlex(other);
		Particle *p = 0;
		if ( rec ) {
			p = other->collide(this, false);
		}
		velocity = new_velocity;
		return p;
	}
	return 0;
}

// Calculate collision with the frame border
void Particle::collide(int xmin, int ymin, int xmax, int ymax) {
	if ( pos.x <= xmin ) {
		pos.x = 1;
		velocity.x *= -1;
	}
	if ( pos.x >= xmax ) {
		pos.x = xmax - 1;
		velocity.x *= -1;
	}
	if ( pos.y <= ymin ) {
		pos.y = 1;
		velocity.y *= -1;
	}
	if ( pos.y >= ymax ) {
		pos.y = ymax - 1;
		velocity.y *= -1;
	}
}