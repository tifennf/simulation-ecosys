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
#define NB_PREDATEURS 20
#define T_WAIT 40000

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
    // Simulation
    srand(1);

    Animal* proies = NULL;
    Animal* predateurs = NULL;
    float energie = 10.0;

    for (size_t i = 0; i < NB_PROIES; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie, &proies);
    }
    for (size_t i = 0; i < NB_PREDATEURS; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie, &predateurs);
    }

    int monde[SIZE_X][SIZE_Y];
    for (size_t i = 0; i < SIZE_X; i++) {
        for (size_t j = 0; j < SIZE_Y; j++) {
            monde[i][j] = 0;
        }
    }

    FILE* data = fopen("Evol_Pop.txt", "w");
    assert(data);

    int nb_proies = compte_animal_it(proies);
    int nb_predateurs = compte_animal_it(predateurs);

    printf("%d\n", nb_proies);
    assert(nb_proies == NB_PROIES);
    assert(nb_predateurs == NB_PREDATEURS);

    int i = 0;
    while (nb_proies > 0 && i < 500) {
        rafraichir_proies(&proies, monde);
        rafraichir_predateurs(&predateurs, &proies);
        rafraichir_monde(monde);

        afficher_ecosys(proies, predateurs);
        printf("Itération %d\n", i + 1);

        fprintf(data, "%d %d %d\n", i + 1, nb_proies, nb_predateurs);

        usleep(T_WAIT);
        nb_proies = compte_animal_it(proies);
        nb_predateurs = compte_animal_it(predateurs);
        i++;
    }

    fclose(data);

    proies = liberer_liste_animaux(proies);
    predateurs = liberer_liste_animaux(predateurs);
    return 0;
}
