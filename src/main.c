/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "../raylib/src/raylib.h"
#include "mouvement.h"
#include "attaque.h"
#include "utility.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "1v1GDN");
    Image fond = LoadImage("fond/resoucres___subway_by_shirouu_kun_d9x3kdx.png");
    Texture2D texture = LoadTextureFromImage(fond);
    UnloadImage(fond);
    
    InitAudioDevice();
    Music music = LoadMusicStream("music/Live and Learn - Sonic Adventure 2 [OST].mp3");
    PlayMusicStream(music);  

    bool debug = false;

    SetTargetFPS(60);            
    bool coli;

    // initialisation des joueurs
    Joueur joueur1;
    Joueur joueur2;
    joueur1.positionX = 50;
    joueur2.positionX = 660;
    joueur1.positionY = joueur2.positionY = 210;
    joueur1.sautable=joueur2.sautable=joueur2.touchable=true;
    joueur1.SAUT=joueur2.SAUT=0;
    joueur1.PV=joueur2.PV=100;
    
    // initialisation des attaques
    Attaque Escarm;
    int escarm_info[8] = {20,joueur1.positionX + 190,joueur1.positionY,50,20,45,30,false};
    Iniatk(&Escarm,escarm_info);

    Attaque Babouche; 
    int babouche_info[8] = {30,joueur1.positionX + 190,joueur1.positionY,70,20,200,45,false};
    Iniatk(&Babouche,babouche_info);

    Attaque Pigeon; 
    int pigeon_info[8] = {10,joueur1.positionX + 190,joueur1.positionY,50,50,0,60,true};
    Iniatk(&Pigeon,pigeon_info);


    Attaque **atk_j1 = (Attaque **) malloc(3 * sizeof(Attaque *)); // allocation dynamique pour le tableau d'attaques
    atk_j1[0] = &Escarm;
    atk_j1[1] = &Babouche;
    atk_j1[2] = &Pigeon; // on initialise le tableau d'attaques j1 avec les attaques créées précédemment


    //atk j2
    Attaque Punch;
    int punch_info[8] = {20,joueur2.positionX - 50,joueur2.positionY,50,20,45,30,false};
    Iniatk(&Punch,punch_info);

    Attaque Slash;
    int slash_info[8] = {30,joueur2.positionX - 70,joueur2.positionY,70,20,200,30,false};
    Iniatk(&Slash,slash_info);

    Attaque Sandale;
    int sandale_info[8] = {10,joueur2.positionX - 50,joueur2.positionY,50,50,0,60,true};
    Iniatk(&Sandale,sandale_info);

    Attaque **atk_j2 = (Attaque **) malloc(3 * sizeof(Attaque *)); // allocation dynamique pour le tableau d'attaques
    atk_j2[0] = &Punch;
    atk_j2[1] = &Slash;
    atk_j2[2] = &Sandale;

    long int CompteFps=0;
    
    AfficheAcceuil(screenWidth,screenHeight);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(IsKeyDown(KEY_P)){debug = !debug;}

        UpdateMusicStream(music);
        CompteFps++;
        
        coli = colision(&joueur1,&joueur2);
        Bouge(&joueur1,coli);
        Bouge2(&joueur2,coli);
        
        
        // mise à jour de la position des attaques et du lag

        MiseAJourAtk(&joueur1,atk_j1,3,true,CompteFps); // maj j1
        MiseAJourAtk(&joueur2,atk_j2,3,false,CompteFps); // maj j2

        DestructionProjectile(&Pigeon ,atk_j2,3,true);
        DestructionProjectile(&Sandale ,atk_j1,3,false);


        // execution des attaques
        
        //j1 
        ExecuteAttaque(&joueur2,&Escarm,IsKeyDown(KEY_C)); // on fait l'attaque Escarmouche
        ExecuteAttaque(&joueur2,&Babouche,IsKeyDown(KEY_V));
        AttaqueDistance(&joueur1,&joueur2,&Pigeon,IsKeyDown(KEY_X));
        
        //j2
        ExecuteAttaque2(&joueur1,&Punch,IsKeyDown(KEY_I));
        ExecuteAttaque2(&joueur1,&Slash,IsKeyDown(KEY_O));
        AttaqueDistance2(&joueur2,&joueur1,&Sandale,IsKeyDown(KEY_U));
        
        BeginDrawing(); 
            ClearBackground(WHITE);
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
            
            //joueur et stats
            //info debug
            
            if (debug){
            DrawText(TextFormat("testmemo?: %i,%i", Escarm.lag.MemoFps, Escarm.lag.SaLag), 10,50, 10, BLACK);
            DrawText(TextFormat("atk?touché? : %i, %i ", IsKeyDown(KEY_T), joueur2.touchable), 10,60, 10, BLACK);
            DrawText(TextFormat("où est la souris: [%i, %i]", GetMouseX(), GetMouseY()), 10, 10, 10, RED); //info position souris
            DrawText(TextFormat("colision : %i",coli), 10, 40, 10, RED); // info colision
            DrawText(TextFormat("position du joueur: [%i, %i]", joueur1.positionX, joueur1.positionY), 10, 20, 10, RED); //position Joueur1
            DrawText(TextFormat("position du joueur2: [%i, %i]", joueur2.positionX, joueur2.positionY), 10, 30, 10, RED); //info position joueur2-
            }
           
            AffichageSprite(&joueur1, &joueur2,  atk_j1, 3,atk_j2, 3);
               
            if (joueur1.PV<=0 || joueur2.PV<=0)
            {
            
                //texture disant d'appuyer sur R
                DrawText(TextFormat("PRESS R TO RESTART"), 20 + 5, 300, 70, WHITE);
                DrawText(TextFormat("PRESS R TO RESTART"), 20, 300, 70, BLACK);                
                if (IsKeyDown(KEY_R))
                {
                    Reset_Combat(&joueur1, &joueur2,  atk_j1, 3,atk_j2, 3,&CompteFps);

                }
            }

            if (IsKeyDown(KEY_R))
                {
                    Reset_Combat(&joueur1, &joueur2,  atk_j1, 3,atk_j2, 3,&CompteFps);
                }
    
        EndDrawing();
        //----------------------------------------------------------------------------------
    
    
    }

    UnloadMusicStream(music);
    CloseAudioDevice(); 
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


