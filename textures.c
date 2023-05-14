#include "textures.h"
#include <FreeImage.h>
#include <GL/gl.h>
#include <stdio.h>


GLuint chargerTexture(const char* filename) {
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
    FIBITMAP* image = FreeImage_Load(format, filename, 0);

    if(!image) {
        fprintf(stderr, "Échec du chargement de l'image %s\n", filename);
        return 0;
    }
        // Inverser l'image
    FreeImage_FlipVertical(image);

    FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);
    FreeImage_Unload(image);
    int w = FreeImage_GetWidth(image32bits);
    int h = FreeImage_GetHeight(image32bits);

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32bits));

    FreeImage_Unload(image32bits);

    return textureId;
}

void dessinerTexture(GLuint textureId, float x, float y, float largeur, float hauteur) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(x, y);                 // bas-gauche
    glTexCoord2f(1, 1); glVertex2f(x + largeur, y);       // bas-droit
    glTexCoord2f(1, 0); glVertex2f(x + largeur, y + hauteur); // haut-droit
    glTexCoord2f(0, 0); glVertex2f(x, y + hauteur);       // haut-gauche
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void libererTexture(GLuint textureId) {
    glDeleteTextures(1, &textureId);
}


