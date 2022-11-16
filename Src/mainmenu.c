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
button play,htp,credits,quit;

void Main_Menu_Init()
{
	//window size
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1270, 800);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);


}

void Main_Menu_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	float center_x = width / 2.f;
	float center_y = height / 2.f;

	play = (button){ center_x, center_y - (center_y / 10 * 3), "PLAY" };
	htp = (button){ center_x, center_y - (center_y / 10), "HOW TO PLAY" };
	credits = (button){ center_x, center_y + (center_y / 10), "CREDITS" };
	quit = (button){ center_x, center_y + (center_y / 10 * 3), "EXIT" };

	//menu buttons in the center
	CP_Settings_Fill(CP_Color_Create(150, 200, 200, 255));
	drawbutton(play.x, play.y, play.text);//play
	drawbutton(htp.x, htp.y, htp.text);//how to play
	drawbutton(credits.x, credits.y, credits.text);//credits
	drawbutton(quit.x, quit.y, quit.text);//exit

	CP_Graphics_DrawRect(width / 0.2f, height / 0.2f - (height / 10.0f * 3.0f), button_width,button_height);

	if (CP_Input_MouseClicked())
	{	//"PLAY" button is clicked
		if (IsAreaClicked(play.x, play.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameStateForced(Mode_Init, Mode_Update, Mode_Exit);
		}
		//"HOW TO PLAY" button is clicked
		else if (IsAreaClicked(htp.x, htp.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		}
		//"CREDITS" button is clicked
		else if (IsAreaClicked(credits.x, credits.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())){
		}
		//"EXIT" button is clicked
		else if (IsAreaClicked(quit.x, quit.y, button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			/*drawbutton(exit.x, exit.y, exit.text);*/
			CP_Engine_Terminate();
		}
	}
}

void Main_Menu_Exit()
{
	
}