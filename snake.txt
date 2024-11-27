#include <raylib.h>
#include <deque>
#include <raymath.h>
#include <iostream>

using namespace std;

const int cellSize = 30;
const int cellCount = 25;
const int offset = 75;
const int cellArea = (2 * offset) + cellSize * cellCount;

double lastUpdateTime = 0;

Color green = { 173, 204, 96, 255 };
Color darkGreen = { 43, 51, 24, 255 };

const int lineThickness = 5;
const int xyOffset = 5;
const int whOffset = 10;
Rectangle outSideBoarder = Rectangle
{
	offset-xyOffset,
	offset-xyOffset,
	cellSize*cellCount+whOffset,
	cellSize*cellCount+whOffset
};

const int fountSize = 40;
const int posXText = offset - 5;
const int posYText = 20;

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
	for (unsigned int i = 0; i < deque.size(); i++)
	{
		if (Vector2Equals(deque[i], element))
		{
			return true;
		}
	}
	return false;
}

bool eventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

class Snake
{
public:
	deque<Vector2> body = {
		Vector2{6, 9},
		Vector2{5, 9},
		Vector2{4, 9}
	};
	Vector2 direction = { 1, 0 };
	bool addSegment = false;

	void Draw()
	{
		for (unsigned int i = 0; i < body.size(); i++)
		{
			float x = body[i].x;
			float y = body[i].y;
			Rectangle segment = Rectangle{
				offset + x * cellSize,
				offset + y * cellSize,
				cellSize,
				cellSize
			};
			DrawRectangleRounded(segment, 0.5, 6, darkGreen);
		}
	}

	void Update()
	{
		body.push_front(Vector2Add(body[0], direction));
		if (addSegment)
		{
			addSegment = false;
		}
		else
		{
			body.pop_back();
		}
	}

	void Reset()
	{
		body = {
			Vector2{6, 9},
			Vector2{5, 9},
			Vector2{4, 9}
		};
		direction = { 1, 0 };
	}
};

class Food {
public:
	Vector2 position;
	Texture2D texture;

	Food(deque<Vector2> snakeBody)
	{
		Image image = LoadImage("Graphics/food.png");
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
		position = GenerateRandomPos(snakeBody);
	}

	~Food()
	{
		UnloadTexture(texture);
	}

	void Draw()
	{
		DrawTexture(
			texture,
			offset + position.x * cellSize,
			offset + position.y * cellSize,
			WHITE
		);
	}

	Vector2 GenerateRandomCell()
	{
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);
		return Vector2{ x, y };
	}

	Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
	{
		Vector2 position = GenerateRandomCell();
		while (ElementInDeque(position, snakeBody))
		{
			position = GenerateRandomCell();
		}
		return position;
	}
};

class Game
{
public:
	Snake snake = Snake();
	Food food = Food(snake.body);
	bool running = true;
	int score = 0;

	void Draw()
	{
		food.Draw();
		snake.Draw();
	}

	void Update()
	{
		if (running)
		{
			snake.Update();
			CheckCollisionWithFood();
			CheckCollisionWithEdges();
			CheckCollisionWithTail();
		}
	}

	void CheckCollisionWithFood()
	{
		if (Vector2Equals(snake.body[0], food.position))
		{
			food.position = food.GenerateRandomPos(snake.body);
			snake.addSegment = true;
			score++;
		}
	}

	void CheckCollisionWithEdges()
	{
		if (snake.body[0].x == cellCount || snake.body[0].x == -1)
		{
			GameOver();
		}
		if (snake.body[0].y == cellCount || snake.body[0].y == -1)
		{
			GameOver();
		}
	}

	void GameOver()
	{
		snake.Reset();
		food.position = food.GenerateRandomPos(snake.body);
		running = false;
		score = 0;
	}

	void CheckCollisionWithTail()
	{
		deque<Vector2> headlessBody = snake.body;
		headlessBody.pop_front();
		if (ElementInDeque(snake.body[0], headlessBody))
		{
			GameOver();
		}
	}
};

int main()
{
	const int screenWidth = cellArea;
	const int screenHeight = cellArea;
	const int fps = 60;

	InitWindow(
		screenWidth,
		screenHeight,
		"Retro Snake Game"
	);
	SetTargetFPS(fps);

	Game game = Game();

	while (!WindowShouldClose())
	{
		//Update
		if (eventTriggered(0.2))
		{
			game.Update();
		}
		if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
		{
			game.snake.direction = { 0, -1 };
			game.running = true;
		}
		if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
		{
			game.snake.direction = { 0, 1 };
			game.running = true;
		}
		if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
		{
			game.snake.direction = { -1, 0 };
			game.running = true;
		}
		if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
		{
			game.snake.direction = { 1, 0 };
			game.running = true;
		}

		//Draw
		BeginDrawing();
		ClearBackground(green);
		DrawRectangleLinesEx(
			outSideBoarder,
			lineThickness,
			darkGreen
		);
		DrawText("Retro Snake", posXText, posYText, fountSize, darkGreen);
		DrawText(
			TextFormat("%i", game.score),
			posXText,
			offset+cellSize*cellCount+whOffset,
			fountSize,
			darkGreen
		);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
