#include "clavier.h"
#include "global.h"
#include "animal.h"

void clavier(unsigned char touche, ptrAnimal animal) {
    switch (touche) {
        case 'z': // Déplacement vers le haut
            if (animal->objet.y - ANIMAL_DEPLACEMENT_Y >= 0) {
                animal->objet.y -= ANIMAL_DEPLACEMENT_Y;
            }
            break;
        case 's': // Déplacement vers le bas
            if (animal->objet.y + ANIMAL_DEPLACEMENT_Y < HAUTEUR_FENETRE) {
                animal->objet.y += ANIMAL_DEPLACEMENT_Y;
            }
            break;
        case 'q': // Déplacement vers la gauche
            if (animal->objet.x - ANIMAL_DEPLACEMENT_X >= 0) {
                animal->objet.x -= ANIMAL_DEPLACEMENT_X;
            }
            break;
        case 'd': // Déplacement vers la droite
            if (animal->objet.x + ANIMAL_DEPLACEMENT_X < LARGEUR_FENETRE) {
                animal->objet.x += ANIMAL_DEPLACEMENT_X;
            }
            break;
    }

    glutPostRedisplay();
}