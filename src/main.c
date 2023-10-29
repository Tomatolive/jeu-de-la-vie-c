/*!
* \file main.c
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date 29/10/2023
* \brief Fichier principale
*/

/*!
* \mainpage Accueil
* \section un Introduction
* Ce programme C est une reproduction du jeu de la vie.\n
* Le programme ne fonctionne que dans un terminal, et nécessite d'utiliser des fichiers textes pour le configurer.
*
* \section deux Structure de fichier
* Le projet comporte plusieurs répertoires : un répertoire source, un répertoire pour l'exécutable et un répertoire pour la documentation doxygen.\n
* Le répertoire source contient les fichiers sources du programme, ce sont ces fichiers qu'il faudra compiler si l'exécutable est supprimé.\n
* Par défaut, le répertoire bin contient déjà l'exécutable.\n
* 
* \section trois Compilation du programme
* Si, pour une quelconque raison, vous devez recompiler le programme, voici un makefile simple qui vous le permettra :
* \verbatim
srcdir = ./src/
bindir = ./bin/
SRC = $(wildcard $(srcdir)*.c)
OBJ = $(subst $(srcdir),$(bindir),$(SRC:.c=.o))
PROG = $(bindir)exe
CC = gcc -Wall -g

all : $(PROG)
$(PROG) : $(OBJ)
	@echo 'Compilation de l executable'
	$(CC) $^ -o $@ -lm
./bin/%.o : ./src/%.c
	@echo 'Compilation des fichiers objets'
	$(CC) -c $^ -o $@ -lm
 \endverbatim
* À noter que ce makefile doit se trouver dans le répertoire parent de src et bin.\n
* De même, faites bien attention à bien placer des tabulations là où elles sont nécessaires, makefile étant très sensible aux espaces. Si le message d'erreur "missing separator. Stop" apparaît, replacer toutes les tabulations manuellement.
* 
* \section quatre Structure du fichier de configuration
* Le fichier doit s'ouvrir sur deux nombres, représentant la longueur et la largueur de la matrice.\n
* Ensuite se trouve les valeurs de la matrice.\n
* Puis nous trouvons un nombre répresentant les tours à effectuer.\n
* Enfin se trouve soit 0 soit 1, nombe qui demande au programme d'utiliser une matrice simple ou une matrice torique (respectivement).\n
* Voici un exemple : 
* \verbatim
13 13
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0
100
0
 \endverbatim
* Attention : un fichier mal structuré ou mal configuré fera planter le programme.
*
* \section cinq Execution du programme
* Le programme s'execute en utilisant en argument le nom (ne pas oublier l'extension) ou l'adresse (relative ou absolue) du programme.\n
* Quelques exemples (avec le fichier placé dans le répertoire parent et l'exécutable dans le répertoire bin):
* \verbatim
- Depuis le répertoire parent : ./bin/exe fichier.txt
- Depuis le répertoire bin : ./exe ../fichier.txt
 \endverbatim
*/


/* Inclusion des entetes des librairies */
#include "fonctions.h" 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

/*!
* \fn int main(int argc, char** argv) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date 29/10/2023
* \brief Fonction principale du projet
* \param argc : Nombre d'arguments
* \param argv : Tableau des arguments
* \return 0   : Si le programme s'est terminé normalement
*/
int main(int argc, char** argv) { 
	/* Si le programme est appelé avec au moins un argument */
	if(argc > 1) {
		/* Si le fichier existe */
		if(fopen(argv[1], "r") != NULL) {
			/* Itérateur */
			int i;
			/* On déclare la matrice, son nombre de ligne, de colonne, le nombre de tour à effectuer et le type de matrice */
			int **matrice = NULL, lignes, colonnes, nbTour, type;
			/* Initialisation de la matrice et des paramètres */
			matrice = lectureFichier(matrice, argv[1], &lignes, &colonnes, &nbTour, &type);
			/* Tours de jeu */
			for(i = 0; i < nbTour; i++) {
				/* On attend le temps indiqué en microsecondes */
				usleep(100000);
				/* On efface le terminal */
				system("clear");
				printf("                             \033[0;37m-------------------------- Tour n°%d--------------------------\n", i+1);
				/* On affiche la matrice */
				afficher(matrice, lignes, colonnes);
				/* On actualise la matrices*/
				actualiser(matrice, lignes, colonnes, type);
			}
			/* On libère la matrice */
			liberer(matrice, colonnes);
			return(EXIT_SUCCESS);
		} else {
			printf("Erreur : le fichier n'exite pas à cette adresse.\nVeuillez consulter la documentation pour plus d'aide.\n");
			return(EXIT_FAILURE);
		}
	} else {
		printf("Erreur : Trop peu d'argument.\nVeuillez consulter la documentation pour plus d'aide.\n");
		return(EXIT_FAILURE);
	}
}
