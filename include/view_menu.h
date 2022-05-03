/** @file affichge.h
 *  @brief Librairie d'affichage du demineur
 *
 * Cette librairie fournit l'intégralité des fonctions nécessaires à l'afichage du démineur.
 */

#ifndef VIEW_MENU_H
#define VIEW_MENU_H
#include <stdio.h>
#include <stdbool.h>
#include <modele_partie.h>

/** @brief Afficher le menu de demarrage.
 *
 * Cette fonction permet d'afficher le menu de démarrage.
 * @return: reprensente l'option de partie choisie par l'utilisateur : (1) Jouer (utilisateur), (2) Jouer (ordinateur), (3) Quitter.
 */
Joueur ChoixJoueur();

/** @brief Afficher le sous menu.
 *
 * Cette fonction permet d'afficher le sous menu.
 * @return: reprensente l'action choisie par l'utilisateur : (1) Jouer un coup, (2) Marquer/Démarquer une case, (3) Abandonner.
 */
int SaisieAction();

/** @brief Créer une partie utilisateur
 *
 * Cette fonction permet de créer une partie utilisateur.
 * @return: pointeur de la partie créée.
 */
Partie *CreerPartieUtilisateur();

/** @brief Créer une partie ordinateur
 *
 * Cette fonction permet de créer une partie en mode ordianteur.
 * @return: pointeur de la partie créée.
 */
Partie* CreerPartieOrdinateur();

/** @brief Demande de roujouer
 *
 * Cette fonction permet à l'utilisateur de rejouer une partie ou de quitter.
 * @return: true ou false en fonction du choix.
 */
bool rejouer();

#endif