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

void AffichageSprite(Joueur *j1, Joueur *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2)
{
    //affichage joueur

    DrawRectangle(j1->positionX,j1->positionY, 190.0f, 270.0f, RED); //joueur 1
    DrawRectangle(j2->positionX,j2->positionY, 190.0f, 270.0f, BLUE); //joueur2
    
    DrawRectangle(20,555, 3*j1->PV, 40, GREEN); //pv joueur1
    DrawRectangle(580,555, 3*j2->PV, 40, GREEN); //pv joueur2

    //affichage attaque

    //j1
    for (int i=0; i < nb_atk1; i++)
    {
        if (liste_atk1[i]->atk_distance ) // attaque à distance 
        {
            if(liste_atk1[i]->executer){DrawRectangle(liste_atk1[i]->espace->positionX,liste_atk1[i]->espace->positionY,liste_atk1[i]->espace->taille,liste_atk1[i]->espace->largeur, YELLOW);}
        }
        else {
            if (liste_atk1[i]->lag.Encours){DrawRectangle(liste_atk1[i]->espace->positionX,liste_atk1[i]->espace->positionY,liste_atk1[i]->espace->taille,liste_atk1[i]->espace->largeur, ORANGE);}
        }
    }

    //j2
    for (int i=0; i < nb_atk2; i++)
    {
        if (liste_atk2[i]->atk_distance)// attaque à distance 
        {
            if(liste_atk2[i]->executer ){DrawRectangle(liste_atk2[i]->espace->positionX,liste_atk2[i]->espace->positionY,liste_atk2[i]->espace->taille,liste_atk2[i]->espace->largeur, PINK);}
        }
        else {
            if (liste_atk2[i]->lag.Encours){DrawRectangle(liste_atk2[i]->espace->positionX,liste_atk2[i]->espace->positionY,liste_atk2[i]->espace->taille,liste_atk2[i]->espace->largeur, PURPLE);}
        }
    }
    
}

void MenuDebug()
{
    // mettre les fonctions d'affichage de hitbox, info sur les personnages et boutton de reset rapide
}

void InitialisationCombat()
{
    // permet de tous reset rapidement en initalisent le combat par rapport à certains paramètre d'origine
}