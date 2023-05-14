#pragma once

#include "objet.h"
#include "voiture.h"
#include "global.h"

#define RONDIN_WIDTH         80
#define RONDIN_HEIGHT        20

#define VITESSE_RONDIN_MIN 5
#define VITESSE_RONDIN_MAX 10

#define NB_RONDIN_MAX 15
#define NB_BANDES_RONDINS 12



typedef struct {
    Objet objet;
    enum Direction direction;
    int vitesse;
} Rondin, *ptrRondin;

void initialiserRondin(ptrRondin rondin, int x, int y, enum Direction direction, int vitesse);
void initialiserListeRondins(Rondin TableRondin[]);
void dessinerRondin(ptrRondin rondin);
void deplacerRondin(ptrRondin rondin, int x);
