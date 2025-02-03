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