// trash zone (y mettre truc qui marchait mais qui ont été remplacer au cas où)

/*
        Escarm.espace->positionX = joueur1.positionX + 190; //prendre en compte l'épaisseur du joueur
        Escarm.espace->positionY = joueur1.positionY + 50; //où il se trouve par rapport aux joueurs
        HitLagTemps(&Escarm,CompteFps,30);
        
        Babouche.espace->positionX = joueur1.positionX + 190; 
        Babouche.espace->positionY = joueur1.positionY + 200;
        HitLagTemps(&Babouche,CompteFps,45);
        
        if (!Pigeon.executer)
        {
            Pigeon.espace->positionX = joueur1.positionX + 190;
            Pigeon.espace->positionY = joueur1.positionY;
        }
        HitLagTemps(&Pigeon,CompteFps,60);

        Punch.espace->positionX = joueur2.positionX - Punch.espace->taille; 
        Punch.espace->positionY = joueur2.positionY + 50;
        HitLagTemps(&Punch,CompteFps,30);
        
        Slash.espace->positionX = joueur2.positionX - Slash.espace->taille; 
        Slash.espace->positionY = joueur2.positionY + 200;
        HitLagTemps(&Slash,CompteFps,30);    

        if (!Sandale.executer)
        {
            Sandale.espace->positionX = joueur2.positionX - 50; // on retire la largeur de l'attaque 
            Sandale.espace->positionY = joueur2.positionY;
        }
        HitLagTemps(&Sandale,CompteFps,60);
        
        
            //info joueur
            DrawRectangle(joueur1.positionX,joueur1.positionY, 190.0f, 270.0f, RED); //joueur 1
            DrawRectangle(joueur2.positionX,joueur2.positionY, 190.0f, 270.0f, BLUE); //joueur2
            
            DrawRectangle(20,555, 3*joueur1.PV, 40, GREEN); //pv joueur1
            DrawRectangle(580,555, 3*joueur2.PV, 40, GREEN); //pv joueur2
            
            //affichage attaque 
            if (Escarm.lag.Encours){DrawRectangle(Escarm.espace->positionX,Escarm.espace->positionY,Escarm.espace->taille,Escarm.espace->largeur, ORANGE);}
            if (Babouche.lag.Encours){DrawRectangle(Babouche.espace->positionX,Babouche.espace->positionY,Babouche.espace->taille,Babouche.espace->largeur, ORANGE);}
            if (Pigeon.executer){DrawRectangle(Pigeon.espace->positionX,Pigeon.espace->positionY,Pigeon.espace->taille,Pigeon.espace->largeur, YELLOW);}
            
            
            if (Punch.lag.Encours){DrawRectangle(Punch.espace->positionX,Punch.espace->positionY,Punch.espace->taille,Punch.espace->largeur, PURPLE);}
            if (Slash.lag.Encours){DrawRectangle(Slash.espace->positionX,Slash.espace->positionY,Slash.espace->taille,Slash.espace->largeur, PURPLE);}
            if (Sandale.executer){DrawRectangle(Sandale.espace->positionX,Sandale.espace->positionY,Sandale.espace->taille,Sandale.espace->largeur, PINK);}
            */
    
                                /*
                    CompteFps=0; // reset pour pas que la mémoire explose
                    joueur1.positionX = 50;
                    joueur2.positionX = 660;
                    joueur1.positionY = joueur2.positionY = 210;
                    joueur1.sautable=joueur2.sautable=joueur2.touchable=true;
                    joueur1.SAUT=joueur2.SAUT=0;
                    joueur1.PV=joueur2.PV=100;*/