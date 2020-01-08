#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pile.h"
#include "lancement.h"
#include "remplissage.h"


/*
    Requires: Une matrice grille valide ie utilisation de la fonction allocation,ligne est le nombre de ligne de la grille et colonne le nombre de colonne de la grille,
              le i 0 et ligne-1 et j entre 0 et colonne-1 permet d'afficher le curseur en fonction de ou on est,une pile valide et initialiser.
    assings:
    ensures: Affiche deux repere un a gauche et l'autre en haut et la grille.Affiche deux curseur pour savoir ou on se trouve dans le programme et afficher la pile

*/

void afficher(Matrice grille,int ligne,int colonne,int i,int j,Pile *maPile){

  /* Calcul de la taille du plus grand nombre en comptant le - et le > */
  int decalage=2;
  int k;
  int l;
  int ligne1=ligne;


  /* Calcul de la taille du plus grand nombre */
  /* Forcement si on divise par 10 un entier positif au bout d'un moment il sera plus petit que 9 cette solution evite d'inclure la librarie maths et d'use le log en base 10 */

  while(ligne1>9){
    decalage++;
    ligne1=ligne1/10;
  }

  printf("\n");
  for(k=0;k<decalage;k++)
  {
    printf(" ");
  }

  for(k=0;k<colonne+1;k++)
  {
    if(k%5==0)
        printf("%-5d",k);
  }

  printf("\n");

   for(k=0;k<decalage;k++)
  {
    printf(" ");
  }

  for(k=0;k<colonne+1;k++)
  {
    if(k==j)
        printf("v");
    else if(k%5==0)
        printf("|");
    else
        printf(" ");
  }

  printf("\n");

  for(k=0;k<ligne;k++)
  {
    if(k%5==0)
        printf("%*d",decalage-1,k);
    else{

    for(l=0;l<decalage-1;l++)
            printf(" ");
      }

    if(k==i)
        printf(">");
    else if(k%5==0)
        printf("-");
    else
        printf(" ");
    printf("%s",grille[k]);

    printf("\n");

  }
  printf("\n");
  afficherPile(maPile);
  printf("\n x:%d,y:%d \n",i,j);


}

