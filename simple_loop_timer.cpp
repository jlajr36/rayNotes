#include "raylib.h"
#include "raymath.h"

typedef struct
{
	float Lifetime;
}Timer;

// Start a timer with a specific lifetime
void StartTimer(Timer* timer, float lifetime)
{
	if (timer != NULL)
	{
		timer->Lifetime = lifetime;
	}
}

// update with current frame time
void UpdateTimer(Timer* timer)
{
	//Subject time if timer has not expired
	if (timer != NULL && timer->Lifetime > 0)
	{
		timer->Lifetime -= GetFrameTime();
	}
}

// Check if time is out.
bool TimerDone(Timer* timer)
{
	if (timer != NULL)
	{
		return timer->Lifetime <= 0;
	}
	return false;
}

int main()
{
	InitWindow(1200, 800, "Timer");
	SetTargetFPS(60);

	float radius = 20;
	float speed = 400;
	Vector2 pos = { radius, 400 };
	Vector2 dir = { 1, 0 };

	float ballLife = 2.0f;

	Timer ballTimer = { 0 };

	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			pos = GetMousePosition();
			StartTimer(&ballTimer, ballLife);
		}
		UpdateTimer(&ballTimer);
		// Move ball if time is going
		if (!TimerDone(&ballTimer))
		{
			pos = Vector2Add(pos, Vector2Scale(dir, GetFrameTime() * speed));

			if (pos.x > GetScreenWidth() - radius)
			{
				pos.x = GetScreenWidth() - radius;
				dir.x = -1;
			}
			else if (pos.x < radius)
			{
				pos.x = radius;
				dir.x = 1;
			}
		}

		BeginDrawing();
			ClearBackground(BLACK);
			if (!TimerDone(&ballTimer))
			{
				DrawCircleV(pos, radius, RED);
			}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
