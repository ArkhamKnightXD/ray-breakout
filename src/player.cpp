#include "player.h"
#include <raylib.h>

Player::Player(float positionX, float positionY)
{
    bounds = Rectangle{positionX, positionY, 64, 16};
    speed = 8;
    score = 0;
    lives = 2;
}

void Player::Update()
{
    if (IsKeyDown(KEY_A) && bounds.x >= 0)
        bounds.x -= speed;

    if (IsKeyDown(KEY_D) && bounds.x <= GetScreenWidth() - bounds.width)
        bounds.x += speed;
}

void Player::Draw()
{
    DrawRectangleRounded(bounds, 0.8, 0, WHITE);
}