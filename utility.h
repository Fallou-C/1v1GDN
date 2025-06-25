#ifndef UTILITY_H
#define UTILITY_H

#include "mouvement.h"
#include "raylib.h"
#include "attaque.h"
#include <stdlib.h>
#include <stdio.h>

void AfficheAcceuil(int screenWidth, int screenHeight); // affiche l'ecran d'accueil

void AffichageSprite(Joueur *j1, Joueur *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2); // affiche les sprites (que les hitbox pour le moment)

void Reset_Combat(Joueur *j1, Joueur *j2,  Attaque **liste_atk1, int nb_atk1,Attaque **liste_atk2, int nb_atk2,long int* CompteFps); // permet de tous reset rapidement en initalisent le combat par rapport à certains paramètre d'origine


#endif // UTILITY_H