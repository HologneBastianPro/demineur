#include <stdio.h>
#include <modele_strategie.h>
#include <stdlib.h>

Position Strategie1(Grille *ptrGrille)
{
  // Strategie de ponderation des voisinages (x8)
  Position position;
  Cellule *cellule;
  Cellule *tmp;
  float pondMin = 1;
  float pondTmp;
  float cptCachee;

  int l=0, c=0;
  do
  {
    l = rand() % (ptrGrille->nombreLigne); 
    c = rand() % (ptrGrille->nombreColonne); 
  } while (ptrGrille->matrice[l][c].visibilite != CACHEE);
  

  for (int ligne = 0; ligne < ptrGrille->nombreLigne; ligne++)
  {
    for (int colonne = 0; colonne < ptrGrille->nombreColonne; colonne++)
    {
      pondTmp = 1;
      tmp = &(ptrGrille->matrice[ligne][colonne]);
      cptCachee = 0;

      if ((tmp->visibilite == DECOUVERTE) && (tmp->nombreBombesVoisines != 0))
      {
        for (int i = 0; i < tmp->voisinage.nombre; i++)
        {
          if (ptrGrille->matrice[tmp->voisinage.tab[i].ligne][tmp->voisinage.tab[i].colonne].visibilite == CACHEE)
          {
            cptCachee++;
          }
        }

        if (cptCachee != 0)
        {
          pondTmp = tmp->nombreBombesVoisines / cptCachee;
        }

        if (pondTmp < pondMin)
        {
          pondMin = pondTmp;
          l = ligne;
          c = colonne;
        }
      }
    }
  }

  // ici dans cellule j'ai l'heureuse élu maintenant je renvois le 1er de ses voisins CACHEE
  cellule = &(ptrGrille->matrice[l][c]);

  int i = 0;
  while (ptrGrille->matrice[cellule->voisinage.tab[i].ligne][cellule->voisinage.tab[i].colonne].visibilite != CACHEE)
  {
    i++;
  }

  position.ligne = cellule->voisinage.tab[i].ligne;
  position.colonne = cellule->voisinage.tab[i].colonne;
  position.ponderation = 1 - pondMin; // passage de pourcentage piegé à pourcentage pas piégé

  return position;
}

Position Strategie2(Grille *ptrGrille)
{
  // Strategie Aleatoire : Propose une case de façon parmis les cases cachée
  Position position;
  do
  {
    position.ligne = rand() % (ptrGrille->nombreLigne); 
    position.colonne = rand() % (ptrGrille->nombreColonne); 
  } while (ptrGrille->matrice[position.ligne][position.colonne].visibilite != CACHEE);
  position.ponderation = 0;
  return position;
}

Position Strategie3(Grille *ptrGrille)
{
  // Strategie de ponderation des voisinages (x8)
  Position position;
  Cellule *tmp;
  float pondMin = 1;
  int cptCachee;
  int l, c;
  int changement = 0;
  int cptMarqueVoisine = 0;
  int tour = 0;

  do
  {
    tour += 1;
    for (int ligne = 0; ligne < ptrGrille->nombreLigne; ligne++)
    {
      for (int colonne = 0; colonne < ptrGrille->nombreColonne; colonne++)
      {
        tmp = &(ptrGrille->matrice[ligne][colonne]);
        cptCachee = 0;
        cptMarqueVoisine = 0;
        if ((tmp->visibilite == DECOUVERTE) && (tmp->nombreBombesVoisines != 0))
        {
          for (int i = 0; i < tmp->voisinage.nombre; i++)
          {
            if (ptrGrille->matrice[tmp->voisinage.tab[i].ligne][tmp->voisinage.tab[i].colonne].visibilite == CACHEE)
            {
              cptCachee += 1;
            }
            if (ptrGrille->matrice[tmp->voisinage.tab[i].ligne][tmp->voisinage.tab[i].colonne].visibilite == MARQUEE)
            {
              cptMarqueVoisine += 1;
            }
          }
          if ((cptCachee + cptMarqueVoisine) == tmp->nombreBombesVoisines)
          {
            for (int i = 0; i < tmp->voisinage.nombre; i++)
            {
              if (ptrGrille->matrice[tmp->voisinage.tab[i].ligne][tmp->voisinage.tab[i].colonne].visibilite == CACHEE)
              {
                SetMarqueCellule(ptrGrille, tmp->voisinage.tab[i].ligne, tmp->voisinage.tab[i].colonne);
              }
            }
          }
          if (tmp->nombreBombesVoisines == cptMarqueVoisine)
          {
            for (int i = 0; i < tmp->voisinage.nombre; i++)
            {
              if (ptrGrille->matrice[tmp->voisinage.tab[i].ligne][tmp->voisinage.tab[i].colonne].visibilite == CACHEE)
              {
                l = tmp->voisinage.tab[i].ligne;
                c = tmp->voisinage.tab[i].colonne;
                pondMin = 0;
                changement += 1;
              }
            }
          }
        }
      }
    }
  } while (changement == 0 && tour != 10);

  if (tour == 10)
  {
    position = Strategie2(ptrGrille);
    return position;
  }

  position.ligne = l;
  position.colonne = c;
  position.ponderation = 1 - pondMin; // passage de pourcentage piegé à pourcentage pas piégé

  return position;
}

Position CalcCoup(Grille *ptrGrille, Strategie strategie)
{
  Position position;
  switch (strategie)
  {
  case STRATEGIE1:
    position = Strategie1(ptrGrille);
    break;

  case STRATEGIE2:
    position = Strategie2(ptrGrille);
    break;

  case STRATEGIE3:
    position = Strategie3(ptrGrille);
    break;

  default:
    // Aucune strategie
    break;
  }
  return position;
}

Session InitSession()
{
  Session session;
  for (int i = FIRST_STRATEGIE; i < STRATEGIE_COUNT; i++)
  {
    session.stats[i] = 0;
  }
  return session;
}
