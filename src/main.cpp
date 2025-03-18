#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"

//g++ -o main main.cpp primary_objects.cpp estruturas.cpp -lfreeglut -lopengl32 -lglu32 -lm


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    ponto p1 = {80, 60};
    ponto p2 = {80, 90};
    glColor3f(0.0, 0.0, 1.0);
    print_point(p1);
    print_point(p2);

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