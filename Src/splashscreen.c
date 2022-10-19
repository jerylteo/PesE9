#include "cprocessing.h"
#include "mainmenu.h"
#include <stdio.h>
#include <math.h>

CP_Image logo;

void splash_screen_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));

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
	CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), transparency);
	if (totalElapsedTime >= 4) {
		CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f); //Get circle on mouse

}

void splash_screen_exit(void)
{
	CP_Image_Free(&logo);
}