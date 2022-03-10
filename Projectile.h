#pragma once

class Projectile {
public:
	Projectile();
	Projectile(float pos_x, float pos_y, float angle, int exist);
	~Projectile();

	float x, y, rad;
	int is;
};