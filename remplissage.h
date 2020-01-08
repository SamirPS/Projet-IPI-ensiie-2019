#ifndef R_H
#define R_H
 
/*
    Requires: un entier colonne et ligne donne par la premiere ligne du fichier.p2d tout les deux positif
    assings: Alloue de la memoire pour stocker une matrice de hauteur ligne  et de largeur colonne donne par la premiere ligne du fichier .p2d
    ensures: une matrice de hauteur ligne et de largeur colonne donne par la premiere ligne du fichier .p2d

*/
Matrice allocation(int colonne,int ligne);

/*
    Requires: ligne est le nombre de ligne de la grille et colonne le nombre de colonne de la grille,tout les deux positif
              char* argv nous permet de recuperer le premier argument qui doit etre un fichier valide
    assings: Copie le fichier .p2d dans la grille hormis la premiere ligne ou il y a ecrit le nombre de ligne et de colonne
    ensures: Une matrice composee du fichier.p2d  hormis la premiere ligne ou il y a ecrit le nombre de ligne et de colonne

*/

/* Permet de remplir la matrice  */
Matrice remplisage(int *colonne,int *ligne,char* argv[]);

#endif