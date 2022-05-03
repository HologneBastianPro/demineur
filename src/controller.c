#include <stdio.h>

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "view_menu.h"
#include "view_strategie.h"
#include "view_grille.h"

int main()
{
  srand(time(NULL));
  Session session = InitSession();
  Partie *ptrPartie;
  Partie *ptrPartieModele; // Partie servant de modèle pour les joueurs type ordinateur.
  Position position;
  Joueur joueur = ChoixJoueur();

  switch (joueur)
  {
  case UTILISATEUR:
    do
    {
      // Creation de la partie
      ptrPartie = CreerPartieUtilisateur();

      while (ptrPartie->ptrGrille->gagne == false && ptrPartie->ptrGrille->perdu == false)
      {
        // Affichage de la grille
        AfficherGrille(ptrPartie);
        // Calcule du coup conseillé
        position = CalcCoup(ptrPartie->ptrGrille, ptrPartie->strategie);
        if (ptrPartie->strategie != 4)
        {
          printf("Coup conseillé : (%d,%d)/%f\n", position.ligne, position.colonne, position.ponderation);
        }

        // Saisie de l'action
        Action action;
        action = SaisieAction();

        switch (action)
        {
        case DECOUVRIR:
          AfficherGrille(ptrPartie);
          // Traitement de l'action DECOUVRIR
          position = SaisiePosition();
          if (DansLaGrille(ptrPartie->ptrGrille, position.ligne, position.colonne))
          {
            DecouvrirCellule(ptrPartie->ptrGrille, position.ligne, position.colonne);
          }
          break;

        case MARQUER:
          AfficherGrille(ptrPartie);
          // Traitement de l'action MARQUER
          position = SaisiePosition();
          if (DansLaGrille(ptrPartie->ptrGrille, position.ligne, position.colonne))
          {
            SetMarqueCellule(ptrPartie->ptrGrille, position.ligne, position.colonne);
          }
          break;
        
        case ABANDONNER:
          ptrPartie->ptrGrille->perdu=true;
          break;

        default:
          break;
        }
        // Test partie gagnée/perdue
        VerifierGagnePerdue(ptrPartie);
      }
      AfficherGrilleReveler(ptrPartie);
      LibererGrille(ptrPartie->ptrGrille);
      free(ptrPartie);

    } while (rejouer());
    break;

  case ORDINATEUR:

    // session.nombrePartie = CreerPartieOrdinateur();
    ptrPartieModele = CreerPartieOrdinateur(&session);

    for (int strategie = FIRST_STRATEGIE; strategie < STRATEGIE_COUNT; strategie++)
    {
      // Pour chaque strategie je joue nombrePartie partie
      for (int i = 0; i < session.nombrePartie; i++)
      {
        ptrPartie = (Partie *)malloc(sizeof(Partie));
        *ptrPartie = InitPartie(ptrPartieModele->ptrGrille->nombreLigne, ptrPartieModele->ptrGrille->nombreColonne, strategie, ptrPartieModele->ptrGrille->nombreMine);

        while (ptrPartie->ptrGrille->gagne == false && ptrPartie->ptrGrille->perdu == false)
        {
          position = CalcCoup(ptrPartie->ptrGrille, ptrPartie->strategie);
          DecouvrirCellule(ptrPartie->ptrGrille, position.ligne, position.colonne);
          VerifierGagnePerdue(ptrPartie);
        }
        if (ptrPartie->ptrGrille->gagne)
        {
          session.stats[strategie] += 1;
        }
        LibererGrille(ptrPartie->ptrGrille);
        free(ptrPartie);
      }
    }
    free(ptrPartieModele); // Désallocation de la partie servant de modèle.
    AffichageStatistique(session);
    break;

  default:
    break;
  }
}
