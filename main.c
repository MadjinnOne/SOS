#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <FreeImage.h>
#include "animal.h"
#include "voiture.h"
#include "route.h"
#include "ruisseau.h"
#include "bordure.h"
#include "global.h"
#include "taniere.h"
#include "ecran.h"
#include "rondin.h"
#include "leaderboard.h"
#include "tir.h"
#include "bouton.h"
#include "textures.h"




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

// Définition de variables globales
int score = 0;
char nomJoueur[MAX_NAME_LENGTH] = "";
GLuint textureFondEcranTitre;
GLuint textureFondEcranScore;
GLuint textureFondEcranCommand;

// Les objets
Route ObjetRoute;
Ruisseau ObjetRuisseau;
Animal ObjetAnimal;
Bordure ObjetBordure_01;
Bordure ObjetBordure_02;
Rondin TableRondin[NB_RONDIN_MAX] = {0};
Taniere ObjetTaniere;
Ecran ecranTitre, ecranFinDeJeu;
// Les ENUMS
enum GameState gameState = TITLE; 
Liste liste_autos;
Liste liste_tirs;




// Définition des fonctions
void initialiser();
void afficherScene();
void afficherScore_Vie(int score, int vie);
void afficherTexte(char *chaine, int x, int y);
bool verifierCollisionVoiture(ptrAnimal animal, ptrRoute route, ptrListe pliste_autos);
void verifierEntreeTaniere(ptrAnimal animal, ptrTaniere taniere);
bool verifierTomberdanseau(ptrAnimal animal, ptrRuisseau ruisseau, Rondin rondin[]);
void afficherEcranFinDeJeu(ptrEcran ecran, int score);
void mouseClick(int button, int state, int x, int y);
void obtenirNomJoueur(char *nomJoueur);
void afficherChampTexte();
void gererSaisieNom(unsigned char key, int x, int y);
void timer(int valeur);
void initRendering();
void handleKeypress(unsigned char key, int x, int y);
void handleResize(int w, int h);

// Fonction principale
int main(int argc, char **argv) {
    // Initialisation de FreeImage
    FreeImage_Initialise(FALSE); // s'il est défini à TRUE, charge uniquement les plugins locaux. Si vous voulez charger tous les plugins disponibles, vous pouvez le passer à FALSE
    // // Initialisation de GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutCreateWindow("SOS");    
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

    glutMouseFunc(mouseClick);

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
    // Libération des ressources de FreeImage
    FreeImage_DeInitialise();
    
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
    //Initialisation des textures
    textureFondEcranTitre = chargerTexture("Textures/titre.png");
    textureFondEcranScore = chargerTexture("Textures/score.png");
    textureFondEcranCommand = chargerTexture("Textures/command.png");
    // Initialiser les véhicules
    initialiserListeVoiture(&liste_autos);
    //initialiserListeTir(&liste_tirs);
    initialiserListeRondins(TableRondin);
    initialiserAnimal(&ObjetAnimal);
}



// Fonction de dessin de la scène
void afficherScene() {
    // Effacement de la scène
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Réinitialiser la matrice de modèle-vue
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (gameState) {
        case TITLE:
            afficherEcranTitre(&ecranTitre, &textureFondEcranTitre);
            break;
        case PLAYING:
            dessinerRoute(&ObjetRoute);
            dessinerRuisseau(&ObjetRuisseau);
            dessinerTaniere(&ObjetTaniere);
            dessinerBordure(&ObjetBordure_01);
            dessinerBordure(&ObjetBordure_02);

            ptrElement element = liste_autos.premier;
            while(element != NULL)
            {
                dessinerVoiture((ptrVoiture)element->objetDefini);
                element = element->suivant;
            }

            for (int i = 0; i < (int) (sizeof(TableRondin) / sizeof(Rondin)); i++) {
                dessinerRondin(&TableRondin[i]);
            }
            // Dessin de l'animal
            dessinerAnimal(&ObjetAnimal);

            // Affichage du score
            afficherScore_Vie(ObjetAnimal.score, ObjetAnimal.vie);
            break;
        case LOSE:
            afficherEcranFinDeJeu(&ecranFinDeJeu, ObjetAnimal.score);
            afficherChampTexte();
            break;
        case COMMANDS:
            afficherEcranCommandes(&textureFondEcranCommand);
            break;
        case LEADERBOARD:
            afficherEcranLeaderboard(&textureFondEcranScore);
        default:
            break;
    }
    // Echange des buffers
    glutSwapBuffers();
}


