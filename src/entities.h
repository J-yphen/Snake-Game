#include <raylib.h>

#pragma once

typedef struct{
    int x;
    int y;
} Coord;

typedef struct Node{
    Node* prev;
    Coord loc;
    Node* next;
} Node;

class Body{
    private:
        Node* head;
        Node* tail;
        Node* drawPtr;
    public:
        Body();
        int qsize();
        Coord pop_front();
        void push_front(Coord loc);
        Coord pop_back();
        void push_back(Coord loc);
        Coord read_front();
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
        Snake();
        void Draw();
};