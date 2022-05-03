#ifndef MODELE_GRILLE_H
#define MODELE_GRILLE_H
#include <stdio.h>
#include <stdbool.h>

/** @brief*/
enum Joueur
{
    UTILISATEUR = 1,
    ORDINATEUR
};
typedef enum Joueur Joueur;

/** @brief*/
enum Action
{
    DECOUVRIR = 1,
    MARQUER,
    ABANDONNER
};
typedef enum Action Action;

/** @brief Definition du type Position  */
struct Position
{
    int ligne;
    int colonne;
    float ponderation;
};
typedef struct Position Position;

/** @brief Definition du type Voisinage  */
struct Voisinage
{
    int nombre;
    Position tab[8]; // Tableau de pointeur sur cellules voisines /// ????????
};
typedef struct Voisinage Voisinage;

/** @brief Enum représentant les différentes visibilités d'une cellule : CACHEE/DECOUVERTE/MARQUEE*/
enum Visibilite
{
    CACHEE,
    DECOUVERTE,
    MARQUEE
};
typedef enum Visibilite Visibilite;

/** @brief Definition du type Cellule */
struct Cellule
{
    bool piege;
    Visibilite visibilite;
    int nombreBombesVoisines;
    Voisinage voisinage;
};
typedef struct Cellule Cellule;

struct Grille
{
    Cellule **matrice;
    int nombreLigne;
    int nombreColonne;
    int nombreMine;

    bool gagne;
    bool perdu;

    int compteurMarque;
    int compteurMarqueBonne;
    int compteurDecouverte;
};
typedef struct Grille Grille;

/** @brief Placer les mines dans la grille.
 *
 * Cette fonction place le nombre de mines demandés aléatoirement dans la grille.
 * @param ptrGrille : pointeur vers la grile dans laquelle on veut placer les mines.
 */
void PlacerMine(Grille *ptrGrille);

/** @brief Calculer le voisinage des cases.
 *
 * Cette fonction permet de calculer le voisinage de chaque case. Ce dernier se compose d'un nombre de voisins et d'un tableau de position de ses voisins.
 * @param ptrGrille : pointeur vers la grille dans laquelle on veut placer les mines.
 */
void CalcVoisinage(Grille *ptrGrille);

/** @brief Calculer le nombre de bombes voisines.
 *
 * Cette fonction permet de calculer le nombre de bombes voisines de chaque cellule.
 * @param ptrGrille : pointeur vers la grille dans laquelle il faut calculer les bombes voisines des cases.
 */
void CalcBombesVoisines(Grille *ptrGrille);

/** @brief Allouer la grille.
 *
 * Cette fonction permet d'allouer la mémoire pour chaque case de la grille.
 * @param ptrGrille : pointeur vers la grille dans laquelle on veut allouer la mémoire de chaque case.
 */
Grille *AllocationGrille(int nbLigne, int nbColonne);

/** @brief Désallouer la grille.
 *
 * Cette fonction permet de désallouer la mémoire pour chaque case de la grille.
 * @param ptrGrille : pointeur vers la grille dans laquelle on veut désallouer la mémoire de chaque case.
 */
void LibererGrille(Grille *ptrGrile);

bool DansLaGrille(Grille *ptrGrille, int ligne, int colonne);

/** @brief Marquer une cellule.
 *
 * Cette fonction permet de marquer une cellule = change sa visibilité en MARQUEE.
 * Elle gère également les compteurs suivant : compteurMarqueBonne et compteurMarque.
 * @param ligne : Coordonnée ligne de la cellule à marquer.
 * @param colonne : Coordonnée colonne de la cellule à découvrir.
 * @param ptrGrille : pointeur vers la grille dans laquelle on veut decouvrir une case.
 */
void SetMarqueCellule(Grille *ptrGrille, int ligne, int colonne);

/** @brief Découvrir une cellule.
 *
 * Cette fonction permet de decouvrir une cellule = change sa visibilité en DECOUVERTE et verifie si cette dernière est piégée.
 * Elle gère également le compteur : compteurDecouverte.
 * @param ligne : Coordonnée ligne de la cellule à découvrir.
 * @param colonne : Coordonnée colonne de la cellule à découvrir.
 * @param partie : pointeur vers la partie dans laquelle on veut decouvrir une case.
 */
void DecouvrirCellule(Grille *ptrGrille, int ligne, int colonne);

#endif