#ifndef CARDS_H
#define CARDS_H

#include "raylib.h"

// Declarações de funções e structs

extern int TOTAL_CARDS;

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
    RenderTexture2D card_texture;
}Cards; // ESTRUTURA PARA AS CARTAS

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

// HAB FUNCTIONS
void disable(   Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                bool player, int *NBUFF_P, int *NBUFF_E);

void secret_power(  Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                    bool player, int *NBUFF_P, int *NBUFF_E);

void adaptative_terrain(Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                        bool player, int *NBUFF_P, int *NBUFF_E);

void heal_pulse(Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                bool player, int *NBUFF_P, int *NBUFF_E);

void heavy_slam(Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                bool player, int *NBUFF_P, int *NBUFF_E);

void levitate(  Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                bool player, int *NBUFF_P, int *NBUFF_E);

void dragons_dance( Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                    bool player, int *NBUFF_P, int *NBUFF_E);

void bulk_up(   Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                bool player, int *NBUFF_P, int *NBUFF_E);

void future_sight(  Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                    bool player, int *NBUFF_P, int *NBUFF_E);

void blizzard(  Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                bool player, int *NBUFF_P, int *NBUFF_E);
//----------------------------------------------------------------------------------------------------------

typedef struct { 
    char nome[20];
    char text[200];
    void (*hability_function)(  Cards *card_player, Cards *card_enemy, Texture2D battleBuffs[], 
                                bool player, int *NBUFF_P, int *NBUFF_E);
}Hability;// HABILIDADES

typedef struct{
    char b_name[20];
    bool b_type[4];
    bool b_trunfo;
    float b_atk;
    float b_hp;
    float b_pso;
    float b_alt;
    int b_hab;
    char p_img[30];
}CreatMenu;

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
void AnimatedBuffs(Texture2D battleBuffs[], int ID_buff, int n_buff, bool player, int *end_animation);

void ShowCards_Menu(Cards card[], Filters activate_filters, RenderTexture2D TextureCards[]);

void Vizualizer(CreatMenu card_info, Backgrounds_cards backgrounds_cards, Texture2D poke_img_buffer, Font poke_font);

#endif // CARDS_H