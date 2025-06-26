#ifndef STRUCT_H
#define STRUCT_H

// Creation d'une ""Classe"" Personnage"

typedef struct Positionnel_{
    // Position
    int positionX; // position en X
    int positionY; // position en Y
    int positionXmax; // position max en X
    int positionYmax; // position max en Y
    int positionXmin; // position min en X
    int positionYmin; // position min en Y

    // Taille
    int taille; // taille de l'objet sur l'axe X
    int largeur; // taille de l'objet sur l'axe Y

    // Vitesse
    int vitesseX; // vitesse de déplacement sur l'axe X
    int vitesseY; // vitesse de déplacement sur l'axe Y
    int vitesseXMax; // vitesse max de déplacement
    int vitesseXMin; // vitesse min de déplacement
    int vitesseYMax; // vitesse max de déplacement
    int vitesseYMin; // vitesse min de déplacement

    // Accélération
    int accelerationX; // accélération sur l'axe X
    int accelerationY; // accélération sur l'axe Y
    int accelerationXMax; // accélération max
    int accelerationXMin; // accélération min
    int accelerationYMax; // accélération max
    int accelerationYMin; // accélération min
} Positionnel;


// Donne un compte rendu de l'etat en terme de frame en fonction de l'état d'action du personnage
// Les frames max seront definies avec des define et des fonctions ""d'interface"" s'occuperont de savoir pour quel personnage quel define regarder
typedef struct Frame_{ 
    // Choses basiques
    int recoveryFrame;
    int atkFrame;
    int stunFrame;
    int idleFrame;

    // Lag
    int offensiveLagFrame;
    int defensiveLagFrame;


} Frame;


typedef struct Personnage_{
    int idPersonnage; // id du type de personnage choisit (pour pouvoir reconnaitre sousPersonnage)
    void * sousPersonnage; //Contiendra un pointeur vers la structure specifique du personnage choisi pour gerer les difference
    int etat;
    int camp;
    int vie;
    int status; // status du personnage (stun, mort, empoisonné, etc.)
    Positionnel position;
    Frame frame; // frame du personnage    
} Personnage;

#endif // STRUCT_H