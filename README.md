# 1v1GDN
j1 est le joueur à gauche et j2 est le joueur à droite


Chose à faire ranger par ordre de priorité/type de truc [diffilculté supposé]

Important : choisir le nombre max d'attaque !
            les touches sont fait pour un clavier qwerty !

à faire : 

- ajouter un vrai menu debug [facile]
- on doit ne pouvoir faire qu'une action à la fois (sauf cas spéciales et par action j'entends attaque, bloqué PAS bouger ou sauter)
- généraliser tous en améliorant la structure des joueurs [ez_mais_chiant] (pris en charge par le quoicoufou)
- lag aussi avant les attaques pas que après [fine]
- durée pendant laquelle l'attaque ferra des dégats (entre les deux lags) [chiantouille]
- dégât qui dure toutes la durée de l'attaque et pas que le début (mais considèrerer comme un seul coup sauf cas spécial) [moyen-chiant]
- fonction avec matrice des attaques en entrée qui initialise toutes les attaques et rennvoie la liste des attaques des deux joueurs (permet de stocker les infos de chaque joueurs sous forme de matrice + associés à une liste pour le nom des attaques) [facile-moyen]
- pas faire plusieurs atttaque en même temps [facile]
- scrolling de la map [dunno]

- faire du knockback [trql]
- deux coups de même puissance s'annule aussi [moyen]

- fonction libérer les pointeurs et autre quand on quitte le jeu (un minimum de politesse) [long_chiant_mais_facile]

- faire en sorte de pouvoir stun les gens quand on les attaques (stun dépend du coup)
- ajouter de l'armure (super armor pour pas que tu te fasses cancel quand tu fais un gros coup)
- mouvement de caméra (=> scrolling maaais différents ça rend le jeu plus dynamique si bien fait) 
- faire en sorte que les personnages puissent changer de côté de terrain
- améliorer les attaques déjà existantes
- différents personnages
- ajouter des sprites
- animation  en régle générale
- menu de selections des personnages
- menu de selection des maps
- menu principaux 
- musiques et bruitages


bug à corriger : 

- regler les collisions quand changement de côté - pb sur la touche de garde
idée en vrac :

* faire un dossier par perso en mettant en argument un chaine de charactere de type "KEY_X" et remplacer X en fonction de si on joue en j1 ou j2
* faire le changement des directions entre j1 et j2 en fonction du signe de pos(j1) - pos(j2)

* reflexion projectile si contrer au bon moment ?

* invinsibilité si trop hit ? (mal implémenter)

* Mettre en place un systeme client/serveur pour permettre de jouer online (quoicouidée) (ne pas oublier aussi dcp de gerer les probleme de difference de fps dans du online qui peut creer du nimportequoicoubeh)

⣿⣿⣿⣿⡏⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠚⢿⣿⣿⣿⣿
⣿⣿⣿⡿⢈⠀⠀⠀⣴⠀⢠⢀⡄⢀⣴⣶⣶⣶⣶⣶⣻⣷⠆⠀⣷⡎⢻⣿⣿⣿
⣿⣿⣿⣷⠄⠀⠀⢠⢛⢠⢣⣾⣷⣸⣿⣿⣿⣿⣿⣿⠟⣃⣼⠁⠁⢸⣿⣿⣿⣿
⣿⣿⣿⢟⠀⠀⠀⠸⢀⡜⣼⣿⣿⣿⣿⣿⣿⣿⠟⣡⣴⣯⡼⣄⡐⠘⢻⣿⣿⣿
⣿⣿⣿⢀⠀⠀⡄⠀⠘⠻⠿⣿⣿⣿⣿⠿⠛⣡⣾⣿⡿⡻⠽⣿⠀⠈⢸⣿⣿⣿
⣿⣿⠏⣈⡄⠀⡅⠀⠀⠀⠀⠀⠈⠉⠉⡄⡘⡃⠉⠈⣐⡛⠣⣿⠀⠊⣼⣿⣿⣿
⡿⠃⠕⢉⠇⠀⡁⠀⠀⠀⠀⠀⠀⢀⢠⡇⣷⠭⠢⡭⣿⣧⣼⡇⣄⢰⣿⣿⣿⣿
⠏⢠⢺⢏⣸⣄⠀⠀⠀⠀⢀⣠⠠⣿⢸⣇⣿⡘⠿⣾⡛⢿⣼⡇⢨⣾⣿⣿⣿⣿
⢄⢑⡌⢰⢣⠂⠁⠀⠀⢰⣿⢋⠐⠛⣼⣿⡷⢃⣁⢽⣹⣼⡿⠁⣾⣿⣿⣿⣿⣿
⣾⠸⠃⢜⠌⢮⠀⠀⠀⠉⠀⠉⠀⠀⠀⠀⠀⠀⠙⠑⢵⠟⢏⢀⣿⣿⣿⣿⣿⣿
⠋⠉⠃⠀⠈⠈⠀⠀⠀⠀⡄⣀⣀⣤⣬⣥⣢⣴⣄⠁⠸⠺⠈⣷⣽⣛⠿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠿⠉⠉⢡⣸⡿⠛⡠⣤⣷⣽⣿⣿⣿⣿⣶⣽⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠉⠡⠙⠐⢦⣥⡿⠋⠻⠿⢿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⡀⠀⣘⣡⠂⠀⠀⠀⠀⠀⠿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣀⣶⣿⣷⣷⣿⡟⠁⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻


Comment raylib gére l'espace :

------------------> X
|
|
|
|
|
v

Y
