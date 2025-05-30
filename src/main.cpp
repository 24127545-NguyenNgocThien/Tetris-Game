#include "../include/raylib.h"
#include "../include/game.h"
#include "../include/color.h"
#include <iostream>
#include <string>
#include <cstring>

double gLastUpdate = 0;

bool EventTriggered(double interval)
{
    double curr_time = GetTime();
    if(curr_time - gLastUpdate >= interval)
    {
        gLastUpdate = curr_time;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(750, 1000, "Tetris Game");
    SetTargetFPS(60);

    Font font = LoadFontEx("../resource/anonymous_pro_bold.ttf", 36, 0, 0);

    Game tetris;

    while(!WindowShouldClose())
    {
        tetris.XuLyBanPhim();
        UpdateMusicStream(tetris.music);

        if(EventTriggered(0.5 - tetris.level / 10))
        {
            tetris.AutoMoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(space_blue);

        DrawRectangleRounded({520, 45, 220, 100}, 0.5, 1, glaucous);
        DrawRectangleRounded({520, 245, 220, 205}, 0.5, 1, glaucous);
        DrawTextEx(font, "Score", {520, 20}, 36, 2, WHITE);
        DrawTextEx(font, "Next", {520, 220}, 36, 2, WHITE);

        std::string score = std::to_string(tetris.score);
        char text_score[10];
        strcpy(text_score, score.c_str());
        Vector2 textSize = MeasureTextEx(font, text_score, 35, 2);
        DrawTextEx(font, text_score, {(520 + (220 - textSize.x) / 2), 80}, 36, 2, WHITE);

        if(tetris.game_over)
        {
            DrawTextEx(font, "GAME", {545, 500}, 70, 2, WHITE);
            DrawTextEx(font, "OVER", {575, 560}, 70, 2, WHITE);
            DrawTextEx(font, "Press R to\nRestart", {520, 900}, 30, 2, YELLOW);
        }

        tetris.DrawGame();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}