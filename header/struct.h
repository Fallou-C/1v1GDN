#ifndef STRUCT_H
#define STRUCT_H
#include <stdbool.h>
#include "../../raylib/src/raylib.h"


typedef struct Personnage_ Personnage; //je sais pas si ça compile j'ai aps raylib sur wsl (Y)
typedef struct GameInfo_ GameInfo;



// SURFACES

//Rectangle existe deja depuis raylib

typedef struct CollectionRectangle_{
    const int nombreRectangle;
    Rectangle * collection;
} CollectionRectangle;

// Le but sera aussi de pouvoir reutiliser cette structure pour des elements du jeu qui n'ont pas une animation definie des la generation (genre un projectile on pourra peut etre faire une boucle sur la hitbox ?) (Y)
typedef struct EnsembleCollectionRectangle_{ //Desolé j'arrive vrm pas a trouver de nom mdrrrrrrrrrrrrr (Y)
    const int nombreFrame;
    CollectionRectangle * ensemble;
} EnsembleCollectionRectangle;



// informations des touches
typedef struct KeyMapping_{
    char up;
    char down;
    char left;
    char right;

    char lightAtk;
    char heavyAtk;
    char dash;
}KeyMapping;


// FRAME



// Donne un compte rendu de l'etat en terme de frame en fonction de l'état d'action du personnage
// Les frames max seront definies avec des define et des fonctions ""d'interface"" s'occuperont de savoir pour quel personnage quel define regarder
typedef struct Frame_{ 
    // Choses basiques
    int recoveryFrame;
    
    int atkFrame; // j'ai l'impression qu'une des parties devrait direct être mit dans les attaques en faisant du lag avant et après l'attaque (F)
    int stunFrame;
    int idleFrame;

    // Lag
    int offensiveLagFrame; // je pense aussi direct dans les attaques mais une condition qui fait qu'on puisse pas balancer 4 attaques en même temps (F) : Ajout de champs d'un pseudo cooldown pour chaque attaque
    int defensiveLagFrame;


} Frame;

// POSITIONNEL


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

    // Accélération (je pense pas que ça sera utile (Le F))
    int accelerationX; // accélération sur l'axe X
    int accelerationY; // accélération sur l'axe Y
    int accelerationXMax; // accélération max
    int accelerationXMin; // accélération min
    int accelerationYMax; // accélération max
    int accelerationYMin; // accélération min
} Positionnel;


// PROJECTILES


typedef struct Projectile_{
    const int idProjectile; // id du type de projectile

    int directionX;
    int directionY; // vecteur

    void * sousProjectile; // Contiendra un pointeur vers la structure specifique du projectile choisi pour gerer les difference
    Positionnel position;
    Frame frame;
    int etat; // Etat du projectile (en vol, en collision, etc.)
    void (*onHit)(Personnage * target, Personnage * source, GameInfo * gameInfo); // Fonction appelée lors d'une collision avec un personnage
    int damage; // Dégâts infligés par le projectile
    int speed; // Vitesse du projectile (norme du vecteur vitesse, pas de decomposition en X et Y)

    int originPositionX; // Position d'origine du projectile (pour le calcul de la portée)
    int originPositionY; // Position d'origine du projectile (pour le calcul de la portée
    int range; // Portée du projectile


    int lifetime; // Durée de vie du projectile avant de disparaître
    int lifetimeCounter; // Compteur de durée de vie du projectile

    int camp; // Camp du projectile (allié ou ennemi)
} Projectile;


// SOUS PERSONNAGES (CHAQUE PERSONNAGE JOUABLE)


// DEFINITION DES POINTEURS DE FONCTION

typedef void (*competence)(Personnage * Personnage, GameInfo * gameInfo); //jsp si ça compile j'ai pas raylib sur WSL (Y)


// Creation d'une ""Classe"" Personnage"

//Paquet de 3 attaques 
typedef struct TriAttaque_{
    competence neutral;
    const int frameNeutral; // max frame pour l'etat neutral
    const int pseudoCooldownNeutral; // pseudo cooldown pour l'etat neutral
    int frameSinceLastNeutral;

    competence side;
    const int frameSide; // max frame pour l'etat side
    const int pseudoCooldownSide;
    int frameSinceLastSide;

    competence down;
    const int frameDown; // max frame pour l'etat down
    const int pseudoCooldownDown; // pseudo cooldown pour l'etat down
    int frameSinceLastDown;
}TriAttaque;

//Couple de paquet de 3 attaques
typedef struct CoupleLegerLourd_{
    TriAttaque light;
    TriAttaque heavy;
}CoupleLegerLourd;

//Collection de toutes les attaques
typedef struct Attaques_{
    CoupleLegerLourd groundedAttacks; // Attaques au sol
    CoupleLegerLourd airborneAttacks; // Attaques en l'air
    CoupleLegerLourd crouchingAttacks; // Attaques accroupies
}Attaques;



typedef struct Personnage_{
    const int idPersonnage; // id du type de personnage choisit (pour pouvoir reconnaitre sousPersonnage)
    void * sousPersonnage; //Contiendra un pointeur vers la structure specifique du personnage choisi pour gerer les difference
    int etat;
    int camp;
    int vie;
    const int vie_max; // j'ai rajouté ça car sinon c'est chiant pour les barres de vie (F)
    int status; // status du personnage (stun, mort, empoisonné, etc.)
    Positionnel position;
    Frame frame; // frame du personnage   
    Attaques attaques; // Collection de toute les attaques en plusieurs etape pour juste avoir a taper la premiere lettre puis tab, contient aussi le max frame ammount (Y)
} Personnage;

typedef struct GameInfo_{
    KeyMapping TouchesJoueur1; // informations des touches
    KeyMapping TouchesJoueur2;

    bool p1EnLigne;  // Peut etre utile plus tard pour la version du code serveur jsp (Y)
    bool p2EnLigne;

    int LobbyProprio; //1 pour joueur 1 et 2 pour joueur 2
} GameInfo;


#endif // STRUCT_H