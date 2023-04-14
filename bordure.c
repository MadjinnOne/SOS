#include "bordure.h"

void initialiserBordure(ptrBordure bordure, int x, int y)
{
    bordure->objet.x = x;
    bordure->objet.y = y;
    bordure->objet.width = BORDURE_WIDTH;
    bordure->objet.height = BORDURE_HEIGHT;
    bordure->objet.r = BORDURE_COLOR_R;
    bordure->objet.g = BORDURE_COLOR_G;
    bordure->objet.b = BORDURE_COLOR_B;
}

void initialiserBordure_haut(ptrBordure bordure)
{
    initialiserBordure(bordure, BORDURE_01_POSITION_X, BORDURE_01_POSITION_Y);
}

void initialiserBordure_bas(ptrBordure bordure)
{
    initialiserBordure(bordure, BORDURE_02_POSITION_X, BORDURE_02_POSITION_Y);
}

void dessinerBordure(ptrBordure bordure)
{
    // Dessin de la bordure
    dessinerObjet(&bordure->objet);
}