#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"
#include "mouvement.h"

#define PLAYER_HOR_SPD 200.0f

float delta=0.03;

void Bouge(Joueur *joueur,bool colision)
{
    if (IsKeyDown(KEY_LEFT) && (joueur->positionX>0))  
    {
        joueur->positionX -= PLAYER_HOR_SPD*delta*2/3;
    }
    if (IsKeyDown(KEY_RIGHT) && !colision)
    {
        joueur->positionX += PLAYER_HOR_SPD*delta;
    }
    if (IsKeyDown(KEY_UP) && (joueur->sautable))
    {
        joueur->sautable = false;
    }
    if (!joueur->sautable) 
        {
            if (joueur->SAUT<40) {joueur->positionY -= PLAYER_HOR_SPD*delta*1 ; joueur->SAUT++;}
            else if (joueur->SAUT<80 && joueur->SAUT>=40) {joueur->positionY += PLAYER_HOR_SPD*delta ; joueur->SAUT++;}
            else 
            {
                joueur->SAUT=0;
                joueur->sautable = true;
            }
        }
}

void Bouge2(Joueur *joueur, bool colision)
{
    if (IsKeyDown(KEY_A) && !colision)
    {
        joueur->positionX -= PLAYER_HOR_SPD*delta;
    }
    if (IsKeyDown(KEY_D) && (joueur->positionX <= 900-190)) //pour pas sortir du terrain
    {
        joueur->positionX += PLAYER_HOR_SPD*delta*2/3;
    }
    if (IsKeyDown(KEY_W) && joueur->sautable)
    {
        joueur->sautable = false;
    }
    if (!joueur->sautable) 
        {
            if (joueur->SAUT<40) {joueur->positionY -= PLAYER_HOR_SPD*delta*1 ; joueur->SAUT++;}
            else if (joueur->SAUT<80 && joueur->SAUT>=40) {joueur->positionY += PLAYER_HOR_SPD*delta ; joueur->SAUT++;}
            else 
            {
                joueur->SAUT=0;
                joueur->sautable = true;
            }
        }
}

bool colision(Joueur *joueur1,Joueur *joueur2) // en théorie un joueur ne peut pas sauter au dessus de l'autre 
{
    if (abs((joueur2->positionX - joueur1->positionX))<190) {return true;}
    else {return false;}
}

void AfficheMenu(int screenWidth, int screenHeight)
{
    Image fondMenu = LoadImage("logoC.png");
    Texture2D textureMenu = LoadTextureFromImage(fondMenu);
    Music musicMenu = LoadMusicStream("Evoland 2 OST - Track 38 (Fighting Magus).mp3");
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
