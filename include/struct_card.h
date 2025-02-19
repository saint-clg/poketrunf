#ifndef STRUCT_CARDS_H
#define STRUCT_CARDS_H

// Declarações de funções e structs

void Strings(char a[], int b);

void SaveBin(FILE *arq_csv, FILE *arq_dat, Cards *buffer);

int CountLines(FILE *arq_dat);

void InitAssets(Cards card[], Backgrounds_cards *backgrounds_cards, Texture2D *pokemon_img, int totalCards, 
                Font *poke_font, Texture2D battleHUD[], Texture2D battleTransition[], Texture2D battleBuffs[], 
                Texture2D TypesTextures[], Font *font_mainmenu, Sound *walk_menuSound, Sound *enter_menuSound, Texture2D *logo, 
                Texture2D *background_mainmenu, Font *Battle_hud_font);

void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, 
                            float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, 
                            Color selectTint, Color selectBackTint);

void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);

void CreatCards(Cards card[], Backgrounds_cards background_cards, Texture2D poke_img[], RenderTexture2D CardTexture[], 
                Font poke_font);

#endif
