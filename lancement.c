#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pile.h"
#include "lancement.h"
#include "remplissage.h"


/*
    Requires: un sens compris entre 0 et 7,i et j deux entiers valides,deux entiers colonne et ligne correspondant au nombre de lignes et de colonne donne par la premiere ligne du fichier .p2d
    assings: Modifie i et j pour qu'on navige dans le tableau comme le programme.p2d le veut afin de ne pas sortir du tableau et eviter les fuites memoires.
    ensures: Que l'on va dans la direction que le fichier.p2d desire

*/
void avancer(int sens,int *i,int *j,int colonne,int ligne)
{
  int testl,testc;
  testl=0;
  testc=0;

  /* Les differents if et else sont la pour verifier si en allant dans la direction qu'on veut on sort du tableau si c'est le cas on modifie i et j en fonction de la
  direction afin de rester dans le tableau  */
  switch(sens)
    {

      /*haut*/
    case 0:
      if(*i-1<0)
    {
      *i=ligne-1;
    }
      else
    {
      *i-=1;
    }
      break;
      /*Bas*/
    case 4:
      if(*i+1>=ligne)
    {
      *i=0;
    }
      else
    {
      *i+=1;
    }
      break;
      /*droite*/
    case 2:
      if(*j+1>=colonne)
    {
      *j=0;
    }
      else
    {
      *j+=1;
    }
      break;
      /*gauche*/
    case 6:
      if(*j-1<0)
    {
      *j=colonne-1;
    }
      else
    {
      *j-=1;
    }
      break;
      /*Diago haut droit*/
    case 1:
    if(*i-1<0)
    {
      testl=1;
      *i=ligne-1;
    }
    if (*j+1>=colonne)
      {
        testc=1;
        *j=0;
      }
    if (*j+1<colonne && testc==0)
    {
      *j+=1;
    }
    if (*i-1>=0 && testl==0)
    {
      *i-=1;
    }
    break;
    /*Diago bas  droit*/
    case 3:
    if(*i+1>=ligne)
    {

      testl=1;
      *i=0;
    }
    if (*j+1>=colonne)
      {
        testc=1;
        *j=0;
      }
    if  (*j+1<colonne && testc==0)
    {

      *j+=1;
    }
    if (*i+1<ligne && testl==0)
      {
      *i+=1;
    }

    break;
    /*Diago haut gauche*/
    case 7:
    if(*i-1<0)
    {
      *i=ligne-1;
      testl=1;
    }
    if (*j-1<0)
      {
        *j=colonne-1;
        testc=1;
      }
    if (*j-1>=0 && testc==0)
    {
      *j-=1;
    }
    if (*i-1>=0 && testl==0)
    {
      *i-=1;
    }
    break;
    case 5:
      /*Diago bas gauche*/
    if(*i+1>=ligne)
    {
      *i=0;
      testl=1;
    }
    if (*j-1<0)
      {
        *j=colonne-1;
        testc=1;
      }
    if (*i+1<ligne && testl==0)
    {
      *i+=1;
    }
    if (*j-1>=0 && testc==0)
    {
      *j-=1;
    }
    break;

    }
}

/*
    Requires: Une pile valide,deux entier lignes et colonne qui sont la taille de la matrice ,
            la matrice grille qui est la matrice ou on a copier le fichier.p2d,i et j sont deux entier pour savoir ou l'on se trouve dans le tableau et faire les differentes action en fonction
             de grille[*i][*j] et sens( compris entre 0 et 7) et une pile breakpoint valide(on empile dans breakpoint avec la fonction (addbreakpoint) et depile avec dell breakpoint.
             et breakdnow qui vaut 0 si (x,y) est pas dans breakpoint et 1 sinon.Et strmode vaut 1 si on rencontre un " et 0 quand on en recontre un autre
    assings: Empiler et depiler des elements dans maPile et afficher des elements et modifie la grille en fonction des instruction donne par le fichier.p2d
    ensures: Si le fichier.p2d a un @ et ne boucle pas il execute les instructions en fonction de la valeur de grille[*i][*j] jusqu'a qu'il arrive a @.Si (i,j) sont dans breakpoint
	alors on sort de la fonction et que breakknow =0.

*/


