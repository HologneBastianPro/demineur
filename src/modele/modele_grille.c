#include <stdio.h>
#include <modele_grille.h>
#include <stdlib.h>

bool DansLaGrille(Grille *ptrGrille, int ligne, int colonne)
{
    if (ligne < 0)
        return false;
    else if (colonne < 0)
        return false;
    else if (ligne > ptrGrille->nombreLigne - 1)
        return false;
    else if (colonne > ptrGrille->nombreColonne - 1)
        return false;
    else
        return true;
}

void PlacerMine(Grille *ptrGrille)
{
    int nbLigne = ptrGrille->nombreLigne;
    int nbColonne = ptrGrille->nombreColonne;
    int i = 0;
    int L, C;

    while (i < ptrGrille->nombreMine)
    {
        L = rand() % nbLigne;
        C = rand() % nbColonne;

        if ((!ptrGrille->matrice[L][C].piege) && DansLaGrille(ptrGrille, L, C))
        {
            ptrGrille->matrice[L][C].piege = true;
            i++;
        }
    }
}

void CalcVoisinage(Grille *ptrGrille)
{

    Cellule *cellule;
    for (int ligne = 0; ligne < ptrGrille->nombreLigne; ligne++)
    {
        for (int colonne = 0; colonne < ptrGrille->nombreColonne; colonne++)
        {
            cellule = &(ptrGrille->matrice[ligne][colonne]);

            cellule->voisinage.nombre = 0;
            for (int lignevoisin = (ligne - 1); lignevoisin <= (ligne + 1); lignevoisin++)
            {
                for (int colonnevoisin = (colonne - 1); colonnevoisin <= (colonne + 1); colonnevoisin++)
                {

                    if (DansLaGrille(ptrGrille, lignevoisin, colonnevoisin) && (colonnevoisin != colonne || lignevoisin != ligne))
                    {
                        cellule->voisinage.tab[cellule->voisinage.nombre].ligne = lignevoisin;
                        cellule->voisinage.tab[cellule->voisinage.nombre].colonne = colonnevoisin;
                        cellule->voisinage.nombre++;
                    }
                }
            }
        }
    }
}

void CalcBombesVoisines(Grille *ptrGrille)
{
    Cellule *cellule;
    for (int ligne = 0; ligne < ptrGrille->nombreLigne; ligne++)
    {
        for (int colonne = 0; colonne < ptrGrille->nombreColonne; colonne++)
        {
            cellule = &(ptrGrille->matrice[ligne][colonne]);

            cellule->nombreBombesVoisines = 0;

            // printf("Case concerné : (%d,%d)",ligne,colonne);
            for (int i = 0; i < cellule->voisinage.nombre; i++)
            {
                // printf("Ligne : %d\n",cellule->voisinage.tab[i].ligne);
                //  printf("Colonne : %d\n",cellule->voisinage.tab[i].colonne);
                if (ptrGrille->matrice[cellule->voisinage.tab[i].ligne][cellule->voisinage.tab[i].colonne].piege)
                    cellule->nombreBombesVoisines++;
            }
        }
    }
}

Grille *AllocationGrille(int nbLigne, int nbColonne)
{

    Grille *grille = malloc(sizeof(Grille));

    grille->matrice = malloc((nbLigne) * sizeof(Cellule)); // Création du premier pointeur reprensentant les colonnes

    // Ensuite pour chaque colonnes on creer un pointeur de ligne
    for (int ligne = 0; ligne < nbLigne; ligne++)
    {
        grille->matrice[ligne] = malloc((nbColonne) * sizeof(Cellule));
    }

    return grille;
}

void LibererGrille(Grille *ptrGrille)
{

    int nbLigne = ptrGrille->nombreLigne;
    for (int ligne = 0; ligne < nbLigne; ligne++)
    {
        free(ptrGrille->matrice[ligne]);
    }

    free(ptrGrille->matrice);
    free(ptrGrille);
}

void SetMarqueCellule(Grille *ptrGrille, int ligne, int colonne)
{
    if (ptrGrille->matrice[ligne][colonne].visibilite == MARQUEE)
    {
        ptrGrille->matrice[ligne][colonne].visibilite = CACHEE;
        ptrGrille->compteurMarque = ptrGrille->compteurMarque - 1;
        if (ptrGrille->matrice[ligne][colonne].piege)
        {
            ptrGrille->compteurMarqueBonne = ptrGrille->compteurMarqueBonne - 1;
        }
    }
    else
    {
        ptrGrille->matrice[ligne][colonne].visibilite = MARQUEE;
        ptrGrille->compteurMarque = ptrGrille->compteurMarque + 1;
        if (ptrGrille->matrice[ligne][colonne].piege)
        {
            ptrGrille->compteurMarqueBonne = ptrGrille->compteurMarqueBonne + 1;
        }
    }
}

void DecouvrirCellule(Grille *ptrGrille, int ligne, int colonne)
{

    Cellule *cellule = &(ptrGrille->matrice[ligne][colonne]);
    if (cellule->visibilite != MARQUEE)
    {
        cellule->visibilite = DECOUVERTE;

        if (cellule->nombreBombesVoisines == 0 && !(cellule->piege))
        {
            for (int i = 0; i < cellule->voisinage.nombre; i++)
            {
                if (ptrGrille->matrice[cellule->voisinage.tab[i].ligne][cellule->voisinage.tab[i].colonne].visibilite == CACHEE)
                    DecouvrirCellule(ptrGrille, cellule->voisinage.tab[i].ligne, cellule->voisinage.tab[i].colonne);
            }
        }

        if (cellule->piege)
        {
            ptrGrille->perdu = true;
        }
        else
        {
            ptrGrille->compteurDecouverte = ptrGrille->compteurDecouverte - 1;
        }
    }
}
