/*!
* \file fonctions.h
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date 29/10/2023
* \brief Fichier d'entetes des focntions
*/


/* Inclusion des entetes des librairies */
#include <stdio.h> 
#include <stdlib.h>
#ifndef FONCTIONS_H 
/*!
* \def FONCTIONS_H
*/
#define FONCTIONS_H 

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
int **allouer(int lignes, int colonnes);

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
void initialiser(int **matrice, int lignes, int colonnes);

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
void afficher(int **matrice, int lignes, int colonnes);

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
int **lectureFichier(int **matrice, char *fichier, int *lignes, int *colonnes, int *nbTour, int *type);

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
int **torique(int **matrice, int lignes, int colonnes);

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
int nbVoisin(int **matrice, int ligne, int colonne, int lignes, int colonnes);

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
void actualiser(int **matrice, int lignes, int colonnes, int type);

/*!
* \fn void liberer(int **matrice, int colonnes) 
* \author Thomas Brasdefer <brasdefert@gmail.com>
* \version 1.0
* \date  29/10/2023
* \brief Libère la mémoire allouée à la matrice
* \param matrice matrice 2D allouée
* \param colonnes nombre de colonne de la matrice
*/
void liberer(int **matrice, int colonnes);

#endif