void lancement(int colonne,int ligne,Matrice grille,int *i,int *j,Pile *maPile,Pile* breakpoint,int *sens,int *breakknow,int *strmode)
{
  int a,b,boucle;
  char carac=0;
  char actuel[256];
  char * endptr;

  /* La boucle se termine si et seulement si le programme .p2d se termine ou que (i,j) sont dans breakpoint et que breakknow vaut zero */
  while(grille[*i][*j]!='@')
    {
	 if(inlist(breakpoint,*i,*j) && *breakknow==0){
		 *breakknow=1;
		 break;
	}
	 else if(*strmode)
	 {    if (grille[*i][*j] == '"')
                *strmode=0;
		  else
	      empiler(maPile,(int)grille[*i][*j]);
	 }
     else if(grille[*i][*j]=='+')
	{
	  empiler(maPile,depiler(maPile)+depiler(maPile));
	}
      else if(grille[*i][*j]=='-')
	{
	  a=depiler(maPile);
	  empiler(maPile,depiler(maPile)-a);
	}
      else if(grille[*i][*j]=='*')
	{
	  empiler(maPile,depiler(maPile)*depiler(maPile));
	}
      else if(grille[*i][*j]==':')
	{
	  a=depiler(maPile);
	  b=depiler(maPile);
	  if(!a)
	    {
	      empiler(maPile,42);
	    }
	  else
	    {
	      empiler(maPile,b/a);
	    }
	}
      else if(grille[*i][*j]=='%')
	{
	  a=depiler(maPile);
	  b=depiler(maPile);
	  if(!a)
	    {
	      empiler(maPile,0xbadc0de);
	    }
	  else
	    {
	      empiler(maPile,b%a);
	    }
	}
      else if(grille[*i][*j]=='!')
	{
	      empiler(maPile,!depiler(maPile));
	}
      else if(grille[*i][*j]=='`')
	{
	  a=depiler(maPile);
	  empiler(maPile,depiler(maPile)>a);
	}
      else if(grille[*i][*j]=='>')
	{
	  *sens=2;
	}
      else if(grille[*i][*j]=='<')
	{
	  *sens=6;
	}
       else if(grille[*i][*j]=='^')
	{
	  *sens=0;
	}
       else if(grille[*i][*j]=='v')
	{
	  *sens=4;
	}
       else if(grille[*i][*j]=='?')
	{
	  
	  *sens=rand()%8;
	}
      else if(grille[*i][*j]=='\'')
	{
	  *sens=depiler(maPile)%8;
	}

      else if(grille[*i][*j]==']')
	{
	  if(!*sens)
	    *sens=7;
	  else
	    *sens-=1;
	}
      else if(grille[*i][*j]=='[')
	{
	  if(*sens==7)
	    *sens=0;
	  else
	    *sens+=1;
	}
      else if(grille[*i][*j]=='_')
	{
	  if(!depiler(maPile))
	    {
	      *sens=2;
	    }
	  else
	    {
	      *sens=6;
	    }
	}
       else if(grille[*i][*j]=='|')
	 {
	  if(!depiler(maPile))
	    {
	      *sens=4;
	    }
	  else
	    {
	      *sens=0;
	    }
	}
       else if(grille[*i][*j]=='/')
	 {
	  if(!depiler(maPile))
	    {
	      *sens=1;
	    }
	  else
	    {
	      *sens=5;
	    }
	}
       else if(grille[*i][*j]=='\\')
	 {

	  if(!depiler(maPile))
	    {
	      *sens=3;
	    }
	  else
	    {
	      *sens=7;
	    }
	}
      else if(grille[*i][*j]=='"')
	{
	  *strmode=1-*strmode;
	}
      else if(grille[*i][*j]=='=')
	{
	a=depiler(maPile);
	empiler(maPile,a);
	empiler(maPile,a);
      }

      else if(grille[*i][*j]=='$')
	{
	a=depiler(maPile);
	b=depiler(maPile);
	empiler(maPile,a);
	empiler(maPile,b);
      }
       else if(grille[*i][*j]==';')
	 {
	depiler(maPile);
      }
      else if(grille[*i][*j]=='.')
	{
	printf("%d ",depiler(maPile));
      }
      else if(grille[*i][*j]==','){
	printf("%c",(char)depiler(maPile)%256);
      }
      else if(grille[*i][*j]=='#'){
	a=depiler(maPile);
	for(boucle=0;boucle<a;boucle++)
	  {
	    avancer(*sens,i,j,colonne,ligne);
	  }
      }
       else if(grille[*i][*j]=='g'){
	a=depiler(maPile);
	b=depiler(maPile);
	if(a<0||b<0||a>=ligne||colonne<=b)
	  {
	    empiler(maPile,0);
	  }
	else
	  {
	    empiler(maPile,(int)grille[a][b]);
	  }

      }
      else if(grille[*i][*j]=='p'){
	a=depiler(maPile);
	b=depiler(maPile);
	if(a<0||b<0||a>=ligne||b>=colonne)
	  {
	    continue;
	  }
	else
	  {
	    grille[a][b]=depiler(maPile)%256;
	  }

      }
      else if(grille[*i][*j]=='&'){
        printf("entrer un entier ");
        fgets(actuel, 256, stdin);
        strtol(actuel, &endptr, 10);
        /*On sort de la boucle quand l'utilisateur a entre un entier */
            while (actuel == endptr)
                {
                    printf("Erreur ,veuillez entrer un entier ");
                    fgets(actuel, 256, stdin);
                    strtol(actuel, &endptr, 10);
                }

            empiler(maPile,strtol(actuel, &endptr, 10));

      }
      else if(grille[*i][*j]=='~'){
	printf("entre un caractere ");
	scanf("%c",&carac);
	empiler(maPile,(int)carac);

      }

      else if (grille[*i][*j]=='0')
	{
	  empiler(maPile,0);
	}
      else if (grille[*i][*j]=='1')
	{
	  empiler(maPile,1);
	}
      else if (grille[*i][*j]=='2')
	{
	  empiler(maPile,2);
	}
      else if (grille[*i][*j]=='3')
	{
	  empiler(maPile,3);
	}
      else if (grille[*i][*j]=='4')
	{
	  empiler(maPile,4);
	}
      else if (grille[*i][*j]=='5')
	{
	  empiler(maPile,5);
	}
      else if (grille[*i][*j]=='6')
	{
	  empiler(maPile,6);
	}
      else if (grille[*i][*j]=='7')
	{
	  empiler(maPile,7);
	}
      else if (grille[*i][*j]=='8')
	{
	  empiler(maPile,8);
	}
      else if (grille[*i][*j]=='9')
	{
	  empiler(maPile,9);
	}
	  *breakknow=0;
      avancer(*sens,i,j,colonne,ligne);
    }
}


