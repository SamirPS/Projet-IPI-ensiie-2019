Sujet disponible ici copier coller du site : http://web4.ensiie.fr/~guillaume.burel/cours/IPI/projet_2019.html

Contexte
Le but de ce projet est d'implanter un interpréteur et un débogueur pour un langage de programmation en deux dimensions appelé prog2d.

Un programme de ce langage est défini par une grille de caractères de largeur et de hauteur données. Un curseur se déplace sur cette grille en fonction des instructions données par le caractère sous le curseur, dans une des huit directions possibles (haut, bas, gauche, droite et les quatre diagonales). Ce curseur possède une inertie : sauf si l'instruction modifie sa direction, il continue à avancer dans la même.

Fonctionnement
Initialement, le curseur est situé à la case en haut à gauche et il se déplace vers la droite.

La grille est torique : si le curseur est sur la dernière colonne et qu'il se déplace à droite, il arrive sur la première colonne, et inversement ; de même, si le curseur est sur la dernière ligne et qu'il se déplace en bas, il arrive sur la première ligne, et inversement.

L'exécution repose sur l'utilisation d'une pile d'entier, qui au départ est vide. Si on essaie de dépiler une valeur sur la pile vide, on retournera 0.

À chaque itération, on exécute l'instruction située sous le curseur, puis on le déplace. La sémantique des instructions est donnée par le tableau suivant :

