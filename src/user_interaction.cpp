#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"
#include "user_interaction.h"
#include <string>
#include <iostream>

extern string mode;
extern int selectedObject;
extern draws structure_list;
extern vector<double> color;

// void keyboardFunc(unsigned char key, int x, int y) {
//     int modifiers = glutGetModifiers();
//     switch (key) {
//         case 'p': 
//             mode = "create_point";
//             break;
//         case 'l':
//             mode = "create_line";
//             break;
//         case 'g':
//             mode = "create_polygon";
//             break;
//         case 's':
//             mode = "select";
//             break;
//         case 'd':
//             mode = "delete";
//             break;
//         case 't':
//             mode = "transformation";
//             break;
//         case '+':
//             if (modifiers == GLUT_ACTIVE_CTRL) {
//                 scale(selectedObject, 1.1);
//             }
//             break;
//         case '-':
//             if (modifiers == GLUT_ACTIVE_CTRL) {
//                 scale(selectedObject, 0.9);
//             }
//             break;
//         case 27: // ESC key to exit
//             exit(0);
//             break;
//     }
//     glutPostRedisplay();
// }

// void specialKeys(int key, int x, int y) {
//     if (mode == "transformation" && selectedObject != -1) {
//         switch (key) {
//             case GLUT_KEY_LEFT:
//                 translate(selectedObject, -10, 0);
//                 break;
//             case GLUT_KEY_RIGHT:
//                 translate(selectedObject, 10, 0);
//                 break;
//             case GLUT_KEY_UP:
//                 translate(selectedObject, 0, -10);
//                 break;
//             case GLUT_KEY_DOWN:
//                 translate(selectedObject, 0, 10);
//                 break;
//         }
//     }
//     glutPostRedisplay();
// }

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (mode == "create_point") {
            create_point(x, 300 - y, color, structure_list);
            glutPostRedisplay();
        }
        else if (mode == "create_line") {
            std::cout << "Antes" << structure_list.lista_pontos.size() << std::endl;
            std::cout << "Antes" << x << " - " << 300 - y << std::endl;
            static int x1, y1;
            static int index;
            static bool firstClick = true;
            
            if (firstClick) {
                x1 = x;
                y1 = 300 - y;
                index = create_point(x1, y1, color, structure_list);
                firstClick = false;
            } else {
                create_line(x1, y1, x, 300 - y, color, color, structure_list);
                structure_list.lista_pontos.erase(structure_list.lista_pontos.begin() + index);
                firstClick = true;
            }
            std::cout << "Depois" << structure_list.lista_pontos.size() << std::endl;
            glutPostRedisplay();
        }
        // else if (mode == "create_polygon") {
        //     create_polygon({{x, y, {1.0f, 0.0f, 0.0f}}}, structure_list);
        // } 
        // else if (mode == "select") {
        //     pair<int, int> index = selecionar_objeto(structure_list, x, y);
        //     selectedObject = index;
        // } else if (mode == "delete") {
        //     deleteObject(selectedObject);
        // }
    }
    glutPostRedisplay();
}

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

        case 12:  break;
        case 13:  break;

        case 14:  break;
        case 15:  break;
        case 16:  break;
        case 17:  break;
        case 18:  break;

        case 11: exit(0); break;
    }
    glutPostRedisplay();
}

void createMenu() {
    int colorSubMenu = glutCreateMenu(menu);
    glutAddMenuEntry("---- Cores ----", 0);
    glutAddMenuEntry("Vermelho", 14);
    glutAddMenuEntry("Verde", 15);
    glutAddMenuEntry("Azul", 16);
    glutAddMenuEntry("Branco", 17);
    glutAddMenuEntry("Preto", 18);

    int menuID = glutCreateMenu(menu);
    glutAddMenuEntry("---------- MENU ----------", 0);
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

    glutAddMenuEntry("---- Arquivo ----", 0);
    glutAddMenuEntry("Salvar", 12);
    glutAddMenuEntry("Carregar", 13);

    glutAddSubMenu("Alterar Cor", colorSubMenu);

    glutAddMenuEntry("Sair", 11);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

