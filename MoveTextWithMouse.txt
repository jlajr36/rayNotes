#include "raylib.h"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Text Mover");

	const char* text = "Move this text";
	const int fontSize = 20;
	Vector2 textPosition = { 10.0f, 10.0f };
	int textWidth = MeasureText(text, fontSize);
	int topCornerPad = 5;
	int bottomCornerPad = 2 * topCornerPad;
	Rectangle textBox = {};

	Vector2 mousePos = { 0.0f, 0.0f };
	bool isDragging = false;
	Vector2 dragOffSet = { 0.0f, 0.0f };

	int infoFontSize = 5;

	while (!WindowShouldClose())
	{
		//Update
		mousePos = GetMousePosition();
		textBox = {
			textPosition.x - topCornerPad,
			textPosition.y - topCornerPad,
			(float)textWidth + bottomCornerPad,
			(float)fontSize + bottomCornerPad
		};
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			if (CheckCollisionPointRec(mousePos, textBox))
			{
				isDragging = true;
				dragOffSet = { 
					mousePos.x - textPosition.x,
					mousePos.y - textPosition.y 
				};
			}
		}

		if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			textPosition.x = mousePos.x - dragOffSet.x;
			textPosition.y = mousePos.y - dragOffSet.y;
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
		{
			isDragging = false;
		}
		
		//Drawing
		BeginDrawing();
		ClearBackground(LIGHTGRAY);
		DrawText(text, (int)textPosition.x, (int)textPosition.y, fontSize, DARKBLUE);
		if (isDragging)
		{
			DrawRectangleLinesEx(textBox, 2, RED);
			//Left Crosshair
			DrawLine(
				0,
				textBox.y + (textBox.height / 2),
				textBox.x,
				textBox.y + (textBox.height / 2),
				RED
			);
			//Right Crosshair
			DrawLine(
				textBox.x + textBox.width,
				textBox.y + (textBox.height / 2),
				screenWidth,
				textBox.y + (textBox.height / 2),
				RED
			);
			//Top Crosshair
			DrawLine(
				textBox.x + (textBox.width / 2),
				0,
				textBox.x + (textBox.width / 2),
				textBox.y,
				RED
			);
			//Buttom Crosshair
			DrawLine(
				textBox.x + (textBox.width / 2),
				textBox.y + textBox.height,
				textBox.x + (textBox.width / 2),
				screenHeight,
				RED
			);

			//Show Text Position
			DrawText(
				TextFormat("Left: %.2f, %.2f", textBox.x, textBox.y),
				textBox.x - 100,
				textBox.y,
				infoFontSize,
				BLUE
			);
			DrawText(
				TextFormat("Right: %.2f, %.2f", textBox.x + textBox.width, textBox.y),
				textBox.x + textBox.width + 5,
				textBox.y,
				infoFontSize,
				BLUE
			);
			DrawText(
				TextFormat("Top: %.2f, %.2f", textBox.x, textBox.y),
				textBox.x,
				textBox.y - 20,
				infoFontSize,
				BLUE
			);
			DrawText(
				TextFormat("Bottom: %.2f, %.2f", textBox.x, textBox.y + textBox.height),
				textBox.x,
				textBox.y + textBox.height + 5,
				infoFontSize,
				BLUE
			);
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
