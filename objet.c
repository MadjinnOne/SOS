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

void dessinerObjetTexture(ptrObjet objet)
{
    glPushMatrix(); // Sauvegarde la matrice de modélisation
    glColor3f(1.0f, 1.0f, 1.0f); // Réinitialiser la couleur à blanc

    // Activer le blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Activer les textures et lier la texture du rondin
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, objet->texture);

    // Dessiner le corps du rondin
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(objet->x, objet->y);
    glTexCoord2f(1, 0); glVertex2f(objet->x + objet->width, objet->y);
    glTexCoord2f(1, 1); glVertex2f(objet->x + objet->width, objet->y + objet->height);
    glTexCoord2f(0, 1); glVertex2f(objet->x, objet->y + objet->height);
    glEnd();

    // Désactiver le blending et les textures
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix(); // Restaurer la matrice de modélisation
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

ptrListe initialiserListe()
{
    ptrListe liste = malloc(sizeof(*liste));
    if (liste == NULL)
        exit(EXIT_FAILURE);
    liste->premier = NULL;
    liste->taille = 0;
    
    return liste;
}

void initialiserListeStatic(ptrListe liste)
{
    if (liste == NULL)
        exit(EXIT_FAILURE);
    liste->premier = NULL;
    liste->taille = 0;
}

void ajouterObjet(ptrListe liste, void* objetDefini)
{
    if (liste == NULL)
        exit(EXIT_FAILURE);

    ptrElement element = malloc(sizeof(*element));
    if (element == NULL)
        exit(EXIT_FAILURE);

    element->objetDefini = objetDefini;
    element->suivant = liste->premier;
    liste->premier = element;
    liste->taille++;
}

void supprimerObjet(ptrListe liste, void* objetDefini)
{
    if (liste == NULL)
        exit(EXIT_FAILURE);
    
    if (objetDefini == NULL)
        exit(EXIT_FAILURE);

    ptrElement element = liste->premier;
    ptrElement element_precedent = NULL;
    while(element != NULL)
    {
        if (element->objetDefini == objetDefini)
        {
            if (element == liste->premier)
                liste->premier = element->suivant;
            else
                element_precedent->suivant = element->suivant;

            liste->taille--;
            free(element);
            break;
        }
        element_precedent = element;
        element = element->suivant;
    }
}