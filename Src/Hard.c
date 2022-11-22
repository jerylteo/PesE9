#include "utils.h"

#define SIZE 40
#define diameter CP_System_GetWindowHeight()/8.0f

GAME game;
float temp[SIZE];

// game core functions
void hard_init(void)
{

	background = CP_Image_Load("Assets/bg.png");
	CP_System_Fullscreen();
	//CP_System_SetWindowSize(1280, 720);
	CP_System_SetFrameRate(60);
	for (int i = 0; i < SIZE; i++) {
		bool fake = FALSE;
		if (i == 4 || i == 8 || i == 13)fake = TRUE;
		CLOWN clown = {
			CP_Random_RangeFloat(0 + (2 * diameter), (float)width - (2 * diameter)),
			CP_Random_RangeFloat(0 + (2 * diameter), (float)height - (3 * diameter)),
			255,
			ACTIVE,
			0,
			0,
			FALSE,
			TRUE
		};
		CLOWN movingclown = {
			CP_Random_RangeFloat(0 + (2 * diameter), (float)width - (2 * diameter)),
			CP_Random_RangeFloat(0 + (2 * diameter), (float)height - (3 * diameter)),
			255,
			ACTIVE,
			0,
			CP_Random_RangeFloat(0,360),
			fake,
			TRUE
		};
		//if (game.movingclown_arr[i].fake == TRUE)game.movingclown_arr[i].state = ACTIVE;

		game.clown_arr[i].time_up = 0;
		game.clown_arr[i] = clown;
		game.movingclown_arr[i] = movingclown;
		temp[i] = CP_Random_RangeFloat(1,2);
	}
	game.totalElapsedTime = 0;
	game.isPaused = 0;
	game.total_clicks = 0;
	game.total_killed = 0;
	game.accuracy = 0;
	game.life = 5;
	game.score = 0;
	game.speed = 4;
}

