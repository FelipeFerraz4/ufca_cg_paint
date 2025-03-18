#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"

using namespace std;

void print_point(ponto p) {
    glBegin(GL_POINTS);
        glVertex2i(p.x, p.y);
    glEnd();
}