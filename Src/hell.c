#include "utils.h"
#define diameter CP_System_GetWindowHeight()/8.0f
#define SIZE 35

GAME game;
float temp[SIZE];
int super_time;


// game core functions
void hell_init(void)
{
	//CP_System_Fullscreen();
	CP_System_SetWindowSize(1280, 720);
	CP_System_SetFrameRate(60);
	for (int i = 0; i < SIZE; i++) {
		super_time = CP_Random_RangeInt(0, 29);
		bool fake = FALSE;
		if (super_time == 0 || super_time == 9 || super_time == 19 || super_time == 29) fake = TRUE;

		

		
		CLOWN clown = {
			CP_Random_RangeFloat(2 * diameter, width - (2 * diameter)),
			CP_Random_RangeFloat(2 * diameter, height - (3 * diameter)),
			255,
			ACTIVE,
			0,
			CP_Random_RangeFloat(0, 360),
			fake,
			FALSE
		};
		game.clown_arr[i] = clown;
		temp[i] = CP_Random_RangeFloat(1, 3);
	}

	CP_Settings_RectMode(CP_POSITION_CENTER);
	game.totalElapsedTime = 0;
	game.isPaused = 0;
	//game.speed = 5;
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
		game.totalElapsedTime += currentElapsedTime;

		// 0 - 3 seconds
		// countdown to game start
		if (0 <= game.totalElapsedTime && game.totalElapsedTime <= 3) {
			for (int i = 0; i <= game.totalElapsedTime; i++) {
				float count = 3 - (float)game.totalElapsedTime;
				CP_Settings_Fill(black);
				CP_Settings_TextSize(100);
				char countdown[50] = { 0 };
				sprintf_s(countdown, _countof(countdown), "Game starting in %.0f...", count--);
				CP_Font_DrawText(countdown, get_center_hor(), get_center_ver());
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			}
		}
		// 3 - 33 seconds
		// game running
		else if (3 <= game.totalElapsedTime && game.totalElapsedTime <= 33 && game.life > 0) {
			int total_clicks = 0;
			float accuracy = 0.0f;
			float idx = game.totalElapsedTime - 3;

			// spawn moving targets
			for (int i = 0; i + 3 < game.totalElapsedTime; i++) {
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

				if (i == super_time) game.clown_arr[i].super = TRUE;
				game.speed = CP_Random_RangeInt(3, 7);
				game.clown_arr[i].x += (game.clown_arr[i].super) ? vector_angle.x * game.speed * 3 : vector_angle.x * game.speed;
				game.clown_arr[i].y += (game.clown_arr[i].super) ? vector_angle.y * game.speed * 3 : vector_angle.y * game.speed;

				//if (super_spawned) game.clown_arr[i].super = FALSE;

				drawclown(
					game.clown_arr[i].x,
					game.clown_arr[i].y,
					diameter / temp[i],
					game.clown_arr[i].trans,
					game.clown_arr[i].fake,
					game.clown_arr[i].super
				);

				if (game.clown_arr[i].state == ACTIVE) {
					game.clown_arr[i].time_up += currentElapsedTime;
				}
			}


			//checks if any spawned targets clicked
			bool die = FALSE;
			if (CP_Input_MouseClicked()) {
				game.total_clicks += 1;
				for (int i = 0; i < idx; i++) {
					int multi = 1;
					if (IsCircleClicked(
						game.clown_arr[i].x,
						game.clown_arr[i].y,
						diameter / temp[i],
						CP_Input_GetMouseX(),
						CP_Input_GetMouseY()
					) && game.clown_arr[i].state == ACTIVE) {
						game.clown_arr[i].trans = 0;
						if (game.clown_arr[i].fake && !game.clown_arr[i].super) die = TRUE;
						else if (game.clown_arr[i].super) multi = 5;
						else {
							game.total_killed += 1;
							game.score += (50 * (5 - game.clown_arr[i].time_up)) * multi;
						}
						multi = 1;
						game.clown_arr[i].state = KILLED;
					}
					//else die = TRUE;
				}
			}
			
			// if no click
			for (int i = 0; i < SIZE; i++) {
				if (game.clown_arr[i].time_up >= 1.5 && game.clown_arr[i].state == ACTIVE && !game.clown_arr[i].fake && !game.clown_arr[i].super) {
					game.clown_arr[i].trans = 0;
					game.life -= 1;
					game.clown_arr[i].state = TIMED_OUT;
				}
				else if (game.clown_arr[i].time_up > 1 && game.clown_arr[i].super) {
					game.clown_arr[i].trans = 0;
					game.clown_arr[i].state = TIMED_OUT;
				}
			}

			// handle dead
			if (die) game.life -= 1;
			if (!game.life) endgamescreen(game.score, "LOSE");

			// handle accuracy
			game.accuracy = game.total_clicks > 0 ? ((float)game.total_killed / (float)game.total_clicks) * 100.0f : 0;


			// print timer
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_TextSize(50);

			char time[100] = { 0 };
			sprintf_s(time, _countof(time), "Timer : %.0f | Accuracy: %.1f | Score: %.0f | Life: %d/3", idx, game.accuracy, game.score, game.life);
			CP_Font_DrawText(time, get_center_hor(), 50);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		}
		else if (game.life <= 0) endgamescreen(game.score, "LOSE");
		else endgamescreen(game.score, "end");
		
	}
	else if (game.isPaused == 1) {
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