void hard_update(void)
{		
	CP_Image_Draw(background, width / 2, height / 2, width, height, 255);
	if (CP_Input_KeyDown(KEY_P)) {
		game.isPaused = 1;	
	}
	else if (game.isPaused == 1) {
		//Pause screen
		game.isPaused = Pausescreen();
	}
	// if game is running
	if (game.isPaused == 0) {

		CP_Graphics_ClearBackground(white);
		float currentElapsedTime = CP_System_GetDt();
		game.totalElapsedTime += currentElapsedTime;
		float idx = (game.totalElapsedTime - 3.0f)/ 2.0f;

		// 0 - 4 seconds
		// countdown to game start
		if (0 <= game.totalElapsedTime && game.totalElapsedTime <= 3) {
			for (int i = 0; i <= game.totalElapsedTime; i++) {
				float count = 3 - (float)game.totalElapsedTime;
				CP_Settings_Fill(fontcolor);
				CP_Settings_TextSize(height/10);
				char countdown[50] = { 0 };
				sprintf_s(countdown, _countof(countdown), "Game starting in %.0f...", count--);
				CP_Font_DrawText(countdown, get_center_hor(), get_center_ver());
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			}
		}

		// 3 - ?? seconds
		// game running
		else if (3 <= game.totalElapsedTime && idx <= game_timer && game.life > 0) {
			game.totalElapsedTime += currentElapsedTime;
			//last 5 seconds timer
			if ((game_timer - idx) <= 5) {
				CP_Settings_TextSize(height / 2);
				CP_Settings_Fill(grey);
				CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
				char fiveseconds[100] = { 0 };
				sprintf_s(fiveseconds, _countof(fiveseconds), "%.1f", (game_timer - idx));
				CP_Font_DrawText(fiveseconds, get_center_hor(), get_center_ver());
			}
			//moving circle code
			for (int i = 0;( i + 3) < game.totalElapsedTime; i++) {
				if (game.bounce == FALSE) {
					if ((game.movingclown_arr[i].x < 0 + (diameter / 2.0f) && game.movingclown_arr[i].angle > 180 && game.movingclown_arr[i].angle < 270) ||
						(game.movingclown_arr[i].x > width - (diameter / 2.0f) && game.movingclown_arr[i].angle < 90 && game.movingclown_arr[i].angle > 0) ||
						(game.movingclown_arr[i].y < 0 + (diameter / 2.0f) && game.movingclown_arr[i].angle > 270 && game.movingclown_arr[i].angle < 360) ||
						(game.movingclown_arr[i].y > height - (diameter / 2.0f) && game.movingclown_arr[i].angle > 90) && game.movingclown_arr[i].angle < 180) {
						game.movingclown_arr[i].angle += 90;
						game.bounce = TRUE;
					}
					else if ((game.movingclown_arr[i].x < 0 + (diameter / 2.0f) && game.movingclown_arr[i].angle < 180 && game.movingclown_arr[i].angle > 90) ||
						(game.movingclown_arr[i].x > width - (diameter / 2.0f) && game.movingclown_arr[i].angle > 270 && game.movingclown_arr[i].angle < 360) ||
						(game.movingclown_arr[i].y < 0 + (diameter / 2.0f) && game.movingclown_arr[i].angle < 270 && game.movingclown_arr[i].angle > 180) ||
						(game.movingclown_arr[i].y > height - (diameter / 2.0f) && game.movingclown_arr[i].angle < 90) && game.movingclown_arr[i].angle > 0) {
						game.movingclown_arr[i].angle -= 90;
						game.bounce = TRUE;
					}
				}
				game.bounce = FALSE;
				if (game.movingclown_arr[i].angle > 360) game.movingclown_arr[i].angle -= 360;
				if (game.movingclown_arr[i].angle < 0) game.movingclown_arr[i].angle += 360;
				CP_Vector vector_angle = AngleToVector(CP_Math_Radians(abs(game.movingclown_arr[i].angle)));

				game.movingclown_arr[i].x += vector_angle.x * game.speed;
				game.movingclown_arr[i].y += vector_angle.y * game.speed;

			//spawn circle every second
				drawclown(
					game.clown_arr[i].x,
					game.clown_arr[i].y,
					diameter / temp[i],
					game.clown_arr[i].trans,
					game.clown_arr[i].fake,
					FALSE
					);
				if (game.movingclown_arr[i].fake == TRUE)
				{
					drawclown(
						game.movingclown_arr[i].x,
						game.movingclown_arr[i].y,
						diameter / temp[i],
						game.movingclown_arr[i].trans,
						game.movingclown_arr[i].fake,
						FALSE
					);
				}
				if (game.clown_arr[i].state == ACTIVE) {
					game.clown_arr[i].time_up += currentElapsedTime;
				}
			}
			//checks if any spawned targets clicked
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
				game.total_clicks += 1;
				for (int i = 0; i  < game.totalElapsedTime; i++) {
					//killed targets
					if (IsCircleClicked(
						game.clown_arr[i].x,
						game.clown_arr[i].y,
						diameter/temp[i],
						CP_Input_GetMouseX(),
						CP_Input_GetMouseY())
					 && game.clown_arr[i].state == ACTIVE) {
							game.clown_arr[i].trans = 0;
							game.total_killed += 1;
							game.score += (50 * (5 - game.clown_arr[i].time_up));
							game.clown_arr[i].state = KILLED;
					}
					//fake target click
					if (IsCircleClicked(
						game.movingclown_arr[i].x,
						game.movingclown_arr[i].y,
						diameter / temp[i],
						CP_Input_GetMouseX(),
						CP_Input_GetMouseY())
					&& game.movingclown_arr[i].state == ACTIVE
					&& game.movingclown_arr[i].fake == TRUE) {
						game.movingclown_arr[i].trans = 0;
						game.life -= 1;
						CP_Settings_Fill(dead);
						CP_Graphics_DrawRect(get_center_hor(), get_center_ver(), width, height);
						game.movingclown_arr[i].state = KILLED;

					}
				}
			}
			/*no clicked*/
			for (int i = 0; i < SIZE; i++) {
				if (game.clown_arr[i].time_up >= 2 && game.clown_arr[i].state == ACTIVE) {
					game.clown_arr[i].trans = 0;
					game.life -= 1;
					CP_Settings_Fill(dead);
					CP_Graphics_DrawRect(get_center_hor(), get_center_ver(), width, height);
					game.clown_arr[i].state = TIMED_OUT;
				}
			}
			//if kill 2 bugs with 1 click
			if (game.accuracy > 100)game.total_clicks++;
			//calculate accuracy
			game.accuracy = game.total_clicks > 0 ? ((float)game.total_killed / (float)game.total_clicks) * 100.0f : 0;
			// print timer
			CP_Settings_Fill(fontcolor);
			CP_Settings_TextSize(75);

			char time[100] = { 0 };
			sprintf_s(time, _countof(time), "Timer : %.0f | Accuracy: %.1f%% | Score: %.0f ", (game_timer - idx), game.accuracy, game.score);
			CP_Font_DrawText(time, get_center_hor(), 50);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);


			//draw hearts
			for (int i = 1; i <= 5; i++) {
				int hearttrans;
				if (i <= game.life ) hearttrans = 255;
				else hearttrans = 0;
					CP_Image_Draw(heart, diameter * i, height - diameter, diameter, diameter, hearttrans);
			}
		}
		else if (game.life <= 0) {
			endgamescreen(game.score, game.accuracy, "LOSE");

		}
		else {
			//CP_Engine_SetNextGameState(End_Game_Init, End_Game_Update, End_Game_Exit);
			endgamescreen(game.score, game.accuracy, "end");
		}
	}

}

void hard_exit(void)
{
	//CP_Engine_SetNextGameStateForced(normal_init, normal_update, normal_exit);
}
