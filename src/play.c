#include "raylib.h"

int PLAY_TIMES = 0;
int TYPE_MATCH;

Cards player1_deck[TOTAL CARDS];
Cards player2_deck[TOTAL CARDS];

void ShuffleDeck(Cards deck[]){

    int indices[TOTALCARDS];

    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    srand(time(NULL));

    // FISHER-YETS
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // INDICE
        // TROCA
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < TOTALCARDS; i++) {
        if(i  % 2 ==0){
            player1_deck[i] = deck[indices[i]];
        }else
        {
            player2_deck[i] = deck[indices[i]];
        }
    }
    
}

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
                   (Rectangle){pos_player1, 105, 290, 290}, (Vector2){0,0}, 0, WHITE);
    
    if (!transitionPlayed)
    {
        DrawTexturePro(battleTransition[currentFrame], (Rectangle){0, 0, 128, 128},
                       (Rectangle){0, 0, 800, 600}, (Vector2){0, 0}, 0, WHITE);
    }
}

void battleHud(Font poke_font, Texture2D battleUtils[10], Sound walk_menuSound){

    const char battle_options[8][10] = {"JOGAR", "DECK", "ITENS", "DECK", "ATK", "HP", "ALTURA", "PESO"};
    static Vector2 battle_options_pos[4] = {475,460}; 
    static Vector2 arrow_position[4] = {{440,470}, {440, 525}, {610, 470}, {610, 525}};
    static int walk_battle_options = 0;
    char match_stats[50];
    
    static bool play = false;
//DESENHA AS INFORMAÇÕES DA PARTIDA
    DrawRectangleRounded((Rectangle){0,0,230,225}, 0.3, 10, (Color){0, 0, 0, 128});
    snprintf(match_stats, sizeof(match_stats), "%d FPS\nTYPE\nTERRENO\n,JOGADAS %d\n DECK PLAYER1 %d\n, DECK PLAYER2 %d",
             GetFPS(), TYPE_MATCH, 16,16);
    DrawTextEx(poke_font, match_stats, (Vector2){10, 10}, 15, 0.2, BLACK);
    DrawRectangleRoundedLines((Rectangle){0,0,230,225}, 0.3, 10, RED);
//DESENHA AS INFORMAÇÕES DA PARTIDA

//ANDA PELO MENU
    if(IsKeyPressed(KEY_DOWN)){
        walk_battle_options++;
        PlaySound(walk_menuSound);
        if(walk_battle_options > 3){
            walk_battle_options = 0;
        }
    }
    if(IsKeyPressed(KEY_UP)){
        walk_battle_options--;
        PlaySound(walk_menuSound);
        if(walk_battle_options < 0){
            walk_battle_options = 3;
        }
    }
    if(IsKeyPressed(KEY_RIGHT)){
        walk_battle_options += 2;
        PlaySound(walk_menuSound);
        if(walk_battle_options > 3){
            walk_battle_options = 0;
        }
    }
    if(IsKeyPressed(KEY_LEFT)){
        walk_battle_options -= 2;
        PlaySound(walk_menuSound);
        if(walk_battle_options < 0){
            walk_battle_options = 3;
        }
    }
// ANDA PELO MENU

    DrawTextureEx(battleUtils[0], arrow_position[walk_battle_options], 0.0f, 3.5, BLACK);
    
    if(!play){
        for(int i = 0; i < 4; i++){
            DrawTextPro(poke_font, battle_options[i], (Vector2){0, 0}, 10, 0.2, BLACK);

            if(i % 2 == 0 || i >){
                if(i > 2){
                    battle_options_pos[i].x += 170;
                }
                if(i %  2 == 0){
                    battle_options_pos[i].y += 55;
                }
            }
        }// DESENHA AS OPÇÕES PARA O JOGADOR
    }// NÃO ESTÁ NO MENU PARA JOGAR

    if(IsKeyPressed(KEY_Z)){
        PlaySound(walk_battle_options);
        if(walk_battle_options == 0 && !play){
            play = true;
        }// ENTRA NO MENU PARA JOGAR

    }// TODAS AS INTERAÇÕES DE CONFIRMAÇÃO

    if(play){
        for(int i = 3; i < 7; i++){
        DrawTextPro(poke_font, battle_options[i], (Vector2){0, 0}, 10, 0.2, BLACK);

            if(i % 2 == 0 || i >){
                if(i > 2){
                    battle_options_pos[i].x += 170;
                }
                if(i %  2 == 0){
                    battle_options_pos[i].y += 55;
                }
            }
        }// DESENHA AS OPÇÕES PARA JOGAR

        if(IsKeyPressed(KEY_X)){
            play = false;
        }
    }// ESTÁ NO MENU PARA JOGAR

};