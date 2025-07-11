#ifndef UTILITY_H
#define UTILITY_H

#include "mouvement.h"
#include "../../raylib/src/raylib.h"
#include "attaque.h"
#include <stdlib.h>
#include <stdio.h>

void AfficheAcceuil(int screenWidth, int screenHeight); // affiche l'ecran d'accueil

float position_camera(Personnage* j1,Personnage* j2); // renvoie la position en x de la caméra 

void AffichageSprite(Personnage *j1, Personnage *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2); // affiche les sprites (que les hitbox pour le moment)

void Reset_Combat(Personnage *j1, Personnage *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2,long int* CompteFps); // permet de tous reset rapidement en initalisent le combat par rapport à certains paramètre d'origine

Texture2D* Load_texture(char** path_texture,int nb_elem); // renvoie un tableau de texture provenant du tableau de chemin fourit (dans le même ordre)

void test_affichage(Texture2D testure, int x , int y, int x_sprite, int y_sprite, int largeur , int longueur) ; // censé être du test mais en vrai sert de fou à afficher les sprites

void Unload_texture(Texture2D* tab_texture, int nb_elem); // on décharge tous par politesse

Personnage Initialisaton_Personnage(int camp, int id, int taille, int largueur); // renvoie un personnage initialisé

#endif // UTILITY_H