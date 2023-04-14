#pragma once

#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
    float r;
    float g;
    float b;
} Objet, *ptrObjet;


void dessinerObjet(ptrObjet objet);
bool CollisionEntreObjets(ptrObjet objet_01 , ptrObjet objet_02);

