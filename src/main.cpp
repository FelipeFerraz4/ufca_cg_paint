#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"

// Para compilar:
//g++ -o main main.cpp primary_objects.cpp estruturas.cpp -lfreeglut -lopengl32 -lglu32 -lm


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    draws structure_list;

    int index_p1 = create_point(80, 90, {1.0, 0.0, 0.0}, structure_list);
    int index_p2 = create_point(80, 60, {0.0, 0.0, 1.0}, structure_list);
    int index_l1 = create_line(100, 90, 100, 60, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, structure_list);

    print_point(structure_list.lista_pontos[index_p1]);
    print_point(structure_list.lista_pontos[index_p2]);
    print_line(structure_list.lista_retas[index_l1]);

    glFlush();
}

int init(void){
    glClearColor(0.0, 0.0, 0.0,0.0);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 250.0, 0.0, 150.0);
    return 0;
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 300);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Hello World OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}