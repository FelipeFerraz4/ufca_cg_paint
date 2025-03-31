#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"
#include "user_interaction.h"
#include <string>
#include <iostream>
#include <cmath>
#include "save_load.h"
#include "animacao.h"

extern string mode;
extern pair<int, int> selectedObject;
extern draws structure_list;
extern vector<double> color;
extern bool fim; 

void translate(pair<int, int> selectedObject, int dx, int dy) {
    int type = selectedObject.first;
    int index = selectedObject.second;
    if (type == 1) {
        ponto &p = structure_list.lista_pontos[index];
        vector<vector<double>> matrix = matrizTransacional(dx, dy);
        calcular_novo_ponto(matrix, p);
    } else if (type == 2) {
        reta &r = structure_list.lista_retas[index];
        vector<vector<double>> matrix = matrizTransacional(dx, dy);
        calcular_novo_ponto(matrix, r[0]);
        calcular_novo_ponto(matrix, r[1]);
    } else if (type == 3) {
        poligono &p = structure_list.lista_poligonos[index];
        vector<vector<double>> matrix = matrizTransacional(dx, dy);
        for (ponto &pt : p) {
            calcular_novo_ponto(matrix, pt);
        }
    }
}

void scale(pair<int, int> selectedObject, double scaleFactor) {
    int type = selectedObject.first;
    int index = selectedObject.second;
    if (type == 2) {
        reta &r = structure_list.lista_retas[index];
        escalonar_r(r, scaleFactor, scaleFactor);
    } else if (type == 3) {
        poligono &p = structure_list.lista_poligonos[index];
        escalonar_p(p, scaleFactor, scaleFactor);
    }
}

void rotate(pair<int, int> selectedObject, double angle) {
    int type = selectedObject.first;
    int index = selectedObject.second;
    double radians = angle * M_PI / 180.0;
    if (type == 2) {
        reta &r = structure_list.lista_retas[index];
        rotacionar_r(r, radians);
    } else if (type == 3) {
        poligono &p = structure_list.lista_poligonos[index];
        rotacionar_p(p, radians);
    }
}

void reflect(pair<int, int> selectedObject, string eixo) {
    int type = selectedObject.first;
    int index = selectedObject.second;
    vector<vector<double>> matrix = matrizReflexao(eixo);

    if (type == 1) { // ponto
        ponto &p = structure_list.lista_pontos[index];
        calcular_novo_ponto(matrix, p);
    } else if (type == 2) { // reta
        reta &r = structure_list.lista_retas[index];
        calcular_novo_ponto(matrix, r[0]);
        calcular_novo_ponto(matrix, r[1]);
    } else if (type == 3) { // polígono
        poligono &p = structure_list.lista_poligonos[index];
        for (ponto &pt : p) {
            calcular_novo_ponto(matrix, pt);
        }
    }
}

void animete() {
    fim = false;
}

