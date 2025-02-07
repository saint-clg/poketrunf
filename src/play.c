#include "raylib.h"
void battleAnimation(Texture2D battleHUD[5], Texture2D battleTransition[16])
{
    static float pos_player1 = 832;   // 64x64      330x330
    static float pos_player2 = -307;  // 64x64     210x210
    static float pos_terrain1 = 832;  // 290x80    521x143
    static float pos_terrain2 = -372; // 155x50   341x110
    const float speedAnimation = 13.0f; // Reduz velocidade em 4x

    // tamanho hud: 240x50   800x167

    static int frameCounter = 0;
    static int currentFrame = 0;

   static bool transitionPlayed = false; // Variável para garantir que a animação seja feita uma vez

    // Incrementa o contador de frames
    frameCounter++;
    if (frameCounter % 4 == 0 && !transitionPlayed)
    {
        currentFrame++; // Passa para o próximo frame da transição
        if (currentFrame >= 16) // Se terminar a animação, marca como já executada
        {
            currentFrame = 15; // Garante que o último frame seja mostrado
            transitionPlayed = true; // Marca que a animação foi concluída
        }
    }

    if (pos_player1 > 0)
        pos_player1 -= speedAnimation;
    if (pos_player2 < 525)
        pos_player2 += speedAnimation;
    if (pos_terrain1 > 0)
        pos_terrain1 -= speedAnimation;
    if (pos_terrain2 < 460)
        pos_terrain2 += speedAnimation;

    DrawTexturePro(battleHUD[0], (Rectangle){0, 0, 240, 50},
                   (Rectangle){0, 432, 800, 167}, (Vector2){0, 0}, 0, WHITE);

    DrawTexturePro(battleHUD[3], (Rectangle){0, 0, 290, 80},
                   (Rectangle){pos_terrain1, 290, 521, 143}, (Vector2){0,0}, 0, WHITE);

    DrawTexturePro(battleHUD[4], (Rectangle){0, 0, 155, 50},
                   (Rectangle){pos_terrain2, 105, 341, 110}, (Vector2){0,0}, 0, WHITE);

    DrawTexturePro(battleHUD[2], (Rectangle){0, 0, 64, 64},
                   (Rectangle){pos_player2, -25, 210, 210}, (Vector2){0,0}, 0, WHITE);

    DrawTexturePro(battleHUD[1], (Rectangle){0, 0, 64, 64},
                   (Rectangle){pos_player1, 105, 330, 330}, (Vector2){0,0}, 0, WHITE);
    
    if (!transitionPlayed)
    {
        DrawTexturePro(battleTransition[currentFrame], (Rectangle){0, 0, 128, 128},
                       (Rectangle){0, 0, 800, 600}, (Vector2){0, 0}, 0, WHITE);
    }
}

void battleHud(){


};