#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "raylib.h"
#include "cards.h"
#include "struct_card.h"

void disable()
{
    printf("magia!");
};
void secret_power()
{
    printf("magia!");
};
void adaptative_terrain()
{
    printf("magia!");
};
void teasure_hunt()
{
    printf("magia!");
};
void swords_dance()
{
    printf("magia!");
};
void heal_pulse()
{
    printf("magia!");
};
void heavy_slam()
{
    printf("magia!");
};
void levitate()
{
    printf("magia!");
};
void dragons_dance()
{
    printf("magia!");
};
void bulk_up()
{
    printf("magia!");
};
void future_sight()
{
    printf("magia!");
};
void blizzard()
{
    printf("magia!");
};

Hability hability[TOTAL_HABILITIES] = {
    {"DISABLE", "Desabilita temporariamente as habilidades e itens usados pelo inimigo, tornando-os incapazes de realizar acoes durante um turno.", disable},
    {"SECRET_POWER", "Libera uma força secreta que causa um debuff aleatório ao inimigo, enfraquecendo suas habilidades ou atributos por um turno.", secret_power},
    {"ADAPTATIVE_TERRAIN", "Modifica o terreno de batalha para favorecer suas cartas, proporcionando um bônus estratégico que fortalece suas habilidades ou atributos.", adaptative_terrain},
    {"TEASURE_HUNT", "Ativa uma busca por itens na pilha, com a quantidade e qualidade dos itens encontrados variando conforme sua sorte.", teasure_hunt},
    {"SWORDS_DANCE", "Realiza uma dança que intensifica temporariamente os pontos de ataque da carta.", swords_dance},
    {"HEAL_PULSE", "Emite uma onda curativa que intensifica temporariamente os ponstos de hp da carta.", heal_pulse},
    {"HEAVY_SLAM", "Aumenta a massas da carta oque aumenta temporariamente o peso da carta.", heavy_slam},
    {"LEVITATE", "Concede à carta a habilidade de levitar oque aumenta temporariamente a altura da carta.", levitate},
    {"DRAGONS_DANCE", "Efetua uma dança draconica ancestral, elevando seu ataque e pontos de vida, ganhando um poder impressionante.", dragons_dance},
    {"BULK_UP", "Aumenta significativamente a massa e o tamanho da carta, elevando seu peso e altura, quando um corpo impressionante.", bulk_up},
    {"FUTURE_SIGHT", "Vislumbra o futuro! Se vencer, rouba duas cartas do inimigo...\nSe perder, compra um item e altera o campo de batalha para uma vantagem inesperada...\n.", future_sight},
    {"BLIZZARD", "Uma tempestade de gelo devastadora que congela a carta inimiga, reduzindo drasticamente todos os seus atributos.", blizzard}};

void ShowCards_Menu(Cards card[], Filters activate_filters, RenderTexture2D TextureCards[], int total_cards)
{
    // Definindo o tamanho e o espaçamento das cartas
    int cardWidth = 110;
    int cardHeight = 180;
    int padding = 10;               // Espaço entre as cartas
    int startX = 310;               // Posição inicial X
    int startY = 20 + scrollOffset; // Posição inicial Y

    static int selectIndex = -1;

    bool filter = true;

    // Inicia a renderização

    for (int i = 0, s = 0; i < total_cards; i++)
    {

        filter = true;

        // Lógica de filtros

        if (activate_filters.check_search)
        {

            if (strcasecmp(activate_filters.search_name, card[i].nome))
                filter = false;
        }

        if (activate_filters.check_type[0])
        {
            if (activate_filters.check_type[1] && card[i].tipo != 'G')
                filter = false;
            if (activate_filters.check_type[2] && card[i].tipo != 'L')
                filter = false;
            if (activate_filters.check_type[3] && card[i].tipo != 'D')
                filter = false;
            if (activate_filters.check_type[4] && card[i].tipo != 'P')
                filter = false;
        }

        if (activate_filters.check_stats[0])
        {
            if (activate_filters.check_stats[1])
            {
                if (card[i].hp < activate_filters.min_filter || card[i].hp > activate_filters.max_filter)
                    filter = false;
            }
            if (activate_filters.check_stats[2])
            {
                if (card[i].ataque < activate_filters.min_filter || card[i].ataque > activate_filters.max_filter)
                    filter = false;
            }
            if (activate_filters.check_stats[3])
            {
                if (card[i].altura < activate_filters.min_filter || card[i].altura > activate_filters.max_filter)
                    filter = false;
            }
            if (activate_filters.check_stats[4])
            {
                if (card[i].peso < activate_filters.min_filter || card[i].peso > activate_filters.max_filter)
                    filter = false;
            }
        }

        if (filter)
        {
            // Cálculo da posição de cada carta (linha e coluna)
            int row = s / 4; // Determina em qual linha a carta ficará
            int col = s % 4; // Determina em qual coluna a carta ficará

            // Posição X e Y da carta
            int posX = startX + (cardWidth + padding) * col;
            int posY = startY + (cardHeight + padding) * row;

            Rectangle CardRect = {posX, posY, cardWidth, cardHeight};

            DrawTexturePro(TextureCards[i].texture,
                           (Rectangle){0, 0, 220, -360},                   // Dimensões originais da textura
                           (Rectangle){posX, posY, cardWidth, cardHeight}, // Nova escala (110x180)
                           (Vector2){0, 0},                                // Ponto de origem (não precisa mudar)
                           0.0f,                                           // Rotação
                           WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), CardRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {

                selectIndex = i;
            }

            s++;
        }
    }

    if (selectIndex != -1)
    {
        Rectangle CardVizualizer = {10, 10, 280, 390};
        DrawTexturePro(TextureCards[selectIndex].texture, (Rectangle){0, 0, 220, -360},
                       CardVizualizer, (Vector2){0, 0}, 0.0f, WHITE);
    }
}

