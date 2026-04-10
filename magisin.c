#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUITS 100
#define MAX_FOURNISSEURS 50
#define MAX_COMMANDES 200
#define MOT_DE_PASSE "emsi2024"

// ======================== STRUCTURES ========================

typedef struct {
    int reference;
    char nom[50];
    float quantite;
    float prixAchat;
    float prixVente;
    int fournisseurReference;
} Produit;

typedef struct {
    int fournisseurReference;
    char nom[50];
    char adresse[100];
} Fournisseur;

typedef struct {
    char date[20];
    int produit;
    int fournisseurReference;
    float prix;
    float quantite;
} Commande;

// ======================== VARIABLES GLOBALES ========================

Produit produits[MAX_PRODUITS];
int nbProduits = 0;

Fournisseur fournisseurs[MAX_FOURNISSEURS];
int nbFournisseurs = 0;

Commande commandes[MAX_COMMANDES];
int nbCommandes = 0;

// ======================== COULEURS ANSI ========================

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BG_BLUE "\033[44m"

// ======================== FONCTIONS UTILITAIRES ========================

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause_program() {
    printf("\n" YELLOW "Appuyez sur Entree pour continuer..." RESET);
    getchar();
    getchar();
}

void afficherLogo() {
    printf(CYAN BOLD);
    printf("  +====================================================+\n");
    printf("  |        " WHITE "EMSI" CYAN " - Ecole Marocaine des Sciences         |\n");
    printf("  |                 " WHITE "de l'Ingenieur" CYAN "                     |\n");
    printf("  |                                                    |\n");
    printf("  |           " MAGENTA "SYSTEME DE GESTION DE MAGASIN" CYAN "            |\n");
    printf("  +====================================================+\n");
    printf(RESET "\n");
}

void afficherSeparateur() {
    printf(BLUE "  ------------------------------------------------------\n" RESET);
}

int verifierMotDePasse() {
    char mdp[50];
    printf(RED BOLD "\n  [!] Cette operation necessite un mot de passe.\n" RESET);
    printf("  Mot de passe : ");
    scanf("%s", mdp);
    if (strcmp(mdp, MOT_DE_PASSE) == 0) {
        printf(GREEN "  [OK] Mot de passe correct.\n" RESET);
        return 1;
    } else {
        printf(RED "  [X] Mot de passe incorrect!\n" RESET);
        return 0;
    }
}

int confirmerAction(const char *action) {
    char choix;
    printf(YELLOW "\n  Confirmer %s ? (o/n) : " RESET, action);
    scanf(" %c", &choix);
    return (choix == 'o' || choix == 'O');
}

// ======================== PRODUITS ========================

int rechercherProduitParRef(int ref) {
    int i;
    for (i = 0; i < nbProduits; i++) {
        if (produits[i].reference == ref) return i;
    }
    return -1;
}

void afficherProduit(Produit p) {
    printf(CYAN "  +-------------------------------------------+\n" RESET);
    printf("  | " BOLD "Reference   : " RESET "%d\n", p.reference);
    printf("  | " BOLD "Nom         : " RESET "%s\n", p.nom);
    printf("  | " BOLD "Quantite    : " RESET "%.2f\n", p.quantite);
    printf("  | " BOLD "Prix Achat  : " RESET "%.2f DH\n", p.prixAchat);
    printf("  | " BOLD "Prix Vente  : " RESET "%.2f DH\n", p.prixVente);
    printf("  | " BOLD "Fournisseur : " RESET "%d\n", p.fournisseurReference);
    printf(CYAN "  +-------------------------------------------+\n" RESET);
}

void ajouterProduit() {
    Produit p;
    if (nbProduits >= MAX_PRODUITS) {
        printf(RED "  [X] Capacite maximale atteinte!\n" RESET);
        return;
    }
    printf(GREEN "\n  === AJOUT D'UN PRODUIT ===\n" RESET);
    printf("  Reference : ");
    scanf("%d", &p.reference);

    if (rechercherProduitParRef(p.reference) != -1) {
        printf(RED "  [X] Cette reference existe deja!\n" RESET);
        return;
    }

    printf("  Nom : ");
    scanf(" %[^\n]", p.nom);
    printf("  Quantite : ");
    scanf("%f", &p.quantite);
    printf("  Prix d'achat : ");
    scanf("%f", &p.prixAchat);
    printf("  Prix de vente : ");
    scanf("%f", &p.prixVente);
    printf("  Reference fournisseur : ");
    scanf("%d", &p.fournisseurReference);

    produits[nbProduits++] = p;
    printf(GREEN "  [OK] Produit ajoute avec succes!\n" RESET);
}

