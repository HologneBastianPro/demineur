/** @file affichge.h
 *  @brief Librairie d'affichage du demineur
 *
 * Cette librairie fournit l'intégralité des fonctions nécessaires à l'afichage du démineur.
 */

#ifndef VIEW_GRILLE_H
#define VIEW_GRILLE_H
#include <stdio.h>
#include <stdbool.h>
#include <modele_partie.h>

/** @brief Afficher la grille
 *
 * Cette fonction affiche la grille de la partie passée en paramètre : ■ pour une case cachée, 
 * ⚑ pour une case marquée, B pour une case piégée, un entier correspondant au nombre de bombes voisines pour les cases découvertes.
 * @param partie : pointeur vers la partie dont on veux afficher la grille.
 */
void AfficherGrille(Partie *partie);

/** @brief Afficher la grille entièrement révélée
 *
 * Cette fonction affiche la grille de la partie passée en paramètre en considérent que toutes les cases sont dévoilées :
 * ⚑ pour une case marquée, B pour une case piégée, un entier correspondant au nombre de bombes voisines pour les autres cases.
 * @param partie : pointeur vers la partie dont on veut afficher la grille en mode test.
 */
void AfficherGrilleReveler(Partie *partie);

/** @brief Saisir une position
 *
 * Cette fonction permet à l'utilisateur d'entrer une position à jouer.
 * @return une position
 */
Position SaisiePosition();

#endif