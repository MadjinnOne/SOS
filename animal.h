#pragma once

#include "objet.h"

#define ANIMAL_POSITION_X    380
#define ANIMAL_POSITION_Y    560
#define ANIMAL_WIDTH         20
#define ANIMAL_HEIGHT        20
#define ANIMAL_COLOR_R        0.0
#define ANIMAL_COLOR_G        1.0
#define ANIMAL_COLOR_B        0.0

#define ANIMAL_DEPLACEMENT_X 20
#define ANIMAL_DEPLACEMENT_Y 20

#define ANIME_NB_VIES    3;

// Directions de déplacement
// enum Direction {
//     UP, DOWN, LEFT, RIGHT
// };

typedef struct {
    Objet objet;
    //enum Direction direction;
    int vie;
    int score;
} Animal, *ptrAnimal;

void initialiserAnimal(ptrAnimal animal);
void dessinerAnimal(ptrAnimal animal);
void deplacerAnimal(ptrAnimal animal, int x, int y);
void reinitialiserPositionAnimal(ptrAnimal animal);