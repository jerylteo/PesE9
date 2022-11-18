#include "cprocessing.h"
#include "utils.h"

int main(void)
{
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);

	//CP_Engine_SetNextGameState(Mode_Init, Mode_Update, Mode_Exit);

	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	//CP_Engine_SetNextGameState(normal_init, normal_update, normal_exit);
	CP_Engine_Run();
	return 0;
}
