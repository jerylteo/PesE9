#include "cprocessing.h"
#include "utils.h"
#include <math.h>
#define width CP_System_GetWindowWidth()
#define height CP_System_GetWindowHeight()
#define button_width CP_System_GetWindowWidth() / 9.0f
#define button_height CP_System_GetWindowHeight() / 15.0f

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// mouse click in area in rect, return 1 if true
	float left = area_center_x - area_width / 2.f, right = area_center_x + area_width / 2.f;
	float top = area_center_y - area_height / 2.f, btm = area_center_y + area_height / 2.f;
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
	CP_Vector ret = CP_Vector_Set((float)x, (float)y);
    return ret;
}

int Pausescreen(void) {
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width /5.0f*4.0f, height / 5.0f * 4.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Font_DrawText("Game Paused", width / 2.0f, height / 3.0f);
	CP_Graphics_DrawRect(width / 3.0f, height / 2.0f, width / 10.0f, height/15.0f);
	CP_Graphics_DrawRect(width / 3.0f * 2, height / 2.0f, width / 10.0f, height/15.0f);
	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(width / 3.0f, height / 2.0f, width / 10.0f, height / 15.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			return 0;
			//printf("Resume\t");
		}
		if (IsAreaClicked(width / 3.0f * 2, height / 2.0f, width / 10.0f, height / 15.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			//printf("Main menu");
		}
		
	}
	else {
		return 1;
	}
}

void endgamescreen(void) {
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Font_DrawText("Game Ended", width / 2.0f, height / 3.0f);
	CP_Graphics_DrawRect(width / 3.0f, height / 2.0f, width / 10.0f, height / 15.0f);
	CP_Graphics_DrawRect(width / 3.0f * 2, height / 2.0f, width / 10.0f, height / 15.0f);
	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(width / 3.0f, height / 2.0f, width / 10.0f, height / 15.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Mode_Init, Mode_Update, Mode_Exit);

		}
		if (IsAreaClicked(width / 3.0f * 2, height / 2.0f, width / 10.0f, height / 15.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			//printf("Main menu");
		}

	}
}

void drawclown(float x, float y, float dia, int trans) {
	CP_Settings_Fill(CP_Color_Create(138, 43, 226, trans));
	CP_Graphics_DrawCircle(x, y, dia);
}

void drawbutton(float x, float y, char* text) {
	CP_Settings_Fill(CP_Color_Create(150, 200, 200, 255));
	CP_Graphics_DrawRect(x, y,button_width,button_height);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);	
	CP_Font_DrawText(text, x, y);
}