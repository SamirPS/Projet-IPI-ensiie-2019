#include <stdlib.h>
#include <stdio.h>


#include "pile.h"
#include "lancement.h"
#include "remplissage.h"


/*
    Requires: une matrice grille valide et une pile initialiser et ligne le nombre de ligne de la matrice
    assings: libere les elements de la memoire afin d'eviter les fuites memoires.
    ensures: que grille et pile a bien ete free

*/


int main(int argc,char* argv[])
{
  srand(time(NULL));
  FILE *fichier=NULL;
  fichier=fopen(argv[1],"r+");
    /* Si le nombre d'argument est plus petit que 1 on quitte le programme et affiche une erreur comme ca on evite la fuite memoire   */

  if(argc<2)
    {
      printf("On doit avoir un argument \n ");
      return 3;
    }

    /* Si le fichier existe pas  on quitte le programme et affiche une erreur comme ca on evite la fuite memoire   */

  if(fichier==NULL)

    {
        printf("Probleme d'ouverture du fichier\n");
        return 4;
            }
    /* On recupere le nombre de ligne et de colonne du fichier    */

  fclose(fichier);


  /* Ouverture du fichier afin de recuperer la longeur et largeur du tableau */

  int colonne,ligne;
  
  
  /* On initialise la pile qui sera utilise,on met i et j a 0 et sens a 2 afin de respecter les consignes donne  */
  int i,j,sens,breakknow,strmode;
  Pile *maPile=initialiser();
  sens=2;
  i=0;j=0;
  breakknow=0;strmode=0;

  Matrice grille;
  grille=remplisage(&colonne,&ligne,argv);
  lancement(colonne,ligne,grille,&i,&j,maPile,maPile,&sens,&breakknow,&strmode);
  int r; 
  for(r=0;r<ligne;r++)
    {
      free(grille[r]);
    }
  free(grille);
  detruirePile(maPile);
  free(maPile);
  return 0;
}