/*
    Requires: Une pile valide,deux entier lignes et colonne qui sont la taille de la matrice ,
            la matrice grille qui est la matrice ou on a copier le fichier.p2d,i et j sont deux entier pour savoir ou l'on se trouve dans le tableau et faire les differentes action en fonction
             de grille[*i][*j] et sens(compris entre 0 et 7) et strmode qui vaut 1 ou 0 ainsi que la grille où se trouve le fichier copie p2d

			 colonne et ligne etant le nombre de colonne et de ligne.et argv l'emplacement du fichier
    assings: On vide la pile via la fonction detruirePile et on se remet en haut a gauche du tableau en mettant *i et *j a 0 et on met sens par defaut a 2 et strmode=0 on cree une matrice debut afin
	de modifier notre grille
    ensures: i et j vaut zero , la pile est vide et sens =2 et strmode=0 et la grille est remise a sa valeur de début 

*/
void restart(int *i,int *j,Pile *maPile,int* strmode,int *sens,Matrice grille,int colonne,int ligne,char* argv[]){
	*i=0;
	*j=0;
	detruirePile(maPile);
	*strmode=0;
	*sens=2;
	Matrice debut=remplisage(&colonne,&ligne,argv);
	int r,l;
	for(r=0;r<ligne;r++)
	{
		for(l=0;l<colonne;l++)
	{
		grille[r][l]=debut[r][l];
	}
	}

	for(r=0;r<ligne;r++)
	{
		free(debut[r]);
	}

	free(debut);
    
}

