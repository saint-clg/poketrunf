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

void InitCardsTextures(Cards card[], Backgrounds_cards *backgrounds_cards, Texture2D *pokemon_img, int totalCards)
{
    // Carregar a textura de fundo da carta
    backgrounds_cards->card_background = LoadTexture(".\\assets\\cards\\img\\card_background.png");

    backgrounds_cards->ice_background = LoadTexture(".\\assets\\cards\\img\\ice_background.png");

    backgrounds_cards->dragon_background = LoadTexture(".\\assets\\cards\\img\\dragon_background.png");

    backgrounds_cards->fighting_background = LoadTexture(".\\assets\\cards\\img\\fighting_background.png");

    backgrounds_cards->pisych_background = LoadTexture(".\\assets\\cards\\img\\pisych_background.png");

    backgrounds_cards->cards_boards = LoadTexture(".\\assets\\cards\\img\\board_card.png");

    backgrounds_cards->super_trunfo_boards = LoadTexture(".\\assets\\cards\\img\\board_card_SP.png");

    // Carregar as imagens dos Pokémon uma vez
    for (int i = 0; i < totalCards; i++)
    {
        char PathPokemon_img[40]; // Caminho para a imagem do Pokémon
        sprintf(PathPokemon_img, ".\\assets\\cards\\img\\%s", card[i].img);
        pokemon_img[i] = LoadTexture(PathPokemon_img);
        if (pokemon_img[i].id == 0)
        {
            printf("Erro ao carregar a imagem do Pokémon %s!\n", card[i].img);
        }
    }
}

static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing,
                                    bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint,
                                    Color selectBackTint)
{
    int length = TextLength(text); // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;    // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f; // Offset X to next character to draw

    float scaleFactor = fontSize / (float)font.baseSize; // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum
    {
        MEASURE_STATE = 0,
        DRAW_STATE = 1
    };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1; // Index where to begin drawing (where a line begins)
    int endLine = -1;   // Index where to stop drawing (where a line ends)
    int lastk = -1;     // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f)
            codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width * scaleFactor : font.glyphs[index].advanceX * scaleFactor;

            if (i + 1 < length)
                glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n'))
                endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine)
                    endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine)
                    endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n')
                state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize * scaleFactor) > rec.height)
                    break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    DrawRectangleRec((Rectangle){rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize * scaleFactor}, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, (Vector2){rec.x + textOffsetX, rec.y + textOffsetY}, fontSize, isGlyphSelected ? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += font.baseSize * scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' '))
            textOffsetX += glyphWidth; // avoid leading spaces
    }
}

static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

void CreatCards(Cards card[], Backgrounds_cards background_cards, Texture2D poke_img[], RenderTexture2D CardTexture[],
                Font poke_font, int TOTAL_CARDS)
{

    for (int i = 0; i < TOTAL_CARDS; i++)
    {

        CardTexture[i] = LoadRenderTexture(220, 360); // renderiza uma nova textura
        if (CardTexture[i].id == 0)
        {
            printf("Erro ao criar a render texture da carta!\n");
            return; // Retorna uma textura vazia em caso de erro
        }

        BeginTextureMode(CardTexture[i]);
        ClearBackground(DARKGRAY); // fundo da carta pintado

        if (card[i].tipo == 'G')
            DrawTexture(background_cards.ice_background, 0, 0, WHITE);
        if (card[i].tipo == 'D')
            DrawTexture(background_cards.dragon_background, 0, 0, WHITE);
        if (card[i].tipo == 'P')
            DrawTexture(background_cards.pisych_background, 0, 0, WHITE);
        if (card[i].tipo == 'L')
            DrawTexture(background_cards.fighting_background, 0, 0, WHITE);

        // DrawRectangle(5,85,100,90,LIGHTGRAY); // status
        // DrawRectangle(5,130,100,45,GRAY); // habilidade

        DrawTexture(background_cards.card_background, 11, 41, WHITE); // fundo da carta

        DrawTextureEx(poke_img[i], (Vector2){25, 55}, 0.0f, 1.8f, WHITE); // pokemon

        if (card[i].trunfo == 1)
        {

            DrawTexture(background_cards.super_trunfo_boards, 0, 0, WHITE);
        }
        else
            DrawTexture(background_cards.cards_boards, 0, 0, WHITE);

        char cardText[200];

        snprintf(cardText, sizeof(cardText), "%c %s #%d", card[i].tipo, card[i].nome, card[i].numero);
        DrawTextEx(poke_font, cardText, (Vector2){13, 12}, 18, 0.2, BLACK);

        snprintf(cardText, sizeof(cardText), "ATK: %d", card[i].ataque);
        DrawTextEx(poke_font, cardText, (Vector2){11, 230}, 15, 0.2, BLACK);

        snprintf(cardText, sizeof(cardText), "HP: %d", card[i].hp);
        DrawTextEx(poke_font, cardText, (Vector2){11, 245}, 15, 0.2, BLACK);

        snprintf(cardText, sizeof(cardText), "ALT: %.2f", card[i].altura);
        DrawTextEx(poke_font, cardText, (Vector2){120, 230}, 15, 0.2, BLACK);

        snprintf(cardText, sizeof(cardText), "PSO: %.2f", card[i].peso);
        DrawTextEx(poke_font, cardText, (Vector2){120, 245}, 15, 0.2, BLACK);

        snprintf(cardText, sizeof(cardText), "Hab: %s", hability[card[i].habilidade].nome);
        DrawTextEx(poke_font, cardText, (Vector2){7, 265}, 15, 0.1, BLACK);

        DrawTextBoxed(poke_font, cardText, (Rectangle){7, 280, 205, 80}, 14, 0, true, BLACK);

        EndTextureMode();
        // Retornar a textura renderizada da carta
    }
}
