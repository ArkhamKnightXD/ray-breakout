#pragma once

#include <raylib.h>

class Brick
{
public:
    Brick(float positionX, float positionY, int score);
    void Update();
    void Draw();

public:
    Rectangle bounds;
    int score;
};