/*
    Requires: Une pile valide,deux entier lignes et colonne qui sont la taille de la matrice ,
            la matrice grille qui est la matrice ou on a copier le fichier.p2d,i et j sont deux entier pour savoir ou l'on se trouve dans le tableau et faire les differentes action en fonction
             de grille[*i][*j] et sens( compris entre 0 et 7) et une pile breakpoint valide(on empile dans breakpoint avec la fonction (addbreakpoint) et depile avec dell breakpoint.
             et breakdnow qui vaut 0 si (x,y) est pas dans breakpoint et 1 sinon.Et strmode vaut 1 si on rencontre un " et 0 quand on en recontre un autre
    assings: Empiler et depiler des elements dans maPile et afficher des elements et modifie la grille en fonction des instruction donne par le fichier.p2d
    ensures: Si le fichier.p2d a un @ et ne boucle pas il execute les instructions en fonction de la valeur de grille[*i][*j] jusqu'a que test=n-1.
    Si (i,j) sont dans breakpoint et que breakknow =0 alors on sort de la fonction.

*/
void step(int colonne,int ligne,Matrice grille , int *i,int *j,int n,Pile* maPile,Pile* breakpoint,int *sens,int *breakknow,int* strmode)
{
  int a,b,boucle;
  char carac=0;
  int test;
  char actuel[256];
  char * endptr;
  for(test=0;test<n;test++)
  {
  if(inlist(breakpoint,*i,*j) && *breakknow==0)
    {
	*breakknow=1;
    break;

	}

	else if(*strmode)
	 {    if (grille[*i][*j] == '"')
                *strmode=0;
		  else
	      empiler(maPile,(int) grille[*i][*j]);
	 }
  else if(grille[*i][*j]=='@')
    {
    break;
	}
  else if(grille[*i][*j]=='+')
	{
	  empiler(maPile,depiler(maPile)+depiler(maPile));
	}
      else if(grille[*i][*j]=='-')
	{
	  a=depiler(maPile);
	  empiler(maPile,depiler(maPile)-a);
	}
      else if(grille[*i][*j]=='*')
	{
	  empiler(maPile,depiler(maPile)*depiler(maPile));
	}
      else if(grille[*i][*j]==':')
	{
	  a=depiler(maPile);
	  b=depiler(maPile);
	  if(!a)
	    {
	      empiler(maPile,42);
	    }
	  else
	    {
	      empiler(maPile,b/a);
	    }
	}
      else if(grille[*i][*j]=='%')
	{
	  a=depiler(maPile);
	  b=depiler(maPile);
	  if(!a)
	    {
	      empiler(maPile,0xbadc0de);
	    }
	  else
	    {
	      empiler(maPile,b%a);
	    }
	}
      else if(grille[*i][*j]=='!')
	{
		empiler(maPile,!depiler(maPile));
	}
      else if(grille[*i][*j]=='`')
	{
	  a=depiler(maPile);
	  empiler(maPile,depiler(maPile)>a);

	}
      else if(grille[*i][*j]=='>')
	{
	  *sens=2;
	}
      else if(grille[*i][*j]=='<')
	{
	  *sens=6;
	}
       else if(grille[*i][*j]=='^')
	{
	  *sens=0;
	}
       else if(grille[*i][*j]=='v')
	{
	  *sens=4;
	}
       else if(grille[*i][*j]=='?')
	{
	  
	  *sens=rand()%8;
	}
      else if(grille[*i][*j]=='\'')
	{
	  *sens=depiler(maPile)%8;
	}

      else if(grille[*i][*j]==']')
	{
	  if(!*sens)
	    *sens=7;
	  else
	    *sens-=1;
	}
      else if(grille[*i][*j]=='[')
	{
	  if(*sens==7)
	    *sens=0;
	  else
	    *sens+=1;
	}
      else if(grille[*i][*j]=='_')
	{
	  if(!depiler(maPile))
	    {
	      *sens=2;
	    }
	  else
	    {
	      *sens=6;
	    }
	}
       else if(grille[*i][*j]=='|')
	 {
	  if(!depiler(maPile))
	    {
	      *sens=4;
	    }
	  else
	    {
	      *sens=0;
	    }
	}
       else if(grille[*i][*j]=='/')
	 {
	  if(!depiler(maPile))
	    {
	      *sens=1;
	    }
	  else
	    {
	      *sens=5;
	    }
	}
       else if(grille[*i][*j]=='\\')
	 {

	  if(!depiler(maPile))
	    {
	      *sens=3;
	    }
	  else
	    {
	      *sens=7;
	    }
	}
      else if(grille[*i][*j]=='"')
	{
	  *strmode=1-*strmode;
	}
      else if(grille[*i][*j]=='=')
	{
	a=depiler(maPile);
	empiler(maPile,a);
	empiler(maPile,a);
      }

      else if(grille[*i][*j]=='$')
	{
	a=depiler(maPile);
	b=depiler(maPile);
	empiler(maPile,a);
	empiler(maPile,b);
      }
       else if(grille[*i][*j]==';')
	 {
	depiler(maPile);
      }
      else if(grille[*i][*j]=='.')
	{
	printf("%d ",depiler(maPile));
      }
      else if(grille[*i][*j]==','){
	printf("%c",(char)depiler(maPile)%256);
      }
      else if(grille[*i][*j]=='#'){
	a=depiler(maPile);
	for(boucle=0;boucle<a;boucle++)
	  {
	    avancer(*sens,i,j,colonne,ligne);
	  }
      }
       else if(grille[*i][*j]=='g'){
	a=depiler(maPile);
	b=depiler(maPile);
	if(a<0||b<0||a>=ligne||colonne<=b)
	  {
	    empiler(maPile,0);
	  }
	else
	  {
	    empiler(maPile,(int)grille[a][b]);
	  }

      }
      else if(grille[*i][*j]=='p'){
	a=depiler(maPile);
	b=depiler(maPile);
	if(a<0||b<0||a>=ligne||b>=colonne)
	  {
	   continue;
	  }
	else
	  {
	    grille[a][b]=depiler(maPile)%256;
	  }

      }
      else if(grille[*i][*j]=='&'){
        printf("entrer un entier ");
        fgets(actuel, 256, stdin);
        strtol(actuel, &endptr, 10);
        /*On sort de la boucle quand l'utilisateur a entre un entier */
            while (actuel == endptr)
                {
                    printf("Erreur ,veuillez entrer un entier ");
                    fgets(actuel, 256, stdin);
                    strtol(actuel, &endptr, 10);
                }

            empiler(maPile,strtol(actuel, &endptr, 10));
      }
      else if(grille[*i][*j]=='~'){
	printf("entre un caractere");
	scanf("%c",&carac);
	empiler(maPile,(int)carac);

      }

      else if (grille[*i][*j]=='0')
	{
	  empiler(maPile,0);
	}
      else if (grille[*i][*j]=='1')
	{
	  empiler(maPile,1);
	}
      else if (grille[*i][*j]=='2')
	{
	  empiler(maPile,2);
	}
      else if (grille[*i][*j]=='3')
	{
	  empiler(maPile,3);
	}
      else if (grille[*i][*j]=='4')
	{
	  empiler(maPile,4);
	}
      else if (grille[*i][*j]=='5')
	{
	  empiler(maPile,5);
	}
      else if (grille[*i][*j]=='6')
	{
	  empiler(maPile,6);
	}
      else if (grille[*i][*j]=='7')
	{
	  empiler(maPile,7);
	}
      else if (grille[*i][*j]=='8')
	{
	  empiler(maPile,8);
	}
      else if (grille[*i][*j]=='9')
	{
	  empiler(maPile,9);
	}

	  *breakknow=0;
      avancer(*sens,i,j,colonne,ligne);
    }
  }



