#include <time.h>
#include <stdlib.h>
#include <stdio.h>7
#include <math.h>
#include <string.h>
#include "raylib.h"
#include "cards.h"
#include "play.h"
#include "struct_card.h"

int ROUND = 0;
int TYPE_MATCH = 0;
char TERRAIN;
Cards *player1_deck;
Cards *player2_deck;

// typedef enum {  HUD = 0, PLAYER1, PLAYER2, TERRAIN1, TERRAIN2, ARROWHUD, ARROWTEXT} BattleHud_code;

void ShuffleDeck(Cards deck[]){

    int indices[TOTAL_CARDS];

    for (int i = 0; i < TOTAL_CARDS; i++) {
        indices[i] = i;
    }

    srand(time(NULL));

    // FISHER-YETS
    for (int i = TOTAL_CARDS - 1; i > 0; i--) {
        int j = rand() % (i + 1); // INDICE
        // TROCA
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < TOTAL_CARDS; i++) {
        if(i  % 2 ==0){
            player1_deck[i] = deck[indices[i]];
        }else
        {
            player2_deck[i] = deck[indices[i]];
        }
    }
    
}

bool battleAnimation(   Texture2D battleTransition[], float *pos_player1, float *pos_player2, 
                        float *pos_terrain1, float *pos_terrain2)
{
    const float speedAnimation = 13.0f; // Reduz velocidade em 4x

    // tamanho hud: 240x50   800x167

    static int frameCounter = 0;
    static int currentFrame = 0;

    bool transitionPlayed = false;

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

    if (*pos_player1 > 0)
        *pos_player1 -= speedAnimation;
    if (*pos_player2 < 525)
        *pos_player2 += speedAnimation;
    if (*pos_terrain1 > 0)
        *pos_terrain1 -= speedAnimation;
    if (*pos_terrain2 < 460)
        *pos_terrain2 += speedAnimation;
    
    if (!transitionPlayed)
    {
        DrawTexturePro(battleTransition[currentFrame], (Rectangle){0, 0, 128, 128},
                       (Rectangle){0, 0, 800, 600}, (Vector2){0, 0}, 0, WHITE);
    }

    return transitionPlayed;
}
void AnimatedHability(int *Playing){

    Rectangle pos_buff = {365,40,209,342};
    Rectangle pos_debuff = {150, 40, 209, 342};
    static float opacity = 0.0f;
    static float timeCount = 0.0f;
    static bool increasing = true; 

    if(increasing){
        opacity += 5;
        if(opacity > 255){
            opacity = 255;
            increasing = false;
        }
    }else {
        opacity -= 5;
        if(opacity < 0){
            opacity = 0;
            increasing = true;
        }
    }// ANIMAÇÃO DE PISCAR A CARTA, VAI E VOLTA

    DrawRectangleRec(pos_buff, (Color){255,255,255, (unsigned char)opacity}); // WHITE
    DrawRectangleRec(pos_debuff, (Color){255,0,0, (unsigned char)opacity}); // RED
    timeCount++;
    if(timeCount > 120){

        timeCount = 0;
        opacity = 0; 

        *Playing = 3;

    }

}

void AnimatedPlaying(Texture2D player1_card, Texture2D player2_card, int *Playing){

    static float frameCount = 0.0f;
    
    static Vector2 pos_card = {580,85};
    static bool end_animation = false;

    if(pos_card.x != 365 && pos_card.y != 40){

        pos_card.x -= 5;
        pos_card.y -= 1;
        

    }else end_animation = true;

    if(end_animation){

        *Playing = 2;
    }
    DrawTexturePro(player1_card, (Rectangle){0, 0, 220, -360},
                   (Rectangle){pos_card.x, pos_card.y, 209, 342}, (Vector2){0, 0}, 0.0f, WHITE);
    DrawTexturePro(player2_card, (Rectangle){0, 0, 220, -360},
                   (Rectangle){150, 40, 209, 342}, (Vector2){0, 0}, 0.0f, WHITE);
}

bool AnimatedTextBox(char text_box[], Font battle_hud_font, float *frameCounter){
    bool end_subtext = false;
       
        // Acelera a animação do texto quando 'Z' é pressionado ou o texto for completo
    if (*frameCounter >= (int)strlen(text_box) || IsKeyPressed(KEY_X)) {
        *frameCounter = strlen(text_box);
        end_subtext = true;
    }else *frameCounter += GetFrameTime() * 60;

    // Desenha o texto de forma animada
    DrawTextBoxed(  battle_hud_font, TextSubtext(text_box, 0, *frameCounter),(Rectangle){30, 460, 370, 110}, 
                    20, 0, true, WHITE);

    return end_subtext;
}

