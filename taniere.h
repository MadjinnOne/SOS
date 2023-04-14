#pragma once

#include "objet.h"

#define TANIERE_POSITION_X    0
#define TANIERE_POSITION_Y    0
#define TANIERE_WIDTH         800
#define TANIERE_HEIGHT        50
#define TANIERE_COLOR_R        0.0
#define TANIERE_COLOR_G        0.5
#define TANIERE_COLOR_B        0.0

typedef struct {
    Objet  objet;
} Taniere, *ptrTaniere;

void initialiserTaniere(ptrTaniere taniere);
void dessinerTaniere(ptrTaniere taniere);