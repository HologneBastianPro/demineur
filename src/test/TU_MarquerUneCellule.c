#include <stdio.h>

#include "view_menu.h"
#include "view_strategie.h"
#include "view_grille.h"
#include <stdlib.h>

int main() {
    Partie partie = InitPartie(10,10,STRATEGIE1,5);
    SetMarqueCellule(partie.ptrGrille, 4, 7);
    AfficherGrille(&partie);
    printf("Ce test verifie le marquage d'une case en ligne : 4 et colonne 7 \n");
}
