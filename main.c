#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "cards.h"
#include "struct_card.h"
#include "play.h"
#include "deck_menu.h"
#include "game_screen.h"

float scrollOffset = 0;
int main()
{

    InitWindow(800, 600, "main");
    SetTargetFPS(60);
    InitAudioDevice();
    //--------------------------------------------------------------------------- VARIAVEIS PARA DECK E GERENCIAMENTO

    Cards buffer; // ESTRUTURA BUFFER PARA GUARDAR INFORMAÇÕES CASO NESCESSARIO (TALVEZ NÃO PRECISE MAIS)
    FILE *arq_csv, *arq_dat;

    arq_dat = fopen(".\\data\\user_deck.dat", "r+b"); // VERIFICA DECK DO USUÁRIO
    if (arq_dat == NULL)                              // DECK DE USUÁRIO NÃO ENCONTRADO (PRIMEIRO ACESSO)
    {
        arq_csv = fopen(".\\assets\\csv\\meta_deck.csv", "r+"); // ABRE O DECK META (DECK INICIAL)
        if (arq_csv == NULL)                                    // VERIFICAÇÃO DESTE ARQUIVO ^
        {

            printf("FALHA AO LER ARQUIVO CSV!\n"); // MENSAGEM DE ERRO
            exit(1);
        } // if

        printf("PRIMEIRA INICIALIZAÇÃO...SALVANDO SEU JOGO <não feche o programa>\n");
        arq_dat = fopen(".\\data\\user_deck.dat", "w+b"); // CRIA UM ARQUIVO PARA O DECK DO USUÁRIO

        if (arq_dat == NULL) // VERIFICAÇÃO DESTE ARQUIVO ^
        {

            printf("FALHA AO CRIAR ARQUIVO!\n"); // MENSAGEM DE ERRO
            exit(1);
        } // if
        SaveBin(arq_csv, arq_dat, &buffer); // COPIANDO META DECK PARA USUÁRIO DECK
        memset(&buffer, 0, sizeof(Cards));  // LIMPA A ESTRUTURA BUFFER

        fclose(arq_csv); // FECHA O META DECK

    } // if (PRIMEIRA INICIALIZAÇÃO);

    TOTAL_CARDS = CountLines(arq_dat);                          // CADA LINHA DO .DAT É UMA CARTA
    Cards *deck = (Cards *)malloc(TOTAL_CARDS * sizeof(Cards)); // CRIA NOSSO DECK COM TAMANHO VARIADO PARA AS CARTAS

    printf("Criando deck...\n\n\n");
    fread(deck, sizeof(Cards), TOTAL_CARDS, arq_dat); // PREENCHE NOSSA ESTRUTURA DECK COM AS INFORMAÇÕES NO NOSSO .DAT

    //--------------------------------------------------------------------------- VARIAVEIS PARA MENUS
    Texture2D pokemon_img[TOTAL_CARDS];
    Backgrounds_cards backgrounds_cards;
    Font poke_font;
    Font Battle_hud_font;
    Texture2D battleHUD[7];
    Texture2D battleTransition[16];
    Texture2D battleBuffs[8];
    Texture2D TypeTextures[4];
    Font font_mainmenu;
    Sound walk_menuSound;
    Sound enter_menuSound;
    Texture2D logo;
    Texture2D background_mainmenu;

    InitAssets( deck, &backgrounds_cards, pokemon_img, TOTAL_CARDS, &poke_font, battleHUD, battleTransition, 
                battleBuffs, TypeTextures, &font_mainmenu, &walk_menuSound, &enter_menuSound, &logo, &background_mainmenu, 
                &Battle_hud_font);

    RenderTexture2D TextureCards[TOTAL_CARDS];

    Cards player1_deck[32];
    Cards player2_deck[32];

    CreatCards(deck, backgrounds_cards, pokemon_img, TextureCards, poke_font);

    GameScreen CurrentScreen = MAIN_MENU;

    int walk_menu = 0, screenWidth = GetScreenWidth();
    const char *menu_options[] = {"Play", "Deck", "Options", "Exit"};

    int Playing = 0;
    
    int ROUND = 0;
    int NBUFF_P = 0;
    int NBUFF_E = 0;

    //--------------------------------------------------------------------------- WHILE DO JOGO

    printf("%d", TOTAL_CARDS);

    while (!WindowShouldClose())
    {

        if (CurrentScreen == MAIN_MENU)
        {

            BeginDrawing();

            ClearBackground((Color)WHITE);
            DrawTexture(background_mainmenu, 0, 0, WHITE);
            DrawTexture(logo, (screenWidth - logo.width) / 2, 50, WHITE);

            for (int i = 0; i < 4; i++)
            {
                Color textColor = (walk_menu == i) ? RED : BLACK;

                float textWidth = MeasureTextEx(font_mainmenu, menu_options[i], 30, 2).x;

                DrawTextEx(font_mainmenu, menu_options[i],
                           (Vector2){(screenWidth - textWidth) / 2.095,
                                     850 / 2 - ((4 * 60) / 2) + i * 60},
                           30, 2, textColor);
            }

            if (IsKeyPressed(KEY_DOWN))
            {

                walk_menu++;
                PlaySound(walk_menuSound);
                if (walk_menu > 3)
                    walk_menu = 0;
            }

            if (IsKeyPressed(KEY_UP))
            {

                walk_menu--;
                PlaySound(walk_menuSound);
                if (walk_menu < 0)
                    walk_menu = 3;
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                PlaySound(enter_menuSound);

                if (walk_menu == 0)
                {
                    CurrentScreen = PLAY;
                }
                if (walk_menu == 1)
                {
                    CurrentScreen = DECK_MENU;
                    if (walk_menu == 2)
                    {
                    }
                    printf("opção 2");
                }
                if (walk_menu == 3)
                {
                    CloseWindow();
                }
            }
            EndDrawing();
        }
        //--------------------------------------------------------------------------- PLAY
        if (CurrentScreen == PLAY)
        {   

            static bool InicializateGame = true;
            static bool end_AnimatedPlaying;
            static bool load_round = false;
            const char  InicializeGame[100] = "Inicializando Jogo...";
            static float frameCounter = 0; 
            static int end_Animatedplaying = 0;
            static int choice; 


            BeginDrawing();

            ClearBackground(WHITE);
            DrawPlayTextures(battleHUD,battleTransition,poke_font,player1_deck, player2_deck, &Playing, &ROUND);
            battleHud(  poke_font,battleHUD[5], battleHUD[6], walk_menuSound, player1_deck, 
                        TextureCards, &Playing, &ROUND, &choice);
            if(InicializateGame){
                ShuffleDeck(deck, player1_deck, player2_deck);
                for(int i =0; i < TOTAL_CARDS; i++){
                }

                for(int t = 0; t < 32; t++){
                    printf("DECK: %s\n", deck[t].nome);
                }
                InicializateGame = false;
                Playing = 0;
                printf("PREPARANDO DECK...");
            }
            if(Playing == 1){
                if(!load_round){
                    NBUFF_E = 0;
                    NBUFF_P = 0;
                    load_round = true;
                    printf("CARREGANDO ROUND...");
                }
            }
            if(Playing == 2 && ROUND % 2 == 0){
                AnimatedHability(&Playing);
                hability[player1_deck[ROUND].habilidade].hability_function(&player1_deck[ROUND],&player2_deck[ROUND],
                    battleBuffs, 1, &NBUFF_P, &NBUFF_P);
                printf("atk: %d, hp: %d, alt: %f, pso: %f", player1_deck[ROUND].ataque, player1_deck[ROUND].hp,
                                                            player1_deck[ROUND].altura, player1_deck[ROUND].peso);
            }
            if(Playing == 2 && ROUND % 2 != 0){
                AnimateHabilityRev(&Playing);
                hability[player2_deck[ROUND].habilidade].hability_function(&player2_deck[ROUND],&player1_deck[ROUND],
                    battleBuffs, 0, &NBUFF_P, &NBUFF_P);
                printf("atk: %d, hp: %d, alt: %f, pso: %f", player2_deck[ROUND].ataque, player2_deck[ROUND].hp,
                                                            player2_deck[ROUND].altura, player2_deck[ROUND].peso);
            }
            if(Playing == 3 && ROUND % 2 == 0){
                AnimateHabilityRev(&Playing);
                hability[player2_deck[ROUND].habilidade].hability_function(&player2_deck[ROUND],&player1_deck[ROUND],
                    battleBuffs, 0, &NBUFF_P, &NBUFF_P);
                printf("atk: %d, hp: %d, alt: %f, pso: %f", player2_deck[ROUND].ataque, player2_deck[ROUND].hp,
                                                            player2_deck[ROUND].altura, player2_deck[ROUND].peso);
            }
            if(Playing == 3 && ROUND % 2 != 0){
                AnimatedHability(&Playing);
                hability[player1_deck[ROUND].habilidade].hability_function(&player1_deck[ROUND],&player2_deck[ROUND],
                                                                            battleBuffs, 1, &NBUFF_P, &NBUFF_P);
                printf("atk: %d, hp: %d, alt: %f, pso: %f", player1_deck[ROUND].ataque, player1_deck[ROUND].hp,
                                                            player1_deck[ROUND].altura, player1_deck[ROUND].peso);
                                            
            }                                                         
            if(Playing == 4){

               if(Comparation(player1_deck[ROUND], player2_deck[ROUND], &choice)){

                    printf("PLAYER1 VENCEU!"); 
               }else printf("PLAYER2 VENCEU!");

               ROUND ++;
               Playing = 0;
               load_round = false;
            }
            EndDrawing();
        }

        //--------------------------------------------------------------------------- DECK MENU
        if (CurrentScreen == DECK_MENU)
        {

            static Filters filters_deck = {
                .check_type = {false, false, false, false, false},
                .check_stats = {false, false, false, false, false},
                .check_search = false,
                .min_filter = 0.0f,
                .max_filter = 999.0f,
                .min_filterText = "MIN...",
                .max_filterText = "MAX...",
                .search_name = "Search..."};

            static CreatMenu CreatCard_buffer = {

                .b_name = "name",
                .b_type = {true, false, false, false},
                .b_trunfo = false,
                .b_atk = 0,
                .b_hp = 0,
                .b_pso = 0,
                .b_alt = 0,
                .b_hab = DISABLE,
                .p_img = "none"};

            static bool addNewCard_menu = false;
            static bool addNewCard_confirm = false;

            InitDeck(   &enter_menuSound, &CurrentScreen, &addNewCard_menu, deck, &filters_deck, TextureCards, 
                        &TOTAL_CARDS, poke_font, &CreatCard_buffer, &backgrounds_cards, &buffer);

            
                        
        //-----------------------------------------------------------------------------------END DECK MENU
        }
    }

    UnloadSound(walk_menuSound);
    UnloadSound(enter_menuSound);
    UnloadFont(font_mainmenu);
    UnloadTexture(logo);
    CloseAudioDevice();
    CloseWindow();
    fclose(arq_dat);
    free(deck);
    free(player1_deck);
    free(player2_deck);
}
