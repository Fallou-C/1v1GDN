#ifndef ATTACK_H
#define ATTACK_H

#include <stdbool.h>
#include "mouvement.h"
#include <stdlib.h>
#include <stdio.h>

//atk
typedef struct HitLag_ {
    bool Encours;
    int MemoFps; //on regarde quand l'attaque a été lancé
    int SaLag; // prend en compte le début et la fin du lag
    int DureeLag;
} HitLag;

typedef struct Espace_ {
    int positionX;
    int positionY;
    int taille; //par défaut la taille et mesure sur l'axe x
    int largeur; // same que taille mais en y
    int pos_relatif;
} Espace;

typedef struct Attaque_ {
    int degat;
    Espace *espace;
    HitLag lag;
    bool executer; // surtout pour les attaques à distances, pour savoir si elles sont activées
    bool atk_distance;
} Attaque;


bool AtkToucheY(Joueur *j,Attaque *atk1, Attaque *atk2); // renvoie si un joueur se fait toucher par atk1 en Y ou si atk1 touche atk2 en Y si joueur null

void ColisionAtk(Joueur *joueur, Attaque *attaque); //colision entre joueur et attaque

void HitLagTemps(Attaque *attaque,long int fpstour,int DureeLag); //gère le temps de lag

void ExecuteAttaque(Joueur *joueur2,Attaque *attaque,bool IsKeyDown); // on exécute l'attaque de Key sur le joueur

void AttaqueDistance(Joueur *joueur1, Joueur *joueur2, Attaque *attaque, bool IsKeyDown); //attaque à distance de j1 sur j2

void MiseAJourAtk(Joueur *joueur, Attaque **liste_atk /*liste de pointeur d'attaque*/, int nb_atk, int CompteFps); // on prend une liste d'attaque d'un joueur et on met à jour leurs positions 

// init attaque avec une liste du format : [degat,posX,posY,taille,largeur,pos-relatif,durrelag]
void Iniatk(Attaque *atk, int* info_atk); // initialise une attaque en fonction des valeurs données

void DestructionProjectile(Attaque *attaque ,Attaque **liste_atk,int nb_atk, bool estj2); // fonctionne partiellement 

void Grab(Joueur *j1, Joueur *j2); // échange les positions des joueurs et infligents des degs (bientôt)

#endif //ATTACK_H