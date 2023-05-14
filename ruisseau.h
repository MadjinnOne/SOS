#pragma once

#include "objet.h"

#define RIVER_POSITION_X    0
#define RIVER_POSITION_Y    60
#define RIVER_WIDTH         800
#define RIVER_HEIGHT        240
#define RIVER_COLOR_R        0.0
#define RIVER_COLOR_G        0.5
#define RIVER_COLOR_B        1.0

typedef struct {
    Objet  objet;
} Ruisseau, *ptrRuisseau;

void initialiserRuisseau(ptrRuisseau ruisseau);
void dessinerRuisseau(ptrRuisseau ruisseau);
