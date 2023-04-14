#include "voiture.h"
#include "global.h"

#define NOMBRE_COULEURS_MAX 6


static void GenererCouleur(ptrVoiture voiture);

void initialiserVoiture(ptrVoiture voiture, int x, int y, enum Direction direction, int vitesse)
{
    voiture->objet.x = x;
    voiture->objet.y = y;
    voiture->objet.width = VOITURE_WIDTH;
    voiture->objet.height = VOITURE_HEIGHT;
    GenererCouleur(voiture);
    voiture->direction = direction;
    voiture->vitesse = vitesse;
}

static void GenererCouleur(ptrVoiture voiture)
{
    struct couleur
    {
        GLfloat r;
        GLfloat g;
        GLfloat b;
    };

    struct couleur couleurs[NOMBRE_COULEURS_MAX] = {{ROUGE}, {BLEU}, {JAUNE}, {ORANGE}, {MAUVE}, {NOIR}};
    int index = rand()%NOMBRE_COULEURS_MAX;
    voiture->objet.r = couleurs[index].r;
    voiture->objet.g = couleurs[index].g;
    voiture->objet.b = couleurs[index].b;
}

void dessinerVoiture(ptrVoiture voiture) {
    glPushMatrix(); // Sauvegarde la matrice de modélisation
    dessinerObjet(&voiture->objet);
    glPopMatrix(); // Restaure la matrice de modélisation
}

/// @brief 
/// @param voiture : 
/// @param x : vitesse de déplacement, si 0, utilise la vitesse définie au sein de l'objet
void deplacerVoiture(ptrVoiture voiture, int x)
{
    int vitesse_x = x;
    if (vitesse_x == 0)
        vitesse_x = voiture->vitesse;
    if (voiture->direction == RIGHT)
    {
        if (voiture->objet.x + vitesse_x < LARGEUR_FENETRE + VOITURE_WIDTH)
        {
            voiture->objet.x += vitesse_x;
        }
        else
        {
            voiture->objet.x = 0 - VOITURE_WIDTH;
        }
    }
    else
    {
        if (voiture->objet.x - vitesse_x > 0 - VOITURE_WIDTH)
        {
            voiture->objet.x -= vitesse_x;
        }
        else
        {
            voiture->objet.x = LARGEUR_FENETRE + VOITURE_WIDTH;
        }
    }
    dessinerVoiture(voiture);
}
