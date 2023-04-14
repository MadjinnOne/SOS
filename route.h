#pragma once

#include "objet.h"

#define ROAD_POSITION_X 0
#define ROAD_POSITION_Y 320
#define ROAD_WIDTH      800
#define ROAD_HEIGHT     200
#define ROAD_COLOR_R    0.2
#define ROAD_COLOR_G    0.2
#define ROAD_COLOR_B    0.2

typedef struct {
    Objet objet;
} Route, *ptrRoute;

void initialiserRoute(ptrRoute route);
void dessinerRoute(ptrRoute route);