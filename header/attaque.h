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


bool AtkToucheY(Personnage *j,Attaque *atk1, Attaque *atk2); // renvoie si un personnage se fait toucher par atk1 en Y ou si atk1 touche atk2 en Y si personnage null

void ColisionAtk(Personnage *personnage, Attaque *attaque); //colision entre personnage et attaque
void ColisionAtk2(Personnage *personnage, Attaque *attaque); //colision entre personnage et attaque (pour j2)

void HitLagTemps(Attaque *attaque,long int fpstour,int DureeLag); //gère le temps de lag

void ExecuteAttaque(Personnage *personnage,Attaque *attaque,bool IsKeyDown); // on exécute l'attaque de Key sur le personnage
void ExecuteAttaque2(Personnage *personnage,Attaque *attaque,bool IsKeyDown); // on exécute l'attaque de Key sur le personnage2

void AttaqueDistance(Personnage *personnage1, Personnage *personnage2, Attaque *attaque, bool IsKeyDown); //attaque à distance de j1 sur j2
void AttaqueDistance2(Personnage *personnage1, Personnage *personnage2, Attaque *attaque, bool IsKeyDown); //attaque à distance de j2 sur j1

void MiseAJourAtk(Personnage *personnage, Attaque **liste_atk /*liste de pointeur d'attaque*/, int nb_atk, int CompteFps); // on prend une liste d'attaque d'un personnage et on met à jour leurs positions 

// init attaque avec une liste du format : [degat,posX,posY,taille,largeur,pos-relatif,durrelag]
void Iniatk(Attaque *atk, int* info_atk); // initialise une attaque en fonction des valeurs données

void DestructionProjectile(Attaque *attaque ,Attaque **liste_atk,int nb_atk, bool estj2); // fonctionne partiellement 

void Grab(Personnage *j1, Personnage *j2); // échange les positions des personnages et infligents des degs (bientôt)

#endif //ATTACK_H