#include "Enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(float pos_x, float pos_y, int exist) {
	x = pos_x;
	y = pos_y;
	is = exist;
}

Enemy::~Enemy() {}