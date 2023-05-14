#pragma once

#include "objet.h"

typedef struct {
    Objet objet;
    char* texte;
} Bouton, *ptrBouton;

ptrBouton creerBouton(int x, int y, int width, int height, float r, float g, float b, char* texte);
void dessinerBouton(ptrBouton bouton);
void dessinerTexteBouton(ptrBouton bouton);
bool clicSurBouton(int xSouris, int ySouris, Bouton bouton);
