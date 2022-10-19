/*!
@file       utils.c
@author     Yeo Zhao Quan Xavier (z.yeo)
@course     CSD-1401
@section    CSD-1401-a
@project	Car Select Game
@date       29-09-2022
@brief      This source file contains function definitions
			for IsAreaClicked, IsCircleClicked and AngleToVector used in mainmenu.c and carlevel.c
*/

#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include <math.h>

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// mouse click in area in rect, return 1 if true
	int left = area_center_x - area_width / 2.f, right = area_center_x + area_width / 2.f;
	int top = area_center_y - area_height / 2.f, btm = area_center_y + area_height / 2.f;
	if (click_x >= left && click_x <= right && click_y >= top && click_y <= btm)  {
		return 1;
	}
	return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	// mouse click in area in circle, return 1 if true
	float radius = diameter / 2.f;
	float distance = (click_x - circle_center_x)* (click_x - circle_center_x) + (click_y-circle_center_y)* (click_y - circle_center_y);
	if (distance <= radius * radius) {
		return 1;
	}
	return 0;
}

/*
AngleToVector will convert an angle with respect to x - axis to a 2D vector
that is rotated counter - clockwise from x - axis.
*/
CP_Vector AngleToVector(float radian_angle)
{
    // TODO 
	double x, y;
	x = cos(radian_angle);
	y = sin(radian_angle);
	CP_Vector ret = CP_Vector_Set(x,y);
    return ret;
}