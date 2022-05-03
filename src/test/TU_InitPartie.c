#include <stdio.h>

#include "view_menu.h"
#include "view_strategie.h"
#include "view_grille.h"
#include <stdlib.h>

int main() {
    Partie partie = InitPartie(10,10,STRATEGIE1,5);
    AfficherGrilleReveler(&partie);
    printf("Ce test verifie l'initialisation d'une partie\n");
}
