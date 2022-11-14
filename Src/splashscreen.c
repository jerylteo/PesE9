#include "cprocessing.h"
#include "utils.h"
#include <stdio.h>
#include <math.h>

CP_Image logo;

void splash_screen_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");// change splash screen?
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_Fullscreen();	

	// initialize settings
	CP_Settings_TextSize(150);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_Fill(CP_Color_Create(100, 20, 100, 255));
}

void splash_screen_update(void)
{
	// get dt and then print total elapsed time
	float currentElapsedTime = CP_System_GetDt();
	static float totalElapsedTime = 0;
	totalElapsedTime += currentElapsedTime;
	int transparency = 256 - abs((int)(totalElapsedTime/2 * 256) % 512 - 256);

	printf("Total Elapsed Time: %f\n",totalElapsedTime);
	CP_Color color1 = CP_Color_Create(255, 0, 0, 255);
	CP_Settings_Fill(color1); // Set colour to red
	CP_Image_Draw(logo, CP_System_GetWindowWidth()/2.0f, CP_System_GetWindowHeight()/2.0f, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), transparency);
	if (totalElapsedTime >= 4 || CP_Input_KeyDown(KEY_SPACE)) {
		CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
}

void splash_screen_exit(void)
{
	CP_Image_Free(&logo);
}