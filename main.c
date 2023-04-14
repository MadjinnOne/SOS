#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "animal.h"
#include "voiture.h"
#include "route.h"
#include "ruisseau.h"
#include "bordure.h"
#include "global.h"
#include "clavier.h"
#include "taniere.h"
#include "ecran.h"




#define LARGEUR_VOITURE 50
#define HAUTEUR_VOITURE 25

#define LARGEUR_RONDIN 100
#define HAUTEUR_RONDIN 25
#define NOMBRE_RONDINS 6
#define LARGEUR_GRENOUILLE 25
#define HAUTEUR_GRENOUILLE 25
#define VITESSE_VOITURE 5
#define VITESSE_RONDIN 3
#define VITESSE_GRENOUILLE 5
#define TEMPS_RONDIN 50
#define TEMPS_ATTENTE_DEBUT 1000

#define NB_VOITURE_MAX 15 
#define NB_BANDES 10

// Définition de variables globales
int score = 0;
// Les objets
Route ObjetRoute;
Ruisseau ObjetRuisseau;
Animal ObjetAnimal;
Bordure ObjetBordure_01;
Bordure ObjetBordure_02;
Voiture TableVoitures[NB_VOITURE_MAX] = {0};
Taniere ObjetTaniere;
Ecran ecranTitre, ecranFinDeJeu;
// Les ENUMS
enum GameState gameState = TITLE; 




// Définition des fonctions
void initialiser();
void afficherScene();
void afficherTextes(int score, int vie);
void afficherTexte(char *chaine, int x, int y);
void verifierCollision(ptrAnimal animal, Voiture voiture[], size_t nombre_voitures);
void verifierEntreeTaniere(ptrAnimal animal, ptrTaniere taniere);
void afficherEcranFinDeJeu(ptrEcran ecran, int score);
void gererClicSouris(int button, int state, int x, int y);

void timer(int valeur);
void initRendering();
void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y);
void handleResize(int w, int h);

// Fonction principale
int main(int argc, char **argv) {
    // // Initialisation de GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutCreateWindow("Frogger");
    /// "initRendering" est une fonction qui peut être utilisée pour initialiser certaines fonctionnalités de rendu OpenGL 
    /// et d'autres paramètres tels que la couleur d'effacement de l'écran, la profondeur, l'éclairage et la texture.
    //initRendering(); //Initialize rendering
    
    // Initialisation des variables et des fonctions de rappel
    initialiser();

    /// La fonction glutDisplayFunc() est une fonction de la bibliothèque GLUT qui permet de spécifier la fonction qui doit être appelée à chaque fois 
    /// que la fenêtre doit être redessinée. 
    /// Cette fonction doit être appelée au moins une fois dans le programme pour que GLUT puisse savoir quelle fonction appeler lors du 
    /// rafraîchissement de la fenêtre.
    /// Elle est utilisée en OpenGL pour définir la fonction qui sera appelée pour afficher le contenu graphique à l'écran. 
    /// En d'autres termes, elle permet de définir la fonction de rendu, c'est-à-dire la fonction qui sera appelée chaque fois que la fenêtre doit être redessinée.
    glutDisplayFunc(afficherScene);

    ///La fonction glutKeyboardFunc() est une fonction de la bibliothèque GLUT (OpenGL Utility Toolkit) qui permet de définir une fonction de rappel 
    /// (callback function) qui sera appelée chaque fois qu'une touche du clavier est pressée. 
    /// La fonction de rappel prendra en paramètre un caractère représentant la touche pressée et deux entiers représentant les coordonnées de la 
    /// souris au moment de la pression de la touche.
    glutKeyboardFunc(handleKeypress);

    glutMouseFunc(gererClicSouris);

    /// La fonction glutReshapeFunc est une fonction de la bibliothèque GLUT (OpenGL Utility Toolkit) 
    /// qui permet de spécifier la fonction à appeler lorsque la fenêtre est redimensionnée. 
    /// Cette fonction prend en paramètre un pointeur vers la fonction à appeler lorsqu'un événement de redimensionnement de la fenêtre est déclenché. 
    /// Cette fonction doit avoir un prototype de la forme suivante :
    /// void fonctionDeRedimensionnement(int width, int height);
    /// où width et height représentent les nouvelles dimensions de la fenêtre en pixels.
    glutReshapeFunc(handleResize);

    ///glutTimerFunc est une fonction de la bibliothèque GLUT qui permet de définir une fonction à appeler de manière asynchrone après un certain délai. 
    glutTimerFunc(TEMPS_RONDIN, timer, 0);
    
    // Lancement de la boucle principale de GLUT
    /// La fonction glutMainLoop() est une fonction infinie qui sert à lancer la boucle de traitement des événements de la bibliothèque GLUT. 
    /// Cette fonction doit être appelée à la fin de la fonction main() pour que le programme ne se termine pas immédiatement et puisse répondre 
    /// aux événements utilisateur tels que la pression de touches du clavier ou les clics de souris.
    /// La boucle de traitement des événements gérée par glutMainLoop() est responsable de l'affichage continu de la fenêtre et de la gestion des 
    /// événements utilisateur tels que la pression de touches du clavier et les clics de souris. Cette fonction ne retourne jamais, 
    /// ce qui signifie que le programme ne peut être arrêté qu'en fermant la fenêtre de l'application ou en utilisant un signal système 
    /// pour interrompre l'exécution du programme.
    glutMainLoop();
    
    return 0;
}

