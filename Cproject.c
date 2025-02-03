#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM 50

// Structure representant un article
typedef struct {
    char nom[MAX_NOM];
    int quantite;
    int priorite;
} Article;

// Structure representant un nœud de la liste chainee
typedef struct noeud {
    Article article;
    struct noeud *suivant;
} Noeud;

// Structure representant un evenement d'historique
typedef struct historique {
    char operation[20];
    char nomArticle[MAX_NOM];
    int ancienneQuantite;
    int nouvelleQuantite;
    struct historique *suivant;
} Historique;
// Fonction pour creer un nouvel article
Noeud* creerArticle(const char *nom, int quantite) {
    Noeud *nouveau = (Noeud*)malloc(sizeof(Noeud));
    strcpy(nouveau->article.nom, nom);
    nouveau->article.quantite = quantite;
    nouveau->suivant = NULL;
    return nouveau;
}

// Fonction pour ajouter un article à la liste et à l'historique
void ajouterArticle(Noeud **tete, Noeud *nouveau, Historique **teteHistorique) {
    // ... (code existant)
    nouveau->suivant = *tete;
    *tete = nouveau;
    // Ajouter à l'historique :
    Historique *nouvelHistorique = (Historique*)malloc(sizeof(Historique));
    strcpy(nouvelHistorique->operation, "Ajout");
    strcpy(nouvelHistorique->nomArticle, nouveau->article.nom);
    nouvelHistorique->ancienneQuantite = 0;
    nouvelHistorique->nouvelleQuantite = nouveau->article.quantite;
    nouvelHistorique->suivant = *teteHistorique;
    *teteHistorique = nouvelHistorique;
}

void supprimerArticle(Noeud **tete, const char *nom, Historique **teteHistorique) {
    // ... (code existant)
    Noeud *precedent = NULL, *courant = *tete;

    while (courant != NULL && strcmp(courant->article.nom, nom) != 0) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Article non trouve.\n");
    } else {
        if (precedent == NULL) {
            *tete = courant->suivant;
        } else {
            precedent->suivant = courant->suivant;
        }
        free(courant);
    }
    // Ajouter à l'historique :
    Historique *nouvelHistorique = (Historique*)malloc(sizeof(Historique));
    strcpy(nouvelHistorique->operation, "Suppression");
    strcpy(nouvelHistorique->nomArticle, nom);
    nouvelHistorique->ancienneQuantite = courant->article.quantite;
    nouvelHistorique->nouvelleQuantite = 0;
    nouvelHistorique->suivant = *teteHistorique;
    *teteHistorique = nouvelHistorique;
}

// Fonction pour afficher la liste
void afficherListe(Noeud *tete) {
    Noeud *courant = tete;
    int i = 1;
    printf("------------------------la voila votre liste de course-----------------------------\n");
    while (courant != NULL) {
        printf("\t\t\t %d. %s (%d)\n", i++, courant->article.nom, courant->article.quantite);
        courant = courant->suivant;
    }
    printf("\n-----------------------------------------------------------------------------------\n");
}

// Fonction pour afficher l'historique
void afficherHistorique(Historique *tete) {
    Historique *courant = tete;
    while (courant != NULL) {
        printf("Operation : %s\n", courant->operation);
        printf("Article : %s\n", courant->nomArticle);
        printf("Ancienne quantite : %d\n", courant->ancienneQuantite);
        printf("Nouvelle quantite : %d\n\n", courant->nouvelleQuantite);
        courant = courant->suivant;
    }
}


// Fonction pour afficher les articles tries par priorite
void afficherArticlesTries(Noeud *tete) {
    // Creer un tableau temporaire pour stocker les articles
    Noeud *courant = tete;
    int nbArticles = 0;
    while (courant != NULL) {
        nbArticles++;
        courant = courant->suivant;
    }
    Article *tabArticles = (Article*)malloc(nbArticles * sizeof(Article));
    courant = tete;
    int i = 0;
    while (courant != NULL) {
        tabArticles[i] = courant->article;
        i++;
        courant = courant->suivant;
    }
// Tri par insertion
    for (int i = 1; i < nbArticles; i++) {
        Article cle = tabArticles[i];
        int j = i - 1;
        while (j >= 0 && tabArticles[j].priorite < cle.priorite) {
            tabArticles[j + 1] = tabArticles[j];
            j = j - 1;
        }
        tabArticles[j + 1] = cle;
    }

    // Afficher les articles tries
    for (int i = 0; i < nbArticles; i++) {
        printf("%s (%d) - Priorite : %d\n", tabArticles[i].nom, tabArticles[i].quantite, tabArticles[i].priorite);
    }

    free(tabArticles);
}
