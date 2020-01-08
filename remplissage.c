#include <stdio.h>
#include <stdlib.h>


#include "pile.h"
#include "lancement.h"
#include "remplissage.h"


/*
    Requires: un entier colonne et ligne donne par la premiere ligne du fichier.p2d qui sont soit nul soit positif
    assings: Alloue de la memoire pour stocker une matrice de hauteur ligne  et de largeur colonne donne par la premiere ligne du fichier .p2d
    ensures: une matrice de hauteur ligne et de largeur colonne donne par la premiere ligne du fichier .p2d

*/
Matrice allocation(int colonne,int ligne){

  int i;
  Matrice grille=(Matrice)malloc((ligne+1)*sizeof(char*));
  for(i=0;i<ligne;i++)
    {
      grille[i]=calloc(colonne,sizeof(Matrice));
    }
  return grille;
}

/*
    Requires: Une matrice grille valide ie utilisation de la fonction allocation,ligne est le nombre de ligne de la grille et colonne le nombre de colonne de la grille qui doivent etre positif,
              char* argv nous permet de recuperer le premier argument qui doit etre un fichier valide
    assings: Copie le fichier .p2d dans la grille hormis la premiere ligne ou il y a ecrit le nombre de ligne et de colonne
    ensures: Une matrice composee du fichier.p2d  hormis la premiere ligne ou il y a ecrit le nombre de ligne et de colonne

*/

/* Permet de remplir la matrice  */
Matrice remplisage(int *colonne,int *ligne,char* argv[]){

  FILE *fichier;
  int j,i;
  fichier=fopen(argv[1],"r+");

    /*Permet de lire la premiere ligne et 
    donc placer le curseur a la seconde ligne pour tout lire 
    sauf le nombre de ligne et de colonne pas besoin de verifier si le fichier a bien ete ouvert car on sait que le fichier
    existe*/

  fscanf(fichier,"%d %d\n",colonne,ligne);
  Matrice grille=allocation(*colonne,*ligne);
  
  for(i=0;i<*ligne;i++)
   {
    for(j=0;j<*colonne;j++)
    {
        grille[i][j]=fgetc(fichier);
    }
    fgetc(fichier);
    }


  fclose(fichier);
  return grille;
}