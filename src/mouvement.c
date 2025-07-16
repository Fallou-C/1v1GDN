// gère les mouvements des personnages

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../raylib/src/raylib.h"
#include "../header/all.h"



float delta=0.03;
int screen_size = 900;

void Bouge(Personnage *Personnage,bool colision,float camx)
{
    if (IsKeyDown(KEY_LEFT) && (Personnage->position.positionX> (camx)) && !IsKeyDown(KEY_RIGHT) && (!colision || Personnage->camp) )  
    {
        if(!Personnage->camp){Personnage->position.positionX -= PLAYER_HOR_SPD*delta;}else{Personnage->position.positionX -= PLAYER_HOR_SPD*delta*2/3;} // on regarde de quelle côté on est pour être plus lent si on recule
    }
    if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT) && (!colision || !Personnage->camp) && (Personnage->position.positionX <= (camx + screen_size - Personnage->position.largeur)) )
    {
        if(Personnage->camp){Personnage->position.positionX += PLAYER_HOR_SPD*delta;}else{Personnage->position.positionX += PLAYER_HOR_SPD*delta*2/3;}
    }
    if (IsKeyDown(KEY_UP) && (Personnage->position.sautable))
    {
        Personnage->position.sautable = false;
    }
    if (!Personnage->position.sautable) 
        {
            if (Personnage->position.durée_saut<40) {Personnage->position.positionY -= PLAYER_HOR_SPD*delta*1 ; Personnage->position.durée_saut++;}
            else if (Personnage->position.durée_saut<80 && Personnage->position.durée_saut>=40) {Personnage->position.positionY += PLAYER_HOR_SPD*delta ; Personnage->position.durée_saut++;}
            else 
            {
                Personnage->position.durée_saut=0;
                Personnage->position.sautable = true;
            }
        }
}

void Bouge2(Personnage *Personnage, bool colision,float camx)
{
    if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && (!colision || Personnage->camp) && (Personnage->position.positionX > (camx )))
    {
        if(!Personnage->camp){Personnage->position.positionX -= PLAYER_HOR_SPD*delta;}else{Personnage->position.positionX -= PLAYER_HOR_SPD*delta*2/3;}
    }
    if (IsKeyDown(KEY_D) && (Personnage->position.positionX <= (camx + screen_size - Personnage->position.largeur)) && !IsKeyDown(KEY_A) && (!colision || !Personnage->camp)) //pour pas sortir du terrain
    {
        if(Personnage->camp){Personnage->position.positionX += PLAYER_HOR_SPD*delta;}else{Personnage->position.positionX += PLAYER_HOR_SPD*delta*2/3;}
    }
    if (IsKeyDown(KEY_W) && Personnage->position.sautable)
    {
        Personnage->position.sautable = false;
    }
    if (!Personnage->position.sautable) 
        {
            if (Personnage->position.durée_saut<40) {Personnage->position.positionY -= PLAYER_HOR_SPD*delta*1 ; Personnage->position.durée_saut++;}
            else if (Personnage->position.durée_saut<80 && Personnage->position.durée_saut>=40) {Personnage->position.positionY += PLAYER_HOR_SPD*delta ; Personnage->position.durée_saut++;}
            else 
            {
                Personnage->position.durée_saut=0;
                Personnage->position.sautable = true;
            }
        }
}

bool colision(Personnage *Personnage1,Personnage *Personnage2) // en théorie un Personnage ne peut pas position.durée_sauter au dessus de l'autre 
{
    if (abs((Personnage2->position.positionX - Personnage1->position.positionX))<Personnage1->position.largeur) {return true;} //remplacer Personnage->position.largeurn par min epaisseur entre les deux personnages 
    else {return false;}
}

// ajouter inertie au position.durée_saut ?