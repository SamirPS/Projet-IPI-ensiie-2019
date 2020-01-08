#ifndef pile_H
#define pile_H


typedef struct Pile Pile;
typedef struct Element Element;
struct Element
{
    int nombre;
    int x;
    int y;
    int sens;
    int strmode;
    Pile* pi;
    char** grille;
    Element *suivant;
};


struct Pile
{
    Element *premier;
};

/* Definition fonction des piles  */
/*
    Requires: Rien
    assings: Alloue l'espace necessaire pour stocker une pile et y met NULL comme premier element de la liste.
    ensures: Retourne une Pile

*/

Pile* initialiser();

/*
    Requires: une pile valide initialiser avec la fonction d'avant et a un entier valide
    assings: Alloue l'espace necessaire pour stocker un element et l'ajoute en tete de liste.
    ensures: Retourne une Pile avec l'element a en tete de la pile

*/
void empiler(Pile *pile, int a);



/*
    Requires: une pile valide initialiser avec la fonction d'initialiser
    assings: Enleve l'element en tete de la pile .
    ensures: Retourne  l'element  en tete de la pile.Si la pile est vide retourne zero

*/

int depiler(Pile *pile);
/*
    Requires: une pile valide initialiser avec la fonction d'initialiser
    assings: rien
    ensures: affiche tout les elements de la liste sommet a gauche avec le code ascii associe sinon ne fait rien.

*/
void afficherPile(Pile *pile);

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser
    assings: Enleve l'element en tete de la pile tant que celle ci n'est pas vide .
    ensures: Retourne  une pile vide

*/
void detruirePile(Pile *pile);

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser, une grille matrice remplie avec la fonction remplissage,previous qui est doit etre une pile valide initialiser
    et (i,j) la position du curseur ,previous doit etre empiler par la fonction empiler 2 uniquement et pile par empiler.strmode vaut 1 si on a un passe un " et 0 quand on a passe un autre "
    colonne et ligne etant le nombre de colonne et de ligne.et argv l'emplacement du fichier
    assings: Alloue l'espace necessaire pour stocker un element composee de la pile,grille,i,j et l'ajoute en tete de liste de previous.
    ensures: la tete de liste de previous est la grille,pile,i,j,strmode

*/

void empiler2(Pile *pile,char** grille,Pile*previous,int i,int j,int strmode,int sens,int colonne,int ligne,char* argv[]);

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser et qu'on empile avec la fonction addbreakpoint et depile avec delbreakpoint et (x,y) qui 
            correspond a la position du curseur.
    assings: empiler (x,y) en tete de liste en allouant assez de memoire
    ensures: le couple (x,y) est en tete de liste 

*/
void addbreakpoint(Pile* prem,int x,int y);


/*
    Requires: une pile valide initialiser avec la fonction d'initialiser et qu'on empile avec la fonction addbreakpoint et depile avec delbreakpoint
    assings: verifie si (x,y) est dans la pile.
    ensures: Retourne 1 si (x,y) est dans la pile 0 sinon

*/
int inlist(Pile* prem,int x,int y);

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser et qu'on empile avec la fonction addbreakpoint et depile avec delbreakpoint et (x,y) qui 
            correspond a la position du curseur.
    assings: Empile dans temp tout les couples differents de (x,y) detruit la pile et empile dans pile tout les element de temp
    ensures: Dans pile il y a tout les anciens element de pile sauf ceux qui etait egal a (x,y) 

*/

void delbreakpoint(Pile* pile,int x,int y);

#endif