void menuModificationProduit() {
    int ref, idx, choix, newRef;
    printf("  Reference du produit a modifier : ");
    scanf("%d", &ref);
    idx = rechercherProduitParRef(ref);

    if (idx == -1) {
        printf(RED "  [X] Produit non trouve!\n" RESET);
        return;
    }

    printf(YELLOW "\n  Produit trouve :\n" RESET);
    afficherProduit(produits[idx]);

    printf(CYAN "\n  Modifier quel champ ?\n" RESET);
    printf("  1) Reference\n");
    printf("  2) Nom\n");
    printf("  3) Quantite\n");
    printf("  4) Prix d'achat\n");
    printf("  5) Prix de vente\n");
    printf("  6) Fournisseur\n");
    printf("  7) Retour\n");
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 7) return;

    if (!confirmerAction("la modification")) return;

    switch (choix) {
        case 1:
            printf("  Nouvelle reference : ");
            scanf("%d", &newRef);
            if (rechercherProduitParRef(newRef) != -1) {
                printf(RED "  [X] Cette reference existe deja!\n" RESET);
                return;
            }
            produits[idx].reference = newRef;
            break;
        case 2:
            printf("  Nouveau nom : ");
            scanf(" %[^\n]", produits[idx].nom);
            break;
        case 3:
            printf("  Nouvelle quantite : ");
            scanf("%f", &produits[idx].quantite);
            break;
        case 4:
            printf("  Nouveau prix d'achat : ");
            scanf("%f", &produits[idx].prixAchat);
            break;
        case 5:
            printf("  Nouveau prix de vente : ");
            scanf("%f", &produits[idx].prixVente);
            break;
        case 6:
            printf("  Nouvelle reference fournisseur : ");
            scanf("%d", &produits[idx].fournisseurReference);
            break;
    }
    printf(GREEN "  [OK] Produit modifie avec succes!\n" RESET);
}

void suppressionProduit() {
    int choix, ref, idx, i;
    printf(CYAN "\n  1) Un par Un\n  2) Tout\n  3) Retour\n" RESET);
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("  Reference du produit a supprimer : ");
        scanf("%d", &ref);
        idx = rechercherProduitParRef(ref);
        if (idx == -1) {
            printf(RED "  [X] Produit non trouve!\n" RESET);
            return;
        }
        afficherProduit(produits[idx]);
        if (!confirmerAction("la suppression")) return;
        for (i = idx; i < nbProduits - 1; i++)
            produits[i] = produits[i + 1];
        nbProduits--;
        printf(GREEN "  [OK] Produit supprime!\n" RESET);
    } else if (choix == 2) {
        if (!verifierMotDePasse()) return;
        if (!confirmerAction("la suppression de TOUS les produits")) return;
        nbProduits = 0;
        printf(GREEN "  [OK] Tous les produits ont ete supprimes!\n" RESET);
    }
}

void rechercheProduit() {
    int choix, ref, idx, i, trouve;
    char nom[50];
    printf(CYAN "\n  1) Par reference\n  2) Par nom\n  3) Par fournisseur\n  4) Retour\n" RESET);
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("  Reference : ");
        scanf("%d", &ref);
        idx = rechercherProduitParRef(ref);
        if (idx != -1) afficherProduit(produits[idx]);
        else printf(RED "  [X] Produit non trouve!\n" RESET);
    } else if (choix == 2) {
        trouve = 0;
        printf("  Nom : ");
        scanf(" %[^\n]", nom);
        for (i = 0; i < nbProduits; i++) {
            if (strstr(produits[i].nom, nom) != NULL) {
                afficherProduit(produits[i]);
                trouve = 1;
            }
        }
        if (!trouve) printf(RED "  [X] Aucun produit trouve!\n" RESET);
    } else if (choix == 3) {
        trouve = 0;
        printf("  Reference fournisseur : ");
        scanf("%d", &ref);
        for (i = 0; i < nbProduits; i++) {
            if (produits[i].fournisseurReference == ref) {
                afficherProduit(produits[i]);
                trouve = 1;
            }
        }
        if (!trouve) printf(RED "  [X] Aucun produit trouve!\n" RESET);
    }
}

