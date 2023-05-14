#pragma once

#include "objet.h"

#define TIR_WIDTH         10
#define TIR_HEIGHT        10
#define VITESSE_TIR       5

// Directions de déplacement du tir
enum DirectionTir {
    UP, DOWN
};

typedef struct {
    Objet objet;
    enum DirectionTir direction;
    int vitesse;
} Tir, *ptrTir;

void initialiserTir(ptrTir tir, int x, int y, enum DirectionTir direction, int vitesse);
void dessinerTir(ptrTir tir);
void deplacerTir(ptrTir tir);
//void ajouterTir(ptrListe liste,ptrAnimal Animal);
void supprimerTir(ptrListe liste, ptrTir tir);
