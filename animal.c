#include "animal.h"
#include "global.h"

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
}

void dessinerAnimal(ptrAnimal animal) {
    glPushMatrix(); // Sauvegarde la matrice de modélisation

    //glTranslatef(animal->objet.x, animal->objet.y, 0); // Déplace la grenouille à la position (x, y)
    //glRotatef(45, 0, 0, 1); // Tourne la grenouille de 45 degrés autour de l'axe z
    //glScalef(2, 2, 1); // Redimensionne la grenouille avec un facteur de 2 sur les axes x et y
    dessinerObjet(&animal->objet);

    glPopMatrix(); // Restaure la matrice de modélisation
}

void deplacerAnimal(ptrAnimal animal, int x, int y)
{
    animal->objet.x += x;
    animal->objet.y += y;
    dessinerAnimal(animal);
}

void reinitialiserPositionAnimal(ptrAnimal animal)
{
    animal->objet.x = ANIMAL_POSITION_X;
    animal->objet.y = ANIMAL_POSITION_Y;
    dessinerAnimal(animal);
}
