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
    int SAUT;
    int PV;
    bool touchable;
} Joueur ;

void Bouge(Joueur *joueur,bool colision); //gère le mouvement du joueur à gauche
void Bouge2(Joueur *joueur, bool colision); //gère le mouvement du joueur à droite

bool colision(Joueur *joueur1,Joueur *joueur2);

void AfficheMenu(int screenWidth, int screenHeight); // flemme de le laisser seul

#endif //MOUVEMENT_H