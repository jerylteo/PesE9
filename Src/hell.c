#include "utils.h"
#define diameter CP_System_GetWindowHeight()/8.0f

GAME game;

// game core functions
void hell_init(void)
{
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);
	CP_System_SetFrameRate(60);
	for (int i = 0; i < 100; i++) {
		CLOWN clown = {
			CP_Random_RangeFloat(2 * diameter, width - (2 * diameter)),
			CP_Random_RangeFloat(2 * diameter, height - (3 * diameter)),
			255,
			INACTIVE,
			CP_Random_RangeFloat(0, 360),
			CP_Random_GetBool()
		};
		game.clown_arr[i] = clown;
	}

	CP_Settings_RectMode(CP_POSITION_CENTER);
	game.isPaused = 0;
	game.speed = 5;
	game.total_clicks = 0;
	game.total_killed = 0;
	game.accuracy = 0;
	game.life = 3;
}

void hell_update(void)
{		
	// if game is running
	if (game.isPaused == 0) {
		if (CP_Input_KeyDown(KEY_P)) game.isPaused = 1;

		CP_Graphics_ClearBackground(bg_gray);
		float currentElapsedTime = CP_System_GetDt();
		static float totalElapsedTime = 0;
		totalElapsedTime += currentElapsedTime;

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
		// 5 - 35 seconds
		// game running
		else if (5 <= totalElapsedTime && totalElapsedTime <= 35) {
			int total_clicks = 0;
			float accuracy = 0.0f;
			float idx = totalElapsedTime - 5;

			// spawn moving targets
			for (int i = 0; i+5 < totalElapsedTime; i++) {
				if ((game.clown_arr[i].x < 0 + (diameter / 2.0f) && game.clown_arr[i].angle > 180 && game.clown_arr[i].angle < 270) ||
					(game.clown_arr[i].x > width - (diameter / 2.0f) && game.clown_arr[i].angle < 90 && game.clown_arr[i].angle > 0) ||
					(game.clown_arr[i].y < 0 + (diameter / 2.0f) && game.clown_arr[i].angle > 270 && game.clown_arr[i].angle < 360) ||
					(game.clown_arr[i].y > height - (diameter / 2.0f) && game.clown_arr[i].angle > 90) && game.clown_arr[i].angle < 180) {
					game.clown_arr[i].angle += 90;
				}
				else if ((game.clown_arr[i].x < 0 + (diameter / 2.0f) && game.clown_arr[i].angle < 180 && game.clown_arr[i].angle > 90) ||
					(game.clown_arr[i].x > width - (diameter / 2.0f) && game.clown_arr[i].angle > 270 && game.clown_arr[i].angle < 360) ||
					(game.clown_arr[i].y < 0 + (diameter / 2.0f) && game.clown_arr[i].angle < 270 && game.clown_arr[i].angle > 180) ||
					(game.clown_arr[i].y > height - (diameter / 2.0f) && game.clown_arr[i].angle < 90) && game.clown_arr[i].angle > 0) {
					game.clown_arr[i].angle -= 90;
				}

				if (game.clown_arr[i].angle > 360) game.clown_arr[i].angle -= 360;
				if (game.clown_arr[i].angle < 0) game.clown_arr[i].angle += 360;
				CP_Vector vector_angle = AngleToVector(CP_Math_Radians(abs(game.clown_arr[i].angle)));

				game.clown_arr[i].x += vector_angle.x * game.speed;
				game.clown_arr[i].y += vector_angle.y * game.speed;


				drawclown(
					game.clown_arr[i].x,
					game.clown_arr[i].y,
					diameter,
					game.clown_arr[i].trans,
					game.clown_arr[i].fake
				);
			}


			//checks if any spawned targets clicked
			bool die = FALSE;
			if (CP_Input_MouseClicked()) {
				game.total_clicks += 1;
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
						game.total_killed += 1;
						if (game.clown_arr[i].fake) die = TRUE;
					}
					//else die = TRUE;
				}
			}

			// handle dead
			if (die) game.life -= 1;
			if (!game.life) endgamescreen();

			// handle accuracy
			game.accuracy = game.total_clicks > 0 ? ((float)game.total_killed / (float)game.total_clicks) * 100.0f : 0;
			

			// print timer
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_TextSize(50);

			char time[50] = { 0 };
			sprintf_s(time, _countof(time), "Timer : %.0f | Accuracy: %.1f | Life: %d/3", (idx-10), game.accuracy, game.life);
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

void hell_exit(void)
{
	//CP_Engine_SetNextGameStateForced(normal_init, normal_update, normal_exit);
}
