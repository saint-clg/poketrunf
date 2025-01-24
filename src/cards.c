#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "cards.h"

void disable(){
    printf("magia!");
};
void secret_power(){
    printf("magia!");
};
void adaptative_terrain(){
    printf("magia!");
};
void teasure_hunt(){
    printf("magia!");
};
void swords_dance(){
    printf("magia!");
};
void heal_pulse(){
    printf("magia!");
};
void heavy_slam(){
    printf("magia!");
};
void levitate(){
    printf("magia!");
};
void dragons_dance(){
    printf("magia!");
};
void bulk_up(){
    printf("magia!");
};
void future_sight(){
    printf("magia!");
};
void blizzard(){
    printf("magia!");
};

Hability hability[TOTAL_HABILITIES] = {
    {"DISABLE", "Desabilita temporariamente as habilidades e itens usados pelo inimigo, tornando-os incapazes de realizar ações durante um turno.", disable},
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
    {"BLIZZARD", "Desencadeia uma tempestade de gelo devastadora que congela a carta inimiga, reduzindo drasticamente todos os seus atributos e enfraquecendo suas ações.", blizzard}
};

void ShowCards_Menu(Cards card[], Filters activate_filters, RenderTexture2D TextureCards[], int total_cards) {
    // Definindo o tamanho e o espaçamento das cartas
    int cardWidth = 110;
    int cardHeight = 180;
    int padding = 10;  // Espaço entre as cartas
    int startX = 310;   // Posição inicial X
    int startY = 20 + scrollOffset;   // Posição inicial Y

    bool filter = true;

    // Inicia a renderização

    for (int i = 0, s = 0; i < total_cards; i++) {

        filter = true;

        // Lógica de filtros

        if(activate_filters.check_search){
        
            if(strcasecmp(search_name, card[i].nome)) filter = false;
        }

        if (activate_filters.check_type[0]) {
            if (activate_filters.check_type[1] && card[i].tipo != 'G') filter = false;
            if (activate_filters.check_type[2] && card[i].tipo != 'L') filter = false;
            if (activate_filters.check_type[3] && card[i].tipo != 'D') filter = false;
            if (activate_filters.check_type[4] && card[i].tipo != 'P') filter = false;
        }

        if (activate_filters.check_stats[0]) {
            if (activate_filters.check_stats[1]) {
                if (card[i].hp < activate_filters.min_filter || card[i].hp > activate_filters.max_filter) filter = false;
            }
            if (activate_filters.check_stats[2]) {
                if (card[i].ataque < activate_filters.min_filter || card[i].ataque > activate_filters.max_filter) filter = false;
            }
            if (activate_filters.check_stats[3]) {
                if (card[i].altura < activate_filters.min_filter || card[i].altura > activate_filters.max_filter) filter = false;
            }
            if (activate_filters.check_stats[4]) {
                if (card[i].peso < activate_filters.min_filter || card[i].peso >   activate_filters.max_filter) filter = false;
            }
        }

        if (filter) {
            // Cálculo da posição de cada carta (linha e coluna)
            int row = s / 4;  // Determina em qual linha a carta ficará
            int col = s % 4;  // Determina em qual coluna a carta ficará

            // Posição X e Y da carta
            int posX = startX + (cardWidth + padding) * col;
            int posY = startY + (cardHeight + padding) * row;

            DrawTextureRec(TextureCards[i].texture, (Rectangle){0, 0, cardWidth, -cardHeight}, (Vector2){posX, posY}, WHITE);
            s++;
        }
    }
}


