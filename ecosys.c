// 21135979
// FABRICI Tifenn
// Intensif

#include "ecosys.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal* creer_animal(int x, int y, float energie) {
    // Alloue de la mémoire pour un animal et retourne son adresse
    Animal* na = (Animal*)malloc(sizeof(Animal));
    assert(na);
    na->x = x;
    na->y = y;
    na->energie = energie;
    na->dir[0] = rand() % 3 - 1;
    na->dir[1] = rand() % 3 - 1;
    na->suivant = NULL;
    return na;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal* ajouter_en_tete_animal(Animal* liste, Animal* animal) {
    assert(animal);
    assert(!animal->suivant);
    animal->suivant = liste;
    return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y, float energie, Animal** liste_animal) {
    // Créer un animal puis l'ajoute en tête de liste
    assert(x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y);

    Animal* a = creer_animal(x, y, energie);
    assert(a);

    *liste_animal = ajouter_en_tete_animal(*liste_animal, a);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal** liste, Animal* animal) {
    // suprime un animal de la liste en comparant son adresse
    assert(liste && *liste);
    assert(animal);

    Animal* tmp;
    Animal* current = *liste;
    Animal* pred = current;

    // on regarde pour le premier animal de la liste
    if (current == animal) {
        tmp = current->suivant;
        free(current);
        *liste = tmp;
        return;
    }

    // sinon on cherche dans la liste
    while (current) {
        if (current == animal) {
            tmp = current->suivant;
            free(current);
            pred->suivant = tmp;
            return;
        }

        pred = current;
        current = current->suivant;
    }

    return;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal* liste) {
    // libère la mémoire allouée d'une liste d'animaux

    Animal* tmp;
    while (liste) {
        tmp = liste->suivant;
        free(liste);
        liste = tmp;
    }

    return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal* la) {
    if (!la) return 0;
    return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal* la) {
    int cpt = 0;
    while (la) {
        ++cpt;
        la = la->suivant;
    }
    return cpt;
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de
 * contenir des erreurs... */
void afficher_ecosys(Animal* liste_proie, Animal* liste_predateur) {
    unsigned int i, j;
    char ecosys[SIZE_X][SIZE_Y];
    Animal* pa = NULL;

    /* on initialise le tableau */
    for (i = 0; i < SIZE_X; ++i) {
        for (j = 0; j < SIZE_Y; ++j) {
            ecosys[i][j] = ' ';
        }
    }

    /* on ajoute les proies */
    pa = liste_proie;
    while (pa) {
        ecosys[pa->x][pa->y] = '*';
        pa = pa->suivant;
    }

    /* on ajoute les predateurs */
    pa = liste_predateur;
    while (pa) {
        if ((ecosys[pa->x][pa->y] == '@') ||
            (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
            ecosys[pa->x][pa->y] = '@';
        } else {
            ecosys[pa->x][pa->y] = 'O';
        }
        pa = pa->suivant;
    }

    /* on affiche le tableau */
    printf("+");
    for (j = 0; j < SIZE_Y; ++j) {
        printf("-");
    }
    printf("+\n");
    for (i = 0; i < SIZE_X; ++i) {
        printf("|");
        for (j = 0; j < SIZE_Y; ++j) {
            putchar(ecosys[i][j]);
        }
        printf("|\n");
    }
    printf("+");
    for (j = 0; j < SIZE_Y; ++j) {
        printf("-");
    }
    printf("+\n");
    int nbproie = compte_animal_it(liste_proie);
    int nbpred = compte_animal_it(liste_predateur);

    printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}

void clear_screen() {
    printf("\x1b[2J\x1b[1;1H"); /* code ANSI X3.4 pour effacer l'ecran */
}

// TD

void write_animal(FILE* dest, Animal* liste_animal, char* type) {
    // sérialise une liste d'animal dans le fichier dest
    assert(dest);

    // écriture de la balise ouvrante
    fprintf(dest, "<%s>\n", type);
    // écriture des animaux
    while (liste_animal) {
        fprintf(dest, "x=%d y=%d dir=[%d %d] e=%.2f\n", liste_animal->x,
                liste_animal->y, liste_animal->dir[0], liste_animal->dir[1],
                liste_animal->energie);

        liste_animal = liste_animal->suivant;
    }
    // écriture de la balise fermante
    fprintf(dest, "</%s>\n", type);
}

void ecrire_ecosys(const char* nom_fichier, Animal* liste_predateur,
                   Animal* liste_proie) {
    // Sérialise les listes d'animaux

    FILE* dest = fopen(nom_fichier, "w");
    assert(dest);

    write_animal(dest, liste_proie, "proies");
    write_animal(dest, liste_predateur, "predateurs");

    fclose(dest);
}

void lire_ecosys(const char* nom_fichier, Animal** liste_predateur,
                 Animal** liste_proie) {
    // Déserialise les listes d'animaux
    // Pre: le fichier est correctement formaté

    FILE* src = fopen(nom_fichier, "r");
    assert(src);

    char buffer[BUFFER_SIZE];
    char* line = fgets(buffer, BUFFER_SIZE, src);

    // cherche le début du bloc proies
    while (strcmp(line, "<proies>\n")) {
        line = fgets(buffer, BUFFER_SIZE, src);
    }

    // sérialise chaque proie
    line = fgets(buffer, BUFFER_SIZE, src);
    while (strcmp(line, "</proies>\n")) {
        int x, y;
        float e;
        int dir[2];

        sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f", &x, &y, &dir[0], &dir[1],
               &e);

        ajouter_animal(x, y, e, liste_proie);
        line = fgets(buffer, BUFFER_SIZE, src);
    }

    // cherche le début du bloc prédateurs
    while (strcmp(line, "<predateurs>\n")) {
        line = fgets(buffer, BUFFER_SIZE, src);
    }

    // sérialise chaque prédateur
    line = fgets(buffer, BUFFER_SIZE, src);
    while (strcmp(line, "</predateurs>\n")) {

        int x, y;
        float e;
        int dir[2];

        sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f\n", &x, &y, &dir[0], &dir[1],
               &e);

        ajouter_animal(x, y, e, liste_predateur);
        line = fgets(buffer, BUFFER_SIZE, src);
    }

    fclose(src);
}