void listeProduits() {
    int i;
    if (nbProduits == 0) {
        printf(YELLOW "  Aucun produit enregistre.\n" RESET);
        return;
    }
    printf(GREEN "\n  === LISTE DES PRODUITS (%d) ===\n" RESET, nbProduits);
    for (i = 0; i < nbProduits; i++)
        afficherProduit(produits[i]);
}

void menuProduits() {
    int choix;
    do {
        clearScreen();
        afficherLogo();
        printf(BG_BLUE WHITE BOLD "  MENU GESTION DES PRODUITS                         " RESET "\n\n");
        printf("  " GREEN "1)" RESET " Ajout d'un produit\n");
        printf("  " GREEN "2)" RESET " Modification\n");
        printf("  " GREEN "3)" RESET " Suppression\n");
        printf("  " GREEN "4)" RESET " Recherche\n");
        printf("  " GREEN "5)" RESET " Liste des produits\n");
        printf("  " RED   "6)" RESET " MENU PRINCIPAL\n");
        afficherSeparateur();
        printf("  Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterProduit(); pause_program(); break;
            case 2: menuModificationProduit(); pause_program(); break;
            case 3: suppressionProduit(); pause_program(); break;
            case 4: rechercheProduit(); pause_program(); break;
            case 5: listeProduits(); pause_program(); break;
            case 6: break;
            default: printf(RED "  Choix invalide!\n" RESET); pause_program();
        }
    } while (choix != 6);
}

// ======================== FOURNISSEURS ========================

int rechercherFournisseurParRef(int ref) {
    int i;
    for (i = 0; i < nbFournisseurs; i++) {
        if (fournisseurs[i].fournisseurReference == ref) return i;
    }
    return -1;
}

void afficherFournisseur(Fournisseur f) {
    printf(MAGENTA "  +-------------------------------------------+\n" RESET);
    printf("  | " BOLD "Reference : " RESET "%d\n", f.fournisseurReference);
    printf("  | " BOLD "Nom       : " RESET "%s\n", f.nom);
    printf("  | " BOLD "Adresse   : " RESET "%s\n", f.adresse);
    printf(MAGENTA "  +-------------------------------------------+\n" RESET);
}

void ajouterFournisseur() {
    Fournisseur f;
    if (nbFournisseurs >= MAX_FOURNISSEURS) {
        printf(RED "  [X] Capacite maximale atteinte!\n" RESET);
        return;
    }
    printf(GREEN "\n  === AJOUT D'UN FOURNISSEUR ===\n" RESET);
    printf("  Reference : ");
    scanf("%d", &f.fournisseurReference);

    if (rechercherFournisseurParRef(f.fournisseurReference) != -1) {
        printf(RED "  [X] Cette reference existe deja!\n" RESET);
        return;
    }

    printf("  Nom : ");
    scanf(" %[^\n]", f.nom);
    printf("  Adresse : ");
    scanf(" %[^\n]", f.adresse);

    fournisseurs[nbFournisseurs++] = f;
    printf(GREEN "  [OK] Fournisseur ajoute avec succes!\n" RESET);
}

