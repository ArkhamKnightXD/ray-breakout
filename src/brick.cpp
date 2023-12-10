#include "brick.h"
#include "ball.h"
#include <raylib.h>

Brick::Brick(float positionX, float positionY, int score)
{
    bounds = Rectangle{positionX, positionY, 64, 20};
    this->score = score;
    isDestroyed = false;
}

void Brick::Draw()
{
    if (!isDestroyed)
        DrawRectangleRounded(bounds, 0.8, 0,  Color{129, 204, 184, 255});
}

//Todo The collision detection fails
void Brick::HasBeenHitByTheBall()
{
    isDestroyed = true;
}