/*bool Playing(Cards player1_deck, Cards player2_deck, int *stats_choice){

    bool player_round;
    static bool end_hability = false;
    float player1_stats, player2_stats;
    bool player_wins;

    if(ROUND %2 == 0){

        player_round = true;
    }else player_round = false;

    if(player_round){
        if(hability[player1_deck.habilidade].hability_function(player1_deck,palyer2_deck,*player_round)){
            if(hability[player2_deck.habilidade].hability_function(player1_deck,palyer2_deck,*player_round)){

                end_hability = true;
            }
        }
        if(end_hability){
                
            }
            if(*stats_choice == 0){
                player1_stats = player1_deck.ataque;
                player2_stats = player2_deck.ataque;
            }else if (*stats_choice == 1){
                player1_stats = player1_deck.hp;
                player2_stats = player2_deck.hp;
            }else if (*stats_choice == 2){
                player1_stats = player1_deck.altura;
                player2_stats = player2_deck.altura;
            }else if (*stats_choice == 3){
                player1_stats = player1_deck.peso;
                player2_stats = player2_deck.peso;
            }

            if(player1_stats > player1_stats){

                player_wins = true;
            }else player_wins = false;

    }


    return player_wins;
}*/

void battleHud( Font battle_hud_font, Texture2D Arrow_black, Texture2D Arrow_red, Sound walk_menuSound, 
                Cards player1_deck[], RenderTexture2D CardTexture[], int *Playing)                
{

    const char battle_options[8][10] = {"JOGAR", "DECK", "ITENS", "HAB", "ATK", "HP", "ALTURA", "PESO"};
    static Vector2 battle_options_pos[4] = {{475, 470}, {475, 525}, {645, 470}, {645, 525}};
    static float last_move = 0.0f;
    static float frameCounter = 0.0f;
    static Vector2 arrow_position[4] = {{440, 470}, {440, 525}, {610, 470}, {610, 525}};
    static Vector2 arrowr_position = {380,460};
    static int walk_battle_options = 0;
    static bool play = false;
    static bool deck = false;
    static bool itens = false;
    static bool hab = false;
    static bool end_subText = false;
    static int count_deck = 0;
    char text_box[300];

    printf("%d", *Playing);

    if(!hab){
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT)) {
            PlaySound(walk_menuSound);

            // ANDA PELO MENU
            if (IsKeyPressed(KEY_DOWN))  walk_battle_options++;
            if (IsKeyPressed(KEY_UP))    walk_battle_options--;
            if (IsKeyPressed(KEY_RIGHT)) walk_battle_options += 2;
            if (IsKeyPressed(KEY_LEFT))  walk_battle_options -= 2;

            // CONTROLE DE OPÇÕES SEMPRE EM 0 E 3
            walk_battle_options = (walk_battle_options + 4) % 4;
        }// IF KEYPRESSED <^> 
    }

    // DESENHA TEXTURA DA SETA
    static bool move = false;
    if(GetTime() - last_move > 0.5){
        last_move = GetTime();
        if (!move)arrow_position[walk_battle_options].x -= 5;
        if (move)arrow_position[walk_battle_options].x += 5;
        if (!move)arrowr_position.y += 10;
        if (move)arrowr_position.y -= 10;
        move = !move;
    }// ANIMAÇÃO E CONTROLE DA POSIÇÃO DA SETA
    DrawTextureEx(Arrow_black,arrow_position[walk_battle_options], 0.0f, 3.5, LIGHTGRAY);

    if(IsKeyPressed(KEY_Z)){
        PlaySound(walk_menuSound);
        if(!play && !itens && !hab){
            if (walk_battle_options == 0) play = true;
            if (walk_battle_options == 1) //deck
            if (walk_battle_options == 2) itens = true;
            if (walk_battle_options == 3) hab = true;

        }   
        if(play){
                if(walk_battle_options == 0) *Playing = 1;
                if(walk_battle_options == 1) *Playing = 1;
                if(walk_battle_options == 2) *Playing = 1;
                if(walk_battle_options == 3) *Playing = 1;
        }
    }// INTERAÇÃO DE CONFIRMAÇÃO

    if(IsKeyPressed(KEY_X)){
        PlaySound(walk_menuSound);
        if(play){
            play = false;
        }
        if(itens){
            itens = false;
        }
    }// INTERAÇÃO DE CANCELAMENTO


    if(!play && !itens){
        for(int i = 0; i < 4; i++){
            DrawTextEx(battle_hud_font, battle_options[i], battle_options_pos[i], 40, 2, BLACK);
        }
    }// MENU INICIAL (SEMPRE EXISTE ENQUANTO PLAY E ITEMS SÃO FALSE)
    if(play && !itens){
        for(int i = 4; i < 8; i++){
            DrawTextEx(battle_hud_font, battle_options[i], battle_options_pos[i-4], 40, 2, BLACK);
        }
    }// OPÇÕES PARA JOGA

    if (hab)
    {
        // Desenha a seta vermelha para mostrar a habilidade
        DrawTextureEx(Arrow_red, arrowr_position, 90.0f, 3.5, RED);

        snprintf(text_box, sizeof(text_box), "HABILIDADE DE %s\n%s: %s", 
                player1_deck[ROUND].nome, 
                hability[player1_deck[ROUND].habilidade].nome, 
                hability[player1_deck[ROUND].habilidade].text);
        

        end_subText = AnimatedTextBox(text_box, battle_hud_font, &frameCounter);
        if(end_subText && IsKeyPressed(KEY_Z)){

            frameCounter = 0.0f;
            hab = false;
        }
    }
}

