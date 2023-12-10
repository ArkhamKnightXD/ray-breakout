#include "ball.h"
#include <raylib.h>

Ball::Ball(float positionX, float positionY)
{
    position = Vector2{positionX, positionY};
    velocity = Vector2{5, 5};
    radius = 15;
}

void Ball::ResetPosition()
{
    position.x = GetScreenWidth() / 2;
    position.y = GetScreenHeight() / 2;

    velocity.x *= -1;
    velocity.y *= 1;
}

void Ball::Update()
{
    position.x += velocity.x;
    position.y += velocity.y;

    if (position.x + radius >= GetScreenWidth() || position.x - radius <= 0)
        velocity.x *= -1;

    if (position.y + radius <= 20)
        velocity.y *= -1;
}

void Ball::Draw()
{
    DrawCircle(position.x, position.y, radius, YELLOW);
}

bool Ball::HasCollide(Rectangle collisionBounds)
{
    return CheckCollisionCircleRec(position, radius, collisionBounds);
}