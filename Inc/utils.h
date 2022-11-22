#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include <errno.h>


CP_Image cursor,death, htpscreen_img, creditscreen_img, heart;
CP_Image title, background, mos, backscreen;
CP_Image start_img, htp_img, credits_img, quit_img, start_img2, htp_img2, credits_img2, quit_img2;
CP_Image normal_img,hard_img,hell_img,back_img, resume_img, main_img, normal_img2, hard_img2, hell_img2, back_img2, resume_img2, main_img2;


#ifndef UTILS_H
#define UTILS_H

#define button_width CP_System_GetWindowWidth() / 6.f
#define button_height CP_System_GetWindowHeight() / 10.f

#define width CP_System_GetWindowWidth()
#define height CP_System_GetWindowHeight()

#define game_timer 20.0f

// colours
#define black CP_Color_Create(0, 0, 0, 255)
#define white CP_Color_Create(255, 255, 255, 255)
#define grey CP_Color_Create(155, 155, 155, 155)
#define dead CP_Color_Create(255, 0, 0, 155)
#define fontcolor CP_Color_Create(160, 82, 45, 255)

int backgroundtrans;

float get_center_hor(void);
float get_center_ver(void);
void changecursor(float x, float y);

typedef enum {
	KILLED,
	MISSED,
	INACTIVE,
	ACTIVE,
	TIMED_OUT,
} CLOWN_STATE;	

typedef enum {
	STILL,
	MOVING,
	FAKE,
	REAL,
	SUPER
} CLOWN_TYPE;

typedef struct{
	float x;
	float y;
	int trans;
	CLOWN_STATE state;
	float time_up;
	float angle;
	bool fake;	// CLOWN_TYPE type == fake
	bool super;
}CLOWN;

typedef struct {
	float x;
	float y;
}button;

typedef struct{
	float x;
	float y;
	int trans;
	float angle;
	CLOWN_STATE state;
}movingclown;



typedef struct {
	int isPaused;
	float totalElapsedTime;
	CLOWN clown_arr[100],movingclown_arr[100];
	//movingclown movingclown_arr[100];
	float center_hor;
	float center_ver;
	int speed;
	int total_clicks;
	int total_killed;
	float accuracy;
	int life;
	float score;
	int miss;
	bool bounce;
	bool movingbounce;
} GAME;

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

void drawclown(float x, float y, float diameter,int trans, bool fake, bool super);

//void drawbutton(float x, float y, char* text);

union CP_Vector AngleToVector(float radian_angle);

int Pausescreen(void);

void endgamescreen(float endscore, float accuracy, char* endgamesate);

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

//htp
void htp_init(void);
void htp_update(void);
void htp_exit(void);

//credits
void credits_init(void);
void credits_update(void);
void credits_exit(void);

#endif