void Vizualizer(CreatMenu card_info, Backgrounds_cards backgrounds_cards, Texture2D poke_img_buffer, Font poke_font)
{

    Rectangle background_card = {0, 0, 220, 360};
    Rectangle background_viz_card = {140, 125, 220, 360};
    Rectangle background_pokemon = {0, 0, 198, 178};
    Rectangle background_viz_pokemon = {151, 166, 198, 178};

    char card_title[30];
    char poke_img_path[30];
    const char stats_text[30];

    if (card_info.b_type[0])
    {

        DrawTexturePro(backgrounds_cards.ice_background, background_card, background_viz_card, (Vector2){0, 0},
                       0, WHITE);
        snprintf(card_title, sizeof(card_title), "G %s", card_info.b_name);
    }
    if (card_info.b_type[1])
    {

        DrawTexturePro(backgrounds_cards.fighting_background, background_card, background_viz_card, (Vector2){0, 0},
                       0, WHITE);
        snprintf(card_title, sizeof(card_title), "L %s", card_info.b_name);
    }
    if (card_info.b_type[3])
    {

        DrawTexturePro(backgrounds_cards.dragon_background, background_card, background_viz_card, (Vector2){0, 0},
                       0, WHITE);
        snprintf(card_title, sizeof(card_title), "D %s", card_info.b_name);
    }
    if (card_info.b_type[4])
    {

        DrawTexturePro(backgrounds_cards.pisych_background, background_card, background_viz_card, (Vector2){0, 0},
                       0, WHITE);
        snprintf(card_title, sizeof(card_title), "P %s", card_info.b_name);
    }

    DrawTexturePro(backgrounds_cards.card_background, background_pokemon, background_viz_pokemon, (Vector2){0, 0},
                   0, WHITE);

    snprintf(poke_img_path, sizeof(poke_img_path), ".\\assets\\cards\\img\\%s.png", card_info.p_img);
    poke_img_buffer = LoadTexture(poke_img_path);
    if (poke_img_buffer.id == 0)
    {
        poke_img_buffer = LoadTexture(".\\assets\\cards\\img\\none.png");
    }
    DrawTextureEx(poke_img_buffer, (Vector2){165, 182}, 0, 1.8f, WHITE);

    if (card_info.b_trunfo)
    {
        DrawTexturePro(backgrounds_cards.super_trunfo_boards, background_card, background_viz_card, (Vector2){0, 0},
                       0, WHITE);
    }
    else DrawTexturePro(backgrounds_cards.cards_boards, background_card, background_viz_card, (Vector2){0, 0}, 0, WHITE);

    DrawTextEx(poke_font, card_title, (Vector2){153, 137}, 18, 0.2, BLACK);

    snprintf(stats_text, sizeof(stats_text), "ATK: %d", (int)card_info.b_atk);
    DrawTextEx(poke_font, stats_text, (Vector2){151, 357}, 15, 0.2, BLACK);

    snprintf(stats_text, sizeof(stats_text), "HP: %d", (int)card_info.b_hp);
    DrawTextEx(poke_font, stats_text, (Vector2){151, 372}, 15, 0.2, BLACK);

    snprintf(stats_text, sizeof(stats_text), "ALT: %.2f", card_info.b_alt);
    DrawTextEx(poke_font, stats_text, (Vector2){260, 357}, 15, 0.2, BLACK);

    snprintf(stats_text, sizeof(stats_text), "PSO: %.2f", card_info.b_pso);
    DrawTextEx(poke_font, stats_text, (Vector2){260, 372}, 15, 0.2, BLACK);

    snprintf(stats_text, sizeof(stats_text), "HAB: %s", hability[card_info.b_hab].nome);
    DrawTextEx(poke_font, stats_text, (Vector2){147, 392}, 15, 0.2, BLACK);

    DrawTextBoxed(poke_font, hability[card_info.b_hab].text, (Rectangle){147, 405, 205, 80}, 14, 0, true, BLACK);
}