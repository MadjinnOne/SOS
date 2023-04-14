#pragma once

#include "objet.h"

#define VOITURE_WIDTH         40
#define VOITURE_HEIGHT        20

#define VITESSE_MIN 10
#define VITESSE_MAX 20

// Directions de déplacement
enum Direction {
    LEFT, RIGHT
};

typedef struct {
    Objet objet;
    enum Direction direction;
    int vitesse;
} Voiture, *ptrVoiture;

void initialiserVoiture(ptrVoiture voiture, int x, int y, enum Direction direction, int vitesse);
void dessinerVoiture(ptrVoiture voiture);
void deplacerVoiture(ptrVoiture voiture, int x);
