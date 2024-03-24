#include <raylib.h>

#pragma once

typedef struct{
    unsigned int x;
    unsigned int y;
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
    public:
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
