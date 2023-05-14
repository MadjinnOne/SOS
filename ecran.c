#include "global.h"
#include "ecran.h"
#include "leaderboard.h"
#include "bouton.h"
#include <stdio.h>
#include <string.h>





// Stockez vos boutons en dehors de la fonction afficherEcranTitre pour qu'ils soient accessibles dans mouseClick
ptrBouton boutonQuitter;
ptrBouton boutonLeaderboard;
ptrBouton boutonCommandes;
ptrBouton boutonJouer;

void afficherEcranTitre(ptrEcran ecran, GLuint *textureFondEcranTitre) {
    // Création des boutons     
    boutonQuitter = creerBouton(LARGEUR_FENETRE / 2 + 290, HAUTEUR_FENETRE / 2 + 240 , 100, 50, 1.0f, 0.0f, 0.0f, "Quitter");    
    boutonLeaderboard = creerBouton(LARGEUR_FENETRE / 2 + 290, HAUTEUR_FENETRE / 2 + 180, 100, 50, 1.0f, 1.0f, 0.0f, "Scores");
    boutonCommandes = creerBouton(LARGEUR_FENETRE / 2 + 290, HAUTEUR_FENETRE / 2 + 120, 100, 50, 1.0f, 1.0f, 0.0f, "Commandes");
    boutonJouer = creerBouton(LARGEUR_FENETRE / 2 + 290, HAUTEUR_FENETRE / 2 + 60, 100, 50, 0.0f, 1.0f, 0.0f, "Jouer");

    // Affichage de la texture de fond
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureFondEcranTitre);
    // Définition de la couleur courante sur blanc
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(LARGEUR_FENETRE, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0, HAUTEUR_FENETRE);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Dessin des boutons
    dessinerBouton(boutonQuitter);
    dessinerBouton(boutonLeaderboard);
    dessinerBouton(boutonCommandes);
    dessinerBouton(boutonJouer);

    // Echange des buffers
    glutSwapBuffers();
}


void afficherEcranLeaderboard(GLuint *textureFondEcranScore) {
    // Affichage de la texture de fond
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureFondEcranScore);
    // Définition de la couleur courante sur blanc
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(LARGEUR_FENETRE, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0, HAUTEUR_FENETRE);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Affichage du titre "Scores" centré
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(LARGEUR_FENETRE / 2 + 110, HAUTEUR_FENETRE / 2 - 200);
    const char *titre = "Scores";
    for (int i = 0; titre[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, titre[i]);
    }

    // Affichage du leaderboard
    LeaderboardEntry entries[MAX_ENTRIES];
    int numEntries;
    lireLeaderboard("leaderboard.txt", entries, &numEntries);

    // Trier les entrées par score
    trierLeaderboard(entries, numEntries);

    // Affichage des entrées du leaderboard
    glColor3f(0.0f, 0.0f, 0.0f);
    // Initialiser la position y au centre de la fenêtre
    float y = HAUTEUR_FENETRE / 2 - 150;
    for (int i = 0; i < numEntries; i++) {
        char entryText[100];
        sprintf(entryText, "%d. %s: %d", i + 1, entries[i].name, entries[i].score);
        glRasterPos2f(LARGEUR_FENETRE / 2 + 110 , y);
        for (int j = 0; entryText[j] != '\0'; j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, entryText[j]);
        }
        // Déplacer la position y vers le bas pour la prochaine entrée
        y += 20;
    }
    // Dessin des boutons
    dessinerBouton(boutonQuitter);
    dessinerBouton(boutonLeaderboard);
    dessinerBouton(boutonCommandes);
    dessinerBouton(boutonJouer); 

    // Échanger les buffers
    glutSwapBuffers();
}




void afficherEcranCommandes(GLuint *textureFondEcranCommand) {
    // Affichage de la texture de fond
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *textureFondEcranCommand);
    // Définition de la couleur courante sur blanc
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(LARGEUR_FENETRE, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0, HAUTEUR_FENETRE);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Affichage du titre "Commandes"
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(LARGEUR_FENETRE / 2 - 70, HAUTEUR_FENETRE - 460);
    const char *titre = "Controles";
    for (int i = 0; titre[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, titre[i]);
    }

    // Affichage des commandes
    const char *commandes[] = {
        "ESC - Quitter le jeu",        
        "Q - Gauche",
        "D - Droite",
        "S - Descendre",        
        "Z - Monter",
        "SPACE - Tirer"
    };
    int nbCommandes = sizeof(commandes) / sizeof(commandes[0]);

    for (int i = 0; i < nbCommandes; i++) {
        glRasterPos2f(LARGEUR_FENETRE / 2 - 100, HAUTEUR_FENETRE - 280 - 30 * i);
        for (int j = 0; commandes[i][j] != '\0'; j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, commandes[i][j]);
        }
    }
    // Dessin des boutons
    dessinerBouton(boutonQuitter);
    dessinerBouton(boutonLeaderboard);
    dessinerBouton(boutonCommandes);
    dessinerBouton(boutonJouer); 

    // Echange des buffers
    glutSwapBuffers();
}



void afficherEcranFinDeJeu(ptrEcran ecran, int score) {
    // Affichage d'un écran noir
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Affichage du texte "Game Over"
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(LARGEUR_FENETRE / 2 - 50, HAUTEUR_FENETRE / 2 - 30);
    const char *message = "Game Over";
    for (int i = 0; message[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }

    // Affichage du score
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    glRasterPos2f(LARGEUR_FENETRE / 2 - 50, HAUTEUR_FENETRE / 2);
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
    }
    // Dessin des boutons
    dessinerBouton(boutonQuitter);
    dessinerBouton(boutonLeaderboard);
    dessinerBouton(boutonCommandes);
    dessinerBouton(boutonJouer); 
    glutSwapBuffers();
}
