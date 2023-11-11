// 21135979
// FABRICI Tifenn
// Intensif

#include "ecosys.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#define NB_PROIES 20
#define NB_PREDATEURS 1
#define T_WAIT 400000

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

// Parametres initiaux
// float p_ch_dir = 0.01;
// float p_reproduce_proie = 0.4;
// float p_reproduce_predateur = 0.5;
// int temps_repousse_herbe = -15;

int main(int argc, char** argv) {

    /* A completer. Part 2:
     * exercice 4, questions 2 et 4
     * exercice 6, question 2
     * exercice 7, question 3
     * exercice 8, question 1
     */

    // test déplacement taure
    Animal* a = creer_animal(0, 0, 10.0);
    a->dir[0] = 1;
    a->dir[1] = 1;
    bouger_animaux(a);
    assert(a->x == SIZE_X - 1);
    assert(a->y == SIZE_Y - 1);
    a->dir[0] = -1;
    a->dir[1] = -1;
    bouger_animaux(a);
    assert(a->x == 0);
    assert(a->y == 0);

    a = liberer_liste_animaux(a);

    // test reproduction
    Animal* proies = NULL;
    Animal* predateurs = NULL;
    lire_ecosys("ecosys.txt", &predateurs, &proies);
    reproduce(&proies, 1);

    assert(compte_animal_it(proies) == 40);
    assert(compte_animal_it(predateurs) == 20);

    afficher_ecosys(predateurs, proies);

    proies = liberer_liste_animaux(proies);
    predateurs = liberer_liste_animaux(predateurs);

    clear_screen();

    // Simulation

    int monde[SIZE_X][SIZE_Y];

    for (size_t i = 0; i < SIZE_X; i++) {
        for (size_t j = 0; j < SIZE_Y; j++) {
            monde[i][j] = 0;
        }
    }

    lire_ecosys("ecosys.txt", &predateurs, &proies);

    FILE* data = fopen("Evol_Pop.txt", "w");
    assert(data);

    int nb_proies = compte_animal_it(proies);
    int nb_predateurs = compte_animal_it(predateurs);
    assert(nb_proies == 20);
    assert(nb_predateurs == 20);

    int i = 0;
    while (nb_proies > 0 && i < 1000) {
        // clear_screen();
        rafraichir_proies(&proies, monde);
        rafraichir_predateurs(&predateurs, &proies);
        rafraichir_monde(monde);

        afficher_ecosys(proies, predateurs);
        printf("Itération %d\n", i + 1);

        fprintf(data, "%d %d %d\n", i + 1, nb_proies, nb_predateurs);

        // usleep(T_WAIT);
        nb_proies = compte_animal_it(proies);
        nb_predateurs = compte_animal_it(predateurs);
        i++;
    }

    fclose(data);

    return 0;
}
