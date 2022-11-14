#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define diameter CP_System_GetWindowHeight()/8.0f
#define size 100
#define width CP_System_GetWindowWidth()
#define height CP_System_GetWindowHeight()
#define spd 10.0f

int isPaused;
clown clown_arr[size];
movingclown movingclown_arr[size];
bool bounce;

void hard_init(void)
{
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1270, 800);
	for (int i = 0; i < size; i++) {
		clown_arr[i] = (clown){ CP_Random_RangeFloat(0 + (2 * diameter), (float)width - (2 * diameter)),
			CP_Random_RangeFloat(0 + (2 * diameter), (float)height - (3 * diameter)),255 };
	}
	for (int i = 0; i < size; i++) {
		movingclown_arr[i] = (movingclown){ CP_Random_RangeFloat(0 + (2 * diameter), (float)width - (2 * diameter)),
			CP_Random_RangeFloat(0 + (2 * diameter), (float)height - (3 * diameter)),255 , CP_Random_RangeFloat(0,360) };
	}
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);

	isPaused = 0;
}

void hard_update(void)
{
	if (isPaused == 0) {
		if (CP_Input_KeyReleased(KEY_P)) {
			isPaused = !isPaused;
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
		else if (totalElapsedTime <= 60 && totalElapsedTime >= 5) {
			float timer = totalElapsedTime - 5;

			//Setting Text Size, Colour and Alignment
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_TextSize(50);
			char time[50] = { 0 };
			sprintf_s(time, _countof(time), "Timer : %.0f", timer);
			CP_Font_DrawText(time, (float)width / 2, 50);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

			//stationery
			for (int i = 0; i + 5 < totalElapsedTime; i++) {
				if (CP_Input_MouseClicked()) {
					if (IsCircleClicked(clown_arr[i].x, clown_arr[i].y, diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
						clown_arr[i].trans = 0;
						printf("Clicked\t");
					}
				}
				CP_Settings_NoStroke();
				drawclown(clown_arr[i].x, clown_arr[i].y, diameter, clown_arr[i].trans);
			}

			//make stationery invis
			for (int i = 0; i + 5 < totalElapsedTime; i++) {
				clown_arr[i-1].trans = 0;
			}


			//moving

			for (int i = 0; i + 5 < totalElapsedTime; i = i + 2) {
				if (CP_Input_MouseClicked()) {
					if (IsCircleClicked(movingclown_arr[i].x, movingclown_arr[i].y, diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
						movingclown_arr[i].trans = 0;
						printf("Clicked\t");
					}
				}
				CP_Vector vector_angle = AngleToVector(CP_Math_Radians(movingclown_arr[i].angle));



				movingclown_arr[i].x += vector_angle.x * spd;
				movingclown_arr[i].y += vector_angle.y * spd;
				if (bounce == FALSE) {
					if ( (movingclown_arr[i].x < 0 + (diameter / 2.0f) && movingclown_arr[i].angle > 180 && movingclown_arr[i].angle < 270) ||
						(movingclown_arr[i].x > width - (diameter / 2.0f) && movingclown_arr[i].angle < 90 && movingclown_arr[i].angle > 0) ||
						(movingclown_arr[i].y < 0 + (diameter / 2.0f) && movingclown_arr[i].angle > 270 && movingclown_arr[i].angle < 360) ||
						(movingclown_arr[i].y > height - (diameter / 2.0f) && movingclown_arr[i].angle > 90) && movingclown_arr[i].angle < 180) {

						movingclown_arr[i].angle += 90;
						if (movingclown_arr[i].angle > 360) movingclown_arr[i].angle -= 360;

						bounce = TRUE;
					}
					else if ((movingclown_arr[i].x < 0 + (diameter / 2.0f) && movingclown_arr[i].angle < 180 && movingclown_arr[i].angle > 90) ||
						(movingclown_arr[i].x > width - (diameter / 2.0f) && movingclown_arr[i].angle > 270 && movingclown_arr[i].angle < 360) ||
						(movingclown_arr[i].y < 0 + (diameter / 2.0f) && movingclown_arr[i].angle < 270 && movingclown_arr[i].angle > 180) ||
						(movingclown_arr[i].y > height - (diameter / 2.0f) && movingclown_arr[i].angle < 90) && movingclown_arr[i].angle > 0) {

						movingclown_arr[i].angle -= 90;
						if (movingclown_arr[i].angle < 0) movingclown_arr[i].angle += 360;

						bounce = TRUE;
					}
				}
				bounce = FALSE;

				CP_Settings_NoStroke();
				drawclown(movingclown_arr[i].x, movingclown_arr[i].y , diameter, movingclown_arr[i].trans);
				//printf("%f \n",movingclown_arr[0].angle);

			}

		}

		else {
			endgamescreen();
		}
	}
	else if (isPaused == 1) {
		//Pause screen
		isPaused = Pausescreen();
	}


	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

}

void hard_exit(void)
{
	//CP_Engine_SetNextGameStateForced(normal_init, normal_update, normal_exit);
}
