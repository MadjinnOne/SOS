#include "rondin.h"
#include "global.h"
#include "textures.h"


void initialiserRondin(ptrRondin rondin, int x, int y, enum Direction direction, int vitesse)
{
    rondin->objet.x = x;
    rondin->objet.y = y;
    rondin->objet.width = RONDIN_WIDTH;
    rondin->objet.height = RONDIN_HEIGHT;
    rondin->objet.r = 0.5f;
    rondin->objet.g = 0.35f;
    rondin->objet.b = 0.05f;
    rondin->direction = direction;
    rondin->vitesse = vitesse;
    rondin->objet.texture = chargerTexture("Textures/rondin.png");  // Charger la texture
}

void initialiserListeRondins(Rondin TableRondin[])
{
    enum Direction dir[NB_BANDES_RONDINS];
    int vitesse[NB_BANDES_RONDINS];
    for (int j = 0; j < NB_BANDES_RONDINS; j++)
    {
        dir[j] = (j%2)?RIGHT:LEFT;
        vitesse[j] = rand() % (VITESSE_MAX - VITESSE_MIN + 1) + VITESSE_MIN;
    }

    for (int i = 0 ; i < NB_RONDIN_MAX; i++)
    {
        int bande;
        if (i >= NB_BANDES_RONDINS)
            bande = rand()%NB_BANDES_RONDINS;
        else
            bande = i;
        int position_x = LARGEUR_FENETRE * i/ NB_RONDIN_MAX;
        initialiserRondin(&TableRondin[i], position_x, 60 + bande*20, dir[bande], vitesse[bande]);
    }
}

void dessinerRondin(ptrRondin rondin) {
    dessinerObjetTexture(&rondin->objet);
}

void deplacerRondin(ptrRondin rondin, int x)
{
    int vitesse_x = x;
    if (vitesse_x == 0)
        vitesse_x = rondin->vitesse;
    if (rondin->direction == RIGHT)
    {
        if (rondin->objet.x + vitesse_x < LARGEUR_FENETRE + RONDIN_WIDTH)
        {
            rondin->objet.x += vitesse_x;
        }
        else
        {
            rondin->objet.x = 0 - RONDIN_WIDTH;
        }
    }
    else
    {
        if (rondin->objet.x - vitesse_x > 0 - RONDIN_WIDTH)
        {
            rondin->objet.x -= vitesse_x;
        }
        else
        {
            rondin->objet.x = LARGEUR_FENETRE + RONDIN_WIDTH;
        }
    }
    dessinerRondin(rondin);
}
