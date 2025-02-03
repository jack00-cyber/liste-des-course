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
