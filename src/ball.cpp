#include "ball.h"
#include <raylib.h>

Ball::Ball(float positionX, float positionY, Sound sound)
{
    position = Vector2{positionX, positionY};
    velocity = Vector2{5, 5};
    radius = 10;
    hitWallSound = sound;
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

    if (position.x + radius >= GetScreenWidth() || position.x - radius <= 0) {

        velocity.x *= -1;
        PlaySound(hitWallSound);
    }

    if (position.y + radius <= 20) {
        
        velocity.y *= -1;
        PlaySound(hitWallSound);
    }
}

void Ball::Draw()
{
    DrawCircle(position.x, position.y, radius, YELLOW);
}

bool Ball::HasCollide(Rectangle collisionBounds)
{
    return CheckCollisionCircleRec(position, radius, collisionBounds);
}