#ifndef PLAY_H
#define PLAY_H

extern int ROUND;
extern int TYPE_MATCH;
extern char TERRAIN;
extern Cards *player1_deck;
extern Cards *player2_deck;


void ShuffleDeck(Cards deck[]);

bool battleAnimation(   Texture2D battleTransition[], float *pos_player1, float *pos_player2, 
                        float *pos_terrain1, float *pos_terrain2);

void AnimatedHability();

void AnimatedPlaying(Texture2D player1_card, Texture2D player2_card, int *Playing);

bool AnimatedTextBox(char text_box[], Font battle_hud_font, float *frameCounter);



void battleHud( Font battle_hud_font, Texture2D Arrow_black, Texture2D Arrow_red, Sound walk_menuSound, 
                Cards player1_deck[], RenderTexture2D CardTexture[], int *Playing);
             
                void DrawPlayTextures(  Texture2D battleHUD[], Texture2D battleTransition[], Font battle_hud_font, 
                    Cards player1_deck[], int *Playing);

#endif 