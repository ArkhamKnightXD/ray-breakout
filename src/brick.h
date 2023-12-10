#pragma once

#include "ball.h"
#include <raylib.h>

class Brick
{
public:
    Brick(float positionX, float positionY, int score);
    void Draw();
    void HasBeenHitByTheBall();

public:
    Rectangle bounds;
    int score;
    bool isDestroyed;
};