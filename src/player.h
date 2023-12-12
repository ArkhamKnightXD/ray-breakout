#pragma once

#include <raylib.h>

class Player
{
public:
    Player(float positionX, float positionY);
    void Update();
    void Draw();

public:
    Rectangle bounds;
    int speed;
    int score;
    int lives;
};