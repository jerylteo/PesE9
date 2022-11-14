#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mode.h" 
#include "cprocessing.h"
#include "mainmenu.h"


#ifndef UTILS_H
#define UTILS_H

// game properties
#define width CP_System_GetWindowWidth()
#define height CP_System_GetWindowHeight()


// colours
#define black CP_Color_Create(0, 0, 0, 255)
#define white CP_Color_Create(255, 255, 255, 255)
#define bg_gray CP_Color_Create(200, 200, 200, 255)

typedef enum {
	KILLED,
	ALIVE,
	INACTIVE,
	ACTIVE
} CLOWN_STATE;

// structs
typedef struct {
	float x;
	float y;
	int trans;
	CLOWN_STATE state;
} CLOWN;

typedef struct {
	int isPaused;
	float totalElapsedTime;
	CLOWN clown_arr[30];
	float center_hor;
	float center_ver;
} GAME;


// helper functions
float get_center_hor(void);
float get_center_ver(void);

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

#endif
