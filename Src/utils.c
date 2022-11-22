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
	backscreen = CP_Image_Load("Assets/backscreen2.png");
	resume_img2 = CP_Image_Load("Assets/resumebutton2.png");
	main_img2 = CP_Image_Load("Assets/menubutton2.png");

	//CP_Settings_ImageMode(CP_POSITION_CENTER);
	//CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f);
	/*drawbutton(resume.x, resume.y, resume.text);
	drawbutton(main.x, main.y, main.text);*/

	CP_Image_Draw(backscreen, width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f, 255);
	CP_Image_Draw(resume_img, resume.x, resume.y, button_width, button_height, 255);
	CP_Image_Draw(main_img, main.x, main.y, button_width, button_height, 255);
	if (CP_Input_GetMouseX() >= resume.x - button_width / 2 &&
		CP_Input_GetMouseX() <= resume.x + button_width / 2 &&
		CP_Input_GetMouseY() <= resume.y + button_height / 2 &&
		CP_Input_GetMouseY() >= resume.y - button_height / 2) {
		CP_Image_Draw(resume_img2, resume.x, resume.y, button_width, button_height, 255);
	}
	if (CP_Input_GetMouseX() >= main.x - button_width / 2 &&
		CP_Input_GetMouseX() <= main.x + button_width / 2 &&
		CP_Input_GetMouseY() <= main.y + button_height / 2 &&
		CP_Input_GetMouseY() >= main.y - button_height / 2) {
		CP_Image_Draw(main_img2, main.x, main.y, button_width, button_height, 255);
	}

	CP_Settings_Fill(fontcolor);
	CP_Settings_TextSize(100);
	CP_Font_DrawText("Game Paused", width / 2.0f, height / 4.0f);

	if(CP_Input_KeyDown(KEY_R))return 0;
	
	if (CP_Input_MouseClicked() ) {
		if (IsAreaClicked(resume.x, resume.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())  ==1 ) {
			printf("Resume\t");
			return 0;
		}
		if (IsAreaClicked(main.x, main.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) ==1) {
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

void endgamescreen(float endscore, float accuracy, char* endgamestate) {
	button mode, main;

	mode = (button){ width / 3.0f, height / 3.0f * 2 };
	main = (button){ width / 3.0f * 2, height / 3.0f * 2 };

	back_img = CP_Image_Load("Assets/backbutton.png");
	main_img = CP_Image_Load("Assets/menubutton.png");
	back_img2 = CP_Image_Load("Assets/backbutton2.png");
	main_img2 = CP_Image_Load("Assets/menubutton2.png");

	backscreen = CP_Image_Load("Assets/backscreen2.png");
	//CP_Settings_ImageMode(CP_POSITION_CENTER);
	//CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	//CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f);
	/*drawbutton(resume.x, resume.y, resume.text);
	drawbutton(main.x, main.y, main.text);*/

	CP_Image_Draw(backscreen, width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f, 255);
	CP_Image_Draw(back_img, mode.x, mode.y, button_width, button_height, 255);
	CP_Image_Draw(main_img, main.x, main.y, button_width, button_height, 255);

	if (CP_Input_GetMouseX() >= mode.x - button_width / 2 &&
		CP_Input_GetMouseX() <= mode.x + button_width / 2 &&
		CP_Input_GetMouseY() <= mode.y + button_height / 2 &&
		CP_Input_GetMouseY() >= mode.y - button_height / 2) {
		CP_Image_Draw(back_img2, mode.x, mode.y, button_width, button_height, 255);
	}
	if (CP_Input_GetMouseX() >= main.x - button_width / 2 &&
		CP_Input_GetMouseX() <= main.x + button_width / 2 &&
		CP_Input_GetMouseY() <= main.y + button_height / 2 &&
		CP_Input_GetMouseY() >= main.y - button_height / 2) {
		CP_Image_Draw(main_img2, main.x, main.y, button_width, button_height, 255);
	}

	CP_Settings_Fill(fontcolor);
	CP_Settings_TextSize(100);
	char scoretext[10000] = { 0 };

	if (endgamestate == "LOSE") {
		sprintf_s(scoretext, _countof(scoretext), "You ran out of lives!\nScore : %.0f", endscore);
	}
	else {
		sprintf_s(scoretext, _countof(scoretext), "Time's Up!\nAccuracy : %.2f%%\nScore : %.0f",accuracy, endscore);

	}

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawTextBox(scoretext, 0, height /4, width);

	//FILE* fp = fopen("Assets/highscore.txt", "a");
	//fprintf(fp, "%.0f", endscore);
	//errno_t err;
	//if (err = fopen(&fp, "Assets/highscore.txt", "a") != 0) {
	//	printf("%s", "haha");
	//}
	//else {
	//	// read highscore & print on screen
	//	fprintf(fp, "%.0f", endscore);
	//}


	//if (fp) {
	//	err = fclose(fp);
	//}


	if (CP_Input_MouseClicked()) {
		if (IsAreaClicked(mode.x, mode.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) ==1) {
			CP_Engine_SetNextGameState(Mode_Init, Mode_Update, Mode_Exit);
		}
		if (IsAreaClicked(main.x, main.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())== 1) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}
}

void drawclown(float x, float y, float dia, int trans, bool fake, bool super) {
	CP_Settings_Fill(CP_Color_Create(138, 43, 226, 0));
	CP_Settings_NoStroke();
	CP_Graphics_DrawCircle(x, y, dia);
	if (fake) mos = CP_Image_Load("./Assets/ladybug.PNG");
	else mos = CP_Image_Load("./Assets/mozz.png");

	if (super) mos = CP_Image_Load("./Assets/cock.png");
	CP_Settings_ImageFilterMode(CP_IMAGE_FILTER_LINEAR);
	CP_Image_Draw(mos, x, y, dia, dia, trans);
}

//void drawbutton(float x, float y, CP_Image buttonimage) {
//	CP_Settings_Fill(CP_Color_Create(150, 200, 200, 255));
//}

void changecursor(float x,float y) {
	int cursorangle;
	CP_System_ShowCursor(FALSE);
	
	CP_POSITION_MODE CP_POSITION_CORNER;
	if (CP_Input_MouseDown(MOUSE_BUTTON_1) == 1) {
		cursor = CP_Image_Load("./Assets/splat2.png");
		cursorangle = 0;
	}
	else {
		cursor = CP_Image_Load("./Assets/splat.png");
		cursorangle = 335;
	}
		CP_Image_DrawAdvanced(cursor, x, y, width / 12, height / 5, 255, cursorangle);
	

}