// Fonction d'initialisation
void initialiser() {
    // Initialisation de la graine aléatoire pour la génération de voitures et de rondins
    srand(time(NULL));
    // Initialisation de l'object route
    initialiserRoute(&ObjetRoute);
    // Initialisation de l'object ruisseau
    initialiserRuisseau(&ObjetRuisseau);
    // Initialisation de l'object taniere
    initialiserTaniere(&ObjetTaniere);

    initialiserBordure_haut(&ObjetBordure_01);
    initialiserBordure_bas(&ObjetBordure_02);
    // Initialiser les véhicules
    // La vitesse et la direction par bande doit être identique
    // Idealement recréer cela en fonction
    {
        enum Direction dir[NB_BANDES];
        int vitesse[NB_BANDES];
        for (int j = 0; j < NB_BANDES; j++)
        {
            dir[j] = (rand()%2)?RIGHT:LEFT;
            vitesse[j] = rand() % (VITESSE_MAX - VITESSE_MIN + 1) + VITESSE_MIN;
        }
        for (int i = 0 ; i < (int)(sizeof(TableVoitures)/sizeof(Voiture)); i++)
        {
            int bande = rand()%NB_BANDES;
            int position_x = LARGEUR_FENETRE * i/ NB_VOITURE_MAX;
            initialiserVoiture(&TableVoitures[i], position_x, 320 + bande*20, dir[bande], vitesse[bande]);
        }
    }

    initialiserAnimal(&ObjetAnimal);
    // positionGrenouilleX = (LARGEUR_ROUTE - LARGEUR_GRENOUILLE) / 2.0; // Initialisation de la position de la grenouille
    // positionGrenouilleY = HAUTEUR_ROUTE + HAUTEUR_RUISSEAU + HAUTEUR_BANDEAU + (HAUTEUR_CASE - HAUTEUR_GRENOUILLE) / 2.0;
    // directionGrenouille = AUCUNE; // Initialisation de la direction de la grenouille
    // etatAnimation = 0; // Initialisation de l'état de l'animation
    // score = 0; // Initialisation du score
    // vie = 3; // Initialisation du nombre de vies
    // etatVictoire = 0; // Initialisation de l'état de la victoire
    // tempsRestant = TEMPS_TOTAL; // Initialisation du temps restant
    // etatDebut = 1; // Initialisation de l'état du début du jeu
}


