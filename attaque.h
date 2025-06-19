#ifndef ATTACK_H
#define ATTACK_H

#include <stdbool.h>
#include "mouvement.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

//atk
typedef struct HitLag_ {
    bool Encours;
    int MemoFps; //on regarde quand l'attaque a été lancé
    int SaLag; // prend en compte le début et la fin du lag
} HitLag;

typedef struct Attaque_ {
    int positionX;
    int positionY;
    int degat;
    int taille; //par défaut la taille et mesure sur l'axe x
    HitLag lag;
    int largeur;// same que taille mais en y
    bool executer; // surtout pour les attaques à distances, pour savoir si elles sont activées
} Attaque;

void ColisionAtk(Joueur *joueur, Attaque *attaque); //colision pour joueur 1
void ColisionAtk2(Joueur *joueur, Attaque *attaque); //colision pour joueur 2   

void HitLagTemps(Attaque *attaque,long int fpstour,int DureeLag); //gère le temps de lag

void ExecuteAttaque(Joueur *joueur2,Attaque *attaque,bool IsKeyDown); // on exécute l'attaque de Key sur le joueur
void ExecuteAttaque2(Joueur *joueur2,Attaque *attaque,bool IsKeyDown); // on exécute l'attaque de Key sur le joueur mais pour j2

void AttaqueDistance(Joueur *joueur1, Joueur *joueur2, Attaque *attaque, bool IsKeyDown); //attaque à distance pour joueur 1
void AttaqueDistance2(Joueur *joueur1, Joueur *joueur2, Attaque *attaque, bool IsKeyDown); //attaque à distance pour joueur 2



#endif //ATTACK_H