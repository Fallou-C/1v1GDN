#include "attaque.h"
#include "mouvement.h"
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"


void ColisionAtk(Joueur *joueur, Attaque *attaque)
{
    if ( abs(joueur->positionX - attaque->positionX ) <= attaque->taille) // on prend la position du joueur par rapport à x 
    {
        if(abs(joueur->positionY - attaque->positionY <= attaque->largeur)& !IsKeyDown(KEY_D)) //on regarde si l'attaque a pas été lancé trop haut
        {joueur->PV -= attaque->degat;}
    }
}

void ColisionAtk2(Joueur *joueur, Attaque *attaque)
{
    if ( abs(joueur->positionX - attaque->positionX ) <= 190) // on prend la position du joueur par rapport à x avec largeur du joueur (important si attaque joueur à gauche)
    {
        if(abs(joueur->positionY - attaque->positionY <= attaque->largeur) & !IsKeyDown(KEY_LEFT))
        {joueur->PV -= attaque->degat;}
    }
}

void HitLagTemps(Attaque *attaque,long int fpstour,int DureeLag) 
{
    if (attaque->lag.Encours)
    {
        if (attaque->lag.SaLag==0)
        {
            attaque->lag.MemoFps= fpstour + DureeLag;
            attaque->lag.SaLag++;
        }
        if ( attaque->lag.MemoFps==fpstour)
        {
            attaque->lag.Encours=false;
            attaque->lag.SaLag=0;
            attaque->lag.MemoFps=0;
        }
    }
}

void ExecuteAttaque(Joueur *joueur1, Joueur *joueur2,Attaque *attaque,bool IsKeyDown) // attaquant attaqué attaque touche
{
    if (IsKeyDown & !attaque->lag.Encours)
    {
        if (!(attaque->lag.Encours))
        {
            attaque->lag.Encours = true;
            ColisionAtk(joueur2,attaque);
        }
    }
}

void ExecuteAttaque2(Joueur *joueur1, Joueur *joueur2,Attaque *attaque,bool IsKeyDown) // attaquant attaqué attaque touche mais on utilise colision2
{
    if (IsKeyDown & !attaque->lag.Encours)
    {
        if (!(attaque->lag.Encours))
        {
            attaque->lag.Encours = true;
            ColisionAtk2(joueur2,attaque);
        }
    }
}


// bug chelou sur les attaques à distances qui se lance sur l'ancienne emplacement du joueur (à garder en feature ptdr)
// + des fois veut pas se lancer
// faire en sorte quelles se détruisent mutuellement 

void AttaqueDistance(Joueur *j1,Joueur *j2,Attaque *attaque,bool Key) //attaque lancé part la joueur 1
{
    if (Key || attaque->executer)
    {
        if (attaque->lag.Encours || (abs(j2->positionX - attaque->positionX ) <= attaque->taille))
        {
            attaque->executer=false;
            attaque->positionX=j1->positionX + 190;
            attaque->positionY=j1->positionY;
        }// si ça touche ou qu'on sort de l'écran on arrête et on reset tous
        else
        {
            attaque->executer=true;
            attaque->positionX += 12;
            if ((abs(j2->positionX - attaque->positionX ) <= attaque->taille) && !attaque->lag.Encours & !IsKeyDown(KEY_D)) //si on est assez proche et qu'on a pas touché y'a colision + esquive si recule
            {
                ColisionAtk(j2,attaque);
                attaque->lag.Encours=true;
            }
        }
    }
}

void AttaqueDistance2(Joueur *j2,Joueur *j1,Attaque *attaque,bool Key) //attaque lancé part la joueur 2
{
    if (Key || attaque->executer)
    {
        if (attaque->lag.Encours || (abs(j1->positionX - attaque->positionX ) <= 190))
        {
            attaque->executer=false;
            attaque->positionX=j2->positionX - attaque->taille;
            attaque->positionY=j2->positionY;
        }// si ça touche ou qu'on sort de l'écran on arrête et on reset tous
        else
        {
            attaque->executer=true;
            attaque->positionX -= 12;
            if ((abs(j1->positionX - attaque->positionX ) <= 190) && (!attaque->lag.Encours) & !IsKeyDown(KEY_LEFT)) //si on est assez proche et qu'on a pas touché y'a colision
            {
                ColisionAtk2(j1,attaque);
                attaque->lag.Encours=true;
            }
        }
    }
}

//ajouté lag quand on se prend une attaque et invul si lag trop long