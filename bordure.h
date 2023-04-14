#pragma once

#include "objet.h"

#define BORDURE_01_POSITION_X    0
#define BORDURE_01_POSITION_Y    300
#define BORDURE_02_POSITION_X    0
#define BORDURE_02_POSITION_Y    520
#define BORDURE_WIDTH         800
#define BORDURE_HEIGHT        20
#define BORDURE_COLOR_R        0.0
#define BORDURE_COLOR_G        0.5
#define BORDURE_COLOR_B        0.0

typedef struct {
    Objet  objet;
} Bordure, *ptrBordure;

void initialiserBordure_haut(ptrBordure bordure);
void initialiserBordure_bas(ptrBordure bordure);
void dessinerBordure(ptrBordure bordure);