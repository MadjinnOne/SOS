#include "global.h"
#include "ecran.h"
#include "clavier.h"
#include <stdio.h>
#include <string.h>

/*
PRE: ecran est un pointeur valide vers un objet Ecran.
POST: L'écran est effacé et affiche un fond noir.
Le texte "SOS" est affiché au centre de l'écran, légèrement au-dessus du milieu.
Le texte "Appuyez sur ENTER pour commencer" est affiché au centre de l'écran, légèrement en dessous du milieu.
L'état précédent des autres éléments de la scène est remplacé par l'écran de titre.
Les tampons sont échangés pour afficher l'écran de titre à l'utilisateur.
*/
void afficherEcranTitre(ptrEcran ecran) {
    // Affichage d'un écran noir
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Affichage du texte "SOS"
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(LARGEUR_FENETRE / 2 - 70, HAUTEUR_FENETRE / 2 + 50);
    const char *titre = "SOS";
    for (int i = 0; titre[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, titre[i]);
    }

    // Affichage du texte "Appuyez sur une touche pour commencer"
    glRasterPos2f(LARGEUR_FENETRE / 2 - 150, HAUTEUR_FENETRE / 2 - 50);
    const char *message = "Appuyez sur ENTER pour commencer";
    for (int i = 0; message[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, message[i]);
    }

    // Echange des buffers
    glutSwapBuffers();
}

/*
PRE: ecran est un pointeur valide vers un objet Ecran.
score est un entier représentant le score du joueur à la fin de la partie.
POST: L'écran est effacé et affiche un fond noir.
Le texte "Game Over" est affiché au centre de l'écran.
Le score de la partie est affiché sous le texte "Game Over".
Un bouton "Rejouer" est dessiné en bas de l'écran.
L'état précédent des autres éléments de la scène est remplacé par l'écran de fin de jeu.
*/
void afficherEcranFinDeJeu(ptrEcran ecran, int score) {   

    // Affichage d'un écran noir
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Affichage du texte "Game Over"
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(LARGEUR_FENETRE / 2 - 50, HAUTEUR_FENETRE / 2);
    const char *message = "Game Over";
    for (int i = 0; message[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }

    // Affichage du score
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    glRasterPos2f(LARGEUR_FENETRE / 2 - 50, HAUTEUR_FENETRE / 2 - 30);
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
    }
    // Dessin du bouton rejouer
    dessinerBouton(LARGEUR_FENETRE / 2 - 50, HAUTEUR_FENETRE - 50, 100, 30, "Rejouer");
}

/*
PRE: x, y, width et height sont des valeurs positives ou nulles.
text est une chaîne de caractères non nulle et valide.
Les coordonnées (x, y) ainsi que la taille du bouton (width, height) sont compatibles avec les dimensions de la fenêtre.
POST: Un bouton rectangulaire est dessiné à l'écran aux coordonnées (x, y) avec une largeur width et une hauteur height.
Le texte fourni en paramètre est affiché et centré dans le bouton.
L'état précédent des autres éléments de la scène reste inchangé.
*/
void dessinerBouton(float x, float y, float width, float height, const char *text) {
    glColor3f(0.5f, 0.5f, 0.5f);
    glRectf(x, y, x + width, y + height);

    glColor3f(1.0f, 1.0f, 1.0f);
    int textWidth = strlen(text) * 9; // 9 est une estimation de la largeur de chaque caractère avec la police GLUT_BITMAP_HELVETICA_18
    int textHeight = 18; // Hauteur de la police GLUT_BITMAP_HELVETICA_18
    int verticalOffset = 15; // Ajustement vertical pour centrer le texte dans le bouton
    glRasterPos2f(x + width / 2 - textWidth / 2, y + height / 2 - textHeight / 2 + verticalOffset);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

/*
PRE: x et y sont des coordonnées de l'écran, telles que 0 <= x <= LARGEUR_FENETRE et 0 <= y <= HAUTEUR_FENETRE.
POST: La fonction retourne 1 si les coordonnées (x, y) se trouvent à l'intérieur du rectangle défini par boutonX, boutonY, boutonWidth et boutonHeight (c'est-à-dire si le point (x, y) est sur le bouton "Rejouer").
La fonction retourne 0 si les coordonnées (x, y) ne se trouvent pas à l'intérieur de ce rectangle (c'est-à-dire si le point (x, y) n'est pas sur le bouton "Rejouer").
*/
int boutonRejouerClique(float x, float y) {
    float boutonX = LARGEUR_FENETRE / 2 - 50;
    float boutonY = HAUTEUR_FENETRE - 50;
    float boutonWidth = 100;
    float boutonHeight = 30;
    //float mouseY = HAUTEUR_FENETRE - y; // Inverser l'axe des ordonnées

    if (x >= boutonX && x <= boutonX + boutonWidth && y >= boutonY && y <= boutonY + boutonHeight) {
        return 1;
    }
    return 0;
}
