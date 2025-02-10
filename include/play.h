#ifndef PLAY_H
#define PLAY_H

extern int ROUND;
extern int TYPE_MATCH;
extern Cards *player1_deck;
extern Cards *player2_deck;

#endif

void ShuffleDeck(Cards deck[]);
bool battleAnimation(   Texture2D battleTransition[], float *pos_player1, float *pos_player2, 
                        float *pos_terrain1, float *pos_terrain2);
bool AnimatedTextBox(char text_box[], Font battle_hud_font, float *frameCounter);
void battleHud( Font battle_hud_font, Texture2D Arrow_black, Texture2D Arrow_red, Sound walk_menuSound, 
                Cards player1_deck[], RenderTexture2D CardTexture[]);
void DrawPlayTextures(  Texture2D battleHUD[], Texture2D battleTransition[], Font battle_hud_font, Cards player1_deck[]);