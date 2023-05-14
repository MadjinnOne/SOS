#pragma once

#include "objet.h"
#ifdef __linux__
    #include <GL/glut.h>
#elif _WIN32
    #include "G:/tmp/freeglut/include/GL/glut.h"
#elif __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
    #error "Unknown platform"
#endif

// Définition de constantes
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

#define ROUGE 1.0,0.0,0.0
#define BLEU 0.0,0.0,1.0
#define JAUNE 1.0,1.0,0.0
#define ORANGE 1.0,0.5,0.0
#define MAUVE 0.5,0.0,0.5
#define NOIR 0.0,0.0,0.0
#define BRUN  0.5,0.25,0.0
#define VERT 0.0,0.5,0.0 

// État du jeu
enum GameState {
    PLAYING, WIN, LOSE, TITLE, INIT, LEADERBOARD, COMMANDS,
};
