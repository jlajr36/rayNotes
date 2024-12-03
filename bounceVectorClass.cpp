#include "raylib.h"

// VectorClass: A simple class to represent 2D vectors (x, y)
class VectorClass {
public:
    float x, y;  // Coordinates of the vector

    // Constructor to initialize vector with given x, y or default to (0, 0)
    VectorClass(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

    // Method to add another vector to the current vector
    void add(VectorClass vec) {
        x += vec.x;  // Add x component
        y += vec.y;  // Add y component
    }
};

int main(void)
{
    // Set the MSAA level (4x anti-aliasing) for smoother graphics
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    // Initialize the window with specified width and height
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Bounce the Ball");

    // Set the target FPS (frames per second) to 60 for smooth animation
    SetTargetFPS(60);

    // Create a position vector for the ball, starting at the center of the screen
    VectorClass position(screenWidth / 2, screenHeight / 2);
    // Create a velocity vector for the ball, controlling the direction and speed
    VectorClass velocity(1.0f, 3.3f);

    // Ball radius for rendering
    int circleRadius = 10;

    // Main game loop - keeps running until the window should close
    while (!WindowShouldClose())    // Until the window should close
    {
        // Update the ball's position by adding the velocity to its current position
        position.add(velocity);

        // Check if the ball hits the horizontal boundaries (left or right)
        if ((position.x > screenWidth) || (position.x < 0)) {
            velocity.x = -velocity.x;  // Reverse the horizontal velocity to make the ball bounce
        }

        // Check if the ball hits the vertical boundaries (top or bottom)
        if ((position.y > screenHeight) || (position.y < 0)) {
            velocity.y = -velocity.y;  // Reverse the vertical velocity to make the ball bounce
        }

        // Begin drawing operations
        BeginDrawing();

        // Clear the screen with a white background color
        ClearBackground(RAYWHITE);

        // Draw the ball (a red circle) at the updated position
        DrawCircle(position.x, position.y, circleRadius, RED);

        // End drawing operations
        EndDrawing();
    }

    // De-Initialization: Close the window and OpenGL context when the game ends
    CloseWindow(); // Close the window and OpenGL context

    return 0;
}
