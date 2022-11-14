#pragma once


typedef struct circle {
	float x;
	float y;
	int trans;
}clown;

typedef struct button {
	float x;
	float y;
	char* text;
}button;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

void drawclown(float x, float y, float diameter,int trans);

void drawbutton(float x, float y, char* text);

union CP_Vector AngleToVector(float radian_angle);

int Pausescreen(void);

void endgamescreen(void);

//normal mode
void normal_init(void);
void normal_update(void);
void normal_exit(void);

//hell mode
void hell_init(void);
void hell_update(void);
void hell_exit(void);

//hard mode
void hard_init(void);
void hard_update(void);
void hard_exit(void);

//mode menu
void Mode_Init(void);
void Mode_Update(void);
void Mode_Exit(void);

//main menu
void Main_Menu_Init(void);
void Main_Menu_Update(void);
void Main_Menu_Exit(void);

//splashscreen
void splash_screen_init(void);
void splash_screen_update(void);
void splash_screen_exit(void);