#include <iostream>
#include "entities.h"
#include "grid.h"

Color darkGreen = {162, 209, 73, 255};
Color limeGreen = {170, 215, 81, 255};
Color oliveGreen = {87, 138, 52, 255};

double lastUpdateTime = 0;

bool eventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Game{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);

    void Draw(){
        food.Draw();
        snake.Draw();
    }
    void Update(){
        snake.Update();
        checkCollisionWithFood();
    }
    void checkCollisionWithFood(){
        if (snake.body.buffer[0].x == food.pos.x && snake.body.buffer[0].y == food.pos.y){
            food.pos = food.GeneratePos(snake.body);
            snake.addSegment = true;
        }
    }
};

int main()
{
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Linky Snake");
    Game game = Game();
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);

        if (eventTriggered(0.1))
            game.Update();

        if((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.direction.y != 1)
            game.snake.direction = {0, -1};

        if((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game.snake.direction.y != -1)
            game.snake.direction = {0, 1};

        if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game.snake.direction.x != 1)
            game.snake.direction = {-1, 0};
        
        if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game.snake.direction.x != -1)
            game.snake.direction = {1, 0};

        for (int i = 2; i < cellCount-2; i++){
            for (int j = 2; j < cellCount-2; j++){
                if(i == 2 || i == cellCount - 3 || j == 2 || j == cellCount - 3)
                    DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, oliveGreen);
                else if (i%2 == 0 && j%2 == 1)
                    DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, limeGreen);
                else if (i%2 == 1 && j%2 == 0)
                    DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, limeGreen);
                    // DrawRectangleLines(i * cellSize, j * cellSize, cellSize, cellSize, WHITE);
            }
        }
        game.Draw();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
