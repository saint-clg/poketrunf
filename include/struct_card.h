#ifndef STRUCT_CARDS_H
#define STRUCT_CARDS_H

// Declarações de funções e structs

#endif // STRUCT_CARDS_H


void Strings(char a[], int b);

void SaveBin(FILE *arq_csv, FILE *arq_dat, Cards *buffer);

int CountLines(FILE *arq_dat);

void InitCardsTextures(Cards card[], Backgrounds_cards *backgrounds_cards, Texture2D *pokemon_img, int totalCards);

void CreatCards(Cards card[], Backgrounds_cards background_cards, Texture2D poke_img[], RenderTexture2D CardTexture[], int TOTAL_CARDS);
