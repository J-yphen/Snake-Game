#include <raylib.h>

Color limeGreen = Color{142, 204, 57, 255};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Linky Snake");
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(limeGreen);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}