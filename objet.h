#pragma once

#include <stdbool.h>
#include <GL/gl.h>
#include <FreeImage.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
    float r;
    float g;
    float b;
    GLuint texture;    
} Objet, *ptrObjet;

// Déclaration préabable pour utilisation dans la définition de la structure plus bas (élément)
typedef struct Element Element, *ptrElement;

struct Element {
    void* objetDefini;
    ptrElement suivant;
};

typedef struct {
    ptrElement premier;
    int taille;
} Liste, *ptrListe;

void dessinerObjet(ptrObjet objet);
void dessinerObjetTexture(ptrObjet objet);
bool CollisionEntreObjets(ptrObjet objet_01 , ptrObjet objet_02);

ptrListe initialiserListe();
void initialiserListeStatic(ptrListe liste);
void ajouterObjet(ptrListe liste, void* objetDefini);
void supprimerObjet(ptrListe liste, void* objetDefini);
