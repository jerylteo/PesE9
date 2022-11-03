#pragma once

typedef struct circle {
	float x;
	float y;
	int trans;
}clown;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

void drawclown(float x, float y, float diameter,int trans);

union CP_Vector AngleToVector(float radian_angle);