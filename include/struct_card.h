#ifndef STRUCT_CARDS_H
#define STRUCT_CARDS_H

// Declarações de funções e structs

#endif // STRUCT_CARDS_H

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

void Strings(char a[], int b);

void SaveBin(FILE *arq_csv, FILE *arq_dat, Cards *buffer);

int CountLines(FILE *arq_dat);

void InitCardsTextures(Cards card[], Backgrounds_cards *backgrounds_cards, Texture2D *pokemon_img, int totalCards);

static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);

static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);

void CreatCards(Cards card[], Backgrounds_cards background_cards, Texture2D poke_img[], RenderTexture2D CardTexture[], 
                Font poke_font, int TOTAL_CARDS);
