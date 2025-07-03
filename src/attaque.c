//gère les attaques
#include "../header/all.h"

#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include "../../raylib/src/raylib.h"


//pensez à ré-organiser les fonctions par thèmes 


bool AtkToucheY(Joueur* j,Attaque* atk1, Attaque* atk2) // renvoie si un joueur se fait toucher par atk1 en Y ou si atk1 touche atk2 en Y si joueur null
{
    if (j != NULL)
    {
        return ((atk1->espace->positionY <= j->positionY) && (abs(atk1->espace->positionY - j->positionY) <= atk1->espace->largeur ) ) || ( (j->positionY <= atk1->espace->positionY) && (abs(atk1->espace->positionY - j->positionY) <= 270 )) ; //270 hauteur du joueurs
    }
    else {
        return (  ((atk1->espace->positionY <= atk2->espace->positionY) && (abs(atk1->espace->positionY - atk2->espace->positionY) <= atk1->espace->largeur )) ||  ((atk1->espace->positionY >= atk2->espace->positionY) && (abs(atk1->espace->positionY - atk2->espace->positionY) <= atk2->espace->largeur)));
    }
}

void ColisionAtk(Joueur *joueur, Attaque *attaque)
{
    if(!joueur->estGauche) // on regarde de quel côté du terrain le joueur se trouve
    {
        if ( abs(joueur->positionX - attaque->espace->positionX ) <= attaque->espace->taille) // on prend la position du joueur par rapport à x 
        {
            if( AtkToucheY(joueur,attaque,NULL) && (abs(joueur->positionY - attaque->espace->positionY <= attaque->espace->largeur)) & !IsKeyDown(KEY_D)) //on regarde si l'attaque a pas été lancé trop haut
            {joueur->PV -= attaque->degat;}
        }
    }
    else
    {
        if ( abs(joueur->positionX - attaque->espace->positionX ) <= 190) // on prend la position du joueur par rapport à x avec largeur du joueur (important si attaque joueur à gauche)
        {
            if( AtkToucheY(joueur,attaque,NULL) && abs(joueur->positionY - attaque->espace->positionY <= attaque->espace->largeur) & !IsKeyDown(KEY_LEFT))
            {joueur->PV -= attaque->degat;}
        }
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


// faire en sorte quelles se détruisent mutuellement (chiant car regarder pour toutes les attaques mais y'a des listes doc c'est ok)

void AttaqueDistance(Joueur *j1,Joueur *j2,Attaque *attaque,bool Key) //attaque lancé part le joueur 1
{
    int direction = 1;

    if (Key || attaque->executer)
    {
        if (!j1->estGauche){ direction = -1;} // de quel sens on tire

        if ((attaque->lag.Encours ) || attaque->espace->positionX > 900  || attaque->espace->positionX < 0) //  on regarde si l'attaque est fini ou si elle est trop loin
        {   // si ça touche ou qu'on sort de l'écran on arrête de l'exécuter (tous les reset des emplacement sont fait à part)
            attaque->executer=false;
        }
        else
        {
            attaque->executer=true;
            attaque->espace->positionX += 12*direction;
            
            if (j1->estGauche){
                if (AtkToucheY(j2,attaque,NULL) && (abs(j2->positionX - attaque->espace->positionX ) <= attaque->espace->taille) && !attaque->lag.Encours ) //si on est assez proche et qu'on a pas touché y'a colision + esquive si recule
                {
                    ColisionAtk(j2,attaque);
                    attaque->executer=false;
                    attaque->lag.Encours=true;
                }
            }
            else{
                if ( AtkToucheY(j2,attaque,NULL) && (abs(j2->positionX - attaque->espace->positionX ) <= 190) && (!attaque->lag.Encours) ) //si on est assez proche et qu'on a pas touché y'a colision
                {
                    ColisionAtk(j2,attaque);
                    attaque->lag.Encours=true;
                    attaque->executer=false;
                }
            }
        }
    }
}

void MiseAJourAtk(Joueur *joueur, Attaque **liste_atk /*liste de pointeur d'attaque*/, int nb_atk,int CompteFps ) // on prend une liste d'attaque d'un joueur et on met à jour leurs positions 
{
    for(int i = 0; i < nb_atk; i++)
    {
        if (!liste_atk[i]->executer) // à cause de ça
        {
            if (joueur->estGauche)
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
        if (attaque->executer && AtkToucheY(NULL,attaque,liste_atk[i]) ) // l'attaque est lancé et vérifie quelles se touchent
        {
            if ((liste_atk[i]->lag.Encours && !liste_atk[i]->atk_distance) || (liste_atk[i]->executer && liste_atk[i]->atk_distance)) // on regarde si on a lancer une attaque
            {
                if (estj2)
                {
                    if (  (abs(attaque->espace->positionX - liste_atk[i]->espace->positionX) < attaque->espace->taille)) // si collision on la détruit 
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

void Grab(Joueur *j1, Joueur *j2)
{
    int x = j1->positionX , y = j1->positionY;
    j1->positionX = j2->positionX;
    j1->positionY = j2->positionY;
    j2->positionX = x;
    j2->positionY = y;
    j1->estGauche ^= 1;
    j2->estGauche ^= 1;
}