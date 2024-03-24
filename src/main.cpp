#include "entities.h"
#include "grid.h"

Color darkGreen = {142, 204, 57, 255};
Color limeGreen = {167, 217, 72, 255};
Color oliveGreen = {52, 64, 24, 255};

int main()
{
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Linky Snake");
    Food food = Food();
    Snake snake = Snake();
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
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
        food.Draw();
        snake.Draw();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
