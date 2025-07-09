// gère les mouvements des personnages

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../raylib/src/raylib.h"
#include "../header/all.h"

#define PLAYER_HOR_SPD 200.0f

float delta=0.03;
//float min_X = -1140;
//float max_X = 1826;

int screen_size = 900;

void Bouge(Joueur *joueur,bool colision,float camx)
{
    if (IsKeyDown(KEY_LEFT) && (joueur->positionX> (camx)) && !IsKeyDown(KEY_RIGHT) && (!colision || joueur->estGauche) )  
    {
        if(!joueur->estGauche){joueur->positionX -= PLAYER_HOR_SPD*delta;}else{joueur->positionX -= PLAYER_HOR_SPD*delta*2/3;} // on regarde de quelle côté on est pour être plus lent si on recule
    }
    if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && (!colision || !joueur->estGauche) && (joueur->positionX <= (camx + screen_size - 190)) ) // ajouter l'epaisseur du joueur (190)
    {
        if(joueur->estGauche){joueur->positionX += PLAYER_HOR_SPD*delta;}else{joueur->positionX += PLAYER_HOR_SPD*delta*2/3;}
    }
    if (IsKeyDown(KEY_UP) && (joueur->sautable))
    {
        joueur->sautable = false;
    }
    if (!joueur->sautable) 
        {
            if (joueur->SAUT<40) {joueur->positionY -= PLAYER_HOR_SPD*delta*1 ; joueur->SAUT++;}
            else if (joueur->SAUT<80 && joueur->SAUT>=40) {joueur->positionY += PLAYER_HOR_SPD*delta ; joueur->SAUT++;}
            else 
            {
                joueur->SAUT=0;
                joueur->sautable = true;
            }
        }
}

void Bouge2(Joueur *joueur, bool colision,float camx)
{
    if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && (!colision || joueur->estGauche) && (joueur->positionX > (camx )))
    {
        if(!joueur->estGauche){joueur->positionX -= PLAYER_HOR_SPD*delta;}else{joueur->positionX -= PLAYER_HOR_SPD*delta*2/3;}
    }
    if (IsKeyDown(KEY_D) && (joueur->positionX <= (camx + screen_size - 190)) && !IsKeyDown(KEY_A) && (!colision || !joueur->estGauche)) //pour pas sortir du terrain
    {
        if(joueur->estGauche){joueur->positionX += PLAYER_HOR_SPD*delta;}else{joueur->positionX += PLAYER_HOR_SPD*delta*2/3;}
    }
    if (IsKeyDown(KEY_W) && joueur->sautable)
    {
        joueur->sautable = false;
    }
    if (!joueur->sautable) 
        {
            if (joueur->SAUT<40) {joueur->positionY -= PLAYER_HOR_SPD*delta*1 ; joueur->SAUT++;}
            else if (joueur->SAUT<80 && joueur->SAUT>=40) {joueur->positionY += PLAYER_HOR_SPD*delta ; joueur->SAUT++;}
            else 
            {
                joueur->SAUT=0;
                joueur->sautable = true;
            }
        }
}

bool colision(Joueur *joueur1,Joueur *joueur2) // en théorie un joueur ne peut pas sauter au dessus de l'autre 
{
    if (abs((joueur2->positionX - joueur1->positionX))<190) {return true;} //remplacer 190n par min epaisseur entre les deux personnages 
    else {return false;}
}

// ajouter inertie au saut ?