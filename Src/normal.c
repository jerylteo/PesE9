#include "cprocessing.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define diameter CP_System_GetWindowHeight()/8.0f
#define size 100

GAME game;

void normal_init(void){
	CP_System_Fullscreen();
	//background = CP_Image_Load("/Assets/bg.png");

	//CP_System_SetWindowSize(1270, 800);
	for (int i = 0; i < size; i++) {

		CLOWN clown ={ 
			CP_Random_RangeFloat(0 + (2 * diameter), width - (2 * diameter) ) ,
			CP_Random_RangeFloat(0 + (2 * diameter), height - (3 * diameter) ) ,
			255,
			ACTIVE,
			0,
			0,
			TRUE,
			TRUE
		};
		game.clown_arr[i].time_up = 0;

		game.clown_arr[i] = clown;
	}
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);

	game.totalElapsedTime = 0;
	game.isPaused = 0;
	game.total_clicks = 0;
	game.total_killed = 0;
	game.accuracy = 0;
	game.score = 0;
}

void normal_update(void)
{
	CP_Image_Draw(background, width / 2, height / 2, width, height, 255);
	if (CP_Input_KeyDown(KEY_P)) {
		game.isPaused = 1;
	}
	else if (game.isPaused == 1) {
		//Pause screen
		game.isPaused = Pausescreen();
	}
	if (game.isPaused == 0) {

		CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));
		float currentElapsedTime = CP_System_GetDt();
		game.totalElapsedTime += currentElapsedTime;
		//printf("%f\n",game.totalElapsedTime);

		if (game.totalElapsedTime <= 3 && game.totalElapsedTime >= 0) {
			for (int i = 0; i <= game.totalElapsedTime; i++) {
				float count = 3 - (float)game.totalElapsedTime;
				CP_Settings_Fill(fontcolor);
				CP_Settings_TextSize(height / 10);
				char countdown[50] = { 0 };
				sprintf_s(countdown, _countof(countdown), "Game starting in %.0f...", count--);
				CP_Font_DrawText(countdown, get_center_hor(), get_center_ver());
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			}
		}
		else if (game.totalElapsedTime <= 13 && game.totalElapsedTime >= 3) {
			float idx = game.totalElapsedTime - 3;
			for (int i = 0; i + 3 < game.totalElapsedTime; i++) {

				drawclown(
					game.clown_arr[i].x,
					game.clown_arr[i].y,
					diameter,
					game.clown_arr[i].trans,
					FALSE,
					FALSE
				);
				if (game.clown_arr[i].state == ACTIVE) {
					game.clown_arr[i].time_up += currentElapsedTime;
				}
			}
			if (CP_Input_MouseClicked()) {
				game.total_clicks += 1;
				printf("click %d\n", game.total_clicks);
				for (int i = 0; i < idx; i++) {
					if (IsCircleClicked(
						game.clown_arr[i].x,
						game.clown_arr[i].y,
						diameter,
						CP_Input_GetMouseX(),
						CP_Input_GetMouseY())
					&& game.clown_arr[i].state == ACTIVE) {
						game.clown_arr[i].trans = 0;
						game.total_killed += 1;
						printf("killed %d\n", game.total_killed);
						game.score += (50 * (5 - game.clown_arr[i].time_up));
						game.clown_arr[i].state = KILLED;
						//printf("Clicked\t");
					}
				}
			}
			//if kill 2 bugs with 1 click
			if (game.accuracy > 100)game.total_clicks--;
			//calculate accuracy
			game.accuracy = game.total_clicks > 0 ? ((float)game.total_killed / (float)game.total_clicks) * 100.0f : 0;

			// print timer
			CP_Settings_Fill(fontcolor);
			CP_Settings_TextSize(50);

			char time[100] = { 0 };
			sprintf_s(time, _countof(time), "Timer : %.0f | Accuracy: %.1f | Score: %.0f | Life: %d/5", (10 - idx), game.accuracy, game.score, game.life);
			CP_Font_DrawText(time, get_center_hor(), 50);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

		}

		else {
			endgamescreen(game.score,"END");

		}
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