void menuModificationFournisseur() {
    int ref, idx, choix, newRef;
    printf("  Reference du fournisseur a modifier : ");
    scanf("%d", &ref);
    idx = rechercherFournisseurParRef(ref);

    if (idx == -1) {
        printf(RED "  [X] Fournisseur non trouve!\n" RESET);
        return;
    }

    afficherFournisseur(fournisseurs[idx]);

    printf(CYAN "\n  Modifier quel champ ?\n" RESET);
    printf("  1) Reference\n");
    printf("  2) Nom\n");
    printf("  3) Adresse\n");
    printf("  4) Retour\n");
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 4) return;
    if (!confirmerAction("la modification")) return;

    switch (choix) {
        case 1:
            printf("  Nouvelle reference : ");
            scanf("%d", &newRef);
            if (rechercherFournisseurParRef(newRef) != -1) {
                printf(RED "  [X] Cette reference existe deja!\n" RESET);
                return;
            }
            fournisseurs[idx].fournisseurReference = newRef;
            break;
        case 2:
            printf("  Nouveau nom : ");
            scanf(" %[^\n]", fournisseurs[idx].nom);
            break;
        case 3:
            printf("  Nouvelle adresse : ");
            scanf(" %[^\n]", fournisseurs[idx].adresse);
            break;
    }
    printf(GREEN "  [OK] Fournisseur modifie avec succes!\n" RESET);
}

void suppressionFournisseur() {
    int choix, ref, idx, i;
    printf(CYAN "\n  1) Un par Un\n  2) Tout\n  3) Retour\n" RESET);
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("  Reference du fournisseur a supprimer : ");
        scanf("%d", &ref);
        idx = rechercherFournisseurParRef(ref);
        if (idx == -1) {
            printf(RED "  [X] Fournisseur non trouve!\n" RESET);
            return;
        }
        afficherFournisseur(fournisseurs[idx]);
        if (!confirmerAction("la suppression")) return;
        for (i = idx; i < nbFournisseurs - 1; i++)
            fournisseurs[i] = fournisseurs[i + 1];
        nbFournisseurs--;
        printf(GREEN "  [OK] Fournisseur supprime!\n" RESET);
    } else if (choix == 2) {
        if (!verifierMotDePasse()) return;
        if (!confirmerAction("la suppression de TOUS les fournisseurs")) return;
        nbFournisseurs = 0;
        printf(GREEN "  [OK] Tous les fournisseurs ont ete supprimes!\n" RESET);
    }
}

void rechercheFournisseur() {
    int choix, ref, idx, i, trouve;
    char nom[50];
    printf(CYAN "\n  1) Par reference\n  2) Par nom\n  3) Retour\n" RESET);
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("  Reference : ");
        scanf("%d", &ref);
        idx = rechercherFournisseurParRef(ref);
        if (idx != -1) afficherFournisseur(fournisseurs[idx]);
        else printf(RED "  [X] Fournisseur non trouve!\n" RESET);
    } else if (choix == 2) {
        trouve = 0;
        printf("  Nom : ");
        scanf(" %[^\n]", nom);
        for (i = 0; i < nbFournisseurs; i++) {
            if (strstr(fournisseurs[i].nom, nom) != NULL) {
                afficherFournisseur(fournisseurs[i]);
                trouve = 1;
            }
        }
        if (!trouve) printf(RED "  [X] Aucun fournisseur trouve!\n" RESET);
    }
}

void listeFournisseurs() {
    int i;
    if (nbFournisseurs == 0) {
        printf(YELLOW "  Aucun fournisseur enregistre.\n" RESET);
        return;
    }
    printf(GREEN "\n  === LISTE DES FOURNISSEURS (%d) ===\n" RESET, nbFournisseurs);
    for (i = 0; i < nbFournisseurs; i++)
        afficherFournisseur(fournisseurs[i]);
}

void menuFournisseurs() {
    int choix;
    do {
        clearScreen();
        afficherLogo();
        printf(BG_BLUE WHITE BOLD "  MENU GESTION DES FOURNISSEURS                     " RESET "\n\n");
        printf("  " GREEN "1)" RESET " Ajout d'un fournisseur\n");
        printf("  " GREEN "2)" RESET " Modification\n");
        printf("  " GREEN "3)" RESET " Suppression\n");
        printf("  " GREEN "4)" RESET " Recherche\n");
        printf("  " GREEN "5)" RESET " Liste des fournisseurs\n");
        printf("  " RED   "6)" RESET " MENU PRINCIPAL\n");
        afficherSeparateur();
        printf("  Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterFournisseur(); pause_program(); break;
            case 2: menuModificationFournisseur(); pause_program(); break;
            case 3: suppressionFournisseur(); pause_program(); break;
            case 4: rechercheFournisseur(); pause_program(); break;
            case 5: listeFournisseurs(); pause_program(); break;
            case 6: break;
            default: printf(RED "  Choix invalide!\n" RESET); pause_program();
        }
    } while (choix != 6);
}

