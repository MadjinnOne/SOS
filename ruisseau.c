#include "ruisseau.h"

void initialiserRuisseau(ptrRuisseau ruisseau)
{
    ruisseau->objet.x = RIVER_POSITION_X;
    ruisseau->objet.y = RIVER_POSITION_Y;
    ruisseau->objet.width = RIVER_WIDTH;
    ruisseau->objet.height = RIVER_HEIGHT;
    ruisseau->objet.r = RIVER_COLOR_R;
    ruisseau->objet.g = RIVER_COLOR_G;
    ruisseau->objet.b = RIVER_COLOR_B;
}

void dessinerRuisseau(ptrRuisseau ruisseau)
{
    // Dessin du ruisseau
    dessinerObjet(&ruisseau->objet);
}
