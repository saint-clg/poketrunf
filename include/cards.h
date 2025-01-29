#ifndef CARDS_H
#define CARDS_H

#include "raylib.h"

// Declarações de funções e structs

typedef struct
{
    char nome[20];
    char tipo;
    int numero;
    bool trunfo;
    int hp;
    int ataque;
    float peso;
    float altura;
    int habilidade;
    char img[30];
} Cards; // ESTRUTURA PARA AS CARTAS

typedef struct {
    Texture2D card_background;
    Texture2D ice_background;
    Texture2D dragon_background;
    Texture2D pisych_background;
    Texture2D fighting_background;
    Texture2D super_trunfo_boards;
    Texture2D cards_boards;
}Backgrounds_cards;

typedef enum {  DISABLE, // #generic #hability
                SECRET_POWER, //#generic #debuf
                ADAPTATIVE_TERRAIN, // #generic #terrain
                TEASURE_HUNT, // #generic #item
                SWORDS_DANCE, // #generic #buff #atk
                HEAL_PULSE,// #generic #buff #hp
                HEAVY_SLAM, // #generic #buff #pso
                LEVITATE, // #generic #buff #alt
                DRANGONS_DANCE, // #dragon buff #all
                BULK_UP, // #fighting buff #pso & #alt
                FUTURE_SIGHT, // #pyshic #hability
                BLIZZARD, // #ice #debuff
                TOTAL_HABILITIES // #devinf
}Hab_code; // HABILIDADES E SEUS CÓDIGOS

void disable();
void secret_power();
void adaptative_terrain();
void teasure_hunt();
void swords_dance();
void heal_pulse();
void heavy_slam();
void levitate();
void dragons_dance();
void bulk_up();
void future_sight();
void blizzard();

typedef struct { 
    char nome[20];
    char text[200];
    void (*hability_function)(void);
}Hability;// HABILIDADES

typedef struct{
    //TYPES FILTER
    bool check_type[5]; // 0=activate 1=ICE 2=
    bool check_stats[5];
    bool check_search;

    //STATUS FILTER
    float min_filter, max_filter;
    char min_filterText[35], max_filterText[35];
    char search_name[40];
}Filters; // FILTROS PARA A PESQUISA

extern Hability hability[TOTAL_HABILITIES];
extern float scrollOffset;

//FUNCTIONS -----------------------------------------------------------------------------------------------------

void ShowCards_Menu(Cards card[], Filters activate_filters, RenderTexture2D TextureCards[], int total_cards, Font poke_font);

#endif // CARDS_H