#ifndef LANCEMENT_H
#define LANCEMENT_H



typedef char  **Matrice;

/*
    Requires: un sens compris entre 0 et 7,i et j deux entiers valides,deux entiers colonne et ligne correspondant au nombre de lignes et de colonne donne par la premiere ligne du fichier .p2d
    assings: Modifie i et j pour qu'on navige dans le tableau comme le programme.p2d le veut afin de ne pas sortir du tableau et eviter les fuites memoires.
    ensures: Que l'on va dans la direction que le fichier.p2d desire

*/
void avancer(int sens,int *i,int *j,int colonne,int ligne);

/*
    Requires: Une pile valide,deux entier lignes et colonne qui sont la taille de la matrice ,
            la matrice grille qui est la matrice ou on a copier le fichier.p2d,i et j sont deux entier pour savoir ou l'on se trouve dans le tableau et faire les differentes action en fonction
             de grille[*i][*j] et sens( compris entre 0 et 7) et une pile breakpoint valide(on empile dans breakpoint avec la fonction (addbreakpoint) et depile avec dell breakpoint.
             et breakdnow qui vaut 0 si (x,y) est pas dans breakpoint et 1 sinon.Et strmode vaut 1 si on rencontre un " et 0 quand on en recontre un autre
    assings: Empiler et depiler des elements dans maPile et afficher des elements et modifie la grille en fonction des instruction donne par le fichier.p2d
    ensures: Si le fichier.p2d a un @ et ne boucle pas il execute les instructions en fonction de la valeur de grille[*i][*j] jusqu'a qu'il arrive a @.
    Si (i,j) sont dans breakpoint alors on sort de la fonction et que breakknow =0 .

*/
void lancement(int colonne,int ligne,Matrice grille,int *i,int *j,Pile *maPile,Pile *breakpoint,int *sens,int *breakknow,int* strmode);

/*
    Requires: Une pile valide,deux entier lignes et colonne qui sont la taille de la matrice ,
            la matrice grille qui est la matrice ou on a copier le fichier.p2d,i et j sont deux entier pour savoir ou l'on se trouve dans le tableau et faire les differentes action en fonction
             de grille[*i][*j] et sens( compris entre 0 et 7) et une pile breakpoint valide(on empile dans breakpoint avec la fonction (addbreakpoint) et depile avec dell breakpoint.
             et breakdnow qui vaut 0 si (x,y) est pas dans breakpoint et 1 sinon.Et strmode vaut 1 si on rencontre un " et 0 quand on en recontre un autre 
    assings: Empiler et depiler des elements dans maPile et afficher des elements et modifie la grille en fonction des instruction donne par le fichier.p2d
    ensures: Si le fichier.p2d a un @ et ne boucle pas il execute les instructions en fonction de la valeur de grille[*i][*j] jusqu'a que test=n-1.
    Si (i,j) sont dans breakpoint et que breakknow =0 alors on sort de la fonction.

*/
void step(int colonne,int ligne,Matrice grille ,int *i,int *j,int n,Pile *maPile,Pile* breakpoint,int *sens,int *breakknow,int *strmode);
/*
    Requires: Une pile valide,deux entier lignes et colonne qui sont la taille de la matrice ,
            la matrice grille qui est la matrice ou on a copier le fichier.p2d,i et j sont deux entier pour savoir ou l'on se trouve dans le tableau et faire les differentes action en fonction
             de grille[*i][*j] et sens(compris entre 0 et 7) et strmode qui vaut 1 ou 0 ainsi que la grille où se trouve le fichier copie p2d
             colonne et ligne etant le nombre de colonne et de ligne.et argv l'emplacement du fichier
    assings: On vide la pile via la fonction detruirePile et on se remet en haut a gauche du tableau en mettant *i et *j a 0 et on met sens par defaut a 2 et strmode=0
    on cree une matrice debut afin de modifier notre grille
    ensures: i et j vaut zero , la pile est vide et sens =2 et strmode=0 et la grille est remise a sa valeur de début 

*/
void restart(int *i,int *j,Pile *pile,int* strmode,int *sens,Matrice grille,int colonne,int ligne,char* argv[]);


/*
    Requires: Une pile valide qui contient l'historique des matrices et pile utilisee ,la matrice grille qui est la matrice ou on a copier le fichier.p2d,
              i et j sont deux entier pour savoir ou l'on se trouve dans le tableau,n pour savoir le nombre de retour en arriere qu'on veut.strmode vaut 1 si on a un passe un " et 0 quand on a passe un autre "
              et une Pile maPile qui sert a l'execution du fichier p2d  valide.Breakpoint pour les points d'arret et breaknow pour eviter de taper deux commande pour sortir du point 'arret
              colonne et ligne qui sont la taille de la matrice
    assings: Modifie la grille et la pile maPile 
    ensures: On a la grille et maPile qui vaut exactement la meme chose que n operation avant.

*/

void prevn(Pile* previous,Matrice grille,int*i,int*j,Pile*maPile,int n,Pile* breakpoint,int * breakknow, int *strmode,int* sens,int colonne,int ligne);

#endif