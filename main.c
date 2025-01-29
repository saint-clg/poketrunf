#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "cards.h"
#include "struct_card.h"

typedef enum {MAIN_MENU, DECK_MENU, PLAY, CONFIG_MENU} GameScreen;  
float scrollOffset = 0;

int main(){

    InitWindow(800, 600, "main");
    InitAudioDevice();
//-------------------------------------------------------------------------------VARIAVEIS PARA DECK E GERENCIAMENTO

    Cards buffer;// ESTRUTURA BUFFER PARA GUARDAR INFORMAÇÕES CASO NESCESSARIO (TALVEZ NÃO PRECISE MAIS)
    FILE *arq_csv, *arq_dat;

    arq_dat = fopen(".\\data\\user_deck.dat", "r+b");// VERIFICA DECK DO USUÁRIO
    if (arq_dat == NULL)// DECK DE USUÁRIO NÃO ENCONTRADO (PRIMEIRO ACESSO)
    {
        arq_csv = fopen(".\\assets\\csv\\meta_deck.csv", "r+");// ABRE O DECK META (DECK INICIAL)
        if (arq_csv == NULL)// VERIFICAÇÃO DESTE ARQUIVO ^ 
        {

            printf("FALHA AO LER ARQUIVO CSV!\n");// MENSAGEM DE ERRO
            exit(1);
        } // if

        printf("PRIMEIRA INICIALIZAÇÃO...SALVANDO SEU JOGO <não feche o programa>\n");
        arq_dat = fopen(".\\data\\user_deck.dat", "w+b");// CRIA UM ARQUIVO PARA O DECK DO USUÁRIO

        if (arq_dat == NULL)// VERIFICAÇÃO DESTE ARQUIVO ^
        {

            printf("FALHA AO CRIAR ARQUIVO!\n");// MENSAGEM DE ERRO
            exit(1);
        } // if 
        SaveBin(arq_csv, arq_dat, &buffer); // COPIANDO META DECK PARA USUÁRIO DECK
        memset(&buffer, 0, sizeof(Cards));  // LIMPA A ESTRUTURA BUFFER

        fclose(arq_csv); // FECHA O META DECK

    } // if (PRIMEIRA INICIALIZAÇÃO);

    int TOTAL_CARDS = CountLines(arq_dat);// CADA LINHA DO .DAT É UMA CARTA
    Cards *deck = (Cards *)malloc(TOTAL_CARDS* sizeof(Cards)); // CRIA NOSSO DECK COM TAMANHO VARIADO PARA AS CARTAS

    printf("Criando deck...\n\n\n");
    fread(deck, sizeof(Cards), TOTAL_CARDS, arq_dat);// PREENCHE NOSSA ESTRUTURA DECK COM AS INFORMAÇÕES NO NOSSO .DAT

//---------------------------------------------------------------------------------------VARIAVEIS PARA MENUS
    Texture2D pokemon_img[TOTAL_CARDS];
    Backgrounds_cards backgrounds_cards;
    InitCardsTextures(deck, &backgrounds_cards, pokemon_img, TOTAL_CARDS);
    Font poke_font = LoadFont(".\\assets\\fonts\\Symtext.ttf");
    RenderTexture2D TextureCards[TOTAL_CARDS];
    CreatCards(deck,backgrounds_cards,pokemon_img,TextureCards,poke_font,TOTAL_CARDS);

    GameScreen CurrentScreen = MAIN_MENU;
    int walk_menu = 0, screenWidth = GetScreenWidth();
    const char *menu_options[] = {"Play", "Deck", "Options", "Exit"};
    Font font_mainmenu = LoadFont(".\\assets\\fonts\\Minecraft.ttf");
    Sound walk_menuSound = LoadSound(".\\assets\\sounds\\move_menu.wav");
    Sound enter_menuSound = LoadSound(".\\assets\\sounds\\enter_menu.wav");
    Texture2D logo = LoadTexture(".\\assets\\img\\logo.png");
    Texture2D background_mainmenu = LoadTexture(".\\assets\\img\\background_mainmenu.png");

//---------------------------------------------------------------------------------------------WHILE DO JOGO
    
    while(!WindowShouldClose()){
        
        if(CurrentScreen == MAIN_MENU){
            
            BeginDrawing();
            
            ClearBackground((Color)WHITE);
            DrawTexture(background_mainmenu, 0,0, WHITE);
            DrawTexture(logo, (screenWidth - logo.width) / 2, 50, WHITE);

            for (int i = 0; i < 4; i++) {
                Color textColor = (walk_menu == i) ? RED : BLACK;

                float textWidth = MeasureTextEx(font_mainmenu, menu_options[i], 30, 2).x;

                DrawTextEx(font_mainmenu, menu_options[i],
                    (Vector2){(screenWidth - textWidth) / 2.095, 
                            850 / 2 - ((4 * 60) / 2) + i * 60},
                    30, 2, textColor);
            }

            if (IsKeyPressed(KEY_DOWN)){

                walk_menu++;
                PlaySound(walk_menuSound);
                if(walk_menu > 3) walk_menu = 0;
            }
                
            if (IsKeyPressed(KEY_UP)){

                walk_menu--;
                PlaySound(walk_menuSound);
                if(walk_menu < 0) walk_menu = 3;
            }

            if(IsKeyPressed(KEY_ENTER)){
                PlaySound(enter_menuSound);

                if(walk_menu == 0){
                    printf("opção 0");
                }
                if(walk_menu == 1){
                    CurrentScreen = DECK_MENU;
                if(walk_menu == 2){
                }   
                    printf("opção 2");
                }
                if(walk_menu == 3){
                    CloseWindow();
                }

            }
            EndDrawing();

        }

        //--------------------------------------------------------------------------- DECK MENU
        if(CurrentScreen == DECK_MENU){

            static Filters filters_deck = {
                .check_type = {false, false, false, false, false},
                .check_stats = {false, false, false, false, false},
                .check_search = false,
                .min_filter = 0.0f,
                .max_filter = 999.0f,
                .min_filterText = "MIN...",
                .max_filterText = "MAX...",
                .search_name = "Search..."
            };

            static bool show_filters = false;
            static bool search_box = false;
            static bool minFilterEditMode = false;
            static bool maxFilterEditMode = false;

            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            if(IsKeyPressed(KEY_ESCAPE)){

                PlaySound(enter_menuSound);
                CurrentScreen = MAIN_MENU;
            }

            DrawRectangle(10,10,280,580, DARKGRAY);// card search shape    
            DrawRectangle(10,10,280,390, GRAY);// card vizualizer
            DrawRectangle(300,10,490,580, GRAY);
           
            //BOTÃO PARA FILTRAR
            if(GuiButton((Rectangle){225,435,40,30},"#47#")){

                show_filters = !show_filters;
            };

            //CAIXA DE TEXTO PARA PESQUISA DO NOME
            if (GuiTextBox((Rectangle){35,435,190,30}, filters_deck.search_name, 
                            sizeof(filters_deck.search_name), search_box)){

                if(IsKeyPressed(KEY_ENTER)){
                    search_box = false;
                    filters_deck.check_search = true;
                    if(!strlen(filters_deck.search_name) || !strcasecmp(filters_deck.search_name, " ")){
                        filters_deck.check_search = false;
                    }
                }else search_box = true; //LÓGICA DE PESQUISA POR ENTER E CAIXA VAZIA
            }
            
            ShowCards_Menu(deck, filters_deck, TextureCards, TOTAL_CARDS, poke_font);

            if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                scrollOffset += GetMouseDelta().y;  // Deslocamento conforme movimento do mouse
            }

            float wheelMove = GetMouseWheelMove();
            scrollOffset += wheelMove * 20;  // Ajuste fino da velocidade do scroll

            // Limites para evitar scroll infinito
            if (scrollOffset > 0) scrollOffset = 0;
            if (scrollOffset < -((TOTAL_CARDS / 4) * (180 + 10) - 580)) scrollOffset = -((TOTAL_CARDS / 4) * (180 + 10) - 580);

            if(show_filters){
                
                //SHAPE
                DrawRectangle(85,465,180,115,LIGHTGRAY);

                // CHECK BOX TYPE FILTER
                GuiCheckBox((Rectangle){90,470,10,10},"TYPE",&filters_deck.check_type[0]);
                if(filters_deck.check_type[0]){
                    GuiCheckBox((Rectangle){100,490,10,10},"ICE",&filters_deck.check_type[1]);
                    GuiCheckBox((Rectangle){100,510,10,10},"FIGHTING",&filters_deck.check_type[2]);
                    GuiCheckBox((Rectangle){100,530,10,10},"DRAGON",&filters_deck.check_type[3]);
                    GuiCheckBox((Rectangle){100,550,10,10},"PYSICH",&filters_deck.check_type[4]);
                }

                // FILTRO POR STATUS    
                    // TEXT BOX PARA VALORES
                if (GuiTextBox((Rectangle){170,470,40,18}, filters_deck.min_filterText, sizeof(filters_deck.min_filterText), minFilterEditMode)) {
                    minFilterEditMode = !minFilterEditMode;  // Alterna o estado de edição
                }
                if (GuiTextBox((Rectangle){220,470,40,18}, filters_deck.max_filterText, sizeof(filters_deck.max_filterText), maxFilterEditMode)) {
                    maxFilterEditMode = !maxFilterEditMode;  // Alterna o estado de edição
                }
                    // CHECK BOX STATS FILTER
                GuiCheckBox((Rectangle){175,470,10,10}," ",&filters_deck.check_stats[0]);
                if(filters_deck.check_stats[0]){
                    GuiCheckBox((Rectangle){175,490,10,10},"HP",&filters_deck.check_stats[1]);
                    GuiCheckBox((Rectangle){175,510,10,10},"ATK",&filters_deck.check_stats[2]);
                    GuiCheckBox((Rectangle){175,530,10,10},"ALTURA",&filters_deck.check_stats[3]);
                    GuiCheckBox((Rectangle){175,550,10,10},"PESO",&filters_deck.check_stats[4]);
                }

                // APLY BUTTON
                if(GuiButton((Rectangle){190,560,70,15}, "APPLY")){
                    // CONVERTE VALOR DA STRING PARA INT
                    filters_deck.min_filter = atof(filters_deck.min_filterText);
                    filters_deck.max_filter = atof(filters_deck.max_filterText);

                    show_filters = !show_filters;
                }

            }
            
            EndDrawing();
        }
        //-----------------------------------------------------------------------------------END DECK MENU
    }

    UnloadSound(walk_menuSound);
    UnloadSound(enter_menuSound);
    UnloadFont(font_mainmenu);
    UnloadTexture(logo);
    CloseAudioDevice();
    CloseWindow();
    fclose(arq_dat);
    free(deck);
}
