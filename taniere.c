#include "taniere.h"

void initialiserTaniere(ptrTaniere taniere)
{
    taniere->objet.x = TANIERE_POSITION_X;
    taniere->objet.y = TANIERE_POSITION_Y;
    taniere->objet.width = TANIERE_WIDTH;
    taniere->objet.height = TANIERE_HEIGHT;
    taniere->objet.r = TANIERE_COLOR_R;
    taniere->objet.g = TANIERE_COLOR_G;
    taniere->objet.b = TANIERE_COLOR_B;
}

void dessinerTaniere(ptrTaniere taniere)
{
    // Dessin de la taniere
    dessinerObjet(&taniere->objet);
}