// ======================== COMMANDES ========================

void afficherCommande(Commande c, int index) {
    printf(YELLOW "  +-------------------------------------------+\n" RESET);
    printf("  | " BOLD "Commande #%d" RESET "\n", index + 1);
    printf("  | " BOLD "Date         : " RESET "%s\n", c.date);
    printf("  | " BOLD "Produit Ref  : " RESET "%d\n", c.produit);
    printf("  | " BOLD "Fournisseur  : " RESET "%d\n", c.fournisseurReference);
    printf("  | " BOLD "Prix         : " RESET "%.2f DH\n", c.prix);
    printf("  | " BOLD "Quantite     : " RESET "%.2f\n", c.quantite);
    printf(YELLOW "  +-------------------------------------------+\n" RESET);
}

void ajouterCommande() {
    Commande c;
    if (nbCommandes >= MAX_COMMANDES) {
        printf(RED "  [X] Capacite maximale atteinte!\n" RESET);
        return;
    }
    printf(GREEN "\n  === AJOUT D'UNE COMMANDE ===\n" RESET);
    printf("  Date (JJ/MM/AAAA) : ");
    scanf(" %[^\n]", c.date);
    printf("  Reference produit : ");
    scanf("%d", &c.produit);
    printf("  Reference fournisseur : ");
    scanf("%d", &c.fournisseurReference);
    printf("  Prix : ");
    scanf("%f", &c.prix);
    printf("  Quantite : ");
    scanf("%f", &c.quantite);

    commandes[nbCommandes++] = c;
    printf(GREEN "  [OK] Commande ajoutee avec succes!\n" RESET);
}

void menuModificationCommande() {
    int index, choix;
    printf("  Numero de la commande a modifier (1-%d) : ", nbCommandes);
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= nbCommandes) {
        printf(RED "  [X] Commande non trouvee!\n" RESET);
        return;
    }

    afficherCommande(commandes[index], index);

    printf(CYAN "\n  Modifier quel champ ?\n" RESET);
    printf("  1) Date\n");
    printf("  2) Produit\n");
    printf("  3) Fournisseur\n");
    printf("  4) Quantite\n");
    printf("  5) Retour\n");
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 5) return;
    if (!confirmerAction("la modification")) return;

    switch (choix) {
        case 1:
            printf("  Nouvelle date : ");
            scanf(" %[^\n]", commandes[index].date);
            break;
        case 2:
            printf("  Nouvelle reference produit : ");
            scanf("%d", &commandes[index].produit);
            break;
        case 3:
            printf("  Nouvelle reference fournisseur : ");
            scanf("%d", &commandes[index].fournisseurReference);
            break;
        case 4:
            printf("  Nouvelle quantite : ");
            scanf("%f", &commandes[index].quantite);
            break;
    }
    printf(GREEN "  [OK] Commande modifiee avec succes!\n" RESET);
}

void suppressionCommande() {
    int choix, index, i;
    printf(CYAN "\n  1) Un par Un\n  2) Tout\n  3) Retour\n" RESET);
    printf("  Choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("  Numero de la commande a supprimer (1-%d) : ", nbCommandes);
        scanf("%d", &index);
        index--;
        if (index < 0 || index >= nbCommandes) {
            printf(RED "  [X] Commande non trouvee!\n" RESET);
            return;
        }
        afficherCommande(commandes[index], index);
        if (!confirmerAction("la suppression")) return;
        for (i = index; i < nbCommandes - 1; i++)
            commandes[i] = commandes[i + 1];
        nbCommandes--;
        printf(GREEN "  [OK] Commande supprimee!\n" RESET);
    } else if (choix == 2) {
        if (!verifierMotDePasse()) return;
        if (!confirmerAction("la suppression de TOUTES les commandes")) return;
        nbCommandes = 0;
        printf(GREEN "  [OK] Toutes les commandes ont ete supprimees!\n" RESET);
    }
}

