#include "entities.h"
#include "grid.h"

bool ElementInSnakeBody(Coord element, Body dequeBody){
    for(int i = 0; i < dequeBody.qsize(); i++){
        if(dequeBody.buffer[i].x == element.x && dequeBody.buffer[i].y == element.y)
            return true;
    }
    return false;
}

Coord GenerateRandomCell(){
    Coord newPos;
    newPos.x = GetRandomValue(3, cellCount - 4);
    newPos.y = GetRandomValue(3, cellCount - 4);
    return newPos;
}

Body::Body(){
    head = 0;
    tail = 0;
}

int Body::qsize() {
    return buffer.size();
}

void Body::push_front(Coord loc) {
    buffer.insert(buffer.begin() + head, loc);
    tail = (tail + 1) % buffer.size();
}

Coord Body::pop_front() {
    if (buffer.empty())
        return Coord{-1, -1}; // Underflow, no elements to pop

    Coord loc = buffer[head];
    head = (head + 1) % buffer.size();
    return loc;
}

void Body::push_back(Coord loc) {
    buffer.push_back(loc);
}

Coord Body::pop_back() {
    if (buffer.empty())
        return Coord{-1, -1}; // Underflow, no elements to pop

    Coord loc = buffer.back();
    buffer.pop_back();
    tail = (tail - 1 + buffer.size()) % buffer.size();
    return loc;
}

Snake::Snake(){
    body = Body();
    direction = {1, 0};
    Coord initLoc = {7, 8};
    body.push_back(initLoc);
    initLoc.x = 6;
    body.push_back(initLoc);
    initLoc.x = 5;
    body.push_back(initLoc);
}

void Snake::Draw(){
    for (int  i = 0; i < body.qsize(); i++){
        int x = body.buffer[i].x;
        int y = body.buffer[i].y;
        Rectangle seg = Rectangle{(float) x * (float) cellSize, (float) y * (float) cellSize, (float) cellSize, (float) cellSize};
        DrawRectangleRounded(seg, 0.5, 6, {56, 88, 33, 255});
    }
}

void Snake::Update(){
    body.pop_back();
    body.push_front({body.buffer[0].x + direction.x, body.buffer[0].y + direction.y});
}

Food::Food(Body snakeBody){
    pos = GeneratePos(snakeBody);
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

Coord Food::GeneratePos(Body snakeBody){
    Coord position = GenerateRandomCell();
    while (ElementInSnakeBody(position, snakeBody))
        position = GenerateRandomCell();
    
    return position;
}

