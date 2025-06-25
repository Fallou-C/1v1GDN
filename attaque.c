//gère les attaques

#include "attaque.h"
#include "mouvement.h"
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

//pensez à ré-organiser les fonctions par thèmes 

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
    if (attaque->lag.Encours) // si on doit mettre du lag
    {
        if (attaque->lag.SaLag==0) // on commence le lag
        {
            attaque->lag.MemoFps = fpstour + DureeLag;
            attaque->lag.SaLag++;
        }
        if ( attaque->lag.MemoFps==fpstour) // on l'arrete
        {
            attaque->lag.Encours=false;
            attaque->executer = false;
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


// faire en sorte quelles se détruisent mutuellement (chiant car regarder pour toutes les attaques mais y'a des listes doc c'est ok)

void AttaqueDistance(Joueur *j1,Joueur *j2,Attaque *attaque,bool Key) //attaque lancé part la joueur 1
{
    if (Key || attaque->executer)
    {
        if ((attaque->lag.Encours ) || attaque->espace->positionX > 900 ) //  on regarde si l'attaque est fini ou si elle est trop loin
        {   // si ça touche ou qu'on sort de l'écran on arrête et on reset tous
            attaque->executer=false;
            attaque->espace->positionX=j1->positionX + 190;
            attaque->espace->positionY=j1->positionY;
        }
        else
        {
            attaque->executer=true;
            attaque->espace->positionX += 12;
            if ((abs(j2->positionY - attaque->espace->positionY ) <= attaque->espace->largeur) && (abs(j2->positionX - attaque->espace->positionX ) <= attaque->espace->taille) && !attaque->lag.Encours & !IsKeyDown(KEY_D)) //si on est assez proche et qu'on a pas touché y'a colision + esquive si recule
            {
                ColisionAtk(j2,attaque);
                attaque->executer=false;
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
                attaque->executer=false;
            }
        }
    }
}

void MiseAJourAtk(Joueur *joueur, Attaque **liste_atk /*liste de pointeur d'attaque*/, int nb_atk, bool est_j1,int CompteFps ) // on prend une liste d'attaque d'un joueur et on met à jour leurs positions 
{
    for(int i = 0; i < nb_atk; i++)
    {
        if (!liste_atk[i]->executer) // à cause de ça
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

void Iniatk(Attaque *atk, int* info_atk /*de taille 8*/) // initialise une attaque en fonction des valeurs données 
{
    // info_atk = {degat,positionX,positionY,taille,largeur,pos_relatif,durrelag,bool atk_distance}    
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
    atk->lag.DureeLag = info_atk[i];i++;

    atk->atk_distance = info_atk[i];
    atk->executer = false;
}

void DestructionProjectile(Attaque *attaque ,Attaque **liste_atk,int nb_atk, bool estj2) // regarde si l'attaque se fait détruire par celle de l'adversaire
{
    for (int i = 0; i < nb_atk; i++)
    {
        if (attaque->executer && ( ( (attaque->espace->positionY<liste_atk[i]->espace->positionY) && (abs(attaque->espace->positionY - liste_atk[i]->espace->positionY) < attaque->espace->largeur ) ) || ( (liste_atk[i]->espace->positionY<attaque->espace->positionY) && (abs(attaque->espace->positionY - liste_atk[i]->espace->positionY) < liste_atk[i]->espace->largeur )) ) ) // l'attaque est lancé et vérifie quelles se touchent
        {
            if ((liste_atk[i]->lag.Encours && !liste_atk[i]->atk_distance) || (liste_atk[i]->executer && liste_atk[i]->atk_distance)) // on regarde si on a lancer une attaque
            {
                if (estj2)
                {
                    if (  (-(attaque->espace->positionX + attaque->espace->taille - liste_atk[i]->espace->positionX) < 1)) // si collision on la détruit 
                    {
                        attaque->executer=false;
                        attaque->lag.Encours=true;
                        if (liste_atk[i]->atk_distance){
                            liste_atk[i]->executer=false;
                            liste_atk[i]->lag.Encours=true;}
                        break;
                    }
                }
                else
                {
                    if ( (abs(liste_atk[i]->espace->positionX   - attaque->espace->positionX) < liste_atk[i]->espace->taille))// pb calcule distance
                    {
                        attaque->executer=false;
                        attaque->lag.Encours=true;
                        if (liste_atk[i]->atk_distance){
                            liste_atk[i]->executer=false;
                            liste_atk[i]->lag.Encours=true;}
                        break;
                    }
                }
            }
        }
    }
}
// partie selon Y ((abs(attaque->espace->positionY + attaque->espace->largeur - liste_atk[i]->espace->positionY - liste_atk[i]->espace->largeur )<1)) &&
// regarder quelle attaque est au dessus de l'autre

//ajouté lag quand on se prend une attaque et invul si lag trop long