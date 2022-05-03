/** @file affichge.h
 *  @brief Librairie d'affichage du demineur
 *
 * Cette Librairie fournit l'integralité des fonctions liée à la jouabilité du jeu demineur.
 */
#ifndef PARTIE_H
#define PARTIE_H
#include <stdio.h>
#include <stdbool.h>

#include <modele_strategie.h>

/** @brief Definition du type Partie */
struct Partie
{
    Grille *ptrGrille;
    Strategie strategie;
};
typedef struct Partie Partie;

/** @brief Initialisation d'une partie.
 *
 * Cette fonction permet la création d'une partie avec différents paramètres.
 * Après avoir créé une instance de partie et affecté les différents paramètres, cette fonction fait appel respectivement à :
 *   AllocationGrille(int nbLigne,int nbColonne);
 *   reset(&partie);
 *   PlacerMine(partie.ptrGrille);
 *   CalcVoisinage(partie.ptrGrille);
 *   CalcBombesVoisines(partie.ptrGrille);
 *   DecouvrirCellule(partie.ptrGrille,position.ligne,position.colonne);
 *   VerifierWinLoose(&partie)
 * @param ligne: Nombre de lignes de la grille.
 * @param colonne: Nombre de colonnes de la grille.
 * @param strategie: Spécifie la strategie affectée à la partie.
 * @param nombreMine: Spécifie le nombre de mines à placer dans la grille.
 * @return partie correspondant à la partie créée. 
 */
Partie InitPartie(int ligne, int colonne, Strategie strategie, int nombreMine);

/** @brief Vérifier si la partie est gagnée ou perdue.
 *
 * Cette fonction vérifie si la partie est gagnée ou perdue et change en conséquence les attributs win/loose de la grille.
 * @param partie : pointeur vers la partie dont on veut vérifier si elle est gagnée ou perdue.
 */
void VerifierGagnePerdue(Partie *partie);

/** @brief Remettre à zéro la partie
 *
 * Cette fonction reset les paramètres de la partie.
 * @param partie : pointeur vers la partie dont on reset les paramètres.
 */
void reset(Partie *partie);

//-------------------------------------------

#endif