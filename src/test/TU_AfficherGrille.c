#include <stdio.h>

#include "view_menu.h"
#include "view_strategie.h"
#include "view_grille.h"
#include <stdlib.h>

int main() {
    Partie partie = InitPartie(10,10,STRATEGIE1,5);
    AfficherGrille(&partie);
    printf("Ce test verifie l'affichage d'une partie avec une grille 10x10 et 5 bombes\n");
}
