#pragma once

#include "ball.h"
#include <raylib.h>

class Brick
{
public:
    Brick(float positionX, float positionY, int score);
    void Update();
    void Draw();
    void HasBeenHitByTheBall(Ball ball);

public:
    Rectangle bounds;
    int score;
    bool setToDestroy;
    bool isDestroyed;
};