void afficherScore_Vie(int score, int vie)
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

/*
void afficherChampTexte() {
    glColor3f(0.0f, 1.0f, 1.0f);
    glRasterPos2i(250, 300);
    for (int i = 0; i < strlen(nomJoueur); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, nomJoueur[i]);
    }
}
*/

void afficherChampTexte() {
    // Définir la couleur en blanc
    glColor3f(1.0f, 1.0f, 1.0f);

    // Dessiner un rectangle blanc
    int x = 300;
    int y = 400;
    int largeur = 200; // Suppose une largeur de 200 pixels pour le cadre
    int hauteur = 20; // Suppose une hauteur de 20 pixels pour le cadre

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + largeur, y);
        glVertex2f(x + largeur, y + hauteur);
        glVertex2f(x, y + hauteur);
    glEnd();

    // Définir la couleur en noir pour le texte
    glColor3f(0.0f, 0.0f, 0.0f);

    // Afficher le texte
    glRasterPos2i(x + 10, y + 12); // Décale de 10 pixels à droite et en haut
    for (int i = 0; i < strlen(nomJoueur); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, nomJoueur[i]);
    }

    // Afficher le texte "Veuillez entrer votre nom:" au-dessus du cadre
    // Définir la couleur en blanc pour le texte
    glColor3f(1.0f, 1.0f, 1.0f);

    const char *message = "Veuillez entrer votre nom:";
    glRasterPos2i(x, y + hauteur - 30); // Positionner le texte 30 pixels au-dessus du cadre
    for (int i = 0; i < strlen(message); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message[i]);
    }
}




void gererSaisieNom(unsigned char key, int x, int y) {
    if (key == 8 || key == 127) { // Touche Backspace ou Delete
        if (strlen(nomJoueur) > 0) {
            nomJoueur[strlen(nomJoueur) - 1] = '\0';
        }
    } else if (key == 13) { // Touche Entrée
        ajouterEntreeLeaderboard("leaderboard.txt", nomJoueur, ObjetAnimal.score);
        gameState = INIT;
    } else if (strlen(nomJoueur) < MAX_NAME_LENGTH - 1) {
        nomJoueur[strlen(nomJoueur) + 1] = '\0';
        nomJoueur[strlen(nomJoueur)] = key;
    }
}

bool verifierCollisionVoiture(ptrAnimal animal, ptrRoute route, ptrListe pliste_autos) {
    // Vérifier si l'animal est sur la route (on pourrait sans doute optimiser mais il faudrait s'assurer que les voiture ne peut être que sur la route également)
    //détection de collision avec la voiture
    if (CollisionEntreObjets(&animal->objet, &route->objet)){
        ptrElement element = pliste_autos->premier;
        while(element != NULL)
        {
            if (CollisionEntreObjets(&animal->objet , (ptrObjet)element->objetDefini)){
                // Collision détectée !
                return true;
            }
            element = element->suivant;
        }
    }
    return false;
}

void verifierEntreeTaniere(ptrAnimal animal, ptrTaniere taniere) {
    if (CollisionEntreObjets(&animal->objet, &taniere->objet)) {
        // L'animal est entré dans la tanière
        animal->score++;
        reinitialiserPositionAnimal(animal);
    }
}