/* PARTIE 2*/

void bouger_animaux(Animal* la) {
    // Bouge un animal en fonction de dir

    Animal* current = la;
    while (current) {

        int a = current->x - current->dir[1];
        int b = current->y - current->dir[0];

        if (a == SIZE_X) {
            a = 0;
        } else if (a < 0) {
            a = SIZE_X - 1;
        }

        if (b == SIZE_Y) {
            b = 0;
        } else if (b < 0) {
            b = SIZE_Y - 1;
        }

        current->x = a;
        current->y = b;

        current = current->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal** liste_animal, float p_reproduce) {
    // Fait reproduire tous les animaux en fonction d'un facteur chance

    Animal* current = *liste_animal;
    float r = (float)(rand()) / RAND_MAX;

    while (current) {
        if (r < p_reproduce) {
            float new_e = current->energie / 2;
            ajouter_animal(current->x, current->y, new_e, liste_animal);
            current->energie = new_e;
        }

        current = current->suivant;
    }
}

void proies_work(Animal* current, int monde[SIZE_X][SIZE_Y]) {
    // La proie va manger de l'herbe si il y en a sur sa case
    assert(current);
    assert(monde);

    int grass = monde[current->x][current->y];

    if (grass >= 0) {
        current->energie += grass;
        monde[current->x][current->y] = temps_repousse_herbe;
    }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal** liste_proie, int monde[SIZE_X][SIZE_Y]) {
    // Fait mourir une proie si elle n'a plus d'énergie, sinon elle travaille
    assert(liste_proie);

    Animal* current = *liste_proie;
    bouger_animaux(current);

    // on actualise l'état des proies et on les fait agir
    // si elles sont encore en vies
    while (current) {
        current->energie -= 1.0;

        Animal* tmp = current->suivant;
        if (current->energie <= 0.0) {
            enlever_animal(liste_proie, current);
        } else {
            proies_work(current, monde);
        }
        current = tmp;
    }

    reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal* animal_en_XY(Animal* li, int x, int y) {
    // Si un animal est présent en (x,y), alors son adresse est retournée

    while (li) {
        if (li->x == x && li->y == y) {
            return li;
        }

        li = li->suivant;
    }

    return NULL;
}

void predateurs_work(Animal* predateur, Animal** liste_proie) {
    // Le prédateur va manger une proie si il y en a une sur sa case
    assert(predateur);
    assert(liste_proie);

    Animal* proie = animal_en_XY(*liste_proie, predateur->x, predateur->y);

    if (proie) {
        predateur->energie += proie->energie;
        enlever_animal(liste_proie, proie);
    }
}

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal** liste_predateur, Animal** liste_proie) {
    // Fait mourir un prédateur si il n'a plus d'énergies, sinon il travaille
    assert(liste_predateur);
    assert(liste_proie);

    Animal* current = *liste_predateur;
    bouger_animaux(current);

    while (current) {
        current->energie -= 1.0;

        Animal* tmp = current->suivant;
        if (current->energie <= 0.0) {
            enlever_animal(liste_predateur, current);
        } else {
            predateurs_work(current, liste_proie);
        }

        current = tmp;
    }

    reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) {
    // Fait pousser de l'herbe
    assert(monde);

    for (size_t i = 0; i < SIZE_X; i++) {
        for (size_t j = 0; j < SIZE_Y; j++) {
            monde[i][j] += 1;
        }
    }
}