int main(int argc,char* argv[])
{
  FILE *fichier=NULL;
  fichier=fopen(argv[1],"r+");

/* Si le nombre d'argument est plus petit que 1 on quitte le programme et affiche une erreur comme ca on evite la fuite memoire   */

  if(argc!=2)
    {
      printf("Pas assez d'argument");
      return 44;
    }
    /* Si le fichier existe pas  on quitte le programme et affiche une erreur comme ca on evite la fuite memoire   */

  if(fichier==NULL)
    {
		printf("Fichier existe pas ");
		return 45;

    }
    /* On recupere le nombre de ligne et de colonne du fichier    */

  fclose(fichier);

  int colonne,ligne,strmode;
  int i,j,sens,n,breakknow,x,y;


  /* On initialise la pile qui sera utilise,on met i et j a 0 et sens a 2 afin de respecter les consignes donne  */
  
  Pile *maPile=initialiser();
  Pile *breakpoint=initialiser();
  Pile *previous=initialiser();


  breakknow=0;strmode=0;
  i=0;j=0;sens=2;

/* On initialiser les deux char permetant de recuperer les instructions donne par l'utilisateur et un char histoirique pour repeter la derniere action */

  char actuel[256];
  char historique[256];

  Matrice grille;

  grille=remplisage(&colonne,&ligne,argv);
  printf("entrer une commande ");

  empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
  empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);

  fgets(actuel, 256, stdin);
  actuel[strlen(actuel)-1]='\0';
  strcpy(historique,actuel);

  /* La boucle s'arrette si et seulement si l'utilisateur entre la commande quit
     strcpy permet de copie ce qu'il y a dans actuel dans historique comme ca si l'user entre " " on relance la commande precedente via le char historique et
     strcmp comparer deux chaine de caractere et renvoie 0 si les deux sont pareils.strstr recherche une occurence dans une chaine de caractere
     si on entre " " on fait les memes actions sauf que l'on remplace actuel par historique ( historique est la derniere commande utilise hors "" */
  while(strcmp(actuel,"quit")!=0)
  {
      if(strcmp(actuel,"restart")==0)
      {
          strcpy(historique,actuel);
          restart(&i,&j,maPile,&strmode,&sens,grille,colonne,ligne,argv);
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
      }

      else if(strcmp(actuel,"prec")==0)
      {
          strcpy(historique,actuel);
          prevn(previous,grille,&i,&j,maPile,1,breakpoint,&breakknow,&strmode,&sens,colonne,ligne);
      }
      else if(strstr(actuel,"prec")!=NULL)
      { 
          strcpy(historique,actuel);
           /* La boucle se termine si l'utilisateur entre un entier  */
           while(!sscanf(actuel,"prec %d",&n))
           {
           printf("\n Erreur entre prec unentier ex : prec 2 ");
           fgets(actuel, 256, stdin);
           sscanf(actuel,"prec %d",&n);
           }
           prevn(previous,grille,&i,&j,maPile,n,breakpoint,&breakknow,&strmode,&sens,colonne,ligne);
           

      }
      else if(strcmp(actuel,"step")==0)
      {
          strcpy(historique,actuel);
          step(colonne,ligne,grille,&i,&j,1,maPile,breakpoint,&sens,&breakknow,&strmode);
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
      }
      else if(strstr(actuel,"step")!=NULL)
      {
          strcpy(historique,actuel);
           /* La boucle se termine si l'utilisateur entre un entier  */
           while(!sscanf(actuel,"step %d",&n))
           {
           printf("\n Erreur entre step unentier ex : step 2 ");
           fgets(actuel, 256, stdin);
           sscanf(actuel,"step %d",&n);
           }
          step(colonne,ligne,grille,&i,&j,n,maPile,breakpoint,&sens,&breakknow,&strmode);
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);

      }

      else if(strstr(actuel,"breakpoint")!=NULL)
      {
          strcpy(historique,actuel);
           /* La boucle se termine si l'utilisateur entre un entier  */
           while(!sscanf(actuel,"breakpoint %d %d",&x,&y))
           {
           printf("\n Erreur entre breakpoint x y avec x et y entier ");
           fgets(actuel, 256, stdin);
           sscanf(actuel,"breakpoint %d %d",&x,&y);
           }
          addbreakpoint(breakpoint,x,y);

      }

       else if(strstr(actuel,"removebp")!=NULL)
      {
          strcpy(historique,actuel);
           /* La boucle se termine si l'utilisateur entre un entier  */
           while(!sscanf(actuel,"removebp %d %d",&x,&y))
           {
           printf("\n Erreur entre removebp x y avec x et y entier ");
           fgets(actuel, 256, stdin);
           sscanf(actuel,"removebp %d %d",&x,&y);
           }
          delbreakpoint(breakpoint,x,y);

      }

    else if(strcmp(actuel,"run")==0)
      {
          strcpy(historique,actuel);
          lancement(colonne,ligne,grille,&i,&j,maPile,breakpoint,&sens,&breakknow,&strmode);
          
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
          
      }

      else if(strcmp(actuel,"")==0)
      {
          if(strcmp(historique,"restart")==0)
      {
          restart(&i,&j,maPile,&strmode,&sens,grille,colonne,ligne,argv);
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
      }
      else if(strcmp(historique,"prec")==0)
      {
          prevn(previous,grille,&i,&j,maPile,1,breakpoint,&breakknow,&strmode,&sens,colonne,ligne);
      }
      else if(strstr(historique,"prec")!=NULL)
      {
           /* La boucle se termine si l'utilisateur entre un entier  */
           while(!sscanf(actuel,"prec %d",&n))
           {
           printf("\n Erreur entre prec unentier ex : prec 2 ");
           fgets(actuel, 256, stdin);
           sscanf(actuel,"prec %d",&n);
           }
           prevn(previous,grille,&i,&j,maPile,n,breakpoint,&breakknow,&strmode,&sens,colonne,ligne);

      }

      else if(strcmp(historique,"step")==0)
      {
          step(colonne,ligne,grille,&i,&j,1,maPile,breakpoint,&sens,&breakknow,&strmode);
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
      }

      else if(strstr(historique,"step")!=NULL)
      {
          sscanf(historique,"step %d",&n);
          step(colonne,ligne,grille,&i,&j,n,maPile,breakpoint,&sens,&breakknow,&strmode);
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
      }
      else if(strcmp(historique,"run")==0)
      {
          lancement(colonne,ligne,grille,&i,&j,maPile,breakpoint,&sens,&breakknow,&strmode);
          empiler2(maPile,grille,previous,i,j,strmode,sens,colonne,ligne,argv);
          
      }

      else if(strstr(historique,"breakpoint")!=NULL)
      {
           /* La boucle se termine si l'utilisateur entre un entier  */
           while(!sscanf(historique,"breakpoint %d %d",&x,&y))
           {
           printf("\n Erreur entre breakpoint x y avec x et y entier ");
           fgets(actuel, 256, stdin);
           sscanf(actuel,"breakpoint %d %d",&x,&y);
           }
          addbreakpoint(breakpoint,x,y);

      }

      else if(strstr(historique,"removebp")!=NULL)
      {
           /* La boucle se termine si l'utilisateur entre un entier  */
           while(!sscanf(historique,"removebp %d %d",&x,&y))
           {
           printf("\n Erreur entre removebp x y avec x et y entier ");
           fgets(actuel, 256, stdin);
           sscanf(actuel,"breakpoint %d %d",&x,&y);
           }
          delbreakpoint(breakpoint,x,y);

      }

      }
      afficher(grille,ligne,colonne,i,j,maPile);
      printf("\n entrer une commande ");
      fgets(actuel, 256, stdin);
      actuel[strlen(actuel)-1]='\0';
  }

  /* On libere la memoire de chaque grille et pile stocke afin d'eviter des fuites memoires on le fait pendant le programme */
 
  for(i=0;i<ligne;i++)
    {
      free(grille[i]);
    }
    free(grille);


  Element *eactuel=previous->premier;
  int r;
  /*Etant donne qu'on avance dans le pile le eactuel vaudra NULL quand il y a aura plus de valeurs possible car la pile a un nombre fini d'element  */
  while(eactuel!=NULL)
  {
    for(r=0;r<ligne;r++)
		{
			free(eactuel->grille[r]);
		}
    	free(eactuel->grille);
      detruirePile(eactuel->pi);
      free(eactuel->pi);
	
		eactuel=eactuel->suivant;
  }

  detruirePile(previous);
  free(previous);
  detruirePile(maPile);
  free(maPile);
  detruirePile(breakpoint);
  
  free(breakpoint);
  free(eactuel);

  

  return 0;
}
