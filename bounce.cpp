#include "raylib.h"

int main(void)
{
    // Set the MSAA level (4x anti-aliasing)
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Bounce the Ball");

    // Set the target FPS (frames per second)
    SetTargetFPS(60);

    // Settings
    int x = screenWidth / 2;
    int y = screenHeight / 2;
    float xspeed = 1.0f;
    float yspeed = 3.3f;

    // Circle parameters
    int circleRadius = 10;
    Vector2 circlePosition = { (float)x, (float)y };

    // Main game loop
    while (!WindowShouldClose())    // Until the window should close
    {
        // Move ball by speed
        x = x + xspeed;
        y = y + yspeed;

        // Check for bounce
        if ((x > screenWidth) || (x < 0)) {
            xspeed = xspeed * -1;
        }
        if ((y > screenHeight) || (y < 0)) {
            yspeed = yspeed * -1;
        }

        // Update position
        circlePosition = { (float)x, (float)y };

        // Begin drawing
        BeginDrawing();

        // Clear background
        ClearBackground(RAYWHITE);

        // Draw the red circle
        DrawCircleV(circlePosition, circleRadius, RED);

        // End drawing
        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close the window and OpenGL context

    return 0;
}
