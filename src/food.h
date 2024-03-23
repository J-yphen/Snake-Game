#include <raylib.h>

#pragma once

typedef struct{
    unsigned int x;
    unsigned int y;
} Coord;


class Food{
    public:
        Coord pos;
        Texture2D texture;
        void Draw();
        Coord GeneratePos(); 
        Food();
        ~Food();
};