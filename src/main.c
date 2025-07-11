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

#include "../../raylib/src/raylib.h"
#include "../header/all.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
* touche : J1 deplacement fleche directionnelles
*
* - Attaque : Escarmouche (C)
* - Attaque : Babouche (V)
* - Attaque : Pigeon (X)
* - Saut : Espace
*
* touche : J2 deplacement ZQSD
*
* - Attaque : Punch (I)
* - Attaque : Slash (O)
* - Attaque : Sandale (U)
* - Saut : Espace
*/
// touche debug : P
// touche echanger place : N

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "1v1GDN");
    Image fond = LoadImage("fond/resoucres___subway_by_shirouu_kun_d9x3kdx.png"); // le 0 0 c'est le centre de l'image btw
    Texture2D texture = LoadTextureFromImage(fond);
    UnloadImage(fond);
    
    InitAudioDevice();
    Music music = LoadMusicStream("music/Live and Learn - Sonic Adventure 2 [OST].mp3");
    PlayMusicStream(music);  

    bool debug = false;
    bool tamp_p = false, tamp_l = false;

    SetTargetFPS(60);            
    bool coli;

    // initialisation des Personnages
    Personnage personnage1 = Initialisaton_Personnage(1,0,270,190);
    Personnage personnage2 = Initialisaton_Personnage(0,0,270,190);

    /*
    personnage1.position.positionX = 50;
    personnage2.position.positionX = 660;
    personnage1.position.positionY = personnage2.position.positionY = 210;
    personnage1.sautable=personnage2.sautable=personnage2.touchable=true;
    personnage1.SAUT=personnage2.SAUT=0;
    personnage1.PV=personnage2.PV=100;
    personnage1.estGauche = true;
    personnage2.estGauche = false;*/
    
    // initialisation des attaques
    Attaque Escarm;
    int escarm_info[8] = {20,personnage1.position.positionX + personnage1.position.largeur,personnage1.position.positionY,50,20,45,30,false};
    Iniatk(&Escarm,escarm_info);

    Attaque Babouche; 
    int babouche_info[8] = {30,personnage1.position.positionX + personnage1.position.largeur,personnage1.position.positionY,70,20,200,45,false};
    Iniatk(&Babouche,babouche_info);

    Attaque Pigeon; 
    int pigeon_info[8] = {10,personnage1.position.positionX + personnage1.position.largeur,personnage1.position.positionY,50,50,0,60,true};
    Iniatk(&Pigeon,pigeon_info);


    Attaque **atk_j1 = (Attaque **) malloc(3 * sizeof(Attaque *)); // allocation dynamique pour le tableau d'attaques
    atk_j1[0] = &Escarm;
    atk_j1[1] = &Babouche;
    atk_j1[2] = &Pigeon; // on initialise le tableau d'attaques j1 avec les attaques créées précédemment


    //atk j2
    Attaque Punch;
    int punch_info[8] = {20,personnage2.position.positionX - 50,personnage2.position.positionY,50,20,45,30,false};
    Iniatk(&Punch,punch_info);

    Attaque Slash;
    int slash_info[8] = {30,personnage2.position.positionX - 70,personnage2.position.positionY,70,20,200,30,false};
    Iniatk(&Slash,slash_info);

    Attaque Sandale;
    int sandale_info[8] = {10,personnage2.position.positionX - 50,personnage2.position.positionY,50,50,0,60,true};
    Iniatk(&Sandale,sandale_info);

    Attaque **atk_j2 = (Attaque **) malloc(3 * sizeof(Attaque *)); // allocation dynamique pour le tableau d'attaques
    atk_j2[0] = &Punch;
    atk_j2[1] = &Slash;
    atk_j2[2] = &Sandale;

    long int CompteFps=0;
    
    char* path[3] = {"test_sprite/test2.png","test_sprite/doggo_kurukuru.png","test_sprite/who.png"};
    Texture2D* tab_test = Load_texture(path,3);

    AfficheAcceuil(screenWidth,screenHeight);

    int memo_doggo=0;
    int cmp_doggo=0;

    Camera2D test_cam;
    float camx = 0,camy = 0;

    test_cam.zoom = 1;
    test_cam.offset = (Vector2){0,0};
    test_cam.rotation = 0;
    test_cam.target = (Vector2){camx,camy};


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        

        if(IsKeyDown(KEY_P) && tamp_p != IsKeyDown(KEY_P)){debug = !debug; }
        tamp_p = IsKeyDown(KEY_P);

        UpdateMusicStream(music);
        CompteFps++;
        
        coli = colision(&personnage1,&personnage2);
        Bouge(&personnage1,coli,camx);
        Bouge2(&personnage2,coli, camx);
        
        
        // mise à jour de la position des attaques et du lag

        MiseAJourAtk(&personnage1,atk_j1,3,CompteFps); // maj j1
        MiseAJourAtk(&personnage2,atk_j2,3,CompteFps); // maj j2

        DestructionProjectile(&Pigeon ,atk_j2,3,true);
        DestructionProjectile(&Sandale ,atk_j1,3,false);


        // execution des attaques
        
        //j1 
        ExecuteAttaque(&personnage2,&Escarm,IsKeyDown(KEY_C)); // on fait l'attaque Escarmouche
        ExecuteAttaque(&personnage2,&Babouche,IsKeyDown(KEY_V));
        AttaqueDistance(&personnage1,&personnage2,&Pigeon,IsKeyDown(KEY_X));
        
        //j2
        ExecuteAttaque2(&personnage1,&Punch,IsKeyDown(KEY_I));
        ExecuteAttaque2(&personnage1,&Slash,IsKeyDown(KEY_O));
        AttaqueDistance2(&personnage2,&personnage1,&Sandale,IsKeyDown(KEY_U));
        
        if(IsKeyDown(KEY_L) && tamp_l != IsKeyDown(KEY_L) ){Grab(&personnage1,&personnage2);}
        tamp_l = IsKeyDown(KEY_L);

        camx = position_camera(&personnage1,&personnage2);
        if(camx < -1145 ) {camx = -1145;}
        else if ( camx > 1145){camx = 1145;}
        test_cam.target = (Vector2){camx,0};

        BeginDrawing(); 
            BeginMode2D(test_cam);

            ClearBackground(WHITE);
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
            
            //Personnage et stats
            //info debug
            
            if (debug){
            DrawText(TextFormat("testmemo?: %i,%i", Escarm.lag.MemoFps, Escarm.lag.SaLag), camx + 10,50, 10, BLACK);
            DrawText(TextFormat("atk?touché? : %i, %i ", IsKeyDown(KEY_T), personnage2.touchable),camx +  10,60, 10, BLACK);
            DrawText(TextFormat("où est la souris: [%i, %i]", GetMouseX(), GetMouseY()),camx +  10, 10, 10, RED); //info position souris
            DrawText(TextFormat("colision : %i",coli),camx +  10, 40, 10, RED); // info colision
            DrawText(TextFormat("position du Personnage: [%i, %i]", personnage1.position.positionX, personnage1.position.positionY),camx +  10, 20, 10, RED); //position personnage1
            DrawText(TextFormat("position du personnage2: [%i, %i]", personnage2.position.positionX, personnage2.position.positionY),camx +  10, 30, 10, RED); //info position personnage2-
            DrawText(TextFormat("position caméra: [%f, %i]", camx, 0),camx + 10, 70, 10, BLACK); //info caméra

            test_affichage(tab_test[2],personnage1.position.positionX + 65,personnage1.position.positionY - 65,0,0,65,45);
            test_affichage(tab_test[2],personnage2.position.positionX + 65,personnage2.position.positionY - 65,65,0,65,45);

            }
            
            if(cmp_doggo>=4){cmp_doggo=0;} // car on a que 4 images
            if (memo_doggo <= CompteFps) {
                cmp_doggo ++;
                memo_doggo = CompteFps + 8;} // la constante c'est la vitesse
                test_affichage(tab_test[1],camx + 860,10,40*cmp_doggo,40,40,40);

            AffichageSprite(&personnage1, &personnage2,  atk_j1, 3,atk_j2, 3);
               
            if (personnage1.PV<=0 || personnage2.PV<=0)
            {
                //texture disant d'appuyer sur R
                DrawText(TextFormat("PRESS R TO RESTART"),camx + 20 + 5, 300, 70, WHITE);
                DrawText(TextFormat("PRESS R TO RESTART"),camx + 20, 300, 70, BLACK);  

            }

            if (IsKeyDown(KEY_R))
                {
                    Reset_Combat(&personnage1, &personnage2,  atk_j1, 3,atk_j2, 3,&CompteFps);
                    cmp_doggo = 0;
                    memo_doggo = 0;
                    camx = 0;
                }
        EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    
    
    }
    Unload_texture(tab_test,3);
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
        Escarm.espace->position.positionX = personnage1.position.positionX + 190; //prendre en compte l'épaisseur du Personnage
        Escarm.espace->position.positionY = personnage1.position.positionY + 50; //où il se trouve par rapport aux Personnages
        HitLagTemps(&Escarm,CompteFps,30);
        
        Babouche.espace->position.positionX = personnage1.position.positionX + 190; 
        Babouche.espace->position.positionY = personnage1.position.positionY + 200;
        HitLagTemps(&Babouche,CompteFps,45);
        
        if (!Pigeon.executer)
        {
            Pigeon.espace->position.positionX = personnage1.position.positionX + 190;
            Pigeon.espace->position.positionY = personnage1.position.positionY;
        }
        HitLagTemps(&Pigeon,CompteFps,60);

        Punch.espace->position.positionX = personnage2.position.positionX - Punch.espace->taille; 
        Punch.espace->position.positionY = personnage2.position.positionY + 50;
        HitLagTemps(&Punch,CompteFps,30);
        
        Slash.espace->position.positionX = personnage2.position.positionX - Slash.espace->taille; 
        Slash.espace->position.positionY = personnage2.position.positionY + 200;
        HitLagTemps(&Slash,CompteFps,30);    

        if (!Sandale.executer)
        {
            Sandale.espace->position.positionX = personnage2.position.positionX - 50; // on retire la largeur de l'attaque 
            Sandale.espace->position.positionY = personnage2.position.positionY;
        }
        HitLagTemps(&Sandale,CompteFps,60);
        
        
            //info Personnage
            DrawRectangle(personnage1.position.positionX,personnage1.position.positionY, 190.0f, 270.0f, RED); //Personnage 1
            DrawRectangle(personnage2.position.positionX,personnage2.position.positionY, 190.0f, 270.0f, BLUE); //personnage2
            
            DrawRectangle(20,555, 3*personnage1.PV, 40, GREEN); //pv personnage1
            DrawRectangle(580,555, 3*personnage2.PV, 40, GREEN); //pv personnage2
            
            //affichage attaque 
            if (Escarm.lag.Encours){DrawRectangle(Escarm.espace->position.positionX,Escarm.espace->position.positionY,Escarm.espace->taille,Escarm.espace->largeur, ORANGE);}
            if (Babouche.lag.Encours){DrawRectangle(Babouche.espace->position.positionX,Babouche.espace->position.positionY,Babouche.espace->taille,Babouche.espace->largeur, ORANGE);}
            if (Pigeon.executer){DrawRectangle(Pigeon.espace->position.positionX,Pigeon.espace->position.positionY,Pigeon.espace->taille,Pigeon.espace->largeur, YELLOW);}
            
            
            if (Punch.lag.Encours){DrawRectangle(Punch.espace->position.positionX,Punch.espace->position.positionY,Punch.espace->taille,Punch.espace->largeur, PURPLE);}
            if (Slash.lag.Encours){DrawRectangle(Slash.espace->position.positionX,Slash.espace->position.positionY,Slash.espace->taille,Slash.espace->largeur, PURPLE);}
            if (Sandale.executer){DrawRectangle(Sandale.espace->position.positionX,Sandale.espace->position.positionY,Sandale.espace->taille,Sandale.espace->largeur, PINK);}

                    CompteFps=0; // reset pour pas que la mémoire explose
                    personnage1.position.positionX = 50;
                    personnage2.position.positionX = 660;
                    personnage1.position.positionY = personnage2.position.positionY = 210;
                    personnage1.sautable=personnage2.sautable=personnage2.touchable=true;
                    personnage1.SAUT=personnage2.SAUT=0;
                    personnage1.PV=personnage2.PV=100;*/