void DrawPlayTextures(  Texture2D battleHUD[], Texture2D battleTransition[], Font battle_hud_font, 
                        Cards player1_deck[], int *Playing)
{
    static bool TransitionPlayed = false;
    char match_stats[50];
    
    // PLAYER & ENEMY TEXTURES POS
    static float pos_player1 = 832;   // 64x64      330x330
    static float pos_player2 = -307;  // 64x64     210x210
    static float pos_terrain1 = 832;  // 290x80    521x143
    static float pos_terrain2 = -372; // 155x50   341x110

    static Vector2 player_buffs = {10,600};
    static Vector2 enemy_buffs = {240,-33};
    
    // CARD TEXTURES POS
    static Vector2 pos_card = {580,85}; // 220x360  580x85

    printf("%d", *Playing);
 
    // DESENHA OS JOGADORES E HUDS NÃO CLICAVEIS
    DrawTexturePro(battleHUD[0], (Rectangle){0, 0, 240, 50},
                   (Rectangle){0, 432, 800, 167}, (Vector2){0, 0}, 0, WHITE);
    DrawTexturePro(battleHUD[3], (Rectangle){0, 0, 290, 80},
                   (Rectangle){pos_terrain1, 290, 521, 143}, (Vector2){0,0}, 0, WHITE);
    DrawTexturePro(battleHUD[4], (Rectangle){0, 0, 155, 50},
                   (Rectangle){pos_terrain2, 105, 341, 110}, (Vector2){0,0}, 0, WHITE);
    DrawTexturePro(battleHUD[2], (Rectangle){0, 0, 64, 64},
                   (Rectangle){pos_player2, -25, 210, 210}, (Vector2){0,0}, 0, WHITE);
    DrawTexturePro(battleHUD[1], (Rectangle){0, 0, 64, 64},
                   (Rectangle){pos_player1, 150, 285, 285}, (Vector2){0,0}, 0, WHITE);
   
    // DESENHA AS INFORMAÇÕES DURANTE A PARTIDA
    if(TransitionPlayed && *Playing == 0){

        DrawRectangleRounded((Rectangle){0,0,230,225}, 0.3, 10, (Color){0, 0, 0, 128});
        snprintf(match_stats, sizeof(match_stats), "%d FPS\nTYPE\nTERRENO\nROUND %d\n DECK PLAYER1 %d\n, DECK PLAYER2 %d",
                GetFPS(), ROUND, 16, 16);
        DrawTextEx(battle_hud_font, match_stats, (Vector2){10, 10}, 25, 0.2, WHITE);
        DrawRectangleRoundedLines((Rectangle){0,0,230,225}, 0.3, 10, RED);// arrumar para ficar melhor dps
        
        // CARTA
        DrawTexturePro(player1_deck[ROUND].card_texture.texture, (Rectangle){0, 0, 220, -360},
                   (Rectangle){pos_card.x, pos_card.y, 209, 342}, (Vector2){0, 0}, 0.0f, WHITE);
    }
    // -----------------------------------------------------------------------------------------------
    
    // CONTROLE DE TRANSIÇÃO
    if(!TransitionPlayed){
        TransitionPlayed =  battleAnimation(battleTransition, &pos_player1, &pos_player2, &pos_terrain1, &pos_terrain2);// anima a transição
    }

    //-------------------------------------------------------------------------------------------------

    if(*Playing > 0 ){
        
        AnimatedPlaying(player1_deck[ROUND].card_texture.texture, player2_deck[ROUND].card_texture.texture, Playing);
    }


}