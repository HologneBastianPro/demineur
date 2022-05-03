#include <stdio.h>
#include <modele_strategie.h>
#include <view_strategie.h>
#include <stdlib.h>

void AffichageStatistique(Session session)
{
  float pourcentage;
  printf("Nom\t\t");
  printf("Parties_gagnées\t\t");
  printf("Parties_jouées\t\t");
  printf("Pourcentage_de_parties_gagnés\t\t\n");
  for (int i = FIRST_STRATEGIE; i < STRATEGIE_COUNT; i++)
  {
    printf("\n");
    printf("Strategie%d\t", i);
    printf("%d\t\t\t", session.stats[i]);
    printf("%d\t\t\t", session.nombrePartie);
    pourcentage = (double)session.stats[i] / session.nombrePartie;
    pourcentage = pourcentage * 100;
    printf("%.2f%\t", pourcentage);
  }
  printf("\n");
}
