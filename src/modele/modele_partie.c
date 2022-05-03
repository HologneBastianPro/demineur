#include <stdio.h>
#include <modele_partie.h>
#include <modele_strategie.h>
#include <stdlib.h>

void reset(Partie *partie)
{

  for (int ligne = 0; ligne < partie->ptrGrille->nombreLigne; ligne++)
  {
    for (int colonne = 0; colonne < partie->ptrGrille->nombreColonne; colonne++)
    {
      partie->ptrGrille->matrice[ligne][colonne].piege = false;
      partie->ptrGrille->matrice[ligne][colonne].visibilite = CACHEE;
    }
  }
}

Partie InitPartie(int ligne, int colonne, Strategie strategie, int nombreMine)
{

  Partie partie;
  partie.ptrGrille = AllocationGrille(ligne, colonne);
  partie.ptrGrille->nombreLigne = ligne;
  partie.ptrGrille->nombreColonne = colonne;

  reset(&partie);
  partie.ptrGrille->compteurDecouverte = ligne * colonne;
  partie.ptrGrille->compteurMarque = 0;
  partie.ptrGrille->compteurMarqueBonne = 0;
  partie.strategie = strategie;
  partie.ptrGrille->gagne = false;
  partie.ptrGrille->perdu = false;
  partie.ptrGrille->nombreMine = nombreMine;
  PlacerMine(partie.ptrGrille);
  CalcVoisinage(partie.ptrGrille);
  CalcBombesVoisines(partie.ptrGrille);

  // Chaque partie commence avec au moins une case non piégée découverte et de préférence un 0:
  Position position;
  int max = ligne * colonne;
  int cpt = 0;
  bool condition = true;
  do
  {
    position.ligne = rand() % (partie.ptrGrille->nombreLigne - 1);
    position.colonne = rand() % (partie.ptrGrille->nombreColonne - 1);

    /* Pour eviter une boucle infini, on considère que si apres ligne*colonne tour de boucle nous n'avons pas trouver de 0
       la grille est "trop" piégé et nous nous contenterons donc de trouver une case non miné pour débuter la partie*/
    if (cpt > max)
      condition = false;
    cpt++;
  } while (partie.ptrGrille->matrice[position.ligne][position.colonne].piege || (partie.ptrGrille->matrice[position.ligne][position.colonne].nombreBombesVoisines != 0 && condition));

  DecouvrirCellule(partie.ptrGrille, position.ligne, position.colonne);
  VerifierGagnePerdue(&partie);

  if (partie.ptrGrille->gagne || partie.ptrGrille->perdu)
  {
    partie = InitPartie(ligne, colonne, strategie, nombreMine);
  }
  return partie;
}

void VerifierGagnePerdue(Partie *partie)
{

  if (partie->ptrGrille->compteurMarque == partie->ptrGrille->nombreMine)
  {
    if (partie->ptrGrille->compteurMarqueBonne == partie->ptrGrille->nombreMine)
    {
      partie->ptrGrille->gagne = true;
    }
    else
    {
      partie->ptrGrille->perdu = true;
    }
  }
  else
  {
    if (partie->ptrGrille->compteurDecouverte == partie->ptrGrille->nombreMine)
    {
      partie->ptrGrille->gagne = true;
    }
  }
}
