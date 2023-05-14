#include "tir.h"
#include "global.h"
#include "animal.h"

void initialiserTir(ptrTir tir, int x, int y, enum DirectionTir direction, int vitesse)
{
    tir->objet.x = x;
    tir->objet.y = y;
    tir->objet.width = TIR_WIDTH;
    tir->objet.height = TIR_HEIGHT;
    tir->direction = direction;
    tir->vitesse = vitesse;
}

void initialiserListeTir(ptrListe tirs, ptrAnimal animal)
{
    initialiserListeStatic(tirs);
}


void dessinerTir(ptrTir tir) {
    glPushMatrix(); // Sauvegarde la matrice de modélisation
    dessinerObjet(&tir->objet);
    glPopMatrix(); // Restaure la matrice de modélisation
}

void deplacerTir(ptrTir tir)
{
    // Assurez-vous que le tir existe
    if (tir == NULL)
        exit(EXIT_FAILURE);

    // Déplacez le tir vers le haut
    tir->objet.y -= tir->vitesse;

    dessinerTir(tir);
}


void ajouterTir(ptrListe liste, ptrAnimal animal)
{
    if (liste == NULL || animal == NULL)
        exit(EXIT_FAILURE);

    ptrTir tir = malloc(sizeof(*tir));
    if (tir == NULL)
        exit(EXIT_FAILURE);

    // Utilisez la position de l'animal pour initialiser le tir
    initialiserTir(tir, animal->objet.x, animal->objet.y, UP, VITESSE_TIR);

    ajouterObjet(liste, tir);
}


void supprimerTir(ptrListe liste, ptrTir tir)
{
    if (liste == NULL)
        exit(EXIT_FAILURE);
       
    supprimerObjet(liste, tir);
    free(tir);
}
