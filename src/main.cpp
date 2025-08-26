#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <string>
#include <map>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currTime = GetTime();
    if (currTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Game game;
    std::map<int, double> getSpeed = {{0, 0.6}, {1, 0.5}, {2, 0.4}, {3, 0.3}, {4, 0.2}, {5, 0.15}};
    Colors temp;
    while (WindowShouldClose() != true)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        if (EventTriggered(getSpeed[game.level]))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(temp.darkBlue);
        // Vẽ Score
        DrawTextEx(font, "Score", {358, 15}, 38, 2, WHITE);
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, temp.lightBlue);

        std::string scoreText = std::to_string(game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText.c_str(), 38, 2);
        DrawTextEx(font, scoreText.c_str(), {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

        // Vẽ block next
        DrawTextEx(font, "Next", {368, 175}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, temp.lightBlue);

        // Vẽ hold block
        DrawTextEx(font, "Hold", {368, 395}, 38, 2, WHITE);
        DrawRectangleRounded({320, 435, 170, 180}, 0.3, 6, temp.lightBlue);

        // Vẽ Level
        std::string levelText = "Level: " + std::to_string(game.level);
        Vector2 levelSize = MeasureTextEx(font, levelText.c_str(), 32, 2);
        DrawTextEx(font, levelText.c_str(), {320 + (170 - levelSize.x) / 2, 135}, 32, 2, WHITE);
        
        game.Draw();
        if (game.gameOver)
        {
            std::string gameOverText = "GAME OVER";
            Vector2 textSize = MeasureTextEx(font, gameOverText.c_str(), 38, 2);
            float x = (500 - textSize.x) / 2 - 88;  // căn giữa theo chiều ngang
            float y = (620 - textSize.y) / 2;  // căn giữa theo chiều dọc

            // Vẽ khung xám phía sau chữ
            DrawRectangle(x - 10, y - 10, textSize.x + 20, textSize.y + 20, temp.darkGrey);
            // Vẽ chữ trắng lên trên
            DrawTextEx(font, gameOverText.c_str(), {x, y}, 38, 2, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
}