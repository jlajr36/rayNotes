#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <deque>

struct Star {
    float x;           // X position
    float y;           // Y position
    float angle;       // Angle in radians
    float speed;       // Speed of movement
    std::deque<Vector2> trail; // Trail positions
};

const int trailLength = 20; // Length of the trail

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Stars Moving Outward with Trail Effect");

    // Create a vector of stars
    std::vector<Star> stars;
    int numStars = 100;
    for (int i = 0; i < numStars; ++i) {
        Star star;
        star.x = static_cast<float>(rand() % screenWidth); // Random X position
        star.y = static_cast<float>(rand() % screenHeight); // Random Y position
        star.angle = atan2f(star.y - screenHeight / 2, star.x - screenWidth / 2); // Angle toward center
        star.speed = static_cast<float>(rand() % 3 + 1); // Speed between 1 and 3
        stars.push_back(star);
    }

    SetTargetFPS(60); // Set the game to run at 60 frames per second

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        for (auto& star : stars) {
            // Store current position in the trail
            if (star.trail.size() >= trailLength) {
                star.trail.pop_front(); // Remove oldest position
            }
            star.trail.push_back({ star.x, star.y }); // Add current position to trail

            // Move star outward
            star.x += star.speed * cosf(star.angle);
            star.y += star.speed * sinf(star.angle);

            // Reset star if it moves off the screen
            if (star.x < 0 || star.x > screenWidth || star.y < 0 || star.y > screenHeight) {
                star.x = static_cast<float>(rand() % screenWidth);
                star.y = static_cast<float>(rand() % screenHeight);
                star.angle = atan2f(star.y - screenHeight / 2, star.x - screenWidth / 2); // Update angle
                star.speed = static_cast<float>(rand() % 3 + 1); // Random speed
                star.trail.clear(); // Clear the trail
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto& star : stars) {
            // Draw the trail
            for (size_t j = 0; j < star.trail.size(); ++j) {
                int alpha = 255 - static_cast<int>(255 * j / trailLength); // Fade effect
                Color trailColor = { 255, 255, 255, static_cast<unsigned char>(alpha) }; // White color with fading alpha
                DrawPixel(static_cast<int>(star.trail[j].x), static_cast<int>(star.trail[j].y), trailColor);
            }

            // Draw the current star position
            DrawPixel(static_cast<int>(star.x), static_cast<int>(star.y), WHITE);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
