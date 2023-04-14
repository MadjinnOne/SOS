#include "objet.h"
#include "global.h"

void dessinerObjet(ptrObjet objet)
{
    // Dessin de la route
    glColor3f(objet->r, objet->g, objet->b);
    glBegin(GL_QUADS);
    glVertex2f(objet->x, objet->y);
    glVertex2f(objet->x + objet->width, objet->y);
    glVertex2f(objet->x + objet->width, objet->y + objet->height);
    glVertex2f(objet->x, objet->y + objet->height);
    glEnd();
}

bool CollisionEntreObjets(ptrObjet objet_01 , ptrObjet objet_02)
{
    if(objet_01->x < (objet_02->x + objet_02->width) && 
        (objet_01->x + objet_01->width) > objet_02->x && 
        objet_01->y < (objet_02->y + objet_02->height) && 
        (objet_01->y + objet_01->height) > objet_02->y)
        return true;
    return false;
}