/*
void afficherScene() {
    // Effacement de la scène
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Réinitialiser la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, LARGEUR_FENETRE, 0, HAUTEUR_FENETRE);

    // Réinitialiser la matrice de modèle-vue
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    dessinerRoute(&ObjetRoute);
    
    dessinerRuisseau(&ObjetRuisseau);
    dessinerTaniere(&ObjetTaniere);

    dessinerBordure(&ObjetBordure_01);
    dessinerBordure(&ObjetBordure_02);

    for (int i = 0; i < (int) (sizeof(TableVoitures)/sizeof(Voiture)); i++)
    {
        dessinerVoiture(&TableVoitures[i]);
    }

    // Dessin de l'animal
    dessinerAnimal(&ObjetAnimal);

    
    // Affichage du score
    afficherTextes(ObjetAnimal.score, ObjetAnimal.vie);

    if (gameState == LOSE){
        afficherEcranFinDeJeu(&ecranFinDeJeu, ObjetAnimal.score);
    }
  
//     // Affichage du temps restant
//     char tempsRestantString[50];
//     sprintf(tempsRestantString, "Temps restant : %d", tempsRestant);
//     glColor3f(1.0, 1.0, 1.0);
//     dessinerTexte(tempsRestantString, 10, HAUTEUR_ROUTE + HAUTEUR_RUISSEAU + 30, 1.0);
    
    // Echange des buffers
    glutSwapBuffers();
}
*/
// Fonction de dessin de la scène
void afficherScene() {
    // Effacement de la scène
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
    

    switch (gameState) {
        case TITLE:
            afficherEcranTitre(&ecranTitre);
            break;
        case PLAYING:
            dessinerRoute(&ObjetRoute);
            dessinerRuisseau(&ObjetRuisseau);
            dessinerTaniere(&ObjetTaniere);
            dessinerBordure(&ObjetBordure_01);
            dessinerBordure(&ObjetBordure_02);

            for (int i = 0; i < (int) (sizeof(TableVoitures) / sizeof(Voiture)); i++) {
                dessinerVoiture(&TableVoitures[i]);
            }

            // Dessin de l'animal
            dessinerAnimal(&ObjetAnimal);

            // Affichage du score
            afficherTextes(ObjetAnimal.score, ObjetAnimal.vie);
            break;
        case LOSE:
            afficherEcranFinDeJeu(&ecranFinDeJeu, ObjetAnimal.score);
            break;
        default:
            break;
    }

    // Echange des buffers
    glutSwapBuffers();
}


void afficherTextes(int score, int vie)
{
    {
        char scoreStr[50]; // Convertit le score en chaîne de caractères
        sprintf(scoreStr, "Score : %d", score);
        afficherTexte(scoreStr, 10, 580); // Affiche le score en haut à gauche de l'écran
    }
    {
        char vieStr[50]; // Convertit le nombre de vies en chaîne de caractères
        sprintf(vieStr, "Vies : %d", vie);
        afficherTexte(vieStr, 720, 580); // Affiche le score en haut à gauche de l'écran
    }
    /*
    if (ObjetAnimal.vie <= 0)
    {
        afficherTexte("Game over", 360, 290);
    }
    */
}

void afficherTexte(char *chaine, int x, int y) {
    glColor3f(1.0, 1.0, 1.0);
    // Positionne la position courante pour dessiner le texte
    glRasterPos2i(x, y);

    // Dessine chaque caractère de la chaîne
    for (int i = 0; i < (int) strlen(chaine); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, chaine[i]);
    }
}

void verifierCollision(ptrAnimal animal, Voiture voiture[], size_t nombre_voitures) {
    // Vérifier si l'animal est sur la route (on pourrait sans doute optimiser mais il faudrait s'assurer que les voiture ne peut être que sur la route également)
    //détection de collision avec la voiture
    for (int i = 0; i < (int)nombre_voitures; i++)
    {
        if (CollisionEntreObjets(&animal->objet , &(voiture+i)->objet)){
            // Collision détectée !
            animal->vie--;
            reinitialiserPositionAnimal(animal);
            // Si le nombre de vies de l'animal est 0, mettre à jour le GameState à LOSE
            if (animal->vie <= 0) {
                gameState = LOSE;
            }
        }
    }
    // // Vérifier si la grenouille est sur un rondin
    // else {
    //     bool surRondin = false;
    //     for (int i = 0; i < NOMBRE_RONDINS; i++) {
    //         if (positionGrenouilleX + LARGEUR_GREN > positionRondinsX[i] &&
    //             positionGrenouilleX < positionRondinsX[i] + LARGEUR_RONDIN &&
    //             positionGrenouilleY + HAUTEUR_GREN > positionRondinsY[i] &&
    //             positionGrenouilleY < positionRondinsY[i] + HAUTEUR_RONDIN) {
    //             // La grenouille est sur un rondin, elle se déplace avec le rondin
    //             positionGrenouilleX += vitesseRondins[i];
    //             surRondin = true;
    //             break;
    //         }
    //     }
    //     if (!surRondin) {
    //         // La grenouille n'est sur aucun rondin, elle tombe dans l'eau
    //         vieGrenouille--;
    //         initialiserGrenouille();
    //     }
    // }
}

void verifierEntreeTaniere(ptrAnimal animal, ptrTaniere taniere) {
    if (CollisionEntreObjets(&animal->objet, &taniere->objet)) {
        // L'animal est entré dans la tanière
        animal->score++;
        reinitialiserPositionAnimal(animal);
    }
}


