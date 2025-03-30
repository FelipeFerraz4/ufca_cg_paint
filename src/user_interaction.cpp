#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"
#include "user_interaction.h"
#include <string>

extern string mode;

void menu(int option) {
    switch (option) {
        case 1: mode = "create_point"; break;
        case 2: mode = "create_line"; break;
        case 3: mode = "create_polygon"; break;
        case 4: mode = "select"; break;
        case 5: mode = "delete"; break;
        case 6: mode = "translate"; break;
        case 7: mode = "rotate"; break;
        case 8: mode = "scale"; break;
        case 9: mode = "reflect"; break;
        case 10: mode = "shear"; break;
        case 11: exit(0);
    }
    glutPostRedisplay();
}

void createMenu() {
    int menuID = glutCreateMenu(menu);

    glutAddMenuEntry("Criar Ponto", 1);
    glutAddMenuEntry("Criar Linha", 2);
    glutAddMenuEntry("Criar Poligono", 3);
    glutAddMenuEntry("Selecionar", 4);
    glutAddMenuEntry("Excluir", 5);
    
    glutAddMenuEntry("---- Transformacoes ----", 0);
    glutAddMenuEntry("Translacao", 6);
    glutAddMenuEntry("Rotacao", 7);
    glutAddMenuEntry("Escala", 8);
    glutAddMenuEntry("Reflexao", 9);
    glutAddMenuEntry("Cisalhamento", 10);

    glutAddMenuEntry("Sair", 11);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

