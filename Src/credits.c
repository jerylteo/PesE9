#include "cprocessing.h"
#include "utils.h"

void credits_init(void) {

	creditscreen_img = CP_Image_Load("Assets/credits1.png");
	back_img = CP_Image_Load("Assets/backbutton.png");
	back_img2 = CP_Image_Load("Assets/backbutton2.png");

}
void credits_update(void) {

	CP_Image_Draw(creditscreen_img, width / 2.0f, height / 2.0f, width / 5.0f * 4.0f, height / 5.0f * 4.0f, 255);
	CP_Image_Draw(back_img, width / 2, height - (button_height * 1.75), button_width, button_height, 255);
	if (IsAreaClicked(width / 2, height - (button_height * 1.75), button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
		CP_Image_Draw(back_img2, width / 2, height - (button_height * 1.75), button_width, button_height, 255);
	}

	if (CP_Input_MouseReleased(MOUSE_BUTTON_1)) {
		if (IsAreaClicked(width / 2, height - (button_height * 1.75), button_width, button_height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}
}
void credits_exit(void) {

}