void timer(int valeur) {
    for (int i = 0; i< (int) (sizeof(TableVoitures)/sizeof(Voiture)); i++)
    {
        deplacerVoiture(&(TableVoitures[i]), 0);
    }
    // deplacerRondins();
    // verifierCollision();
    verifierCollision(&ObjetAnimal, TableVoitures, sizeof(TableVoitures)/sizeof(Voiture));
    // Vérification entrée taniere
    verifierEntreeTaniere(&ObjetAnimal, &ObjetTaniere);

    // if (positionGrenouilleY >= HAUTEUR_ROUTE + HAUTEUR_GREN && vieGrenouille > 0) {
    //     // La grenouille est sur le ruisseau et n'est pas morte, on ajoute un point
    // scoreGrenouille++;
    if (ObjetAnimal.vie <= 0)
    {
    }

    /// La fonction glutPostRedisplay() est utilisée pour indiquer à GLUT qu'une nouvelle image doit être dessinée. Elle demande essentiellement à GLUT de rappeler la fonction de rappel de rendu (définie à l'aide de glutDisplayFunc()) dès que possible. Cela est souvent utilisé pour créer des animations ou pour rafraîchir l'affichage lorsque quelque chose a changé dans la scène.
    /// En appelant glutPostRedisplay(), GLUT marque le contexte de rendu comme étant "sale" et indique que la scène doit être redessinée lors du prochain cycle de boucle GLUT. Lorsque GLUT exécute la prochaine boucle, il appelle la fonction de rappel de rendu, qui est alors chargée de dessiner la nouvelle image.
    glutPostRedisplay();
    ///La fonction glutTimerFunc est une fonction de la bibliothèque GLUT qui permet de définir une fonction de rappel (callback) qui sera appelée après un délai donné en millisecondes. 
    glutTimerFunc(100, timer, 0);
}

//Initializes 3D rendering
void initRendering() {
    // Effacer l'écran en noir
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Activation du Z-buffer
    glEnable(GL_DEPTH_TEST);

    // Activation de l'éclairage
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // Activation de la texture
    glEnable(GL_TEXTURE_2D);

    // Activation du blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
                    int x, int y) {    //The current mouse coordinates
    if (gameState == TITLE && key == 13){ // La touche Entrée a le code ASCII 13
        gameState = PLAYING;
        }               
    switch (key) {
        case 27: //Escape key
            exit(0); //Exit the program
        case 'z':
        case 's':
        case 'q':
        case 'd':
            clavier(key, &ObjetAnimal);
            verifierCollision(&ObjetAnimal, TableVoitures, sizeof(TableVoitures)/sizeof(Voiture));
            break;
    }
}

/*
PRE: button est un entier représentant le bouton de la souris concerné (dans ce cas, GLUT_LEFT_BUTTON).
state est un entier représentant l'état du bouton de la souris (dans ce cas, GLUT_DOWN).
x est un entier représentant la position horizontale du curseur de la souris au moment du clic.
y est un entier représentant la position verticale du curseur de la souris au moment du clic.
POST: Si le bouton de la souris gauche a été cliqué (GLUT_LEFT_BUTTON et GLUT_DOWN) et que l'état du jeu est LOSE, la fonction vérifie si le bouton "Rejouer" a été cliqué en utilisant boutonRejouerClique(x, y).
Si le bouton "Rejouer" a été cliqué, le jeu est réinitialisé en appelant initialiser(), et l'état du jeu passe à PLAYING.
 */
void gererClicSouris(int button, int state, int x, int y) {
    // Inverser l'axe des ordonnées
    //y = HAUTEUR_FENETRE - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (gameState == LOSE && boutonRejouerClique(x, y)) {
            // Réinitialisez le jeu et changez l'état du jeu en PLAYING
            initialiser();
            gameState = PLAYING;
        }
    }
}


//Called when the window is resized
void handleResize(int w, int h) {
    glClearColor(0, 0, 0, 0.0); // Définition de la couleur de fond
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    glOrtho(0.0, LARGEUR_FENETRE, HAUTEUR_FENETRE, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    // gluPerspective(45.0,                  //The camera angle
    //                (double)w / (double)h, //The width-to-height ratio
    //                1.0,                   //The near z clipping coordinate
    //                200.0);                //The far z clipping coordinate
}
