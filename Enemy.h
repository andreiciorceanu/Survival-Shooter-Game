#pragma once

class Enemy {
public:
	Enemy();
	Enemy(float pos_x, float pos_y, int exist);
	~Enemy();

	float x, y;
	int is;
};