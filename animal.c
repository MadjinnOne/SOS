#include "animal.h"
#include "global.h"
#include "rondin.h"
#include "objet.h"
#include "textures.h"
#include "tir.h"

void initialiserAnimal(ptrAnimal animal)
{
    animal->objet.x = ANIMAL_POSITION_X;
    animal->objet.y = ANIMAL_POSITION_Y;
    animal->objet.width = ANIMAL_WIDTH;
    animal->objet.height = ANIMAL_HEIGHT;
    animal->objet.r = ANIMAL_COLOR_R;
    animal->objet.g = ANIMAL_COLOR_G;
    animal->objet.b = ANIMAL_COLOR_B;
    animal->vie = ANIME_NB_VIES;
    animal->score = 0;
    animal->objet.texture = chargerTexture("Textures/animal.png");
}

void dessinerAnimal(ptrAnimal animal) {
    dessinerObjetTexture(&animal->objet);
}

void deplacerAnimal(ptrAnimal animal, int x, int y)
{
    if ((animal->objet.x + x < LARGEUR_FENETRE) && (animal->objet.x + x >= 0))
        animal->objet.x += x;
    if ((animal->objet.y + y >= 0) && (animal->objet.y + y < HAUTEUR_FENETRE))
        animal->objet.y += y;
    dessinerAnimal(animal);
}

void entrée_clavier_animal(unsigned char touche, ptrAnimal animal) {

    switch (touche) {
        case 'z': // Déplacement vers le haut
            deplacerAnimal(animal, 0, -ANIMAL_DEPLACEMENT_Y);
            break;
        case 's': // Déplacement vers le bas
            deplacerAnimal(animal, 0, ANIMAL_DEPLACEMENT_Y);
            break;
        case 'q': // Déplacement vers la gauche
            deplacerAnimal(animal, -ANIMAL_DEPLACEMENT_X, 0);
            break;
        case 'd': // Déplacement vers la droite
            deplacerAnimal(animal, ANIMAL_DEPLACEMENT_X, 0);
            break;
        case ' ': // Tirer
            //ajouterTir(tirs, animal);
    }
}

bool animalSurRondin(ptrAnimal animal, Rondin rondins[], int nbRondins, int *index) {
    for (int i = 0; i < nbRondins; i++) {
        if (CollisionEntreObjets(&animal->objet, &rondins[i].objet)) {
            *index = i;
            return true;
        }
    }
    return false;
}

void deplacerAnimalAvecRondin(ptrAnimal animal, ptrRondin rondin) {
    if (rondin->direction == RIGHT) {
        deplacerAnimal(animal, rondin->vitesse, 0);
    } else {
        deplacerAnimal(animal, -rondin->vitesse, 0);
    }
}

void reinitialiserPositionAnimal(ptrAnimal animal)
{
    animal->objet.x = ANIMAL_POSITION_X;
    animal->objet.y = ANIMAL_POSITION_Y;
    dessinerAnimal(animal);
}
