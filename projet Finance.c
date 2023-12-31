#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CompteEpargne {
    char dateOperation[20];
    char dateValeur[20];
    double operation;
    double solde;
    int nbJours;
    double tre;
    double interetBrut;
    double interetTrim;
};

struct ListeComptes {
    struct CompteEpargne *comptes;
    size_t taille;
    double interetTotalTrim;
};

void ajouterCompte(struct ListeComptes *liste, char *dateOperation, double operation, double tre);
void afficherComptes(struct ListeComptes *liste);

int main() {
    struct ListeComptes liste = {NULL, 0, 0};
    char dateOperation[20];
    double operation;
    double tre;
    char commande[10];

    do {
        // Saisie des informations de l'utilisateur
        printf("Entrez la date d'op�ration (YYYY-MM-DD) : ");
        scanf("%s", dateOperation);

        printf("Entrez le montant de l'op�ration : ");
        scanf("%lf", &operation);

        printf("Entrez le TRE : ");
        scanf("%lf", &tre);

        // Ajout du compte � la liste
        ajouterCompte(&liste, dateOperation, operation, tre);

        // Affichage des comptes
        afficherComptes(&liste);

        // Demander � l'utilisateur s'il veut ajouter un autre compte
        printf("Voulez-vous ajouter un autre compte ? (Entrez 'exit' pour quitter) : ");
        scanf("%s", commande);

    } while (strcmp(commande, "exit") != 0);

    // Lib�ration de la m�moire
    free(liste.comptes);

    return 0;
}

void ajouterCompte(struct ListeComptes *liste, char *dateOperation, double operation, double tre) {
    // Allouer de la m�moire pour un nouveau compte
    liste->comptes = realloc(liste->comptes, (liste->taille + 1) * sizeof(struct CompteEpargne));

    // Initialiser le compte
    sprintf(liste->comptes[liste->taille].dateOperation, "%s", dateOperation);
    sprintf(liste->comptes[liste->taille].dateValeur, "%s", dateOperation);
    liste->comptes[liste->taille].operation = operation;
    liste->comptes[liste->taille].solde = (liste->taille == 0) ? operation : liste->comptes[liste->taille - 1].solde + operation;
    liste->comptes[liste->taille].nbJours = (liste->taille == 0) ? 0 : 3;  // Remplacez par la logique appropri�e
    liste->comptes[liste->taille].tre = tre;
    liste->comptes[liste->taille].interetBrut = (tre * liste->comptes[liste->taille].nbJours * liste->comptes[liste->taille].solde) / 360;
    liste->comptes[liste->taille].interetTrim = (liste->comptes[liste->taille].interetBrut * 80) / 100;

    // Augmenter la taille du tableau
    liste->taille++;
}

void afficherComptes(struct ListeComptes *liste) {
    printf("Liste des comptes :\n");
    for (size_t i = 0; i < liste->taille; i++) {
        printf("Compte %zu :\n", i + 1);
        printf("   Date d'op�ration : %s\n", liste->comptes[i].dateOperation);
        printf("   Date de valeur    : %s\n", liste->comptes[i].dateValeur);
        printf("   Solde             : %.2f\n", liste->comptes[i].solde);
        printf("   Nb. jours         : %d\n", liste->comptes[i].nbJours);
        printf("   TRE               : %.2f\n", liste->comptes[i].tre);
        printf("   Int�r�t Brut      : %.2f\n", liste->comptes[i].interetBrut);
        printf("   Int�r�t Trim      : %.2f\n", liste->comptes[i].interetTrim);
        printf("\n");
    }

    // Calcul de l'int�r�t total trim
    for (size_t i = 0; i < liste->taille; i++) {
        liste->interetTotalTrim += liste->comptes[i].interetTrim;
    }

    printf("Int�r�t total trim : %.2f\n", liste->interetTotalTrim);
}
