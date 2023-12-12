#include <raylib.h>
#include "ball.h"
#include "player.h"
#include "brick.h"
#include <vector>
#include <stdio.h>

std::vector<Brick> createBricks() {

    std::vector<Brick> bricks;

    int positionX;
    int positionY = 40;
    int brickPoints = 8;

    for (int i = 0; i < 8; i++)
    {
        positionX = 0;

        for (int j = 0; j < 15; j++)
        {
            bricks.push_back(Brick(positionX, positionY, brickPoints));
            positionX += 64;
        }

        brickPoints--;
        positionY += 22;
    }

    return bricks;
}


int main()
{
    const int screenWidth = 960;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "Breakout!");
    SetTargetFPS(60);

    Player player = Player(screenWidth / 2, screenHeight - 40);

    std::vector<Brick> bricks = createBricks();

    InitAudioDevice();

    Sound playerHitSound = LoadSound("assets/sounds/drop.wav");
    Sound brickHitSound = LoadSound("assets/sounds/okay.wav");
    Sound hitWallSound = LoadSound("assets/sounds/magic.wav");

    Ball ball = Ball(screenWidth / 2, screenHeight / 2, hitWallSound);

    while (!WindowShouldClose())
    {
        player.Update();
        ball.Update();

        // I need to use normal for loop, because the collision logic doesn't work with foreach
        // This is because everytime I have a completed loop in a foreach, it creates a new object
        //and for that same reason it resets the object isDestroyed state.
        for (int i = 0; i < bricks.size(); i++)
        {
            if (!bricks[i].isDestroyed && ball.HasCollide(bricks[i].bounds))
            {
                ball.velocity.y *= -1;

                bricks[i].isDestroyed = true;

                player.score += bricks[i].brickPoints; 

                PlaySound(brickHitSound);
            }
        }

        if (ball.HasCollide(player.bounds))
        {
            ball.velocity.y *= -1;
            PlaySound(playerHitSound);
        }

        if (ball.position.y > screenHeight)
        {
            if (player.lives > 0)
            {
                player.lives--;

                ball.ResetPosition();
            }
        }

        BeginDrawing();

            ClearBackground(Color{0,0,0,0});

            DrawText(TextFormat("Score: %i", player.score), 150, 10, 20, WHITE);
            DrawText(TextFormat("Lives %i", player.lives), screenWidth - 250, 10, 20, WHITE);

            for (Brick brick : bricks)
            {
                brick.Draw();
            }

            ball.Draw();

            player.Draw();

        EndDrawing();
    }

    UnloadSound(playerHitSound);
    UnloadSound(brickHitSound);
    CloseAudioDevice();

    CloseWindow();
    return 0;
}