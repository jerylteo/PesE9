	#pragma once

	#include <math.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdbool.h>
	#include "cprocessing.h"
CP_Image background, mos;

	#ifndef UTILS_H
	#define UTILS_H

	#define button_width CP_System_GetWindowWidth() / 9.f
	#define button_height CP_System_GetWindowHeight() / 15.f

	#define width CP_System_GetWindowWidth()
	#define height CP_System_GetWindowHeight()

	float get_center_hor(void);
	float get_center_ver(void);

	typedef enum {
		KILLED,
		MISSED,
		INACTIVE,
		ACTIVE,
		TIMED_OUT,
	} CLOWN_STATE;

	typedef struct{
		float x;
		float y;
		int trans;
		CLOWN_STATE state;
		float time_up;
	}CLOWN;

	typedef struct {
		float x;
		float y;
		char* text;
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
		CLOWN clown_arr[100];
		movingclown movingclown_arr[100];
		float center_hor;
		float center_ver;
		int speed;
		int total_clicks;
		int total_killed;
		float accuracy;
		int life;
		float score;
		int miss;
	} GAME;

	int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

	int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

	void drawclown(float x, float y, float diameter,int trans);

	void drawbutton(float x, float y, char* text);

	union CP_Vector AngleToVector(float radian_angle);

	int Pausescreen(void);

	void endgamescreen(float endscore);

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

	#endif