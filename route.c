#include "route.h"
#include "global.h"
#include "textures.h"

void initialiserRoute(ptrRoute route)
{
    route->objet.x = ROAD_POSITION_X;
    route->objet.y = ROAD_POSITION_Y;
    route->objet.width = ROAD_WIDTH;
    route->objet.height = ROAD_HEIGHT;
    route->objet.r = ROAD_COLOR_R;
    route->objet.g = ROAD_COLOR_G;
    route->objet.b = ROAD_COLOR_B;
    route->objet.texture = chargerTexture("Textures/road.png");  // Charger la texture    
}

void dessinerRoute(ptrRoute Route) { // NEED UPDATE
    dessinerObjetTexture(&Route->objet);
}