/*
    Requires: Une pile valide qui contient l'historique des matrices et pile utilisee ,la matrice grille qui est la matrice ou on a copier le fichier.p2d,
              i et j sont deux entier pour savoir ou l'on se trouve dans le tableau,n pour savoir le nombre de retour en arriere qu'on veut.
              et une Pile maPile qui sert a l'execution du fichier p2d  valide.
			  Breakpoint pour les points d'arret et breaknow pour eviter de taper deux commande pour sortir du point 'arret
			  colonne et ligne etant le nombre de colonne et de ligne.
    assings: Modifie la grille et la pile maPile
    ensures: On a la grille et maPile qui vaut exactement la meme chose que n operation avant.

*/

void prevn(Pile* previous,Matrice grille,int*i,int*j,Pile*maPile,int n,Pile* breakpoint,int *breakknow,int * strmode,int *sens,int colonne,int ligne)
{
    Element *elementaenlever =previous->premier;
	int k,r,s;
	for(k=0;k<n;k++)
	{
		if(previous->premier!=NULL && elementaenlever->suivant!=NULL)
	{
    for(r=0;r<ligne;r++)
    {
        for(s=0;s<colonne;s++)
        {
            grille[r][s]=elementaenlever->suivant->grille[r][s];
        }
    }
		
		*i=elementaenlever->suivant->x;
		*j=elementaenlever->suivant->y;
		*strmode=elementaenlever->suivant->strmode;
		*sens=elementaenlever->suivant->sens;
		detruirePile(maPile);
		
    /* On fait avancer actuel a chaque fois dans la liste , arrive au dernier element quand il va rechercher le suivant ca sera NULL et donc la boucle s'arette */
	 while(elementaenlever->suivant->pi->premier!=NULL)
    {
        empiler(maPile,depiler(elementaenlever->suivant->pi));
    }
    
	    previous->premier=elementaenlever->suivant;

		for(r=0;r<ligne;r++)
		{
			free(elementaenlever->grille[r]);
		}

    	free(elementaenlever->grille);
		
		detruirePile(elementaenlever->pi);
		free(elementaenlever->pi);
		free(elementaenlever);
	
	}
		if(inlist(breakpoint,previous->premier->x,previous->premier->y))
		{
			*breakknow=1;
			break;
		}
	else{
		break;
		}		
	}

}
