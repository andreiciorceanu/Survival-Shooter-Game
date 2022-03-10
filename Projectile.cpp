#include "Projectile.h"

Projectile::Projectile() {}

Projectile::Projectile(float pos_x, float pos_y, float angle, int exist) {
	x = pos_x;
	y = pos_y;
	rad = angle;
	is = exist;
}

Projectile::~Projectile() {}