//gère les attaques

#include "attaque.h"
#include "mouvement.h"
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"


void ColisionAtk(Joueur *joueur, Attaque *attaque)
{
    if ( abs(joueur->positionX - attaque->espace->positionX ) <= attaque->espace->taille) // on prend la position du joueur par rapport à x 
    {
        if(abs(joueur->positionY - attaque->espace->positionY <= attaque->espace->largeur)& !IsKeyDown(KEY_D)) //on regarde si l'attaque a pas été lancé trop haut
        {joueur->PV -= attaque->degat;}
    }
}

void ColisionAtk2(Joueur *joueur, Attaque *attaque)
{
    if ( abs(joueur->positionX - attaque->espace->positionX ) <= 190) // on prend la position du joueur par rapport à x avec largeur du joueur (important si attaque joueur à gauche)
    {
        if(abs(joueur->positionY - attaque->espace->positionY <= attaque->espace->largeur) & !IsKeyDown(KEY_LEFT))
        {joueur->PV -= attaque->degat;}
    }
}

void HitLagTemps(Attaque *attaque,long int fpstour,int DureeLag) 
{
    if (attaque->lag.Encours)
    {
        if (attaque->lag.SaLag==0)
        {
            attaque->lag.MemoFps = fpstour + DureeLag;
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

void ExecuteAttaque(Joueur *joueur,Attaque *attaque,bool IsKeyDown) // attaquant attaqué attaque touche
{
    if (IsKeyDown & !attaque->lag.Encours)
    {
        if (!(attaque->lag.Encours))
        {
            attaque->lag.Encours = true;
            ColisionAtk(joueur,attaque);
        }
    }
}

void ExecuteAttaque2(Joueur *joueur,Attaque *attaque,bool IsKeyDown) // attaquant attaqué attaque touche mais on utilise colision2
{
    if (IsKeyDown & !attaque->lag.Encours)
    {
        if (!(attaque->lag.Encours))
        {
            attaque->lag.Encours = true;
            ColisionAtk2(joueur,attaque);
        }
    }
}


// faire en sorte quelles se détruisent mutuellement 

void AttaqueDistance(Joueur *j1,Joueur *j2,Attaque *attaque,bool Key) //attaque lancé part la joueur 1
{
    if (Key || attaque->executer)
    {
        if ((attaque->lag.Encours ) || attaque->espace->positionX > 900 ) //  on regarde si l'attaque est fini ou si elle est trop loin
        {
            attaque->executer=false;
            attaque->espace->positionX=j1->positionX + 190;
            attaque->espace->positionY=j1->positionY;
        }// si ça touche ou qu'on sort de l'écran on arrête et on reset tous
        else
        {
            attaque->executer=true;
            attaque->espace->positionX += 12;
            if ((abs(j2->positionY - attaque->espace->positionY ) <= attaque->espace->largeur) && (abs(j2->positionX - attaque->espace->positionX ) <= attaque->espace->taille) && !attaque->lag.Encours & !IsKeyDown(KEY_D)) //si on est assez proche et qu'on a pas touché y'a colision + esquive si recule
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
        if (attaque->lag.Encours || attaque->espace->positionX < 0)
        {
            attaque->executer=false;
            attaque->espace->positionX=j2->positionX - attaque->espace->taille;
            attaque->espace->positionY=j2->positionY;
        }// si ça touche ou qu'on sort de l'écran on arrête et on reset tous
        else
        {
            attaque->executer=true;
            attaque->espace->positionX -= 12;
            if ( (abs(j1->positionY - attaque->espace->positionY ) <= attaque->espace->largeur) && (abs(j1->positionX - attaque->espace->positionX ) <= 190) && (!attaque->lag.Encours) & !IsKeyDown(KEY_LEFT)) //si on est assez proche et qu'on a pas touché y'a colision
            {
                ColisionAtk2(j1,attaque);
                attaque->lag.Encours=true;
            }
        }
    }
}

void MiseAJourAtk(Joueur *joueur, Attaque **liste_atk /*liste de pointeur d'attaque*/, int nb_atk, bool est_j1,int CompteFps ) // on prend une liste d'attaque d'un joueur et on met à jour leurs positions 
{
    /*for(int i=0;i<3;i++){fprintf(stderr,"atk_j1[%d] posX=%d, posY=%d, taille=%d, largeur=%d, pos_relatif=%d\n",
            i,
            liste_atk[i]->espace->positionX,
            liste_atk[i]->espace->positionY,
            liste_atk[i]->espace->taille,
            liste_atk[i]->espace->largeur,
            liste_atk[i]->espace->pos_relatif
        );} */
    for(int i = 0; i < nb_atk; i++)
    {
        if (!liste_atk[i]->executer)
        {
            if (est_j1)
            {
                liste_atk[i]->espace->positionX = joueur->positionX + 190;
                liste_atk[i]->espace->positionY = joueur->positionY + liste_atk[i]->espace->pos_relatif; // ajouter la position de l'attaque relatif au personnage
            }
            else
            {
                liste_atk[i]->espace->positionX = joueur->positionX - liste_atk[i]->espace->taille;
                liste_atk[i]->espace->positionY = joueur->positionY + liste_atk[i]->espace->pos_relatif;
            }
        }
        HitLagTemps(liste_atk[i],CompteFps,liste_atk[i]->lag.DureeLag);
    }
}

void Iniatk(Attaque *atk, int* info_atk /*de taille 7*/) // initialise une attaque en fonction des valeurs données 
{
    // info_atk = {degat,positionX,positionY,taille,largeur,pos_relatif,durrelag}    
    int i = 0;

    atk->espace = (Espace*) malloc(sizeof(Espace));

    atk->degat = info_atk[i];i++;
    atk->espace->positionX = info_atk[i];i++;
    atk->espace->positionY = info_atk[i];i++;
    atk->espace->taille = info_atk[i];i++;
    atk->espace->largeur = info_atk[i];i++;
    atk->espace->pos_relatif = info_atk[i];i++;

    atk->lag.Encours = false;
    atk->lag.MemoFps = 0;
    atk->lag.SaLag = 0;
    atk->lag.DureeLag = info_atk[i];

    atk->executer = false;
}



//ajouté lag quand on se prend une attaque et invul si lag trop long