#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cards.h"

void Strings(char a[], int b)
{

    setbuf(stdin, NULL);
    fgets(a, b, stdin);
    a[strcspn(a, "\n")] = '\0';
    return;
} // Strings

void SaveBin(FILE *arq_csv, FILE *arq_dat, Cards *buffer)
{

    char header[200], linha[200];

    fgets(header, 200, arq_csv); // ignora cabeçalho

    while (fgets(linha, 200, arq_csv) != NULL)
    {

        sscanf(linha, " %19[^,], %c, %d, %d, %d, %d, %f, %f, %d, %29[^,\n]", 
               buffer->nome,
               &buffer->tipo,
               &buffer->numero,
               (int *)&buffer->trunfo,
               &buffer->hp,
               &buffer->ataque,
               &buffer->peso,
               &buffer->altura,
               &buffer->habilidade,
               buffer->img);

        fwrite(buffer, sizeof(Cards), 1, arq_dat);
    } // enquanto houver linhas

    rewind(arq_dat);
    return;

} // salva o metagame no arquivo bin na primeira vez que você abre o jogo

int CountLines(FILE *arq_dat)
{

    int lines = 0;
    long int size;

    fseek(arq_dat, 0, SEEK_END);
    size = ftell(arq_dat);
    lines = size / sizeof(Cards); // verifica quantas cartas tem no arquivo bin

    rewind(arq_dat);

    return lines;
} // conta quantas linhas tem no arquivo csv (quantidade de cartas)

void InitCardsTextures(Cards card[], Backgrounds_cards *backgrounds_cards, Texture2D *pokemon_img, int totalCards) {
    // Carregar a textura de fundo da carta
    backgrounds_cards->card_background = LoadTexture(".\\assets\\cards\\img\\card_background.png");
   
    backgrounds_cards->ice_background = LoadTexture(".\\assets\\cards\\img\\ice_background.png");
    
    backgrounds_cards->dragon_background = LoadTexture(".\\assets\\cards\\img\\dragon_background.png");
    
    backgrounds_cards->fighting_background = LoadTexture(".\\assets\\cards\\img\\fighting_background.png");
    
    backgrounds_cards->pisych_background = LoadTexture(".\\assets\\cards\\img\\pisych_background.png");

    backgrounds_cards->cards_boards = LoadTexture(".\\assets\\cards\\img\\board_card.png");

    backgrounds_cards->super_trunfo_boards = LoadTexture(".\\assets\\cards\\img\\board_card_SP.png");

    // Carregar as imagens dos Pokémon uma vez
    for (int i = 0; i < totalCards; i++) {
        char PathPokemon_img[40]; // Caminho para a imagem do Pokémon
        sprintf(PathPokemon_img, ".\\assets\\cards\\img\\%s", card[i].img);
        pokemon_img[i] = LoadTexture(PathPokemon_img);
        if (pokemon_img[i].id == 0) {
            printf("Erro ao carregar a imagem do Pokémon %s!\n", card[i].img);
        }
    }
}

void CreatCards(Cards card[], Backgrounds_cards background_cards, Texture2D poke_img[], RenderTexture2D CardTexture[], int TOTAL_CARDS){
    
    for(int i =0; i < TOTAL_CARDS; i++){

        CardTexture[i] = LoadRenderTexture(110,180); // renderiza uma nova textura
        if (CardTexture[i].id == 0) {
            printf("Erro ao criar a render texture da carta!\n");
            return; // Retorna uma textura vazia em caso de erro
        }

        BeginTextureMode (CardTexture[i]);
        ClearBackground(DARKGRAY); // fundo da carta pintado

        if(card[i].tipo == 'G') DrawTexture(background_cards.ice_background,0,0,WHITE);
        if(card[i].tipo == 'D') DrawTexture(background_cards.dragon_background,0,0,WHITE);
        if(card[i].tipo == 'P') DrawTexture(background_cards.pisych_background,0,0,WHITE);
        if(card[i].tipo == 'L') DrawTexture(background_cards.fighting_background,0,0,WHITE);


        //DrawRectangle(5,85,100,90,LIGHTGRAY); // status
        //DrawRectangle(5,130,100,45,GRAY); // habilidade

        DrawTexture(background_cards.card_background, 5,20, WHITE); // fundo da carta
        
        DrawTextureEx(poke_img[i], (Vector2){10,22}, 0.0f, 0.9f, WHITE); // pokemon

        if(card[i].trunfo == 1){

            DrawTexture(background_cards.super_trunfo_boards,0,0,WHITE);
        }else DrawTexture(background_cards.cards_boards,0,0,WHITE);

        char cardText[200];
        
        snprintf(cardText, sizeof(cardText), "%c %s #%d", card[i].tipo, card[i].nome, card[i].numero);
        DrawText(cardText, 5, 5, 1, BLACK);

        snprintf(cardText, sizeof(cardText), "HP: %d", card[i].hp);
        DrawText(cardText, 8, 115, 6, BLACK);

        snprintf(cardText, sizeof(cardText), "ATK: %d", card[i].ataque);
        DrawText(cardText, 8, 130, 6, BLACK);

        snprintf(cardText, sizeof(cardText), "ALT: %.2f", card[i].altura);
        DrawText(cardText, 55, 115, 6, BLACK); 

        snprintf(cardText, sizeof(cardText), "PSO: %.2f", card[i].peso);
        DrawText(cardText, 55, 130, 6, BLACK);

        snprintf(cardText, sizeof(cardText), "Hab: %s", hability[card[i].habilidade].nome);
        DrawText(cardText, 8, 140, 10, BLACK);

        snprintf(cardText, sizeof(cardText), "%s", hability[card[i].habilidade].text);
        DrawText(cardText, 8, 150, 10, BLACK);

        EndTextureMode();
        // Retornar a textura renderizada da carta
    }
}
