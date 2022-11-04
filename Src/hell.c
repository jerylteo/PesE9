#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define diameter 100
#define size 500

int isPaused;
clown clown_arr[size];

void hell_init(void)
{
	CP_System_Fullscreen();
	//CP_System_SetWindowSize(1270, 800);
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();
	for (int i = 0; i < size; i++) {
		clown_arr[i] = (clown){ CP_Random_RangeFloat(0 + (2 * diameter), (float)width - (2 * diameter)),
			CP_Random_RangeFloat(0 + (2 * diameter), (float)height - (3 * diameter)),255 };
	}
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);

	isPaused = 0;
}

void hell_update(void)
{
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();
	if (isPaused == 0) {
		if (CP_Input_KeyDown(KEY_P)) {
			isPaused = 1;
		}
		CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));
		float currentElapsedTime = CP_System_GetDt();
		static float totalElapsedTime = 0;
		totalElapsedTime += currentElapsedTime;
		printf("%f\n", totalElapsedTime);

		if (totalElapsedTime <= 5 && totalElapsedTime >= 0) {

			for (int i = 0, displaycountdown = 5; i <= totalElapsedTime; i++, displaycountdown--) {
				float count = 5 - totalElapsedTime;
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Settings_TextSize(250);
				char countdown[50] = { 0 };
				sprintf_s(countdown, _countof(countdown), "Game starting in %.0f...", count--);
				CP_Font_DrawText(countdown, (float)width / 2, (float)height / 2);
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			}
		}
		else if (totalElapsedTime <= 15 && totalElapsedTime >= 5) {
			float timer = totalElapsedTime - 5;
			for (int i = 0; i + 5 < totalElapsedTime; i++) {
				if (CP_Input_MouseClicked()) {
					if (IsCircleClicked(clown_arr[i].x, clown_arr[i].y, diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
						clown_arr[i].trans = 0;
						printf("Clicked\t");
					}
				}
				CP_Settings_NoStroke();
				drawclown(clown_arr[i].x, clown_arr[i].y, diameter, clown_arr[i].trans);

				//Setting Text Size, Colour and Alignment
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Settings_TextSize(50);

				char time[50] = { 0 };
				sprintf_s(time, _countof(time), "Timer : %.0f", timer);
				CP_Font_DrawText(time, (float)width / 2, 50);
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			}
		}

		else {
			CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, 400, 300);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Game Ended", width / 2.0f, height / 2.0f);

		}
	}
	else {
		//Pause screen
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(width / 2.0f, height / 2.0f, width - 400.0f, height - 200.0f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
		CP_Font_DrawText("Game Paused", width / 2.0f, height / 2.0f - 300);
		CP_Graphics_DrawRect(width / 3.0f, height / 2.0f, 200, 100);
		CP_Graphics_DrawRect(width / 3.0f * 2, height / 2.0f, 200, 100);
		if (CP_Input_MouseClicked()) {
			if (IsAreaClicked(width / 3.0f, height / 2.0f, 200, 200, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				isPaused = 0;
				printf("Resume\t");
			}
			if (IsAreaClicked(width / 3.0f * 2, height / 2.0f, 200, 200, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				//go main menu
				printf("Main menu");
			}
		}

	}
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}

void hell_exit(void)
{
	//CP_Engine_SetNextGameStateForced(normal_init, normal_update, normal_exit);
}

//void drawclown(float x, float y, float dia,int trans) {
//	CP_Settings_Fill(CP_Color_Create(138, 43, 226,trans));
//	CP_Graphics_DrawCircle(x, y, dia);
//}