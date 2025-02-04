void PlayBattleAnimation(Texture2D battle_hud, Texture2D battle_terrain_player1, 
                         Texture2D battle_terrain_player2, Texture2D battle_player1, 
                         Texture2D battle_player2, Texture2D battle_transition[], 
                         int *transitionFrame, float *animationTimer, float dt) {

    static float posPlayer1X = 800;  // Inicia fora da tela (direita)
    static float posPlayer2X = -210; // Inicia fora da tela (esquerda)
    static float posTerrain1X = 800; // Inicia fora da tela (direita)
    static float posTerrain2X = -341; // Inicia fora da tela (esquerda)

    const float SLIDE_SPEED = 10.0f;

    // Atualizar posições (deslizamento)
    if (posPlayer1X > 0) {
        posPlayer1X -= SLIDE_SPEED * dt * 60;
        posTerrain1X -= SLIDE_SPEED * dt * 60;
    }
    if (posPlayer2X < 525) {
        posPlayer2X += SLIDE_SPEED * dt * 60;
        posTerrain2X += SLIDE_SPEED * dt * 60;
    }

    // Atualizar animação de transição
    *animationTimer += dt;
    if (*animationTimer >= 0.1f) {
        (*transitionFrame)++;
        if (*transitionFrame >= 16) *transitionFrame = 15;
        *animationTimer = 0.0f;
    }

    // Desenhar terrenos deslizando
    DrawTexturePro(battle_terrain_player1, (Rectangle){0, 0, 521, 143}, 
                   (Rectangle){posTerrain1X, 290, 521, 143}, 
                   (Vector2){0, 0}, 0, WHITE);

    DrawTexturePro(battle_terrain_player2, (Rectangle){0, 0, 341, 110}, 
                   (Rectangle){posTerrain2X, 105, 341, 110}, 
                   (Vector2){0, 0}, 0, WHITE);

    // Desenhar players deslizando
    DrawTexturePro(battle_player1, (Rectangle){0, 0, 330, 330}, 
                   (Rectangle){posPlayer1X, 105, 330, 330}, 
                   (Vector2){0, 0}, 0, WHITE);

    DrawTexturePro(battle_player2, (Rectangle){0, 0, 210, 210}, 
                   (Rectangle){posPlayer2X, -25, 210, 210}, 
                   (Vector2){0, 0}, 0, WHITE);

    // Desenhar HUD de batalha
    DrawTexturePro(battle_hud, (Rectangle){0, 0, 800, 167}, 
                   (Rectangle){0, 432, 800, 167}, 
                   (Vector2){0, 0}, 0, WHITE);

    // Desenhar animação de transição
    DrawTexture(battle_transition[*transitionFrame], 0, 0, WHITE);
}
