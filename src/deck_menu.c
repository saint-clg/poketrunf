#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "raygui.h"
#include "cards.h"
#include "struct_card.h"
#include <string.h>
#include "game_screen.h"

void InitDeck(Sound *enter_menuSound, GameScreen *CurrentScreen, bool *addNewCard_menu, Cards *deck, Filters *filters_deck, RenderTexture2D *TextureCards, int *TOTAL_CARDS, Font poke_font, CreatMenu *CreatCard_buffer, Backgrounds_cards *backgrounds_cards){

    static bool show_filters = false;
    static bool editCard_menu = false;
    static bool search_box = false;
    static bool minFilterEditMode = false;
    static bool maxFilterEditMode = false;

    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    if (IsKeyPressed(KEY_ESCAPE))
    {

        PlaySound(*enter_menuSound);
        *CurrentScreen = MAIN_MENU;
    }

    DrawRectangle(10, 10, 280, 580, DARKGRAY); // card search shape
    DrawRectangle(10, 10, 280, 390, GRAY);     // card vizualizer
    DrawRectangle(300, 10, 490, 580, GRAY);

    // BOTÃO PARA FILTRAR
    if (GuiButton((Rectangle){225, 435, 40, 30}, "#47#"))
    {

        show_filters = !show_filters;
    };

    // BOTÃO PARA ADICIONAR CARTAS
    if (GuiButton((Rectangle){35, 405, 105, 25}, "AddNewCard"))
    {

        *addNewCard_menu = !*addNewCard_menu;
    };

    if (GuiButton((Rectangle){160, 405, 105, 25}, "Delet/Modify Card"))
    {

        editCard_menu = !editCard_menu;
    };

    // CAIXA DE TEXTO PARA PESQUISA DO NOME
    if (GuiTextBox((Rectangle){35, 435, 190, 30}, filters_deck->search_name,
                    sizeof(filters_deck->search_name), search_box))
    {

        if (IsKeyPressed(KEY_ENTER))
        {
            search_box = false;
            filters_deck->check_search = true;
            if (!strlen(filters_deck->search_name) || !strcasecmp(filters_deck->search_name, " "))
            {
                filters_deck->check_search = false;
            }
        }
        else
            search_box = true; // LÓGICA DE PESQUISA POR ENTER E CAIXA VAZIA
    }

    ShowCards_Menu(deck, *filters_deck, TextureCards);

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        scrollOffset += GetMouseDelta().y; // Deslocamento conforme movimento do mouse
    }

    float wheelMove = GetMouseWheelMove();
    scrollOffset += wheelMove * 20; // Ajuste fino da velocidade do scroll

    // Limites para evitar scroll infinito
    if (scrollOffset > 0)
        scrollOffset = 0;
    if (scrollOffset < -((*TOTAL_CARDS / 4) * (180 + 10) - 580))
        scrollOffset = -((*TOTAL_CARDS / 4) * (180 + 10) - 580);

    if (*addNewCard_menu)
    {
        Texture2D poke_img_buffer;

        static bool name_box = false;
        static bool img_box = false;
        static char stats_text[4][5];
        static bool edit_stats_bar[4] = {false, false, false, false};

        if (GuiWindowBox((Rectangle){120, 100, 560, 440}, "Creating Menu"))
            *addNewCard_menu = false;

        DrawRectangle(130, 120, 540, 410, DARKGRAY);

        if (GuiTextBox((Rectangle){400, 140, 260, 40}, CreatCard_buffer->b_name, sizeof(CreatCard_buffer->b_name),
                        name_box))
        {

            if (IsKeyPressed(KEY_ENTER))
            {

                name_box = false;
            }
            else
                name_box = true;
        }

        DrawRectangle(140, 125, 220, 360, BLACK);
        // LIGAR 1 DESLIGA OS OUTROS
        if (GuiCheckBox((Rectangle){400, 190, 50, 40}, "ICE", &CreatCard_buffer->b_type[0]))
        {
            CreatCard_buffer->b_type[1] = false;
            CreatCard_buffer->b_type[2] = false;
            CreatCard_buffer->b_type[3] = false;
        }
        if (GuiCheckBox((Rectangle){525, 190, 50, 40}, "FIGHTING", &CreatCard_buffer->b_type[1]))
        {
            CreatCard_buffer->b_type[0] = false;
            CreatCard_buffer->b_type[2] = false;
            CreatCard_buffer->b_type[3] = false;
        }
        if (GuiCheckBox((Rectangle){400, 240, 50, 40}, "DRAGON", &CreatCard_buffer->b_type[2]))
        {
            CreatCard_buffer->b_type[0] = false;
            CreatCard_buffer->b_type[1] = false;
            CreatCard_buffer->b_type[3] = false;
        }
        if (GuiCheckBox((Rectangle){525, 240, 50, 40}, "PSYCHIC", &CreatCard_buffer->b_type[3]))
        {
            CreatCard_buffer->b_type[0] = false;
            CreatCard_buffer->b_type[1] = false;
            CreatCard_buffer->b_type[2] = false;
        }

        GuiSliderBar((Rectangle){400, 290, 80, 40}, "MIN", "MAX", &CreatCard_buffer->b_atk, 0, 150);
        snprintf(stats_text[0], 5, "%.2f", CreatCard_buffer->b_atk);
        if (GuiTextBox((Rectangle){400, 290, 80, 40}, stats_text[0], sizeof(stats_text[0]), edit_stats_bar[0]))
        {
            edit_stats_bar[0] = !edit_stats_bar[0];
        }
        GuiSliderBar((Rectangle){400, 340, 80, 40}, "MIN", "MAX", &CreatCard_buffer->b_hp, 0, 150);
        snprintf(stats_text[1], 5, "%.2f", CreatCard_buffer->b_hp);
        if (GuiTextBox((Rectangle){400, 340, 80, 40}, stats_text[1], sizeof(stats_text[1]), edit_stats_bar[1]))
        {
            edit_stats_bar[1] = !edit_stats_bar[1];
        }
        GuiSliderBar((Rectangle){525, 290, 80, 40}, "MIN", "MAX", &CreatCard_buffer->b_alt, 0, 150);
        snprintf(stats_text[2], 5, "%.2f", CreatCard_buffer->b_alt);
        if (GuiTextBox((Rectangle){525, 290, 70, 40}, stats_text[2], sizeof(stats_text[2]), edit_stats_bar[2]))
        {
            edit_stats_bar[2] = !edit_stats_bar[2];
        }
        GuiSliderBar((Rectangle){525, 340, 80, 40}, "MIN", "MAX", &CreatCard_buffer->b_pso, 0, 150);
        snprintf(stats_text[3], 5, "%.2f", CreatCard_buffer->b_pso);
        if (GuiTextBox((Rectangle){525, 340, 80, 40}, stats_text[3], sizeof(stats_text[3]), edit_stats_bar[3]))
        {
            edit_stats_bar[3] = !edit_stats_bar[3];
        }

        if (GuiCheckBox((Rectangle){400, 390, 50, 40}, "TRUNFO", &CreatCard_buffer->b_trunfo));
        if (GuiTextBox((Rectangle){525, 390, 135, 40}, CreatCard_buffer->p_img, sizeof(CreatCard_buffer->p_img),
                        img_box)){

            if (IsKeyPressed(KEY_ENTER))
            {

                img_box = false;
            }
            else
                img_box = true;
        }

        if (GuiButton((Rectangle){140, 495, 220, 30}, "CONFIRM"))
        {
        }
        if (GuiButton((Rectangle){400, 440, 260, 30}, "VISUALIZER"))
        {
        }

        Vizualizer(*CreatCard_buffer, *backgrounds_cards, poke_img_buffer, poke_font);
    }

    if (show_filters)
    {

        // SHAPE
        DrawRectangle(85, 465, 180, 115, LIGHTGRAY);

        // CHECK BOX TYPE FILTER
        GuiCheckBox((Rectangle){90, 470, 10, 10}, "TYPE", &filters_deck->check_type[0]);
        if (filters_deck->check_type[0])
        {
            GuiCheckBox((Rectangle){100, 490, 10, 10}, "ICE", &filters_deck->check_type[1]);
            GuiCheckBox((Rectangle){100, 510, 10, 10}, "FIGHTING", &filters_deck->check_type[2]);
            GuiCheckBox((Rectangle){100, 530, 10, 10}, "DRAGON", &filters_deck->check_type[3]);
            GuiCheckBox((Rectangle){100, 550, 10, 10}, "PSYCHIC", &filters_deck->check_type[4]);
        }

        // FILTRO POR STATUS
        // TEXT BOX PARA VALORES
        if (GuiTextBox((Rectangle){170, 470, 40, 18}, filters_deck->min_filterText, sizeof(filters_deck->min_filterText), minFilterEditMode))
        {
            minFilterEditMode = !minFilterEditMode; // Alterna o estado de edição
        }
        if (GuiTextBox((Rectangle){220, 470, 40, 18}, filters_deck->max_filterText, sizeof(filters_deck->max_filterText), maxFilterEditMode))
        {
            maxFilterEditMode = !maxFilterEditMode; // Alterna o estado de edição
        }
        // CHECK BOX STATS FILTER
        GuiCheckBox((Rectangle){175, 470, 10, 10}, " ", &filters_deck->check_stats[0]);
        if (filters_deck->check_stats[0])
        {
            GuiCheckBox((Rectangle){175, 490, 10, 10}, "HP", &filters_deck->check_stats[1]);
            GuiCheckBox((Rectangle){175, 510, 10, 10}, "ATK", &filters_deck->check_stats[2]);
            GuiCheckBox((Rectangle){175, 530, 10, 10}, "ALTURA", &filters_deck->check_stats[3]);
            GuiCheckBox((Rectangle){175, 550, 10, 10}, "PESO", &filters_deck->check_stats[4]);
        }

        // APLY BUTTON
        if (GuiButton((Rectangle){190, 560, 70, 15}, "APPLY"))
        {
            // CONVERTE VALOR DA STRING PARA INT
            filters_deck->min_filter = atof(filters_deck->min_filterText);
            filters_deck->max_filter = atof(filters_deck->max_filterText);

            show_filters = !show_filters;
        }
    }

    EndDrawing();

    return;
}//InitDeck