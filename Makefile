all:   debo inter
debo : debogueur.o pile.o lancement.o remplissage.o
	gcc -g -Wall -Wextra debogueur.o pile.o lancement.o remplissage.o -o debo
inter : interpreteur.o pile.o lancement.o remplissage.o
	gcc -g -Wall -Wextra interpreteur.o pile.o lancement.o remplissage.o -o inter
pile.o : pile.c pile.h
	gcc -g -Wall -Wextra -c pile.c
lancement.o : lancement.c lancement.h
	gcc -g -Wall -Wextra -c  lancement.c
interpreteur.o : interpreteur.c 
	gcc -g -Wall -Wextra -c interpreteur.c
debogueur.o : debogueur.c
	gcc -g -Wall -Wextra -c debogueur.c
remplissage.o : remplissage.c remplissage.h
	gcc -g -Wall -Wextra -c remplissage.c