bool verifierTomberdanseau(ptrAnimal animal, ptrRuisseau ruisseau, Rondin rondin[]) {
    if (CollisionEntreObjets(&animal->objet, &ruisseau->objet)){  // Si je suis sur le ruisseau alors je commence à vérifier 
        for(int i=0;i<NB_RONDIN_MAX;i++){                               // Je parcours tous les
            if (CollisionEntreObjets(&animal->objet, &(rondin + i)->objet)) { // Si je  suis  sur un rondin                                              // Tout va bien
                return false;
            }
        }
        return true;
    }
    return false;
}

void timer(int valeur) {
        switch(gameState) {
        case INIT:
            initialiserAnimal(&ObjetAnimal);
            strcpy(nomJoueur,"");
            gameState = TITLE;
            break;
        case PLAYING:
            ptrElement element = liste_autos.premier;
            while(element != NULL)
            {
                deplacerVoiture((ptrVoiture)element->objetDefini, 0);
                element = element->suivant;
            }
            // deplacerRondins();
            for (int i = 0; i< (int) (sizeof(TableRondin)/sizeof(Rondin)); i++)
            {
                deplacerRondin(&(TableRondin[i]), 0);
            }
            int index = 0;
            if (animalSurRondin(&ObjetAnimal,TableRondin, (sizeof(TableRondin)/sizeof(Rondin)), &index))
                deplacerAnimalAvecRondin(&ObjetAnimal,&TableRondin[index]);
            // verifierCollision();
            if (verifierCollisionVoiture(&ObjetAnimal, &ObjetRoute, &liste_autos))
            {
                ObjetAnimal.vie--;
                reinitialiserPositionAnimal(&ObjetAnimal);
            }
            // Vérification entrée taniere
            verifierEntreeTaniere(&ObjetAnimal, &ObjetTaniere);
            //Vérification tombé dans l'eau ?    
            if (verifierTomberdanseau(&ObjetAnimal, &ObjetRuisseau, TableRondin))
            {
                ObjetAnimal.vie--;
                reinitialiserPositionAnimal(&ObjetAnimal);
            }
            

            // if (positionGrenouilleY >= HAUTEUR_ROUTE + HAUTEUR_GREN && vieGrenouille > 0) {
            //     // La grenouille est sur le ruisseau et n'est pas morte, on ajoute un point
            // scoreGrenouille++;
            if (ObjetAnimal.vie <= 0)
            {
                gameState = LOSE;
            }
            break;
            case WIN:
            case LOSE:
            case TITLE:
            case LEADERBOARD:
            case COMMANDS:
            default:
            break;
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
    if (key == 27) //Escape key
        exit(0); //Exit the program
    switch (gameState) {
        case TITLE: 
            if (key == 13) {
                gameState = PLAYING;
            }
            break;
        case PLAYING:
            entrée_clavier_animal(key, &ObjetAnimal);
            break;
        case LOSE:
            gererSaisieNom(key, 0, 0);
            break;
        case WIN:
            break;
        default: 
            exit(0);
            break;
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

//Pointeurs vers les boutons dans ecran.c
extern ptrBouton boutonQuitter;
extern ptrBouton boutonLeaderboard;
extern ptrBouton boutonCommandes;
extern ptrBouton boutonJouer;

void mouseClick(int button, int state, int x, int y) {
    // Vérifiez si le bouton gauche de la souris a été cliqué
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clicSurBouton(x, y, *boutonQuitter)) {
            // Quitter le jeu
            exit(0);
        } else if (clicSurBouton(x, y, *boutonLeaderboard)) {
            // Changer l'état du jeu pour afficher le leaderboard
            gameState = LEADERBOARD; // Supposons que vous avez un état LEADERBOARD
        } else if (clicSurBouton(x, y, *boutonCommandes)) {
            // Changer l'état du jeu pour afficher les commandes
            gameState = COMMANDS; // Supposons que vous avez un état COMMANDS
        } else if (clicSurBouton(x, y, *boutonJouer)) {
            // Changer l'état du jeu pour jouer
            gameState = PLAYING; // Supposons que vous avez un état PLAYING
        }
    }
}
