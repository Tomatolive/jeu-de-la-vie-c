/*!
* \file fonctions.c
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date 29/10/2023
* \brief Fichier de corps des fonctions
*/


/* Inclusion des entetes des librairies */
#include "fonctions.h" 
#include <stdio.h>
#include <stdlib.h>

/*!
* \fn int **allouer(int lignes, int colonnes) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Fonction qui alloue de la mémoire à une matrice 2D
* \param lignes nombre de ligne de la matrice
* \param colonnes nombre de colonne de la matrice
* \return matrice allouée
*/
int **allouer(int lignes, int colonnes) {
    /* Itérateur */
    int i;
    /* Allocation de la mémoire */
    int **matrice = (int**)malloc(lignes * sizeof(int*));
    for(i = 0; i < colonnes; i++) {
        /* Allocation de la mémoire */
        matrice[i] = (int*)malloc(colonnes * sizeof(int));
    }
    return matrice;
}

/*!
* \fn void initialiser(int **matrice, int lignes, int colonnes)  
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Initialise à 0 les cases de la matrice
* \param matrice matrice 2D allouée
* \param lignes nombre de ligne de la matrice
* \param colonnes nombre de colonne de la matrice
*/
void initialiser(int **matrice, int lignes, int colonnes) {
    /* Itérateurs */
    int i, j;
    for(i = 0; i < lignes; i++) {
        for(j = 0; j < colonnes; j++) {
            /* On initialise la matrice à 0 */
            matrice[i][j] = 0;
        }
    }
}

/*!
* \fn void afficher(int **matrice, int lignes, int colonnes) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Affiche la matrice
* \param matrice matrice 2D allouée
* \param lignes nombre de ligne de la matrice
* \param colonnes nombre de colonne de la matrice
*/
void afficher(int **matrice, int lignes, int colonnes) {
    /* Itérateurs */
    int i, j;
    for(i = 1; i < lignes - 1; i++) {
        for(j = 1; j < colonnes - 1; j++) {
            /* Si la case de coordonnées i et j vaut 1, on affiche un carré noir, un carré blanc sinon */
            (matrice[i][j] == 1) ? (printf("\033[0;37m ■")) : (printf("\033[0;30m ■"));
        }
        printf("\n");
    }
}

/*!
* \fn int **lectureFichier(int **matrice, char *fichier, int *lignes, int *colonnes, int *nbTour, int *type) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Initialise la matrice et les différents paramétrage du jeu contenus dans le fichier texte
* \param matrice matrice 2D allouée et initialisée à 0
* \param fichier nom ou adresse du fichier contenant le paramétrage du jeu
* \param lignes nombre de ligne de la matrice
* \param colonnes nombre de colonne de la matrice
* \param nbTour nombre de tour effectué par le jeu
* \param type différencie le type entre matrice simple et matrice torique
* \return matrice initialisée prête pour le jeu
*/
int **lectureFichier(int **matrice, char *fichier, int *lignes, int *colonnes, int *nbTour, int *type) {
    /* Itérateurs */
    int i, j;
    /* Ouverture du fichier en mode lecture */
    FILE *fp = fopen(fichier, "r");
    /* On récupère les nombres de ligne et de colonne */
    fscanf(fp, "%d %d", lignes, colonnes);
    if (lignes <= 0 || colonnes <= 0) {
        printf("Les nombres de ligne et de colonne ne peuvent être ni nuls ni négatifs\n");
        exit(1);
    }
    /* On incrémente les nombres de ligne et de colonne par 2 afin de pouvoir entourer la matrice de 0 (nécessaire pour la matrice torique) */
    *lignes += 2;
    *colonnes += 2;
    /* On alloue la matrice*/
    matrice = allouer(*lignes, *colonnes);
    /* On initialise la matrice à 0 */
    initialiser(matrice, *lignes, *colonnes);
    /* Les boucles ne vont parcourir que la matrice "visible" (i.e. sans le contour de 0 supplémentaire) */
    for(i=1; i < *lignes-1; i++) {
        for(j=1; j < *colonnes-1; j++) {
            /* On récupère les valeurs et on les place dans la matrice */
            fscanf(fp, "%d", &matrice[i][j]);
        }
    }
    /* On récupère le nombre de tour à effectuer */
    fscanf(fp, "%d", nbTour);
    /* On récupère la valeur qui va nous donner une matrice simple ou torique */
    fscanf(fp,"%d", type);
    /* On referme le fichier */
    fclose(fp);
    return(matrice);
}

