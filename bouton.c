#include "bouton.h"
#include <GL/glut.h>

ptrBouton creerBouton(int x, int y, int width, int height, float r, float g, float b, char* texte) {
    ptrBouton bouton = (ptrBouton)malloc(sizeof(Bouton));
    bouton->objet.x = x;
    bouton->objet.y = y;
    bouton->objet.width = width;
    bouton->objet.height = height;
    bouton->objet.r = r;
    bouton->objet.g = g;
    bouton->objet.b = b;
    bouton->texte = texte;
    return bouton;
}

void dessinerBouton(ptrBouton bouton) {
    dessinerObjet(&(bouton->objet));
    dessinerTexteBouton(bouton);
}

void dessinerTexteBouton(ptrBouton bouton) {
    glColor3f(0.0f, 0.0f, 0.0f); // Couleur du texte
    glRasterPos2f(bouton->objet.x + 10, bouton->objet.y + bouton->objet.height / 2); // Position du texte
    for (int i = 0; bouton->texte[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, bouton->texte[i]);
    }
}

bool clicSurBouton(int xSouris, int ySouris, Bouton bouton) {
    // Convertir les coordonnées de la souris en coordonnées de fenêtre
    // Notez que les coordonnées y sont inversées car l'origine est en haut à gauche
    float windowX = (float)xSouris;
    float windowY = (float)(ySouris);

    // Vérifiez si le clic était sur le bouton
    return windowX >= bouton.objet.x && windowX <= bouton.objet.x + bouton.objet.width &&
           windowY >= bouton.objet.y && windowY <= bouton.objet.y + bouton.objet.height;
}

