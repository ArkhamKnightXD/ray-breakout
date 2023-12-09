#include <raylib.h>
#include "ball.h"
#include "player.h"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};
    Color green = Color{38, 185, 154, 255};
    Color lightGreen = Color{129, 204, 184, 255};

    const int screenWidth = 960;
    const int screenHeight = 640;

    InitWindow(screenWidth, screenHeight, "Breakout!");
    SetTargetFPS(60);

    Player player = Player(screenWidth / 2, screenHeight - 40);

    Ball ball = Ball(screenWidth / 2, screenHeight / 2);

    // InitAudioDevice();   

    Sound hitSound = LoadSound("assets/sounds/okay.wav");
    // Music music = LoadMusicStream("assets/music/pixel3.mp3");

    // music.looping = true;

    // PlayMusicStream(music);

    while (!WindowShouldClose())
    {
        // UpdateMusicStream(music);

        player.Update();
        ball.Update();

        //Check collision between a circle and a rectangle
        if (ball.HasCollideWithPlayer(player.bounds)) 
        {
            ball.velocity.y *= -1;
            PlaySound(hitSound);
        }

        if (ball.position.y > screenHeight)
        {
            player.score++;
            ball.ResetPosition();
        }
        
        BeginDrawing();

            ClearBackground(darkGreen);

            //Right side color
            DrawRectangle(screenWidth/2, 0, screenWidth/2, screenHeight, green);

            // circle for the half of the court.
            DrawCircle(screenWidth/2, screenHeight/2, 150, lightGreen);

            DrawLine(screenWidth /2, screenHeight, screenWidth / 2, 0, WHITE);

            DrawText(TextFormat("%i", player.score), 230, 20, 80, WHITE);
        
            player.Draw();
    
            ball.Draw();

        EndDrawing();
    }

    UnloadSound(hitSound);     
    // UnloadMusicStream(music);

    CloseAudioDevice();     

    CloseWindow();
    return 0;
}