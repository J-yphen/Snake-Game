#include "food.h"
#include "grid.h"

Food::Food(){
    pos = GeneratePos();
    Image image = LoadImage("Graphics\\apple.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

Food::~Food(){
    UnloadTexture(texture);
}

void Food::Draw(){
    // DrawRectangle(pos.x * cellSize, pos.y * cellSize, cellSize, cellSize, RED);
    DrawTexture(texture, pos.x * cellSize, pos.y * cellSize, WHITE);
}

Coord Food::GeneratePos(){
    Coord newPos;
    newPos.x = GetRandomValue(3, cellCount - 4);
    newPos.y = GetRandomValue(3, cellCount - 4);
    return newPos;
}