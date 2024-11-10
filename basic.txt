/********
*
* Basic Raylib Window with
*
*********/

#include "raylib.h"

// Main App Entry

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Basic Raylib Window.");

	const int fps = 60;
	
	SetTargetFPS(fps);

	const char* welcomeText = "This is a window!";
	int fontSize = 20;
	float spacing = 1.0f;
	Vector2 textSize = MeasureTextEx(GetFontDefault(), welcomeText, fontSize, spacing);

	int halfWidth = screenWidth / 2;
	int halfHeight = screenHeight / 2;

	int wordOffsetX = halfWidth - textSize.x;
	int wordOffsetY = halfHeight - textSize.y;

	while (!WindowShouldClose())
	{
		//** Draw Loop **
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawText(welcomeText, wordOffsetX, wordOffsetY, fontSize, RED);
		EndDrawing();
		//********
	}

	CloseWindow();

	return 0;
}
