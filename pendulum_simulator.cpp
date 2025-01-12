#include "raylib.h"
#include <cmath>

#define PI 3.14159f

// Constants for pendulum
const float G = 9.81f;   // Gravitational acceleration (m/s^2)
const float L = 2.0f;    // Length of pendulum (meters)

// Global variables for pendulum motion
float amplitude = PI / 4;  // Initial angle (45 degrees)
float frequency = 1.0f;  // Frequency in Hz
float angularFrequency = 2 * PI * frequency; // ω = 2π * frequency
float phase = 0.0f;  // Phase of the pendulum motion
float timeElapsed = 0.0f;  // Time accumulator

// Frequency bounds
const float minFrequency = 0.1f;
const float maxFrequency = 1.0f;

int main() {
    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Pendulum Simulator");

    // Pendulum position setup
    Vector2 pendulumOrigin = { screenWidth / 2, 150 };  // Anchor point of pendulum
    float pendulumLength = 400.0f; // Length in pixels
    Vector2 pendulumBob = { pendulumOrigin.x + pendulumLength * sin(amplitude), pendulumOrigin.y + pendulumLength * cos(amplitude) };

    SetTargetFPS(60);  // Set FPS to 60 for smooth animation

    // Main game loop
    while (!WindowShouldClose()) {
        // Update the time accumulator
        timeElapsed += GetFrameTime();

        // Calculate the angular frequency based on the current frequency
        angularFrequency = 2 * PI * frequency;

        // Calculate the angle of the pendulum
        float angle = amplitude * cos(angularFrequency * timeElapsed);

        // Update pendulum bob position based on the angle
        pendulumBob.x = pendulumOrigin.x + pendulumLength * sin(angle);
        pendulumBob.y = pendulumOrigin.y + pendulumLength * cos(angle);

        // Input handling for frequency adjustment
        if (IsKeyPressed(KEY_UP)) {
            frequency += 0.1f;  // Increase frequency
            if (frequency > maxFrequency) frequency = maxFrequency;  // Limit frequency to max
        }
        if (IsKeyPressed(KEY_DOWN)) {
            frequency -= 0.1f;  // Decrease frequency
            if (frequency < minFrequency) frequency = minFrequency;  // Limit frequency to min
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the pendulum
        DrawLineV(pendulumOrigin, pendulumBob, BLACK);  // Rod of the pendulum
        DrawCircleV(pendulumBob, 20, DARKBLUE);         // Bob of the pendulum

        // Draw text info
        DrawText("Pendulum Simulator", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Frequency: %.1f Hz", frequency), 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();  // Close window and OpenGL context

    return 0;
}
