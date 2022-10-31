#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include "normal.h"

rect start, end, tutorial;

void Main_Menu_Init()
{
    CP_System_Fullscreen();
    CP_Settings_RectMode(CP_POSITION_CENTER);
}

void Main_Menu_Update()
{
    start = (rect){ CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, 200, 50 };
    tutorial = (rect){ CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f + 100, 200, 50 };
    end = (rect){ CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f + 200, 200, 50 };

    CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));

    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    // Start button
    CP_Graphics_DrawRect(start.x,start.y,start.width,start.height);
    // Exit Button
    CP_Graphics_DrawRect(end.x, end.y, end.width, end.height);
    CP_Graphics_DrawRect(tutorial.x, tutorial.y, tutorial.width, tutorial.height);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    //Setting Text Size, Colour and Alignment
    CP_Settings_TextSize(20);
    CP_Font_DrawText("Play", start.x, start.y);
    CP_Font_DrawText("Exit", end.x, end.y);
    CP_Font_DrawText("How to Play", tutorial.x, tutorial.y);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    // For when left clicked is pressed
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
    {
        if (IsAreaClicked(start.x, start.y, start.width, start.height,CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
            CP_Engine_SetNextGameStateForced(normal_init, normal_update, normal_exit);
        }
        if (IsAreaClicked(end.x, end.y, end.width, end.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
        {
            CP_Engine_Terminate();
        }
    }
}

void Main_Menu_Exit(){}