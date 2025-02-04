#include "raylib.h"
void battleAnimation(Texture2D battleHUD[5], Texture2D battleTransition[16])
{

    static float pos_player1 = 832;   // 64x64      330x330
    static float pos_player2 = -307;  // 64x64     210x210
    static float pos_terrain1 = 832;  // 290x80    521x143
    static float pos_terrain2 = -372; // 155x50   341x110
    const float speedAnimation = 13.0f;

    // tamanho hud: 240x50   800x167

    static int frameCounter = 0; // Contador de frames do jogo
    static int currentFrame = 0; // Índice do frame atual da transição

    frameCounter++;
    if (frameCounter % 4 == 0)
    {
        currentFrame++; // Passa para o próximo frame
        if (currentFrame >= 16)
            currentFrame = 0; // Volta para o primeiro frame se atingir o último
    }

    if (pos_player1 > 0)
        pos_player1 -= speedAnimation;
    if (pos_player2 < 525)
        pos_player2 += speedAnimation;
    if (pos_terrain1 > 0)
        pos_terrain1 -= speedAnimation;
    if (pos_terrain2 < 460)
        pos_terrain2 += speedAnimation;

    DrawTexturePro(battleTransition[currentFrame], (Rectangle){0, 0, 128, 128},
                   (Rectangle){0, 0, 800, 600}, (Vector2){0, 0}, 0, WHITE);

    // Atualiza o frame da transição a cada 4 frames do jogo

    DrawTexturePro(battleHUD[0], (Rectangle){0, 0, 240, 50},
                   (Rectangle){0, 432, 800, 167}, (Vector2){0, 432}, 0, WHITE);

    DrawTexturePro(battleHUD[1], (Rectangle){0, 0, 64, 64},
                   (Rectangle){pos_player1, 105, 330, 330}, (Vector2){pos_player1, 105}, 0, WHITE);

    DrawTexturePro(battleHUD[2], (Rectangle){0, 0, 64, 64},
                   (Rectangle){pos_player2, -25, 210, 210}, (Vector2){pos_player2, -25}, 0, WHITE);

    DrawTexturePro(battleHUD[3], (Rectangle){0, 0, 290, 80},
                   (Rectangle){pos_terrain1, 290, 521, 143}, (Vector2){pos_terrain1, 290}, 0, WHITE);

    DrawTexturePro(battleHUD[4], (Rectangle){0, 0, 155, 50},
                   (Rectangle){pos_terrain2, 105, 341, 110}, (Vector2){pos_terrain2, 105}, 0, WHITE);
}