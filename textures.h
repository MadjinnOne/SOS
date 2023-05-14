#pragma once
#include <GL/gl.h>

// Charge une image depuis un fichier et retourne un identifiant de texture OpenGL.
GLuint chargerTexture(const char* filename);

// Dessine une texture à une position spécifique avec une largeur et une hauteur spécifiques.
void dessinerTexture(GLuint textureId, float x, float y, float largeur, float hauteur);

// Libère la mémoire associée à une texture.
void libererTexture(GLuint textureId);


