//---------------------------------------------------------
// file:	mainmenu.c
// author:	Low Jun Jie Gordon
// email:	junjiegordon.low@digipen.edu
//
// brief:	Definition of functions for Main_Menu_Init(),
//			Main_Menu_Update(), Main_Menu_Exit()
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "utils.h"

button play, htp, credits, quit;

void Main_Menu_Init()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//window size
	CP_System_Fullscreen();
	//CP_System_SetWindowSize(1270, 800);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);
	//load font
	CP_Font FONT = CP_Font_Load("Assets/Ribeye/Ribeye-Regular.ttf");
	CP_Font_Set(FONT);
	//load image
	title = CP_Image_Load("Assets/title1.png");
	background = CP_Image_Load("Assets/bg.png");
	start_img = CP_Image_Load("Assets/startbutton.png");
	htp_img = CP_Image_Load("Assets/htpbutton.png");
	credits_img = CP_Image_Load("Assets/creditsbutton.png");
	quit_img = CP_Image_Load("Assets/exitbutton.png");
	start_img2 = CP_Image_Load("Assets/startbutton2.png");
	htp_img2 = CP_Image_Load("Assets/htpbutton2.png");
	credits_img2 = CP_Image_Load("Assets/creditsbutton2.png");
	quit_img2 = CP_Image_Load("Assets/exitbutton2.png");
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

}

void Main_Menu_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	float center_x = width / 2.f;
	float center_y = height / 2.f;

	play = (button){ center_x, height - button_height * 5.5};
	htp = (button){ center_x, height - button_height * 4};
	credits = (button){ center_x, height - button_height *2.5 };
	quit = (button){ center_x, height - button_height };

	//menu buttons in the center
	//CP_Settings_Fill(CP_Color_Create(150, 200, 200, 255));
	//drawbutton(play.x, play.y, play.text);//play
	//drawbutton(htp.x, htp.y, htp.text);//how to play
	//drawbutton(credits.x, credits.y, credits.text);//credits
	//drawbutton(exit.x, exit.y, exit.text);//exit

	//Draw image
	CP_IMAGE_WRAP_MODE(CP_IMAGE_WRAP_CLAMP);
	CP_Image_Draw(background, width / 2.0f, height / 2.0f, width, height, 255);
	CP_Settings_TextSize(width/10);
	CP_Settings_Fill(fontcolor);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("PEST ZERO", center_x, center_y - (center_y / 10 * 5));
	CP_Image_Draw(start_img, play.x,play.y, button_width, button_height, 255);
	CP_Image_Draw(htp_img, htp.x,htp.y, button_width, button_height, 255);
	CP_Image_Draw(credits_img, credits.x,credits.y, button_width, button_height, 255);
	CP_Image_Draw(quit_img, quit.x,quit.y, button_width, button_height, 255);

	if (IsAreaClicked(play.x, play.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(start_img2, play.x, play.y, button_width, button_height, 255);
	}
	if (IsAreaClicked(htp.x, htp.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(htp_img2, htp.x, htp.y, button_width, button_height, 255);
	}
	if (IsAreaClicked(credits.x, credits.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(credits_img2, credits.x, credits.y, button_width, button_height, 255);
	}
	if (IsAreaClicked(quit.x, quit.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(quit_img2, quit.x, quit.y, button_width, button_height, 255);
	}

	//Button clicked
	if (CP_Input_MouseClicked())
	{	//"PLAY" button is clicked
		if (IsAreaClicked(play.x, play.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameStateForced(Mode_Init, Mode_Update, Mode_Exit);
		}
		//"HOW TO PLAY" button is clicked
		else if (IsAreaClicked(htp.x, htp.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		}
		//"CREDITS" button is clicked
		else if (IsAreaClicked(credits.x, credits.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		}
		//"EXIT" button is clicked
		else if (IsAreaClicked(quit.x, quit.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_Terminate();
		}
	}
}

void Main_Menu_Exit()
{
	//CP_Image_Free(&start_img);
	//CP_Image_Free(&htp_img);
	//CP_Image_Free(&credits_img);
	//CP_Image_Free(&quit_img);
}