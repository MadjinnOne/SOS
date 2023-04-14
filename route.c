#include "route.h"

void initialiserRoute(ptrRoute route)
{
    route->objet.x = ROAD_POSITION_X;
    route->objet.y = ROAD_POSITION_Y;
    route->objet.width = ROAD_WIDTH;
    route->objet.height = ROAD_HEIGHT;
    route->objet.r = ROAD_COLOR_R;
    route->objet.g = ROAD_COLOR_G;
    route->objet.b = ROAD_COLOR_B;
}

void dessinerRoute(ptrRoute route)
{
    // Dessin de la route
    dessinerObjet(&route->objet);
}