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

float position_camera(Personnage* j1,Personnage* j2)
{
    if( j1->position.positionX < j2->position.positionX )
    {
        return j1->position.positionX + abs(j1->position.positionX - j1->position.largeur - j2->position.positionX)/2 - screenWidth/2;
    }
    return j2->position.positionX + abs(j2->position.positionX - j1->position.largeur - j1->position.positionX)/2 - screenWidth/2;
}

void AffichageSprite(Personnage *j1, Personnage *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2) //amener à evoluer quand y'aura les sprites
{
    //affichage Personnage

    // a transformer en menu debug quand on aura un debut de sprite et remplacer les rectangles par DrawRectangleLines

    /*
    char* path = "test_sprite/test4.png";
    Texture2D testure = LoadTexture(path);
    Rectangle frameRec = { 190*externe, 0, 190, 270 }; // x y (coordonnée dans l'image) largeur longueur que l'on regarde dans l'image
    Vector2 position.position = {j1->position.positionX,j1->position.positionY };
    externe++;
    if(externe>2){externe=0;}*/

    Color tab_couleur[7] = {RED,ORANGE,YELLOW,GREEN,BLUE,DARKBLUE,PURPLE};


    DrawRectangle(j1->position.positionX,j1->position.positionY, j1->position.largeur, j1->position.taille, tab_couleur[j1->idPersonnage]); //Personnage 1
    DrawRectangle(j2->position.positionX,j2->position.positionY, j2->position.largeur, j2->position.taille, tab_couleur[j2->idPersonnage]); //Personnage2
    
    float camx = position_camera(j1,j2);

    if(camx >= -1145 && camx < 1145)
    {
        DrawRectangle(camx + 20,555, 300*(j1->PV)/j1->pv_max, 40, GREEN); //pv Personnage1 à généraliser -> ajouter les HP max pour aider pour ça et le reset formule : Hpmax <=> 300px
        DrawRectangleLines(camx + 20,555, 300, 40, BLACK); 
        DrawRectangle(camx + 580,555, 300*j2->PV/j1->pv_max, 40, GREEN); //pv Personnage2
        DrawRectangleLines(camx + 580,555, 300, 40, BLACK);
    }
    else if (camx < -1145)
    {
        DrawRectangle(-1145 + 20,555, 300*(j1->PV)/j1->pv_max, 40, GREEN); 
        DrawRectangleLines(-1145 + 20,555, 300, 40, BLACK); 
        DrawRectangle(-1145 + 580,555, 300*j2->PV/j1->pv_max, 40, GREEN);
        DrawRectangleLines(-1145 + 580,555, 300, 40, BLACK);
    }
    else
    {
        DrawRectangle(1145 + 20,555,300*(j1->PV)/j1->pv_max, 40, GREEN); 
        DrawRectangleLines(1145 + 20,555, 300, 40, BLACK); 
        DrawRectangle(1145 + 580,555, 300*j2->PV/j1->pv_max, 40, GREEN);
        DrawRectangleLines(1145 + 580,555, 300, 40, BLACK);
    }
    // généralsier pour que tous s'adapte en fonction de la taille de l'ecran choisi

    //affichage attaque

    //j1
    for (int i=0; i < nb_atk1; i++)
    {
        if (liste_atk1[i]->atk_distance ) // attaque à distance 
        {
            //if(liste_atk1[i]->executer){DrawRectangle(liste_atk1[i]->espace->positionX,liste_atk1[i]->espace->positionY,liste_atk1[i]->espace->taille,liste_atk1[i]->espace->largeur, YELLOW);}
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
            //if(liste_atk2[i]->executer ){DrawRectangle(liste_atk2[i]->espace->positionX,liste_atk2[i]->espace->positionY,liste_atk2[i]->espace->taille,liste_atk2[i]->espace->largeur, PINK);}
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

/*Attaque** InitialisationCombat() // renvoie une liste de pointeur attaque du Personnage après les avoir initialisés
{

}*/

void Reset_Combat(Personnage *j1, Personnage *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2,long int* CompteFps) // permet de tous reset rapidement en initalisent le combat par rapport à certains paramètre d'origine
{
    // initailisation fps
    *CompteFps = 0;

    // initiatlisation des Personnages
    j1->position.positionX = 50;
    j2->position.positionX = 660;
    j1->position.positionY = j2->position.positionY = 210;
    j1->position.sautable = j2->position.sautable = j2->touchable = true;
    j1->position.durée_saut = j2->position.durée_saut = 0;
    j1->PV = j2->PV = 100;
    j1->camp = 1;
    j2->camp = 0;

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

Positionnel Initialisaton_Position(int camp,int taille,int largueur) // renvoie une position.position initialisée en fonction du camp
{
    Positionnel position;
    if (camp == 1)
    {
        position.positionX = 50;
        position.positionY = 210;
    }
    else
    {
        position.positionX = 660;
        position.positionY = 210;
    }
    
    position.largeur = largueur;
    position.taille = taille;

    position.sautable = true;
    position.durée_saut = 0;

    position.vitesseX = 0;
    position.vitesseY = 0;
    position.accelerationX = 0;
    position.accelerationY = 0;
    position.vitesseXMax = 0; // vitesse max de déplacement
    position.vitesseXMin = 0;  // vitesse min de déplacement
    position.vitesseYMax = 0; // vitesse max de déplacement
    position.vitesseYMin = 0;  // vitesse min de déplacement
    position.accelerationXMax = 0; // accélération max
    position.accelerationXMin = 0;  // accélération min
    position.accelerationYMax = 0; // accélération max
    position.accelerationYMin = 0;  // accélération min
    position.positionXmax = 0; // position.position max en X
    position.positionYmax = 0;// position.position max en Y
    position.positionXmin = 0; // position.position min en X
    position.positionYmin = 0;// position.position min en Y
    // Initialisation des position.positions min et max
    
    return position;
}

Frame Initialisation_Frame(void)
{
    Frame frame;
    frame.recoveryFrame = 0;
    frame.atkFrame = 0;
    frame.stunFrame = 0;
    frame.idleFrame = 0;
    frame.offensiveLagFrame = 0;
    frame.defensiveLagFrame = 0;
    return frame;
}

Attaques Initialisation_Attaques(void)
{
    Attaques attaques = {0};
    // Toutes les valeurs sont initialisées à zéro ou NULL grâce à l'initialisation = {0}
    return attaques;
}

EnsembleCollectionRectangle Initialisation_Rectangle(void)
{
    EnsembleCollectionRectangle ensemble = {
        .nombreFrame = 0,
        .ensemble = NULL
    };
    return ensemble;
}

Personnage Initialisaton_Personnage(int camp, int id, int taille, int largueur) // renvoie un personnage initialisé à amélliorer pour mettre une structure quand on aura avancé plus
{
    Personnage personnage = {
        .idPersonnage = id,
        .sousPersonnage = NULL,
        .etat = 0,
        .camp = camp,
        .touchable = true,
        .PV = 100,
        .pv_max = 100,
        .status = 0,
        .position = Initialisaton_Position(camp,taille,largueur),
        .frame = Initialisation_Frame(),
        .attaques = Initialisation_Attaques(),
        .hurtBox = Initialisation_Rectangle()
    };
    return personnage;
}

void AnimationSprite(Animation* anime,Texture2D texture, Attaque* atk,long int CompteFps)
{
    if(anime->cmpt_frame >= anime->nb_frame ){anime->cmpt_frame = 0;} 
    if (anime->memo_fps <= CompteFps) {
        anime->cmpt_frame ++;
        anime->memo_fps = CompteFps + 20;} // la constante c'est la vitesse
    if(atk->executer || (atk->lag.Encours && !atk->atk_distance)){test_affichage(texture,atk->espace->positionX,atk->espace->positionY,anime->largeur*anime->cmpt_frame,anime->longueur,anime->largeur,anime->longueur);}
}