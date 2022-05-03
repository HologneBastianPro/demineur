#ifndef VIEW_STRATEGIE_H
#define VIEW_STRATEGIE_H
#include <stdio.h>
#include <stdbool.h>
#include <modele_strategie.h>
#include <modele_grille.h>

/** @brief Afficher les statistiques
 *
 * Cette fonction permet d'afficher les différentes statistiques issues des résultats des parties jouées avec les différentes
 * stratégies.
 * @param session : session dans laquelle on lance l'ensemble des parties.
 */
void AffichageStatistique(Session session);

#endif