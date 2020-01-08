#include <stdio.h>
#include <stdlib.h>

#include "pile.h"
#include "lancement.h"
#include "remplissage.h"

/* Definition fonction des piles  */
/*
    Requires: Rien
    assings: Alloue l'espace necessaire pour stocker une pile et y met NULL comme premier element de la liste.
    ensures: Retourne une Pile

*/
Pile* initialiser()
{
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
    return pile;
}

/*
    Requires: une pile valide initialiser avec la fonction d'avant et a un entier valide
    assings: Alloue l'espace necessaire pour stocker un element et l'ajoute en tete de liste.
    ensures: Retourne une Pile avec l'element a en tete de la pile

*/

void empiler(Pile *pile, int a)
{
    Element *nouveau = malloc(sizeof(*nouveau));

    nouveau->nombre = a;
    /* ->x et ->y sont utilise pour les breakpoint or ici on veut juste empiler un entier si on met pas les deux a un chiffre negatif on a un risque de voir un breakpoint la
        ou on veut pas */
    nouveau->x=-123;
    nouveau->y=-34443;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}
/*
    Requires: une pile valide initialiser avec la fonction d'initialiser, une grille matrice remplie avec la fonction remplissage,previous qui est doit etre une pile valide initialiser
    et (i,j) la position du curseur ,previous doit etre empiler par la fonction empiler 2 uniquement et pile par empiler.strmode vaut 1 si on a un passe un " et 0 quand on a passe un autre "
    colonne et ligne etant le nombre de colonne et de ligne.et argv l'emplacement du fichier
    assings: Alloue l'espace necessaire pour stocker un element composee de la pile,grille,i,j et l'ajoute en tete de liste de previous.
    ensures: la tete de liste de previous est la grille,pile,i,j,strmode

*/

void empiler2(Pile *pile,char** grille,Pile*previous,int i,int j,int strmode,int sens,int colonne,int ligne,char *argv[] ){

    Element *nouveau = malloc(sizeof(*nouveau));
    int k,l;

    nouveau->pi=initialiser();
    nouveau->strmode=strmode;
    Element *actuel=pile->premier;
    /* On fait avancer actuel a chaque fois dans la liste , arrive au dernier element quand il va rechercher le suivant ca sera NULL et donc la boucle s'arette */
    while(actuel!=NULL)
    {
        Element *nouveau2 = malloc(sizeof(*nouveau2));
        nouveau2->nombre =actuel->nombre;
        nouveau2->suivant = nouveau->pi->premier;
        nouveau->pi->premier = nouveau2;
        actuel=actuel->suivant;

    }
    
    nouveau->grille=remplisage(&colonne,&ligne,argv);
    
    for(k=0;k<ligne;k++)
    {
        for(l=0;l<colonne;l++)
        {
            nouveau->grille[k][l]=grille[k][l];
        }
    }

    nouveau->x=i;
    nouveau->y=j;
    nouveau->sens=sens;
    nouveau->suivant=previous->premier;
    
    previous->premier = nouveau;
    
}



/*
    Requires: une pile valide initialiser avec la fonction d'initialiser
    assings: Enleve l'element en tete de la pile .
    ensures: Retourne  l'element  en tete de la pile.Si la pile est vide retourne zero

*/

int depiler(Pile *pile)
{
    Element *elementaenlever = pile->premier;
    int nombre=0;
    if(pile->premier!=NULL){
        nombre=elementaenlever->nombre;
        pile->premier = pile->premier->suivant;
        free(elementaenlever);
    }
    return nombre;
}

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser
    assings: Enleve l'element en tete de la pile tant que celle ci n'est pas vide .
    ensures: Retourne  une pile vide

*/
void detruirePile(Pile *pile)
{
    
    /* On depile tant que pile premier n'est pas null soit tant que la liste est pas vide,on a pas un n fini de valeurs dans la liste
    et donc apress les n depiler pile premier pointera vers NULL*/

    while (pile->premier!= NULL)
    {
        depiler(pile);
    }
}

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser
    assings: rien
    ensures: affiche tout les elements de la liste sommet a gauche avec le code ascii associe sinon ne fait rien.

*/

void afficherPile(Pile *pile)
{
    Element *actuel = pile->premier;

    /* On fait avancer actuel a chaque fois dans la liste , arrive au dernier element quand il va rechercher le suivant ca sera NULL et donc la boucle s'arette */
    while (actuel != NULL)
    {
        printf("%d (%c) |", actuel->nombre,actuel->nombre%256);
        actuel = actuel->suivant;
    }
}


/*
    Requires: une pile valide initialiser avec la fonction d'initialiser et qu'on empile avec la fonction addbreakpoint et depile avec delbreakpoint
    assings: verifie si (x,y) est dans la pile.
    ensures: Retourne 1 si (x,y) est dans la pile 0 sinon

*/
int inlist(Pile* pile,int x,int y){
    Element *actuel= pile->premier;

    /* On fait avancer actuel a chaque fois dans la liste , arrive au dernier element quand il va rechercher le suivant ca sera NULL et donc la boucle s'arette */
    while(actuel!=NULL)
    {
        if(actuel->x==x && actuel->y==y)
            return 1;
        actuel=actuel->suivant;
    }
    return 0;
}

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser et qu'on empile avec la fonction addbreakpoint et depile avec delbreakpoint et (x,y) qui 
            correspond a la position du curseur.
    assings: empiler (x,y) en tete de liste en allouant assez de memoire
    ensures: le couple (x,y) est en tete de liste 

*/
void addbreakpoint(Pile* pile,int x,int y)
{   
    Element *nouveau = malloc(sizeof(*nouveau));

    nouveau->x = x;
    nouveau->y = y;

    nouveau->suivant=pile->premier;
    pile->premier = nouveau;

} 

/*
    Requires: une pile valide initialiser avec la fonction d'initialiser et qu'on empile avec la fonction addbreakpoint et depile avec delbreakpoint et (x,y) qui 
            correspond a la position du curseur.
    assings: Empile dans temp tout les couples differents de (x,y) detruit la pile et empile dans pile tout les element de temp
    ensures: Dans pile il y a tout les anciens element de pile sauf ceux qui etait egal a (x,y) 

*/


void delbreakpoint(Pile* pile,int x,int y)
{   
    Pile* temp=initialiser();

    Element *actuel=pile->premier;
    
    Element *tempactuel=temp->premier;

    /* On fait avancer actuel a chaque fois dans la liste , arrive au dernier element quand il va rechercher le suivant ca sera NULL et donc la boucle s'arette */
    while(actuel!=NULL)
    {
        if(actuel->x==x && actuel->y==y){}
        
        else{
            addbreakpoint(temp,actuel->x,actuel->y);
        }

       actuel=actuel->suivant;
    }
   
    detruirePile(pile);
    tempactuel=temp->premier;
   /* On fait avancer tempactuel a chaque fois dans la liste , arrive au dernier element quand il va rechercher le suivant ca sera NULL et donc la boucle s'arette */
    while(tempactuel!=NULL)
    {
       addbreakpoint(pile,tempactuel->x,tempactuel->y);
       tempactuel=tempactuel->suivant;
    }

    detruirePile(temp);
    free(temp);
} 

