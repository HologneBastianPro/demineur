#include <stdio.h>
#include <view_menu.h>
#include <couleur.h>
#include <stdlib.h>

Joueur ChoixJoueur()
{
  system("clear");

  printf(" _____  ______ __  __ _____ _   _ ______ _    _ _____\n");
  printf("|  __ \\|  ____|  \\/  |_   _| \\ | |  ____| |  | |  __ \\\n");
  printf("| |  | | |__  | \\  / | | | |  \\| | |__  | |  | | |__) |\n");
  printf("| |  | |  __| | |\\/| | | | | . ` |  __| | |  | |  _  /\n");
  printf("| |__| | |____| |  | |_| |_| |\\  | |____| |__| | | \\ \\\n");
  printf("|_____/|______|_|  |_|_____|_| \\_|______|\\____/|_|  \\_\\\n");
  printf("\n\n");

  couleur("34;1");
  printf("+--- MENU DU DEMINEUR ---+\n");
  printf("| 1 - Partie normale     |\n");
  printf("| 2 - Partie ordinateur  |\n");
  printf("| 3 - EXIT               |\n");
  printf("+------------------------+\n\n");
  couleur("0");

  printf("Saisir un choix : ");
  int k;
  scanf("%d", &k);
  system("clear");
  Joueur joueur = k;
  return joueur;
}

int SaisieAction()
{
  couleur("34;1");
  printf("\n+-----------------------------------+\n");
  printf("| 1 - Jouer un coup                 |\n");
  printf("| 2 - Marquer/Démarquer une case    |\n");
  printf("| 3 - Abandonner                    |\n");
  printf("+-----------------------------------+\n\n");
  couleur("0");
  printf("Saisir un choix : ");
  int k;
  scanf("%d", &k);
  system("clear");
  return k;
}

Partie *CreerPartieUtilisateur()
{
  Partie *ptrPartie;
  ptrPartie = (Partie *)malloc(sizeof(Partie));

  printf("\033[H\033[2J");
  printf("--- CREER UNE PARTIE MANUELLE---\n");

  // Saisie du nombre de lignes
  int ligne;
  do
  {
    printf("Nombre de lignes de la grille : ");
    scanf("%d", &ligne);
    if (ligne < 2)
    {
      printf("\033[H\033[2J");
      printf("  --> Le nombre de lignes doit au minimum être de 2.\n");
    }
  } while (ligne < 2);

  // Saisie du nombre de colonnes
  int colonne;
  do
  {
    printf("Nombre de colonnes de la grille : ");
    scanf("%d", &colonne);
    if (colonne < 2)
    {
      printf("\033[H\033[2J");
      printf("  --> Le nombre de colonnes doit au minimum être de 2.\n");
    }
  } while (colonne < 2);

  // Saisie de la strategie
  int strategie;
  do
  {
    printf("Choisir une strategie :\n");
    printf("1 - Strategie1\n");
    printf("2 - Aléatoire\n");
    printf("4 - Aucune\n");
    printf("Saisir : ");
    scanf("%d", &strategie);
    if (strategie != 1 && strategie != 2 && strategie != 4)
    {
      printf("\033[H\033[2J");
      printf("  --> La stratégie doit être 1, 2 ou 4.\n");
    }
  } while (strategie != 1 && strategie != 2 && strategie != 4);

  // Saisie du nombre de mines
  int kmine;
  int nombreDeMineMax = ligne * colonne*0.9;
  do
  {
    printf("Nombre de mines : ");
    scanf("%d", &kmine);
    if ((kmine >= nombreDeMineMax) || (kmine < 1))
    {
      printf("  -->Le nombre de mines doit être inferieur à 90 pourcents du nombre de cases.\n");
    }
  } while ((kmine >= nombreDeMineMax) || (kmine < 1));

  printf("\033[H\033[2J");
  *ptrPartie = InitPartie(colonne, ligne, strategie, kmine);
  return ptrPartie;
}

Partie *CreerPartieOrdinateur(Session *session)
{
  // Creation de la partie qui servira de modèle pour toutes les autres.
  Partie *ptrPartie;
  ptrPartie = (Partie *)malloc(sizeof(Partie));

  printf("\033[H\033[2J");
  printf("--- CREER UNE SESSION ORDINATEUR---\n\n");

  printf("------------------------------------------------------------------------\n");
  printf("- /!\\ La saisie de grille géante (Exemple 10000*10000) peut entrainer  -\n");
  printf("-     sur certains ordinateurs des segmentations fault dûes à une      -\n");
  printf("-     demande d'allocation mémoire que la machine ne peut supporter.   -\n");
  printf("------------------------------------------------------------------------\n\n");

  printf("Saisir le nombre de parties par strategie : ");
  int nombrePartie;
  scanf("%d", &nombrePartie);
  session->nombrePartie = nombrePartie;

  // Saisie du nombre de lignes
  int ligne;
  do
  {
    printf("Nombre de lignes de la grille : ");
    scanf("%d", &ligne);
    if (ligne < 2)
    {
      printf("\033[H\033[2J");
      printf("  --> Le nombre de lignes doit au minimum être de 2.\n");
    }
  } while (ligne < 2);

  // Saisie du nombre de colonnes
  int colonne;
  do
  {
    printf("Nombre de colonnes de la grille : ");
    scanf("%d", &colonne);
    if (colonne < 2)
    {
      printf("\033[H\033[2J");
      printf("  --> Le nombre de colonnes doit au minimum être de 2.\n");
    }
  } while (colonne < 2);

  // Saisie du nombre de mines
  int nombreDeMineMax = ligne * colonne*0.9;
  int kmine;
  do
  {
    printf("Nombre de mines : ");
    scanf("%d", &kmine);
    if ((kmine >= nombreDeMineMax) || (kmine < 1))
    {
      printf("  --> -->Le nombre de mines doit être inferieur à 90 pourcents du nombre de cases.\n");
    }
  } while ((kmine >= nombreDeMineMax) || (kmine < 1));

  *ptrPartie = InitPartie(ligne, colonne, STRATEGIE1, kmine);
  printf("\033[H\033[2J");
  return ptrPartie;
}

bool rejouer()
{
  char rejouer;
  couleur("0");
  printf("Rejouer (O/N) : ");
  scanf("%s", &rejouer);

  if (rejouer == 'O' || rejouer == 'o')
  {
    return true;
  }
  else
  {
    return false;
  }
};
