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

#include "C:\raylib\raylib\src\raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define PLAYER_HOR_SPD 200.0f

typedef struct Joueur_ {
    int positionX;
    int positionY;
    bool sautable;
    int SAUT;
    int PV;
    bool touchable;
} Joueur ;

float delta=0.03;




void Bouge(Joueur *joueur,bool colision)
{
    if (IsKeyDown(KEY_LEFT) && (joueur->positionX>0))  
    {
        joueur->positionX -= PLAYER_HOR_SPD*delta*2/3;
    }
    if (IsKeyDown(KEY_RIGHT) && !colision)
    {
        joueur->positionX += PLAYER_HOR_SPD*delta;
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

void Bouge2(Joueur *joueur, bool colision)
{
    if (IsKeyDown(KEY_A) && !colision)
    {
        joueur->positionX -= PLAYER_HOR_SPD*delta;
    }
    if (IsKeyDown(KEY_D) && (joueur->positionX <= 900-190)) //pour pas sortir du terrain
    {
        joueur->positionX += PLAYER_HOR_SPD*delta*2/3;
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

bool colision(Joueur *joueur1,Joueur *joueur2)
{
    if (abs((joueur2->positionX - joueur1->positionX))<190) {return true;}
    else {return false;}
}

void AfficheMenu(int screenWidth, int screenHeight)
{
    Image fondMenu = LoadImage("C:\\Users\\ultim\\Pictures\\Saved Pictures\\logoC2.png");
    Texture2D textureMenu = LoadTextureFromImage(fondMenu);
    UnloadImage(fondMenu);
    Music musicMenu = LoadMusicStream("C:\\Users\\ultim\\Downloads\\Evoland 2 OST - Track 38 (Fighting Magus).mp3");
    PlayMusicStream(musicMenu);
    while(!IsKeyDown(KEY_ENTER) & !WindowShouldClose())
    {
        UpdateMusicStream(musicMenu);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(textureMenu, screenWidth/2 - textureMenu.width/2, screenHeight/2 - textureMenu.height/2 +100, WHITE);
        EndDrawing();
    }
    UnloadMusicStream(musicMenu);
}


//atk
typedef struct HitLag_ {
    bool Encours;
    int MemoFps; //on regarde quand l'attaque a été lancé
    int SaLag; // prend en compte le début et la fin du lag
} HitLag;

typedef struct Attaque_ {
    int positionX;
    int positionY;
    int degat;
    int taille; //par défaut la taille et mesure sur l'axe x
    HitLag lag;
    int largeur;// same que taille mais en y
    bool executer; // surtout pour les attaques à distances, pour savoir si elles sont activées
} Attaque;

//------------------------------------------------------------------------------------
// Program main entry point
//---------------------------------Vector2 position;--------------------------------------------------

//déplacement
void Bouge(Joueur *joueur,bool colision);
void Bouge2(Joueur *joueur, bool colision);
bool colision(Joueur *joueur1,Joueur *joueur2);
void AfficheMenu(int screenWidth, int screenHeight);

// attaque et vie



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

void AttaqueDistance(Joueur *j1,Joueur *j2,Attaque *attaque,bool Key) //attaque lancé part la joueur 1
{
    if (Key || attaque->executer)
    {
        if (attaque->lag.Encours || (attaque->positionX > 1000 ))
        {
            attaque->executer=false;
            attaque->positionX=j1->positionX + 190;
            attaque->positionY=j1->positionY;
        }// si ça touche ou qu'on sort de l'écran on arrête et on reset tous
        else
        {
            attaque->executer=true;
            attaque->positionX += 12;
            if ((abs(j2->positionX - attaque->positionX ) <= attaque->taille) & !attaque->lag.Encours & !IsKeyDown(KEY_D)) //si on est assez proche et qu'on a pas touché y'a colision + esquive si recule
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
        if (attaque->lag.Encours || (attaque->positionX < 0 ))
        {
            attaque->executer=false;
            attaque->positionX=j2->positionX - attaque->taille;
            attaque->positionY=j2->positionY;
        }// si ça touche ou qu'on sort de l'écran on arrête et on reset tous
        else
        {
            attaque->executer=true;
            attaque->positionX -= 12;
            if ((abs(j1->positionX - attaque->positionX ) <= 190) & (!attaque->lag.Encours) & !IsKeyDown(KEY_LEFT)) //si on est assez proche et qu'on a pas touché y'a colision
            {
                ColisionAtk2(j1,attaque);
                attaque->lag.Encours=true;
            }
        }
    }
}

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "1v1GDN");
    Image fond = LoadImage("C:\\Users\\ultim\\Downloads\\resoucres___subway_by_shirouu_kun_d9x3kdx.png");
    Texture2D texture = LoadTextureFromImage(fond);
    UnloadImage(fond);
    
    InitAudioDevice();
    Music music = LoadMusicStream("C:\\Users\\ultim\\Downloads\\Live and Learn - Sonic Adventure 2 [OST].mp3");
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
