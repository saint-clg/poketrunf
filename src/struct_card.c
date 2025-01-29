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

void DrawWrappedText(   Font font, const char *text, int posX, int posY, int fontSize, int maxWidth, int lineSpacing, 
                        Color color){
    int length = strlen(text);
    char buffer[256]; // Buffer temporário para armazenar a linha
    int lineStart = 0;
    int bufferIndex = 0;
    int currentX = posX;
    int currentY = posY;

    for (int i = 0; i <= length; i++) {
        buffer[bufferIndex] = text[i];

        // Quebra a linha se atingir a largura máxima ou encontrar uma quebra de linha manual
        if (MeasureTextEx(font, buffer, fontSize, 1).x > maxWidth || text[i] == '\n' || text[i] == '\0') {
            buffer[bufferIndex] = '\0'; // Finaliza a linha

            DrawTextEx(font, buffer, (Vector2){ currentX, currentY }, fontSize, 1, color);

            currentY += fontSize + lineSpacing; // Avança para a próxima linha
            bufferIndex = 0; // Reinicia o buffer para a próxima linha

            if (text[i] == ' ') {
                lineStart = i + 1; // Pula o espaço
            }
        } else {
            bufferIndex++;
        }
    }
}

void CreatCards(Cards card[], Backgrounds_cards background_cards, Texture2D poke_img[], RenderTexture2D CardTexture[], 
                Font poke_font, int TOTAL_CARDS){
    
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
        DrawTextEx(poke_font,cardText,(Vector2){6,6},11,0.2,BLACK);

        snprintf(cardText, sizeof(cardText), "HP: %d", card[i].hp);
        DrawTextEx(poke_font,cardText,(Vector2){8,115},11,0.2,BLACK);

        snprintf(cardText, sizeof(cardText), "ATK: %d", card[i].ataque);
        DrawTextEx(poke_font,cardText,(Vector2){8,130},11,0.2,BLACK);

        snprintf(cardText, sizeof(cardText), "ALT: %.2f", card[i].altura);
        DrawTextEx(poke_font,cardText,(Vector2){53,115},11,0.2,BLACK);

        snprintf(cardText, sizeof(cardText), "PSO: %.2f", card[i].peso);
        DrawTextEx(poke_font,cardText,(Vector2){53,130},11,0.2,BLACK);

        snprintf(cardText, sizeof(cardText), "Hab: %s", hability[card[i].habilidade].nome);
        DrawTextEx(poke_font,cardText,(Vector2){8,140},11,0.2,BLACK);

        snprintf(cardText, sizeof(cardText), "%s", hability[card[i].habilidade].text);
        DrawWrappedText(poke_font,cardText,8,145,10,100,1,BLACK);

        EndTextureMode();
        // Retornar a textura renderizada da carta
    }
}
