#pragma once

typedef struct recto {
	float x;
	float y;
	int width;
	int height;
}rect;

void Main_Menu_Init(void);
void Main_Menu_Update(void);
void Main_Menu_Exit(void);