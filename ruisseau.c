#include "ruisseau.h"
#include "global.h"
#include "textures.h"

void initialiserRuisseau(ptrRuisseau ruisseau)
{
    ruisseau->objet.x = RIVER_POSITION_X;
    ruisseau->objet.y = RIVER_POSITION_Y;
    ruisseau->objet.width = RIVER_WIDTH;
    ruisseau->objet.height = RIVER_HEIGHT;
    ruisseau->objet.r = RIVER_COLOR_R;
    ruisseau->objet.g = RIVER_COLOR_G;
    ruisseau->objet.b = RIVER_COLOR_B;
    ruisseau->objet.texture = chargerTexture("Textures/ruisseau.png");  // Charger la texture
}

void dessinerRuisseau(ptrRuisseau ruisseau) // UPDATE
{
    dessinerObjetTexture(&ruisseau->objet);
}