/*!
* \fn int **torique(int **matrice, int lignes, int colonnes) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Ajuste la matrice pour qu'elle devienne une matrice torique
* \param matrice matrice 2D allouée
* \param lignes nombre de ligne de la matrice
* \param colonnes nombre de colonne de la matrice
* \return matrice torique
*/
int **torique(int **matrice, int lignes, int colonnes) {
    /* Itérateurs */
    int i, j;
    /* On place la dernière ligne de la matrice "visible" dans la ligne tout à fait en haut */
    for(j = 0; j < colonnes; j++) {
        matrice[0][j]= matrice[lignes - 2][j];
    }
    /* On place la dernière colonne de la matrice "visible" dans la colonne tout à fait à gauche */
    for(i = 0; i < lignes; i++) {
        matrice[i][0]= matrice[i][colonnes - 2];
    }
    /* On place la première ligne de la matrice "visible" dans la ligne tout à fait en bas */
    for(j = 0; j < colonnes; j++) {
        matrice[lignes - 1][j]= matrice[1][j];
    }
    /* On place la première colonne de la matrice "visible" dans la colonne tout à fait à droite */
    for(i = 0; i < lignes; i++) {
        matrice[i][colonnes - 1]= matrice[i][1];
    }
    return(matrice);
}

/*!
* \fn int nbVoisin(int **matrice, int ligne, int colonne, int lignes, int colonnes) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Compte le nombre de voisin d'une cellule
* \param matrice matrice 2D allouée
* \param ligne ligne de la cellule
* \param colonne colonne de la cellule
* \param lignes nombre de ligne de la matrice
* \param colonnes nombre de colonne de la matrice
* \return nombre de voisin
*/
int nbVoisin(int **matrice, int ligne, int colonne, int lignes, int colonnes) {
    /* itérateurs */
    int i, j;
    /* Variable qui compte le nombre de voisin, initialisée à -1 si la cellule qui nous intéresse est vivante, 0 si elle est morte */
    int voisin = -matrice[ligne][colonne];
    /* Valeur de départ de i, valant -1 s'il existe une case en haut de la cellule, 0 sinon */
    int const a = (ligne - 1 >= 0) ? -1 : 0;
    /* Valeur limite de i, valant 2 s'il existe une case en bas de la cellule, 1 sinon */
    int const b = (ligne + 1 < lignes) ? 2 : 1;
    /* Valeur de départ de j, valant -1 s'il existe une case à gauche de la cellule, 0 sinon */
    int const c = (colonne - 1 >= 0) ? -1 : 0;
    /* Valeur limite de j, valant 2 s'il existe une case à droite de la cellule, 1 sinon */
    int const d = (colonne + 1 < colonnes) ? 2 : 1;

    for(i = a; i < b; i++) {
        for(j = c; j < d; j++) {
            if(matrice[ligne + i][colonne + j] == 1) {
                voisin++;
            }
        }
    }
    return(voisin);
}

/*!
* \fn void actualiser(int **matrice, int lignes, int colonnes, int type) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Actualise le jeu, en mettant à jour l'état des cellules
* \param matrice matrice 2D allouée
* \param lignes nombre de ligne de la matrice
* \param colonnes nombre de colonne de la matrice
* \param type différencie le type entre matrice simple et matrice torique
*/
void actualiser(int **matrice, int lignes, int colonnes, int type) {
    /* Itérateurs */
    int i, j;
    /* Nombre de voisin d'une cellule */
    int nb;
    /* Matrice temporaire, servant à stocker les états actualisés des cellules */
    int **matriceTemp;
    /* On alloue la matrice temporaire */
    matriceTemp = allouer(lignes, colonnes);
    /* On initialise la matrice temporaire à 0 */
    initialiser(matriceTemp, lignes, colonnes);
    /* Les boucles vont parcourir toutes cases "visibles" */
    for(i = 1; i < lignes - 1; i++) {
        for(j = 1; j < colonnes - 1; j++) {
            nb = nbVoisin(matrice, i, j, lignes, colonnes);
            if(matrice[i][j] == 1) {
                /* Si la cellule est vivante et qu'elle a 2 ou 3 voisins, alors elle reste vivante, sinon elle meurt */
                matriceTemp[i][j] = (nb == 2 || nb ==3) ? 1 : 0;
            } else {
                /* Si la cellule est morte et qu'elle a 3 voisins, alors elle naît, sinon elle reste morte */
                matriceTemp[i][j] = (nb == 3) ? 1 : 0;
            }
        }
    }
    /* On place toutes les valeurs "visibles" de la matrice temporaire dans la matrice */
    for(i = 1; i < lignes - 1; i++) {
        for(j = 1; j <colonnes - 1; j++) {
            matrice[i][j] = matriceTemp[i][j];
        }
    }
    /* Si la matrice est torique */
    if (type == 1) {
        matrice = torique(matrice, lignes, colonnes);
    }
    /* On libère la matrice temporaire */
    liberer(matriceTemp, colonnes);
}

/*!
* \fn void liberer(int **matrice, int colonnes) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Libère la mémoire allouée à la matrice
* \param matrice matrice 2D allouée
* \param colonnes nombre de colonne de la matrice
*/
void liberer(int **matrice, int colonnes) {
    /* Itérateur */
    int i;
    /* On libère la mémoire */
    for(i = 0; i < colonnes; i++) {
        free(matrice[i]);
    }
    /* On libère la mémoire */
    free(matrice);
    matrice = NULL;
}