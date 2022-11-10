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

int Pausescreen(void);

void endgamescreen(void);

void normal_init(void);

void normal_update(void);

void normal_exit(void);


void hell_init(void);

void hell_update(void);

void hell_exit(void);


void hard_init(void);

void hard_update(void);

void hard_exit(void);