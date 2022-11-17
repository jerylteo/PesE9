#include "cprocessing.h"
#include "utils.h"
#include <math.h>



// helper functions
float get_center_hor(void) {
	return (float)width / 2;
}
float get_center_ver(void) {
	return (float)height / 2;
}


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
	button resume, main;

	resume = (button){ width / 3.0f, height / 2.0f };
	main = (button){ width / 3.0f * 2, height / 2.0f};

	resume_img = CP_Image_Load("Assets/resumebutton.png");
	main_img = CP_Image_Load("Assets/menubutton.png");
	background = CP_Image_Load("Assets/bg.png");
	//CP_Settings_ImageMode(CP_POSITION_CENTER);
	//CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f);
	/*drawbutton(resume.x, resume.y, resume.text);
	drawbutton(main.x, main.y, main.text);*/

	CP_Image_Draw(background, width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f, 255);
	CP_Image_Draw(resume_img, resume.x, resume.y, button_width, button_height, 255);
	CP_Image_Draw(main_img, main.x, main.y, button_width, button_height, 255);

	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	CP_Settings_TextSize(50);
	CP_Font_DrawText("Game Paused", width / 2.0f, height / 3.0f);

	if(CP_Input_KeyDown(KEY_R))return 0;

	if (CP_Input_MouseClicked() ) {
		if (IsAreaClicked(resume.x, resume.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) ) {
			printf("Resume\t");
			return 0;
		}
		if (IsAreaClicked(main.x, main.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			printf("Main menu");
		}
		return 1;
	}
	else {
		/*CP_Image_Free(&start_img);
		CP_Image_Free(&back_img);
		CP_Image_Free(&background);*/
		return 1;
	}
}

void endgamescreen(float endscore, char* endgamestate) {
	button mode, main;

	mode = (button){ width / 3.0f, height / 3.0f * 2 };
	main = (button){ width / 3.0f * 2, height / 3.0f * 2 };

	quit_img = CP_Image_Load("Assets/exitbutton.png");
	main_img = CP_Image_Load("Assets/menubutton.png");
	background = CP_Image_Load("Assets/bg.png");
	//CP_Settings_ImageMode(CP_POSITION_CENTER);
	//CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f);
	/*drawbutton(resume.x, resume.y, resume.text);
	drawbutton(main.x, main.y, main.text);*/

	CP_Image_Draw(background, width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f, 255);
	CP_Image_Draw(quit_img, mode.x, mode.y, button_width, button_height, 255);
	CP_Image_Draw(main_img, main.x, main.y, button_width, button_height, 255);

	CP_Settings_Fill(CP_Color_Create(240, 128, 128, 255));
	CP_Settings_TextSize(50);
	char scoretext[10000] = { 0 };

	if (endgamestate == "LOSE") {
		sprintf_s(scoretext, _countof(scoretext), "You ran out of lives!\nScore : %.0f", endscore);
	}
	else {
		sprintf_s(scoretext, _countof(scoretext), "Game Ended\nScore : %.0f", endscore);

	}

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	CP_Font_DrawTextBox(scoretext, get_center_hor(), get_center_ver(),width/3);

	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(mode.x, mode.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Mode_Init, Mode_Update, Mode_Exit);
		}
		if (IsAreaClicked(main.x, main.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}

	}
}

void drawclown(float x, float y, float dia, int trans) {
	CP_Settings_Fill(CP_Color_Create(138, 43, 226, 0));
	CP_Settings_NoStroke();
	CP_Graphics_DrawCircle(x, y, dia);
	mos = CP_Image_Load("./Assets/mozz.PNG");
	CP_Image_Draw(mos, x, y, dia, dia, trans);
}

//void drawbutton(float x, float y, CP_Image buttonimage) {
//	CP_Settings_Fill(CP_Color_Create(150, 200, 200, 255));
//}