#include <raylib.h>
#include "ball.h"
#include "player.h"
#include "brick.h"
#include <vector>

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
    SetTargetFPS(144);

    std::vector<Brick> bricks = createBricks();

    Player player = Player(screenWidth / 2, screenHeight - 40);

    InitAudioDevice();

    Sound playerHitSound = LoadSound("assets/sounds/drop.wav");
    Sound brickHitSound = LoadSound("assets/sounds/okay.wav");
    Sound hitWallSound = LoadSound("assets/sounds/magic.wav");

    Ball ball = Ball(screenWidth / 2, screenHeight / 2 -80, hitWallSound);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        player.Update(deltaTime);
        ball.Update(deltaTime);

        // when I use &brick this is a reference to the original Brick object in the bricks vector.
        // Changes to brick (like setting brick.isDestroyed to true) directly modify the original Brick in the vector.
        // When I don't use & brick is a copy of each Brick object in the bricks vector.
        // Changes to brick do not affect the original Brick objects in the vector.
        for (Brick &brick : bricks)
        {
            if (!brick.isDestroyed && ball.HasCollide(brick.bounds))
            {
                ball.velocity.y *= -1;

                brick.isDestroyed = true;

                player.score += brick.brickPoints; 

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