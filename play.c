#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TRANSITION_FRAMES 16
#define SLIDE_SPEED 10.0f  // Velocidade do deslize

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Battle Transition");
    SetTargetFPS(60);

    // Carregar texturas da HUD de batalha
    Texture2D battle_hud = LoadTexture(".\\assets\\img\\battle\\battle_hud.png");
    Texture2D battle_terrain_player1 = LoadTexture(".\\assets\\img\\battle\\battle_terrain_player1.png");
    Texture2D battle_terrain_player2 = LoadTexture(".\\assets\\img\\battle\\battle_terrain_player2.png");
    Texture2D battle_player1 = LoadTexture(".\\assets\\img\\battle\\battle_player1.png");
    Texture2D battle_player2 = LoadTexture(".\\assets\\img\\battle\\battle_player2.png");

    // Carregar transições de batalha
    Texture2D battle_transition[TRANSITION_FRAMES];
    char battle_transition_path[50];
    for (int i = 0; i < TRANSITION_FRAMES; i++) {
        snprintf(battle_transition_path, sizeof(battle_transition_path), 
                 ".\\assets\\animations\\battle_transition\\%d.png", i);
        battle_transition[i] = LoadTexture(battle_transition_path);
    }

    // Definição de retângulos das texturas (posição e tamanho)
    Rectangle hudSource = { 0, 0, 800, 167 };
    Rectangle hudDest = { 0, 432, 800, 167 };

    Rectangle terrainPlayer1Src = { 0, 0, 521, 143 };
    Rectangle terrainPlayer2Src = { 0, 0, 341, 110 };

    Rectangle player1Src = { 0, 0, 330, 330 };
    Rectangle player2Src = { 0, 0, 210, 210 };

    // Posições iniciais (fora da tela para deslizar)
    float posPlayer1X = SCREEN_WIDTH;
    float posPlayer2X = -player2Src.width;
    float posTerrain1X = SCREEN_WIDTH;
    float posTerrain2X = -terrainPlayer2Src.width;

    int transitionFrame = 0;
    float animationTimer = 0.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Atualizar posições (deslizamento)
        if (posPlayer1X > 0) {
            posPlayer1X -= SLIDE_SPEED * dt * 60;
            posTerrain1X -= SLIDE_SPEED * dt * 60;
        }
        if (posPlayer2X < 525) {
            posPlayer2X += SLIDE_SPEED * dt * 60;
            posTerrain2X += SLIDE_SPEED * dt * 60;
        }

        // Atualizar animação de transição
        animationTimer += dt;
        if (animationTimer >= 0.1f) {
            transitionFrame++;
            if (transitionFrame >= TRANSITION_FRAMES) transitionFrame = TRANSITION_FRAMES - 1;
            animationTimer = 0.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenhar terrenos deslizando
        DrawTexturePro(battle_terrain_player1, terrainPlayer1Src, 
                       (Rectangle){ posTerrain1X, 290, 521, 143 }, 
                       (Vector2){ 0, 0 }, 0, WHITE);

        DrawTexturePro(battle_terrain_player2, terrainPlayer2Src, 
                       (Rectangle){ posTerrain2X, 105, 341, 110 }, 
                       (Vector2){ 0, 0 }, 0, WHITE);

        // Desenhar players deslizando
        DrawTexturePro(battle_player1, player1Src, 
                       (Rectangle){ posPlayer1X, 105, 330, 330 }, 
                       (Vector2){ 0, 0 }, 0, WHITE);

        DrawTexturePro(battle_player2, player2Src, 
                       (Rectangle){ posPlayer2X, -25, 210, 210 }, 
                       (Vector2){ 0, 0 }, 0, WHITE);

        // Desenhar HUD de batalha
        DrawTexturePro(battle_hud, hudSource, hudDest, (Vector2){ 0, 0 }, 0, WHITE);

        // Desenhar animação de transição
        DrawTexture(battle_transition[transitionFrame], 0, 0, WHITE);

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(battle_hud);
    UnloadTexture(battle_terrain_player1);
    UnloadTexture(battle_terrain_player2);
    UnloadTexture(battle_player1);
    UnloadTexture(battle_player2);
    for (int i = 0; i < TRANSITION_FRAMES; i++) UnloadTexture(battle_transition[i]);

    CloseWindow();
    return 0;
}
