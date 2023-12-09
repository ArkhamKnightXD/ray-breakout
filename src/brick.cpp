#include "brick.h"
#include <raylib.h>

Brick::Brick(float positionX, float positionY, int score)
{
    bounds = Rectangle{positionX, positionY, 64, 16};
    this->score = score;
}

void Brick::Update()
{
    
}

void Brick::Draw()
{
    DrawRectangleRounded(bounds, 0.8, 0, WHITE);
}