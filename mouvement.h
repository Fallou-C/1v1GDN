#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <stdbool.h>
#include "mouvement.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _Joueur {
    int positionX;
    int positionY;
    bool sautable;
    int SAUT; // permet de savoir où on en est dans le saut
    int PV; // créer struct personnage où on met toutes les infos ou le nom et on regarde dans un dossier où y'a tous
    bool touchable;
    int cpt_invinsible; // valeurs avant laquelle on devient invincible à mettre à 0 
} Joueur ;

void Bouge(Joueur *joueur,bool colision); //gère le mouvement du joueur à gauche
void Bouge2(Joueur *joueur, bool colision); //gère le mouvement du joueur à droite

bool colision(Joueur *joueur1,Joueur *joueur2); // on se touche ouuu


#endif //MOUVEMENT_H