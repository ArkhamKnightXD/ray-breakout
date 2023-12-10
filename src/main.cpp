#include <raylib.h>
#include "ball.h"
#include "player.h"
#include "brick.h"
#include <vector>
#include <stdio.h>

int main()
{
    const int screenWidth = 960;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "Breakout!");
    SetTargetFPS(60);

    Player player = Player(screenWidth / 2, screenHeight - 40);

    Ball ball = Ball(screenWidth / 2, screenHeight / 2);

    std::vector<Brick> bricks;

    int positionX;
    int positionY = 0;
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
        positionY += 20;
    }

    // InitAudioDevice();

    // Sound hitSound = LoadSound("assets/sounds/okay.wav");
    // Music music = LoadMusicStream("assets/music/pixel3.mp3");

    // music.looping = true;

    // PlayMusicStream(music);

    while (!WindowShouldClose())
    {
        // UpdateMusicStream(music);

        player.Update();
        ball.Update();

        for (Brick brick : bricks)
        {
            if (!brick.isDestroyed && ball.HasCollide(brick.bounds))
            {
                ball.velocity.y *= -1;

                // the brick doesn't destroy, the variable set to true, but later it set to false again. 
                printf("before collision: %d\n", brick.isDestroyed);

                brick.HasBeenHitByTheBall();

                brick.bounds.y = 50;

                printf("after collision: %d\n", brick.isDestroyed);
            }
        }

        // Check collision between a circle and a rectangle
        if (ball.HasCollide(player.bounds))
        {
            ball.velocity.y *= -1;
            // PlaySound(hitSound);
        }

        if (ball.position.y > screenHeight)
        {
            player.score++;
            ball.ResetPosition();
        }

        BeginDrawing();

        ClearBackground(Color{0,0,0,0});

        // DrawText(TextFormat("%i", player.score), 230, 20, 80, WHITE);

        for (Brick brick : bricks)
        {
            brick.Draw();
        }

        player.Draw();

        ball.Draw();

        EndDrawing();
    }

    // UnloadSound(hitSound);
    // UnloadMusicStream(music);

    CloseAudioDevice();

    CloseWindow();
    return 0;
}