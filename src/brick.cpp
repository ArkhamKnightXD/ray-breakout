#include "brick.h"
#include "ball.h"
#include <raylib.h>

Brick::Brick(float positionX, float positionY, int score)
{
    bounds = Rectangle{positionX, positionY, 64, 20};
    this->score = score;
    setToDestroy = false;
    isDestroyed = false;
}

void Brick::Update()
{
    if (setToDestroy)
        isDestroyed = true;
}

void Brick::Draw()
{
    if (!isDestroyed)
        DrawRectangleRounded(bounds, 0.8, 0,  Color{129, 204, 184, 255});
}

//Todo The collision detection fails
void Brick::HasBeenHitByTheBall(Ball ball)
{
    bool hasCollide = ball.HasCollide(bounds);

    if (!isDestroyed && hasCollide)
    {
        ball.velocity.y *= -1;
        setToDestroy = true;
    }
}
