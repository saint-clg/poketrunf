#ifndef DECK_MENU_H
#define DECK_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "cards.h"
#include "struct_card.h"
#include <string.h>
#include "game_screen.h"

void InitDeck(  Sound *enter_menuSound, GameScreen *CurrentScreen, bool *addNewCard_menu, Cards *deck, 
                Filters *filters_deck, RenderTexture2D *TextureCards, int *TOTAL_CARDS, 
                Font poke_font, CreatMenu *CreatCard_buffer, Backgrounds_cards *backgrounds_cards, 
                Cards *nova_carta);


#endif