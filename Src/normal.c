#include "cprocessing.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define diameter CP_System_GetWindowHeight()/8.0f
#define size 100
#define width CP_System_GetWindowWidth()
#define height CP_System_GetWindowHeight()

int isPaused;
clown clown_arr[size];

void normal_init(void)
{
	CP_System_Fullscreen();
	//CP_System_SetWindowSize(1270, 800);
	for (int i = 0; i < size; i++) {
		clown_arr[i] = (clown){ CP_Random_RangeFloat(0 + (2 * diameter), (float)width - (2 * diameter)),
			CP_Random_RangeFloat(0 + (2 * diameter), (float)height - (3 * diameter)),255 };
	}
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);

	isPaused = 0;
}

void normal_update(void)
{
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

			endgamescreen();


		}
	}
	else if (isPaused==1){
		//Pause screen
		isPaused = Pausescreen();
	}
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}

void normal_exit(void)
{
	//CP_Engine_SetNextGameStateForced(normal_init, normal_update, normal_exit);
}
