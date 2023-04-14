#pragma once

#include "objet.h"

enum EcranType {
    ECRAN_TITRE, ECRAN_FIN_DE_JEU
};

typedef struct {
    enum EcranType type;
} Ecran, *ptrEcran;

void afficherEcranTitre(ptrEcran ecran);
void afficherEcranFinDeJeu(ptrEcran ecran, int score);
void dessinerBouton(float x, float y, float width, float height, const char *text);
int boutonRejouerClique(float x, float y);