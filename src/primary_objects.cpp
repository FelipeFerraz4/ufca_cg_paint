#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"

using namespace std;

void print_point(ponto p) {
    glBegin(GL_POINTS);
        glColor3f(p.cor[0], p.cor[1], p.cor[2]);
        glVertex2i(p.x, p.y);
    glEnd();
}