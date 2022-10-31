#include "cprocessing.h"
#include "mainmenu.h"
#include "splashscreen.h"
#include "normal.h"

int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(normal_init, normal_update, normal_exit);
	CP_Engine_Run();
	return 0;
}