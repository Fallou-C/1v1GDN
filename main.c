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


    SetTargetFPS(60);            
    bool coli;

    Joueur joueur1;
    Joueur joueur2;
    joueur1.positionX = 50;
    joueur2.positionX = 660;
    joueur1.positionY = joueur2.positionY = 210;
    joueur1.sautable=joueur2.sautable=joueur2.touchable=true;
    joueur1.SAUT=joueur2.SAUT=0;
    joueur1.PV=joueur2.PV=100;
    
    // def atk : {coX, coY,degat,taille,{false,0,0},largeur,false}
    //atk j1
    Attaque escarm = {joueur1.positionX + 190,joueur1.positionY,20,50,{false,0,0},20,false}; // posX posY degats taille (parametre par defauts du lag)
    Attaque Babouche = {joueur1.positionX + 190,joueur1.positionY,30,70,{false,0,0},20,false};
    Attaque Pigeon = {joueur1.positionX + 190,joueur1.positionY,10,50,{false,0,0},50,false};
    
    //atk j2
    Attaque Punch = {joueur2.positionX - 50,joueur2.positionY,20,50,{false,0,0},20,false};
    Attaque Slash = {joueur2.positionX - 70,joueur2.positionY,30,70,{false,0,0},20,false};
    Attaque Sandale = {joueur2.positionX - 50,joueur1.positionY,10,50,{false,0,0},50,false};
    
    long int CompteFps=0;
    AfficheMenu(screenWidth,screenHeight);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        UpdateMusicStream(music);
        CompteFps++;
        
        coli = colision(&joueur1,&joueur2);
        Bouge(&joueur1,coli);
        Bouge2(&joueur2,coli);
        
        
        // position des attaques
        
        escarm.positionX = joueur1.positionX + 190; //prendre en compte l'épaisseur du joueur
        escarm.positionY = joueur1.positionY + 50; //où il se trouve par rapport aux joueurs
        HitLagTemps(&escarm,CompteFps,30);
        
        Babouche.positionX = joueur1.positionX + 190; 
        Babouche.positionY = joueur1.positionY + 200;
        HitLagTemps(&Babouche,CompteFps,45);
        
        HitLagTemps(&Pigeon,CompteFps,60);

        Punch.positionX = joueur2.positionX - Punch.taille; 
        Punch.positionY = joueur2.positionY + 50;
        HitLagTemps(&Punch,CompteFps,30);
        
        Slash.positionX = joueur2.positionX - Slash.taille; 
        Slash.positionY = joueur2.positionY + 200;
        HitLagTemps(&Slash,CompteFps,30);    

        HitLagTemps(&Sandale,CompteFps,60);
        //attaque execution
        
        //j1 
        ExecuteAttaque(&joueur1,&joueur2,&escarm,IsKeyDown(KEY_C)); // on fait l'attaque escarmouche
        ExecuteAttaque(&joueur1,&joueur2,&Babouche,IsKeyDown(KEY_V));
        AttaqueDistance(&joueur1,&joueur2,&Pigeon,IsKeyDown(KEY_X));
        
        //j2
        ExecuteAttaque2(&joueur2,&joueur1,&Punch,IsKeyDown(KEY_I));
        ExecuteAttaque2(&joueur2,&joueur1,&Slash,IsKeyDown(KEY_O));
        AttaqueDistance2(&joueur2,&joueur1,&Sandale,IsKeyDown(KEY_U));
        
        BeginDrawing(); 
            ClearBackground(WHITE);
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
            
            //joueur et stats
            //info debug
            /*
            DrawText(TextFormat("testmemo?: %i,%i", escarm.lag.MemoFps, escarm.lag.SaLag), 10,50, 10, BLACK);
            DrawText(TextFormat("atk?touché? : %i, %i ", IsKeyDown(KEY_T), joueur2.touchable), 10,60, 10, BLACK);
            DrawText(TextFormat("où est la souris: [%i, %i]", GetMouseX(), GetMouseY()), 10, 10, 10, RED); //info position souris
            DrawText(TextFormat("colision : %i",coli), 10, 40, 10, RED); // info colision
            DrawText(TextFormat("position du joueur: [%i, %i]", joueur1.positionX, joueur1.positionY), 10, 20, 10, RED); //position Joueur1
            DrawText(TextFormat("position du joueur2: [%i, %i]", joueur2.positionX, joueur2.positionY), 10, 30, 10, RED); //info position joueur2-
            */
            
            //info joueur
            DrawRectangle(joueur1.positionX,joueur1.positionY, 190.0f, 270.0f, RED); //joueur 1
            DrawRectangle(joueur2.positionX,joueur2.positionY, 190.0f, 270.0f, BLUE); //joueur2
            
            DrawRectangle(20,555, 3*joueur1.PV, 40, GREEN); //pv joueur1
            DrawRectangle(580,555, 3*joueur2.PV, 40, GREEN); //pv joueur2
            
            //attaque Pigeon
            if (escarm.lag.Encours){DrawRectangle(escarm.positionX,escarm.positionY,escarm.taille,escarm.largeur, ORANGE);}
            if (Babouche.lag.Encours){DrawRectangle(Babouche.positionX,Babouche.positionY,Babouche.taille,Babouche.largeur, ORANGE);}
            if (Pigeon.executer){DrawRectangle(Pigeon.positionX,Pigeon.positionY,Pigeon.taille,Pigeon.largeur, YELLOW);}
            
            
            if (Punch.lag.Encours){DrawRectangle(Punch.positionX,Punch.positionY,Punch.taille,Punch.largeur, PURPLE);}
            if (Slash.lag.Encours){DrawRectangle(Slash.positionX,Slash.positionY,Slash.taille,Slash.largeur, PURPLE);}
            if (Sandale.executer){DrawRectangle(Sandale.positionX,Sandale.positionY,Sandale.taille,Sandale.largeur, PINK);}

               
            if (joueur1.PV<=0 || joueur2.PV<=0)
            {
            
                //texture disant d'appuyer sur R
                DrawText(TextFormat("PRESS R TO RESTART"), 20 + 5, 300, 70, WHITE);
                DrawText(TextFormat("PRESS R TO RESTART"), 20, 300, 70, BLACK);                
                if (IsKeyDown(KEY_R))
                {
                    CompteFps=0; // reset pour pas que la mémoire explose
                    joueur1.positionX = 50;
                    joueur2.positionX = 660;
                    joueur1.positionY = joueur2.positionY = 210;
                    joueur1.sautable=joueur2.sautable=joueur2.touchable=true;
                    joueur1.SAUT=joueur2.SAUT=0;
                    joueur1.PV=joueur2.PV=100;
                }
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
