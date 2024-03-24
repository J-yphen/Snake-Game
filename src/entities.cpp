#include <iostream>
#include "entities.h"
#include "grid.h"

Body::Body(){
    head = nullptr;
    tail = nullptr;
    drawPtr = head;
}

int Body::qsize(){
    int size_of_queue=0;
    Node* temp = head;
    while (temp != tail){
        size_of_queue++;
        temp = temp->next;
    }
    if (temp == tail && temp != nullptr)
        size_of_queue++;
    return size_of_queue;
}

void Body::push_front(Coord loc){
    Node* newNode = new Node;
    newNode->loc = loc;

    if (head == nullptr && tail == nullptr){
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode;
    }
}

Coord Body::pop_front(){
    if (head == tail){
        if (head == nullptr){
            Coord null;
            null.x = -1;
            null.y = -1;
            return null;
        }
        else{
            Node* temp;
            temp = head;
            head = nullptr;
            tail = nullptr;
            Coord head_loc;
            head_loc = temp->loc;
            free(temp);
            return head_loc;
        }
    }
    else{
        Node* temp;
        temp = head;
        head = head->next;
        head->prev = nullptr;
        Coord head_loc;
        head_loc = temp->loc;
        free(temp);
        return head_loc;
    }
}

void Body::push_back(Coord loc){
    Node* newNode = new Node;
    newNode->loc = loc;

    if (head == nullptr && tail == nullptr){
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = nullptr;
        tail = newNode;
    }
}

Coord Body::pop_back(){
    if (head == tail){
        if (tail == nullptr){
            Coord null;
            null.x = -1;
            null.y = -1;
            return null;
        }
        else{
            Node* temp;
            temp = tail;
            head = nullptr;
            tail = nullptr;
            Coord tail_loc;
            tail_loc = temp->loc;
            free(temp);
            return tail_loc;
        }
    }
    else{
        Node* temp;
        temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        Coord tail_loc;
        tail_loc = temp->loc;
        free(temp);
        return tail_loc;
    }
}

Coord Body::read_front(){
    Node* temp = drawPtr;
    if (temp == nullptr){
        Coord null;
        null.x = -1;
        null.y = -1;
        drawPtr = head; // Resets pointer.
        return null;
    }
    drawPtr = drawPtr->next;
    return temp->loc;
}

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

Snake::Snake(){
    body = Body();
    Coord initLoc;
    initLoc.x = 7;
    initLoc.y = 8;
    body.push_back(initLoc);
    initLoc.x = 6;
    body.push_back(initLoc);
    initLoc.x = 5;
    body.push_back(initLoc);
}

void Snake::Draw(){
    for (int  i = 0; i < body.qsize(); i++){
        Coord temp;
        temp = body.read_front();
        if (temp.x == -1 && temp.y == -1)
            break;
        Rectangle seg = Rectangle{(float) temp.x * (float) cellSize, (float) temp.y * (float) cellSize, (float) cellSize, (float) cellSize};
        DrawRectangleRounded(seg, 0.5, 6, BLACK);
    }
    
}