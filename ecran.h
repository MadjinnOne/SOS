#pragma once

#include "objet.h"

enum EcranType {
    ECRAN_TITRE, ECRAN_FIN_DE_JEU
};
typedef struct {
    enum EcranType type;
} Ecran, *ptrEcran;

void afficherEcranTitre(ptrEcran ecran, GLuint *textureFondEcranTitre);
void afficherEcranFinDeJeu(ptrEcran ecran, int score);
void afficherEcranCommandes(GLuint *textureFondEcranCommand);
void afficherEcranLeaderboard(GLuint *textureFondEcranScore);

