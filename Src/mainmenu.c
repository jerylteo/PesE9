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
#include "mode.h"

void Main_Menu_Init()
{
	//window size
	CP_System_SetWindowSize(1270, 800);
}

void Main_Menu_Update()
{
	//colors, width and height
	CP_Color green_Color = CP_Color_Create(0, 255, 0, 255);
	CP_Color red_Color = CP_Color_Create(255,0,0,255);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	float center_x = CP_System_GetWindowWidth() / 2.0f;
	float center_y = CP_System_GetWindowHeight() / 2.0f;

	//menu buttons in the center
	CP_Settings_Fill(CP_Color_Create(150, 200, 200, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(center_x, (center_y - 180), 150, 50); //play
	CP_Graphics_DrawRect(center_x, (center_y - 60), 150, 50); //how to play
	CP_Graphics_DrawRect(center_x, (center_y + 60), 150, 50); //credits
	CP_Graphics_DrawRect(center_x, (center_y + 180), 150, 50); //exit
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText("PLAY", center_x, (center_y - 180 ));
	CP_Font_DrawText("HOW TO PLAY", center_x, (center_y - 60));
	CP_Font_DrawText("CREDITS", center_x, (center_y + 60));
	CP_Font_DrawText("EXIT", center_x, (center_y + 180));
	
	if (CP_Input_MouseClicked())
	{	//"PLAY" button is clicked
		if (IsAreaClicked(center_x, (center_y - 180), 150, 50, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Settings_Fill(green_Color);
			CP_Graphics_DrawRect(center_x, (center_y - 180), 150, 50);
			CP_Font_DrawText("PLAY", center_x, (center_y - 180));
			CP_Engine_SetNextGameState(Mode_Init, Mode_Update, Mode_Exit);
		}
		//"HOW TO PLAY" button is clicked
		else if (IsAreaClicked(center_x, (center_y - 60), 150, 50, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Settings_Fill(green_Color);
			CP_Graphics_DrawRect(center_x, (center_y - 60), 150, 50);
			CP_Font_DrawText("HOW TO PLAY", center_x, (center_y - 60));
		}
		//"CREDITS" button is clicked
		else if (IsAreaClicked(center_x, (center_y + 60), 150, 50, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Settings_Fill(green_Color);
			CP_Graphics_DrawRect(center_x, (center_y + 60), 150, 50);
			CP_Font_DrawText("CREDITS", center_x, (center_y + 60));
		}
		//"EXIT" button is clicked
		else if (IsAreaClicked(center_x, (center_y + 180), 150, 50, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Settings_Fill(red_Color);
			CP_Graphics_DrawRect(center_x, (center_y + 180), 150, 50);
			CP_Font_DrawText("EXIT", center_x, (center_y - 180));
			CP_Engine_Terminate();
		}
	}
}

void Main_Menu_Exit()
{
	
}