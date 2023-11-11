// 21135979
// FABRICI Tifenn
// Intensif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "ecosys.h"

int main() {

    Animal* liste_proie = NULL;
    Animal* liste_predateur = NULL;
    float energie = 10.0;

    srand(time(NULL));

    for (size_t i = 0; i < 20; i++) {
        int x = rand() % SIZE_X;
        int y = rand() % SIZE_Y;

        ajouter_animal(x, y, energie, &liste_proie);
    }

    for (size_t i = 0; i < 20; i++) {
        int x = rand() % SIZE_X;
        int y = rand() % SIZE_Y;

        ajouter_animal(x, y, energie, &liste_predateur);
    }

    assert(compte_animal_rec(liste_proie) == 20);
    assert(compte_animal_rec(liste_predateur) == 20);

    afficher_ecosys(liste_predateur, liste_proie);

    // écriture test
    ecrire_ecosys("ecosys.txt", liste_predateur, liste_proie);

    // suppression test
    int i = 0;
    while (i < 5) {

        enlever_animal(&liste_proie, liste_proie);
        enlever_animal(&liste_predateur, liste_predateur);

        i++;
    }

    assert(compte_animal_rec(liste_proie) == 15);
    assert(compte_animal_rec(liste_predateur) == 15);

    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur);

    // lecture test
    Animal* proies = NULL;
    Animal* predateurs = NULL;
    lire_ecosys("ecosys.txt", &predateurs, &proies);

    assert(compte_animal_it(predateurs) == 20);
    assert(compte_animal_it(proies) == 20);

    afficher_ecosys(predateurs, proies);

    liberer_liste_animaux(proies);
    liberer_liste_animaux(predateurs);

    return 0;
}