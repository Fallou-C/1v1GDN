#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include <stdbool.h>
#include "mouvement.h"
#include "../../raylib/src/raylib.h"
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
    bool estGauche;
} Joueur ;

void Bouge(Personnage *joueur,bool colision,float camx); //gère le mouvement du joueur à gauche
void Bouge2(Personnage *joueur, bool colision,float camx); //gère le mouvement du joueur à droite

bool colision(Personnage *joueur1,Personnage *joueur2); // on se touche ouuu


#endif //MOUVEMENT_H