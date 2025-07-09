// fichier contenant tous les fonctions aucun rapport avec le système de combat (menu et debug)

#include <stdbool.h>
#include "../header/all.h"
#include "../../raylib/src/raylib.h"
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

int externe = 0;
int screenWidth = 900;

float position_camera(Joueur* j1,Joueur* j2)
{
    if( j1->positionX < j2->positionX )
    {
        return j1->positionX + abs(j1->positionX -190 - j2->positionX)/2 - screenWidth/2;
    }
    return j2->positionX + abs(j2->positionX - 190 - j1->positionX)/2 - screenWidth/2;
}

void AffichageSprite(Joueur *j1, Joueur *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2) //amener à evoluer quand y'aura les sprites
{
    //affichage joueur

    // a transformer en menu debug quand on aura un debut de sprite et remplacer les rectangles par DrawRectangleLines

    /*
    char* path = "test_sprite/test4.png";
    Texture2D testure = LoadTexture(path);
    Rectangle frameRec = { 190*externe, 0, 190, 270 }; // x y (coordonnée dans l'image) largeur longueur que l'on regarde dans l'image
    Vector2 position = {j1->positionX,j1->positionY };
    externe++;
    if(externe>2){externe=0;}*/

    DrawRectangle(j1->positionX,j1->positionY, 190.0f, 270.0f, RED); //joueur 1
    //DrawTextureRec(testure, frameRec, position, WHITE);

    DrawRectangle(j2->positionX,j2->positionY, 190.0f, 270.0f, BLUE); //joueur2
    
    float camx = position_camera(j1,j2);

    if(camx >= -1145 && camx < 1145)
    {
        DrawRectangle(camx + 20,555, 3*(j1->PV), 40, GREEN); //pv joueur1 à généraliser -> ajouter les HP max pour aider pour ça et le reset formule : Hpmax <=> 300px
        DrawRectangle(camx + 580,555, 3*j2->PV, 40, GREEN); //pv joueur2
    }
    else if (camx < -1145)
    {
        DrawRectangle(-1145 + 20,555, 3*(j1->PV), 40, GREEN); 
        DrawRectangle(-1145 + 580,555, 3*j2->PV, 40, GREEN);
    }
    else
    {
        DrawRectangle(1145 + 20,555, 3*(j1->PV), 40, GREEN); 
        DrawRectangle(1145 + 580,555, 3*j2->PV, 40, GREEN);
    }
    // généralsier pour que tous s'adapte en fonction de la taille de l'ecran choisi

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

Texture2D* Load_texture(char** path_texture,int nb_elem) // renvoie un tableau de texture provenant du tableau de chemin fourit (dans le même ordre)
{
    Texture2D* tab_texture = (Texture2D*) malloc(nb_elem*sizeof(Texture2D));

    for(int i = 0; i < nb_elem ; i++)
    {
        tab_texture[i] = LoadTexture(path_texture[i]);
    }

    return tab_texture;
}

void Unload_texture(Texture2D* tab_texture, int nb_elem)
{
    for(int i = 0; i < nb_elem ; i++)
    {
        UnloadTexture(tab_texture[i]);
    }   
}

void MenuDebug()
{
    // mettre les fonctions d'affichage de hitbox, info sur les personnages et boutton de reset rapide
}

Attaque** InitialisationCombat() // renvoie une liste de pointeur attaque du joueur après les avoir initialisés
{

}

void Reset_Combat(Joueur *j1, Joueur *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2,long int* CompteFps) // permet de tous reset rapidement en initalisent le combat par rapport à certains paramètre d'origine
{
    // initailisation fps
    *CompteFps = 0;

    // initiatlisation des joueurs
    j1->positionX = 50;
    j2->positionX = 660;
    j1->positionY = j2->positionY = 210;
    j1->sautable = j2->sautable = j2->touchable = true;
    j1->SAUT = j2->SAUT = 0;
    j1->PV = j2->PV = 100;
    j1->estGauche = true;
    j2->estGauche = false;

    // re-initialisation des attaques

    //j1
    for (int i=0; i < nb_atk1; i++)
    {
        liste_atk1[i]->executer = false;
        liste_atk1[i]->lag.Encours = false;
        liste_atk1[i]->lag.MemoFps = 0;
        liste_atk1[i]->lag.SaLag = 0;
    }

    //j2
    for (int i=0; i < nb_atk2; i++)
    {
        liste_atk2[i]->executer = false;
        liste_atk2[i]->lag.Encours = false;
        liste_atk2[i]->lag.MemoFps = 0;
        liste_atk2[i]->lag.SaLag = 0;
    }
}

//faire une fonction pour l'animation avec en argument le (dossiers de sprite ou tableau des noms des sprites) et un tableau qui prend le nombre de frame entre chaque sprite
void test_affichage(Texture2D testure, int x , int y, int x_sprite, int y_sprite, int largeur , int longueur)
{
    Rectangle frameRec = { x_sprite, y_sprite, largeur, longueur }; // x y largeur longueur 
    Vector2 position = { x, y };
    DrawTextureRec(testure, frameRec, position, WHITE);
}
