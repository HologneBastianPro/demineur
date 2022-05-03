#include <stdio.h>
#include <view_grille.h>
#include <couleur.h>
#include <stdlib.h>
#include <stdbool.h>

void AfficherGrille(Partie *partie)
{
    printf("\033[H\033[2J");
    printf("      ");
    for (int i = 0; i < partie->ptrGrille->nombreColonne; i++)
    {
        printf("%2d   ", i);
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < partie->ptrGrille->nombreColonne + 1; i++)
    {
        printf("―――――");
    }
    printf("\n");

    for (int ligne = 0; ligne < partie->ptrGrille->nombreLigne; ligne++)
    {
        printf("%2d |  ", ligne);
        for (int colonne = 0; colonne < partie->ptrGrille->nombreColonne; colonne++)
        {
            if (partie->ptrGrille->matrice[ligne][colonne].visibilite == CACHEE)
            {
                printf(" ■   ");
            }
            else if (partie->ptrGrille->matrice[ligne][colonne].visibilite == MARQUEE)
            {
                couleur("31");
                printf(" ⚑   ");
                couleur("0");
            }
            else
            {
                if (partie->ptrGrille->matrice[ligne][colonne].piege)
                {

                    printf("💣   ");
                }
                else
                {

                    switch (partie->ptrGrille->matrice[ligne][colonne].nombreBombesVoisines)
                    {
                    case 0:
                        break;
                    case 1:
                        couleur("34");
                        break;
                    case 2:
                        couleur("32");
                        break;
                    case 3:
                        couleur("33");
                        break;

                    default:
                        couleur("31");
                        break;
                    }

                    printf(" %d   ", partie->ptrGrille->matrice[ligne][colonne].nombreBombesVoisines);
                    couleur("0");
                }
            }
        }
        printf(" |\n");
        if (ligne < partie->ptrGrille->nombreLigne - 1)
        {
            printf("   |  ");
            for (int colonne = 0; colonne < partie->ptrGrille->nombreColonne; colonne++)
            {
                printf("     ");
            }
            printf(" |\n");
        }
    }
    printf("   ");
    for (int i = 0; i < partie->ptrGrille->nombreColonne + 1; i++)
    {
        printf("―――――");
    }
    printf("\n\n");
}

void AfficherGrilleReveler(Partie *ptrPartie)
{
    printf("\033[H\033[2J");
    printf("      ");
    for (int i = 0; i < ptrPartie->ptrGrille->nombreColonne; i++)
    {
        printf("%2d   ", i);
    }
    printf("\n");
    printf("   ");
    for (int i = 0; i < ptrPartie->ptrGrille->nombreColonne + 1; i++)
    {
        printf("―――――");
    }
    printf("\n");

    for (int ligne = 0; ligne < ptrPartie->ptrGrille->nombreLigne; ligne++)
    {
        printf("%2d |  ", ligne);
        for (int colonne = 0; colonne < ptrPartie->ptrGrille->nombreColonne; colonne++)
        {

            if (ptrPartie->ptrGrille->matrice[ligne][colonne].piege)
            {
                printf("💣   ");
            }
            else
            {
                switch (ptrPartie->ptrGrille->matrice[ligne][colonne].nombreBombesVoisines)
                {
                case 0:
                    break;
                case 1:
                    couleur("34");
                    break;
                case 2:
                    couleur("32");
                    break;
                case 3:
                    couleur("33");
                    break;

                default:
                    couleur("31");
                    break;
                }

                printf(" %d   ", ptrPartie->ptrGrille->matrice[ligne][colonne].nombreBombesVoisines);
                couleur("0");
            }
        }
        printf(" |\n");
        if (ligne < ptrPartie->ptrGrille->nombreLigne - 1)
        {
            printf("   |  ");
            for (int colonne = 0; colonne < ptrPartie->ptrGrille->nombreColonne; colonne++)
            {
                printf("     ");
            }
            printf(" |\n");
        }
    }
    printf("   ");
    for (int i = 0; i < ptrPartie->ptrGrille->nombreColonne + 1; i++)
    {
        printf("―――――");
    }
    printf("\n\n");

    if (ptrPartie->ptrGrille->gagne)
    {
      printf("Bravo tu as gagné !!\n");
    }
    else
    {
       printf("Perdu !!\n");
    }
    
}

Position SaisiePosition()
{
    Position position;
    printf("Saisir ligne : ");
    scanf("%d", &position.ligne);
    printf("Saisir colonne : ");
    scanf("%d", &position.colonne);
    return position;
}
