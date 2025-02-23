#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <vector>

// Define a structure to store the position and color together
struct Point {
    Vector2 position;
    Color color;
};

// Linear interpolation between two colors
Color LerpColor(Color start, Color end, float t) {
    return Color{
        (unsigned char)(start.r + (end.r - start.r) * t),
        (unsigned char)(start.g + (end.g - start.g) * t),
        (unsigned char)(start.b + (end.b - start.b) * t),
        (unsigned char)(start.a + (end.a - start.a) * t)
    };
}

int main() {
    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Random Walk with Color Gradient");

    // Seed random number generator
    std::srand(std::time(0));

    // Initial position is in the center of the screen
    Vector2 position = { (float)screenWidth / 2, (float)screenHeight / 2 };

    // Store all points visited by the random walk along with their color
    std::vector<Point> points;

    // Define start and end colors for the gradient transition
    Color startColor = RED;
    Color endColor = BLUE;

    // Set the random walk step size
    const float stepSize = 5.0f;

    // Progress variable to handle the gradient interpolation
    float progress = 0.0f;

    // Main game loop
    while (!WindowShouldClose()) {
        // Update logic
        if (IsKeyPressed(KEY_SPACE)) {
            // Reset the points and position to the center when spacebar is pressed
            points.clear();
            position = { (float)screenWidth / 2, (float)screenHeight / 2 };
            points.push_back({ position, startColor });
            progress = 0.0f; // Reset gradient progress
        } else {
            // Random walk: move in a random direction
            int direction = std::rand() % 4;
            switch (direction) {
                case 0: position.x += stepSize; break; // Move right
                case 1: position.x -= stepSize; break; // Move left
                case 2: position.y += stepSize; break; // Move down
                case 3: position.y -= stepSize; break; // Move up
            }

            // Check if the position is outside the screen boundaries
            if (position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight) {
                // Reset to center if off-screen
                position = { (float)screenWidth / 2, (float)screenHeight / 2 };
            }

            // Calculate the interpolated color between startColor and endColor based on progress
            Color currentColor = LerpColor(startColor, endColor, progress);

            // Store the new position with its color
            points.push_back({ position, currentColor });

            // Increase the progress to create a smooth color transition (wrap around after 1.0)
            progress += 0.005f; // Adjust this value for faster/slower gradient transition
            if (progress > 1.0f) progress = 0.0f; // Wrap around to create a continuous gradient
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw all the visited points with their gradient colors
        for (size_t i = 0; i < points.size(); ++i) {
            // Draw each point with its fixed color
            DrawCircleV(points[i].position, 2.0f, points[i].color);
        }

        // Draw the instructions
        DrawText("Press SPACE to reset the walk.", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close the window and OpenGL context

    return 0;
}
