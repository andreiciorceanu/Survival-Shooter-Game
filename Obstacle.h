#pragma once

 class Obstacle {
 public:
	 Obstacle();
	 Obstacle(float pos_x, float pos_y, float scaleX, float scaleY);
	 ~Obstacle();

	 float x, y;
	 float scale_x, scale_y;
 };