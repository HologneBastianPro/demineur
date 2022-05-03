#ifndef MODELE_STRATEGIE_H
#define MODELE_STRATEGIE_H
#include <stdio.h>
#include <stdbool.h>

#include <modele_grille.h>

// ---------------- Enumerations ----------------

/** @brief Enum représentant les différentes strategies */
enum Strategie
{
    STRATEGIE1 = 1,
    STRATEGIE2,
    STRATEGIE3,
    STRATEGIE_COUNT,
    FIRST_STRATEGIE = STRATEGIE1
};
typedef enum Strategie Strategie;


// ---------------- Structures ----------------

/** @brief Definition du type session : entité supérieure à la partie qui contient les x parties lancées en mode parties ordianteurs*/
struct Session
{
    int stats[STRATEGIE_COUNT];
    int nombrePartie;
};
typedef struct Session Session;

/** @brief Calculer un coup
 *
 * Cette fonction calcule un coup en fonction de la strategie affectée à la partie et renvoie un cellule potentiellement intéréssante à decouvrir
 * ainsi qu'une pondération de fiabilité.
 * @param ptrGrille : pointeur vers la grille dont on veut obtenir un conseil.
 * @return cellule conseilée et set sa pondération.
 */
Position CalcCoup(Grille *ptrGrille, Strategie strategie);

/** @brief Utiliser la stratégie 1
 *
 * Cette fonction calcule un coup en fonction de la strategie 1 et renvoie un cellule potentiellement intéréssante à decouvrir
 * ainsi qu'une pondération de fiabilité.
 * @param ptrGrille : pointeur vers la grille dont on veut obtenir un conseil.
 * @return cellule conseilée et set sa pondération.
 */
Position Strategie1(Grille *ptrGrille);

/** @brief Utiliser la stratégie 2 (Aléatoire)
 *
 * Cette fonction calcule un coup en fonction de la strategie 2 et renvoie un cellule potentiellement intéréssante à decouvrir
 * ainsi qu'une pondération de fiabilité.
 * @param ptrGrille : pointeur vers la grille dont on veut obtenir un conseil.
 * @return cellule conseilée et set sa pondération.
 */
Position Strategie2(Grille *ptrGrille);

/** @brief Utiliser la stratégie 3
 *
 * Cette fonction calcule un coup en fonction de la strategie 3 et renvoie un cellule potentiellement intéréssante à decouvrir
 * ainsi qu'une pondération de fiabilité.
 * @param ptrGrille : pointeur vers la grille dont on veut obtenir un conseil.
 * @return cellule conseilée et set sa pondération.
 */
Position Strategie3(Grille *ptrGrille);

/** @brief Créer une "session" 
 *
 * Cette fonction créer une "session" qui permet à l'ordinateur de jouer plusieurs parties.
 * @return cellule conseilée et set sa pondération.
 */
Session InitSession();

#endif