Instr.	Description
+	Addition : On dépile deux entiers a et b, et on empile a+b
-	Soustraction : On dépile deux entiers a puis b, et on empile b-a
*	Multiplication : On dépile deux entiers a et b, et on empile a×b
:	Division entière : On dépile deux entiers a puis b, et on empile la division euclidienne de b par a. Si a vaut 0, on empile 42.
%	Reste : On dépile deux entiers a puis b, et on empile le reste de la division euclidienne de b par a. Si a vaut 0, on empile 0xbadc0de.
!	Non logique : On dépile un entier. Si c'est 0 on empile 1, sinon on empile 0.
`	Plus grand que : On dépile deux entiers a et b, et on empile 1 si b>a, 0 sinon.
>	Change la direction pour aller à droite.
<	Change la direction pour aller à gauche.
^	Change la direction pour aller en haut.
v	Change la direction pour aller en bas.
?	Choisit une direction au hasard (diagonales comprises)
'	Dépile un entier. Change la direction en fonction du reste de la division euclidienne de cet entier par 8 :
7	0	1
6	 	2
5	4	3
]	Tourne à gauche de 45°.
[	Tourne à droite de 45°.
_	Conditionnelle horizontale : dépile un entier, change la direction vers la droite si c'est 0, vers la gauche sinon.
|	Conditionnelle verticale : dépile un entier, change la direction vers le bas si c'est 0, vers le haut sinon.
/	Conditionnelle diagonale : dépile un entier, change la direction vers le haut et la droite si c'est 0, vers le bas et la gauche sinon.
\	Conditionnelle diagonale : dépile un entier, change la direction vers le bas et la droite si c'est 0, vers le haut et la gauche sinon.
"	Passe en mode chaîne de caractère : empile la valeur ASCII de tous les caractères suivants dans la direction courante jusqu'à atteindre un autre "
=	Duplique le sommet de la pile. Si la pile est vide, empile deux fois l'entier 0.
$	Échange les deux valeurs au sommet de la pile. Si la pile contient un seul élément, empile l'entier 0 au-dessus. Si la pile est vide, empile deux fois l'entier 0.
;	Retire la valeur au sommet de la pile. Sans effet si la pile est déjà vide.
.	Dépile un entier et l'affiche comme un entier.
,	Dépile un entier et affiche le caractère correspond au code ASCII de sa valeur tronquée à l'intervalle [0;255].
#	Pont : dépile un entier n et saute au-dessus des n prochains caractères (c'est-à-dire qu'on avance sans exécuter les instructions auxquelles ils correspondent éventuellement).
g	Get : dépile deux entiers x et y, et empile la valeur (code ASCII) de la grille à la position (x,y). Si la position est en dehors de la grille, empile 0.
p	Put : dépile trois entiers x, y et z, et écrit z (code ASCII de la valeur tronquée entre 0 et 255) dans la grille à la position (x,y). Si la position est en dehors de la grille, ne fait rien.
&	Demande à l'utilisateur d'entrer un entier, et empile cet entier.
~	Demande à l'utilisateur d'entrer un caractère, et empile la valeur ASCII de ce caractère.
@	Fin du programme.
0 à 9	Empile l'entier correspondant.
' '	Espace : Ne fait rien.
Interpréteur
Dans un premier temps, on va écrire un interpréteur, c'est-à-dire un exécutable qui prend en argument le nom d'un fichier contenant un programme prog2d, et qui exécute les instructions du programme jusqu'à atteindre @.

Si le nombre d'argument est plus petit que 1, on affichera un message d'usage de l'exécutable, s'il est plus grand que 1 on ne considérera que le premier.

Un fichier contenant un programme prog2d sera composé d'une première ligne contenant deux entiers correspondant à la largeur w et la hauteur h de la grille, puis h lignes de longueur w qui correspondent au contenu de la grille.

Vous trouverez dans ce répertoire des exemples de fichiers contenant des programmes prog2d. Votre interpréteur devra impérativement tous les exécuter sans erreur. Lors de la correction, des tests avec d'autres programmes seront également effectués.

Débogueur
On écrit maintenant un débogueur, c'est-à-dire un exécutable qui prend en argument le nom d'un fichier contenant un programme prog2d, et qui va ensuite attendre des commandes entrées par l'utilisateur pour avancer dans le programme pas à pas, en affichant l'état du programme avant chaque entrée.

Pour afficher l'état d'un programme, on va d'abord afficher la grille du programme (qui peut être modifiée par les instructions p). On entourera cette grille de repères et d'indicateurs pour indiquer où se trouve le curseur.

On affiche ensuite l'état de la pile, en mettant le sommet à gauche, et en affichant pour chaque valeur, l'entier et entre parenthèse le caractère correspondant à son code ASCII (tronqué à l'intervalle [0;255]).

On affiche enfin la position du curseur sous la forme x: n, y: m.

L'affichage attendu est donc de la forme:

   0    5    10   15   20   25   30   35   40   45   50   55   60   65   70   75   
   |    |    |  v |    |    |    |    |    |    |    |    |    |    |    |    | 
 0-vv  <      <                                                                 
       2                                                                        
      >^v v<                                                                    
    v13v4                                                                    
      >^<  ^<                                                                   
 5->  >?>  ?>5^                                                                 
      >v<  v<                                                                   
    v97v6                                                                    
      >v< v<                                                                    
       8                                                                        
10-    >  >   ^                                                                 
    vv  <      <                                                                
        2                                                                       
       >^v v<                                                                   
     v13v4                                                                   
15-    >^<  ^<                                                                  
    >  >?>  ?>5^                                                                
       >v<  v<     v          ,*25           <<                                 
     v97v6                                ,,                                 
       >v< v<                                ""                                 
20-     8                                    ><                                 
        >  >   ^                             ""v                                
  >  >*=.>0"!rebmun tupnI">=2#2,_;25*,=&=99p`|^<       _0"!niw uoY">=2#2,_;25*,@
         ^         <                         >=99g01-*+^                        

 98 (b) | 101 (e) | 114 (r) | 33 (!) | 0 (�) | 3 () ||

x: 22, y: 13
Dans un premier temps, les commandes que peuvent entrer l'utilisateur sont les suivantes :
step : avance d'une étape, c'est-à-dire exécute l'instruction sous le curseur et déplace ce dernier.
step n : avance de n étape(s), c'est-à-dire répète n fois ce qui est décrit précédemment.
run : continue à exécuter le programme jusqu'à atteindre @.
restart : retourne à l'état initial.
quit : quitte le débogueur.
Si l'utilisateur entre une ligne vide, il faut répéter la dernière commande. (Donc, en entrant step, puis en appuyant plusieurs fois sur entrée, on va avancer étape par étape dans le programme.) Avant chaque demande de commande à l'utilisateur, on affichera l'état du programme comme indiqué ci-dessus.
Extensions
On ajoute les commandes suivantes :
prec : recule d'une étape, c'est-à-dire revient dans l'état précédent la dernière instruction.
prec n : recule de n étape(s).
breakpoint x y : ajoute un point d'arrêt à la position (x,y) ; lors d'une commande ultérieure run, step n ou prec n, force l'arrêt si la position du curseur est dans la liste des points d'arrêts.
removebp x y : retire le point d'arrêt à la position (x,y) ; sans effet si le point d'arrêt à cette position n'existait pas.
