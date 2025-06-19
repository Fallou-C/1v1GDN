// fichier contenant tous les fonctions aucun rapport avec le système de combat (menu et debug)

#include <stdbool.h>
#include "mouvement.h"
#include "raylib.h"
#include "attaque.h"
#include <stdlib.h>
#include <stdio.h>


void AfficheAcceuil(int screenWidth, int screenHeight)
{
    Image fondMenu = LoadImage("fond/logoC.png");
    Texture2D textureMenu = LoadTextureFromImage(fondMenu);
    Music musicMenu = LoadMusicStream("music/Evoland 2 OST - Track 38 (Fighting Magus).mp3");
    PlayMusicStream(musicMenu);
    while(!IsKeyDown(KEY_ENTER) & !WindowShouldClose())
    {
        UpdateMusicStream(musicMenu);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(textureMenu, screenWidth/2 - textureMenu.width/2, screenHeight/2 - textureMenu.height/2 +100, WHITE);
        EndDrawing();
    }
    UnloadImage(fondMenu);
    UnloadMusicStream(musicMenu);
}

void MenuDebug()
{
    // mettre les fonctions d'affichage de hitbox, info sur les personnages et boutton de reset rapide
}

void InitialisationCombat()
{
    // permet de tous reset rapidement en initalisent le combat par rapport à certains paramètre d'origine
}