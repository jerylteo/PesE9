//---------------------------------------------------------
// file:	mainmenu.c
// author:	Low Jun Jie Gordon
// email:	junjiegordon.low@digipen.edu
//
// brief:	Definition of functions for Mode_Init(),
//			Mode_Update(), Mode_Exit()
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "utils.h"

button normal, hard, hell, back;

void Mode_Init()
{
	//window size
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1270, 800);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);

	//load image
	normal_img = CP_Image_Load("Assets/normalbutton.png");
	hard_img = CP_Image_Load("Assets/hardbutton.png");
	hell_img = CP_Image_Load("Assets/hellbutton.png");
	back_img = CP_Image_Load("Assets/backbutton.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
}

void Mode_Update()
{
	//colors, width and height
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	float center_x = width / 2.0f;
	float center_y = height / 2.0f;

	normal = (button){ center_x, center_y - (center_y / 10 * 3) };
	hard = (button){ center_x, center_y - (center_y / 10)};
	hell = (button){ center_x, center_y + (center_y / 10) };
	back = (button){ center_x, center_y + (center_y / 10 * 3) };

	//menu buttons in the center
	//menu buttons in the center
	/*CP_Settings_Fill(CP_Color_Create(150, 200, 200, 255));
	drawbutton(normal.x, normal.y);
	drawbutton(hard.x, hard.y);
	drawbutton(hell.x, hell.y)
	drawbutton(back.x, back.y);*/

	CP_Image_Draw(background, CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, width, height, 255);
	CP_Image_Draw(normal_img, normal.x, normal.y, button_width, button_height, 255);
	CP_Image_Draw(hard_img, hard.x, hard.y, button_width, button_height, 255);
	CP_Image_Draw(hell_img, hell.x, hell.y, button_width, button_height, 255);
	CP_Image_Draw(back_img, back.x, back.y, button_width, button_height, 255);

	if (IsAreaClicked(normal.x, normal.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(normal_img, normal.x, normal.y, button_width, button_height, 255);
	}
	if (IsAreaClicked(hard.x, hard.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(hard_img, hard.x, hard.y, button_width, button_height, 255);
	}
	if (IsAreaClicked(hell.x, hell.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(hell_img, hell.x, hell.y, button_width, button_height, 255);
	}
	if (IsAreaClicked(back.x, back.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(back_img, back.x, back.y, button_width, button_height, 255);
	}

	if (CP_Input_MouseClicked())
	{	//"NORMAL" button is clicked
		if (IsAreaClicked(normal.x, normal.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameStateForced(normal_init, normal_update, normal_exit);
		}
		//"HARD" button is clicked
		else if (IsAreaClicked(hard.x, hard.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameStateForced(hard_init, hard_update, hard_exit);

		}
		//"HELL" button is clicked
		else if (IsAreaClicked(hell.x, hell.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameStateForced(hell_init, hell_update, hell_exit);
		}
		//"BACK" button is clicked
		else if (IsAreaClicked(back.x, back.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}
}

void Mode_Exit()
{
	//CP_Image_Free(&normal_img);
	//CP_Image_Free(&hard_img);
	//CP_Image_Free(&hell_img);
	//CP_Image_Free(&back_img);
}