#include <raylib.h>
#include <vector>

#pragma once
using namespace std;

typedef struct{
    int x;
    int y;
} Coord;

class Body{
    private:
        int head;
        int tail;
    public:
        vector<Coord> buffer;
        Body();
        int qsize();
        Coord pop_front();
        void push_front(Coord loc);
        Coord pop_back();
        void push_back(Coord loc);
};

class Food{
    public:
        Coord pos;
        Texture2D texture;
        void Draw();
        Coord GeneratePos(); 
        Food();
        ~Food();
};

class Snake{
    private:
        Body body;

    public:
        Coord direction;
        Snake();
        void Draw();
        void Update();
};