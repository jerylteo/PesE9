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
	//CP_System_Fullscreen();
	//background = CP_Image_Load("/Assets/bg.png");

	CP_System_SetWindowSize(1270, 800);
	for (int i = 0; i < size; i++) {

		CLOWN clown ={ 
			CP_Random_RangeFloat(0 + (2 * diameter), width - (2 * diameter) ) ,
			CP_Random_RangeFloat(0 + (2 * diameter), height - (3 * diameter) ) ,
			255,
			ACTIVE
		};
		game.clown_arr[i].time_up = 0;

		game.clown_arr[i] = clown;
	}
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_System_SetFrameRate(60);

	game.totalElapsedTime = 0;
	game.isPaused = 0;
	game.score = 0;
}

void normal_update(void)
{
	if (game.isPaused == 0) {
		if (CP_Input_KeyDown(KEY_P)) {
			game.isPaused = 1;
		}
		CP_Graphics_ClearBackground(CP_Color_Create(200, 200, 200, 255));
		CP_Image_Draw(background, width / 2, height / 2, width, height, 155);

		float currentElapsedTime = CP_System_GetDt();
		
		game.totalElapsedTime += currentElapsedTime;
		//printf("%f\n",game.totalElapsedTime);

		if (game.totalElapsedTime <= 5 && game.totalElapsedTime >= 0) {

			for (int i = 0, displaycountdown = 5; i <= game.totalElapsedTime; i++, displaycountdown--) {
				float count = 5 - game.totalElapsedTime;
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Settings_TextSize(height/10);
				char countdown[50] = { 0 };
				sprintf_s(countdown, _countof(countdown), "Game starting in %.0f...", count--);
				CP_Font_DrawText(countdown, (float)width / 2, (float)height / 2);
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			}
		}
		else if (game.totalElapsedTime <= 15 && game.totalElapsedTime >= 5) {
			float timer = game.totalElapsedTime - 5;
			for (int i = 0; i + 5 < game.totalElapsedTime; i++) {

				drawclown(game.clown_arr[i].x, game.clown_arr[i].y, diameter, game.clown_arr[i].trans, true, false);
				if (game.clown_arr[i].state == ACTIVE) {
					game.clown_arr[i].time_up += currentElapsedTime;
				}

				if (CP_Input_MouseClicked()) {
					if (IsCircleClicked(game.clown_arr[i].x, game.clown_arr[i].y, diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && game.clown_arr[i].trans==255) {
						game.clown_arr[i].trans = 0;
						game.total_killed += 1;
						game.score += (50 * (5 - game.clown_arr[i].time_up));
						game.clown_arr[i].state = KILLED;
						//printf("Clicked\t");
					}
					if (game.clown_arr[i].state == KILLED) {
						game.score += 50;
						game.clown_arr[i].state = INACTIVE;
					}
				}

				//Setting Text Size, Colour and Alignment
				CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
				CP_Settings_TextSize(50);
				char time[50] = { 0 };
				sprintf_s(time, _countof(time), "Timer : %.0f", timer);
				CP_Font_DrawText(time, (float)width / 2, 50);
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
				char scoretext[50] = { 0 };
				sprintf_s(scoretext, _countof(scoretext), "Score : %.0f", game.score);
				CP_Font_DrawText(scoretext, (float)width / 4, 50);

			}
		}

		else {

			endgamescreen(game.score,"END");


		}
	}
	else if (game.isPaused==1){
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