void rechercheCommande() {
    int choix, ref, i, trouve, idx;
    char nom[50];
    printf(CYAN "\n  1) Par reference produit\n  2) Par nom produit\n  3) Par fournisseur\n  4) Par produit\n  5) Retour\n" RESET);
    printf("  Choix : ");
    scanf("%d", &choix);

    trouve = 0;

    if (choix == 1) {
        printf("  Reference produit : ");
        scanf("%d", &ref);
        for (i = 0; i < nbCommandes; i++) {
            if (commandes[i].produit == ref) {
                afficherCommande(commandes[i], i);
                trouve = 1;
            }
        }
    } else if (choix == 2) {
        printf("  Nom du produit : ");
        scanf(" %[^\n]", nom);
        for (i = 0; i < nbCommandes; i++) {
            idx = rechercherProduitParRef(commandes[i].produit);
            if (idx != -1 && strstr(produits[idx].nom, nom) != NULL) {
                afficherCommande(commandes[i], i);
                trouve = 1;
            }
        }
    } else if (choix == 3) {
        printf("  Reference fournisseur : ");
        scanf("%d", &ref);
        for (i = 0; i < nbCommandes; i++) {
            if (commandes[i].fournisseurReference == ref) {
                afficherCommande(commandes[i], i);
                trouve = 1;
            }
        }
    } else if (choix == 4) {
        printf("  Reference produit : ");
        scanf("%d", &ref);
        for (i = 0; i < nbCommandes; i++) {
            if (commandes[i].produit == ref) {
                afficherCommande(commandes[i], i);
                trouve = 1;
            }
        }
    } else {
        return;
    }

    if (!trouve) printf(RED "  [X] Aucune commande trouvee!\n" RESET);
}

void listeCommandes() {
    int i;
    if (nbCommandes == 0) {
        printf(YELLOW "  Aucune commande enregistree.\n" RESET);
        return;
    }
    printf(GREEN "\n  === LISTE DES COMMANDES (%d) ===\n" RESET, nbCommandes);
    for (i = 0; i < nbCommandes; i++)
        afficherCommande(commandes[i], i);
}

void menuCommandes() {
    int choix;
    do {
        clearScreen();
        afficherLogo();
        printf(BG_BLUE WHITE BOLD "  MENU GESTION DES COMMANDES                        " RESET "\n\n");
        printf("  " GREEN "1)" RESET " Ajout d'une commande\n");
        printf("  " GREEN "2)" RESET " Modification\n");
        printf("  " GREEN "3)" RESET " Suppression\n");
        printf("  " GREEN "4)" RESET " Recherche\n");
        printf("  " GREEN "5)" RESET " Liste des commandes\n");
        printf("  " RED   "6)" RESET " MENU PRINCIPAL\n");
        afficherSeparateur();
        printf("  Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterCommande(); pause_program(); break;
            case 2: menuModificationCommande(); pause_program(); break;
            case 3: suppressionCommande(); pause_program(); break;
            case 4: rechercheCommande(); pause_program(); break;
            case 5: listeCommandes(); pause_program(); break;
            case 6: break;
            default: printf(RED "  Choix invalide!\n" RESET); pause_program();
        }
    } while (choix != 6);
}

// ======================== MENU PRINCIPAL ========================

int main() {
    int choix;

    do {
        clearScreen();
        afficherLogo();
        printf(BG_BLUE WHITE BOLD "  MENU PRINCIPAL                                    " RESET "\n\n");
        printf("  " GREEN "1)" RESET " Gestion des Produits\n");
        printf("  " GREEN "2)" RESET " Gestion des Fournisseurs\n");
        printf("  " GREEN "3)" RESET " Gestion des Commandes\n");
        printf("  " RED   "4)" RESET " QUITTER\n");
        afficherSeparateur();
        printf("  Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: menuProduits(); break;
            case 2: menuFournisseurs(); break;
            case 3: menuCommandes(); break;
            case 4:
                clearScreen();
                afficherLogo();
                printf(GREEN BOLD "  Merci d'avoir utilise notre systeme!\n");
                printf("  Au revoir!\n" RESET);
                break;
            default:
                printf(RED "  Choix invalide!\n" RESET);
                pause_program();
        }
    } while (choix != 4);

    return 0;
}
