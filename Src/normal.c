#include "utils.h"
#define diameter CP_System_GetWindowHeight()/8.0f

GAME game;

// game core functions
void normal_init(void)
{
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);
	CP_System_SetFrameRate(60);
	for (int i = 0; i < 30; i++) {
		CLOWN clown = {
			CP_Random_RangeFloat(2 * diameter, width - (2 * diameter)),
			CP_Random_RangeFloat(2 * diameter, height - (3 * diameter)),
			255,
			INACTIVE
		};
		game.clown_arr[i] = clown;
	}

	game.isPaused = 0;
}

void normal_update(void)
{		
	if (CP_Input_KeyDown(KEY_P)) {
		game.isPaused = !game.isPaused;	// toggle pause state
	}

	// if game is running
	if (game.isPaused == 0) {

		CP_Graphics_ClearBackground(bg_gray);
		float currentElapsedTime = CP_System_GetDt();
		static float totalElapsedTime = 0;
		totalElapsedTime += currentElapsedTime;
		printf("%f\n", totalElapsedTime);

		// 0 - 4 seconds
		// countdown to game start
		if (0 <= totalElapsedTime && totalElapsedTime <= 5) {
			for (int i = 0; i <= totalElapsedTime; i++) {
				float count = 5 - (float)totalElapsedTime;
				CP_Settings_Fill(black);
				CP_Settings_TextSize(100);
				char countdown[50] = { 0 };
				sprintf_s(countdown, _countof(countdown), "Game starting in %.0f...", count--);
				CP_Font_DrawText(countdown, get_center_hor(), get_center_ver());
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			}
		}
		// 5 - 15 seconds
		// game running
		else if (5 <= totalElapsedTime && totalElapsedTime <= 15) {
			float idx = totalElapsedTime - 5;

			for (int i = 0; i+5 < totalElapsedTime; i++) {
				drawclown(
					game.clown_arr[i].x, 
					game.clown_arr[i].y, 
					diameter, 
					game.clown_arr[i].trans,
					ACTIVE
					);
			}


			//checks if any spawned targets clicked
			if (CP_Input_MouseClicked()) {
				for (int i = 0; i < idx; i++) {
					if (IsCircleClicked(
						game.clown_arr[i].x,
						game.clown_arr[i].y,
						diameter,
						CP_Input_GetMouseX(),
						CP_Input_GetMouseY()
					)) {
						game.clown_arr[i].state = KILLED;
						game.clown_arr[i].trans = 0;
					}
				}
			}

			// print timer
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_TextSize(50);

			char time[50] = { 0 };
			sprintf_s(time, _countof(time), "Timer : %.0f", (idx-10));
			CP_Font_DrawText(time, get_center_hor(), 50);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}

		else {
			endgamescreen();
		}
	}
	else if (game.isPaused == 1){
		//Pause screen
		game.isPaused = Pausescreen();
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
