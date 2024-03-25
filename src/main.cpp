#include <iostream>
#include "entities.h"
#include "grid.h"

Color darkGreen = {162, 209, 73, 255};
Color limeGreen = {170, 215, 81, 255};
Color oliveGreen = {87, 138, 52, 255};

static bool allowMove = false;
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
    bool running = true;
    int score = 0;

    void Draw(){
        food.Draw();
        snake.Draw();
    }
    void Update(){
        if(running){
            snake.Update();
            checkCollisionWithFood();
            checkCollisionWithEdges();
        }
    }
    void checkCollisionWithFood(){
        if (snake.body.buffer[0].x == food.pos.x && snake.body.buffer[0].y == food.pos.y){
            food.pos = food.GeneratePos(snake.body);
            snake.addSegment = true;
            score++;
        }
    }
    void checkCollisionWithEdges(){
        if (snake.body.buffer[0].x == cellSize ||  snake.body.buffer[0].x == -1 ){
            GameOver();
        }

        if (snake.body.buffer[0].y == cellSize ||  snake.body.buffer[0].y == -1 ){
            GameOver();
        }
    }
    void checkCollisionWithTail(){
        Body headlessBody = snake.body;
        headlessBody.pop_front();
        if(ElementInSnakeBody(snake.body.buffer[0], headlessBody)){
            GameOver();
        }
    }
    void GameOver(){
        snake.Reset();
        food.pos = food.GeneratePos(snake.body);
        running = false;
        score = 0;
    }
};

int main()
{
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Linky Snake");
    Game game = Game();
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (eventTriggered(0.15)){
            allowMove = true;
            game.Update();
        }

        if((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.direction.y != 1 && allowMove){
            game.snake.direction = {0, -1};
            game.running = true;
            allowMove = false;
        }

        if((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game.snake.direction.y != -1 && allowMove){
            game.snake.direction = {0, 1};
            game.running = true;
            allowMove = false;
        }

        if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game.snake.direction.x != 1 && allowMove){
            game.snake.direction = {-1, 0};
            game.running = true;
            allowMove = false;
        }
        
        if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game.snake.direction.x != -1 && allowMove){
            game.snake.direction = {1, 0};
            game.running = true;
            allowMove = false;
        }

        // for (int i = 2; i < cellCount-2; i++){
        //     for (int j = 2; j < cellCount-2; j++){
        //         if(i == 2 || i == cellCount - 3 || j == 2 || j == cellCount - 3)
        //             DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, oliveGreen);
        //         else if (i%2 == 0 && j%2 == 1)
        //             DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, limeGreen);
        //         else if (i%2 == 1 && j%2 == 0)
        //             DrawRectangle(i * cellSize, j * cellSize, cellSize, cellSize, limeGreen);
        //             // DrawRectangleLines(i * cellSize, j * cellSize, cellSize, cellSize, WHITE);
        //     }
        // }

        ClearBackground(darkGreen);
        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, BLACK);
        DrawText("Linky Snake", offset - 5, 10, 40, BLACK);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, BLACK);
        game.Draw();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