void keyboardFunc(unsigned char key, int x, int y) {
    int modifiers = glutGetModifiers();
    switch (key) {
        case 'p': 
            mode = "create_point";
            break;
        case 'l':
            mode = "create_line";
            break;
        case 'g':
            mode = "create_polygon";
            break;
        case 's':
            mode = "select";
            break;
        case 'd':
            mode = "delete";
            break;
        case 't':
            mode = "translate";
            break;
        case 'r': 
            mode = "rotate"; 
            break;
        case '[':  // Rotação anti-horária
            if (mode == "rotate") {
                std::cout << "Rotacionando -10 graus" << std::endl;
                rotate(selectedObject, -10);
            }
            break;
        case ']':  // Rotação horária
            if (mode == "rotate") {
                std::cout << "Rotacionando +10 graus" << std::endl;
                rotate(selectedObject, 10);
            }
            break;
        case '+':
            std::cout << "scale" << std::endl;
            scale(selectedObject, 1.1);
            break;
        case '-':
            std::cout << "scale" << std::endl;
            scale(selectedObject, 0.9);
            break;
        case 27: // ESC key to exit
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    if (mode == "translate" && selectedObject.first > 0) {
        switch (key) {
            case GLUT_KEY_LEFT:
                translate(selectedObject, 10, 0);
                break;
            case GLUT_KEY_RIGHT:
                translate(selectedObject, -10, 0);
                break;
            case GLUT_KEY_UP:
                translate(selectedObject, 0, -10);
                break;
            case GLUT_KEY_DOWN:
                translate(selectedObject, 0, 10);
                break;
        }
    }
    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (mode == "create_point") {
            create_point(x, 300 - y, color, structure_list);
            glutPostRedisplay();
        }
        else if (mode == "create_line") {
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
            glutPostRedisplay();
        }
        else if (mode == "create_triangle") {
            static vector<ponto> vertices;
            static vector<int> index;
            
            ponto new_point;
            new_point.x = x;
            new_point.y = 300 - y;
            new_point.cor = color;

            index.push_back(create_point(x, 300 - y, color, structure_list));
            vertices.push_back(new_point);
        
            if (vertices.size() == 3) {
                create_polygon(vertices, structure_list);
                for (int i = 0; i < index.size(); i++) {
                    structure_list.lista_pontos.erase(structure_list.lista_pontos.begin() + index[i]);
                }
                vertices.clear();
                index.clear();
            }
            glutPostRedisplay();
        }
        else if (mode == "create_rectangle") {
            static vector<ponto> vertices;
            static vector<int> index;
            
            ponto new_point;
            new_point.x = x;
            new_point.y = 300 - y;
            new_point.cor = color;
            
            index.push_back(create_point(x, 300 - y, color, structure_list));
            vertices.push_back(new_point);
            
            
            if (vertices.size() == 2) {  
                int x1 = min(vertices[0].x, vertices[1].x);
                int y1 = min(vertices[0].y, vertices[1].y);
                int x2 = max(vertices[0].x, vertices[1].x);
                int y2 = max(vertices[0].y, vertices[1].y);
                
                vector<ponto> rect_vertices;
        
                ponto p1, p2, p3, p4;
                
                p1.x = x1; p1.y = y1; p1.cor = color;
                p2.x = x2; p2.y = y1; p2.cor = color;
                p3.x = x2; p3.y = y2; p3.cor = color;
                p4.x = x1; p4.y = y2; p4.cor = color;
        
                rect_vertices.push_back(p2);
                rect_vertices.push_back(p1);
                rect_vertices.push_back(p4);
                rect_vertices.push_back(p3);
        
                create_polygon(rect_vertices, structure_list);
                
                for (int i = 0; i < index.size(); i++) {
                    structure_list.lista_pontos.erase(structure_list.lista_pontos.begin() + index[i]);
                }
        
                vertices.clear();
                index.clear();
            }        
            glutPostRedisplay();
        }
        else if (mode == "select") {
            selectedObject = {0, 0};
            selectedObject = selecionar_objeto(structure_list, x, 300 - y);
            std::cout << selectedObject.first << " - " << selectedObject.second << std::endl;
        } 
        else if (mode == "delete") {
            if (selectedObject.first == 1) { 
                structure_list.lista_pontos.erase(structure_list.lista_pontos.begin() + selectedObject.second);
            } 
            else if (selectedObject.first == 2) {
                structure_list.lista_retas.erase(structure_list.lista_retas.begin() + selectedObject.second);
            } 
            else if (selectedObject.first == 3) {
                structure_list.lista_poligonos.erase(structure_list.lista_poligonos.begin() + selectedObject.second);
            }
            selectedObject = {0, 0};
            glutPostRedisplay();
        }
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

        case 12: save_objects(structure_list); break;
        case 13: load_objects(structure_list); break;

        case 14:  break;
        case 15:  break;
        case 16:  break;
        case 17:  break;
        case 18:  break;
        case 19: mode = "create_triangle"; break;
        case 20: mode = "create_rectangle"; break;
        // case 21: mode = "create_circle"; break;
        case 21: reflect(selectedObject, "x"); break;
        case 22: reflect(selectedObject, "y"); break;
        case 23: reflect(selectedObject, "origem"); break;
        case 24: reflect(selectedObject, "y=x"); break;
        case 25: reflect(selectedObject, "y=-x"); break;
        case 26: animete(); break;
        case 11: exit(0); break;
    }
    glutPostRedisplay();
}

void createMenu() {
    int reflectSubMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Eixo X", 21);
    glutAddMenuEntry("Eixo Y", 22);
    glutAddMenuEntry("Origem", 23);
    glutAddMenuEntry("reta y = x", 24);
    glutAddMenuEntry("reta y = -x", 25);

    int createSubMenu = glutCreateMenu(menu);
    glutAddMenuEntry("--- Criar ---", 0);
    glutAddMenuEntry("Criar Ponto", 1);
    glutAddMenuEntry("Criar Linha", 2);
    glutAddMenuEntry("Criar Triangulo", 19);
    glutAddMenuEntry("Criar Retangulo", 20);
    // glutAddMenuEntry("Criar Circulo", 21);
    glutAddMenuEntry("Criar Poligono", 3);

    int colorSubMenu = glutCreateMenu(menu);
    glutAddMenuEntry("---- Cores ----", 0);
    glutAddMenuEntry("Vermelho", 14);
    glutAddMenuEntry("Verde", 15);
    glutAddMenuEntry("Azul", 16);
    glutAddMenuEntry("Branco", 17);
    glutAddMenuEntry("Preto", 18);

    int menuID = glutCreateMenu(menu);
    glutAddMenuEntry("---------- MENU ----------", 0);
    glutAddSubMenu("Criar", createSubMenu);
    glutAddMenuEntry("Selecionar", 4);
    glutAddMenuEntry("Excluir", 5);

    glutAddMenuEntry("---- Transformacoes ----", 0);
    glutAddMenuEntry("Translacao", 6);
    glutAddMenuEntry("Rotacao", 7);
    glutAddMenuEntry("Escala", 8);
    glutAddSubMenu("Reflexao", reflectSubMenu);
    glutAddMenuEntry("Cisalhamento", 10);

    glutAddMenuEntry("---- Arquivo ----", 0);
    glutAddMenuEntry("Salvar", 12);
    glutAddMenuEntry("Carregar", 13);
    glutAddMenuEntry("Animando", 26);

    glutAddSubMenu("Alterar Cor", colorSubMenu);

    glutAddMenuEntry("Sair", 11);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

