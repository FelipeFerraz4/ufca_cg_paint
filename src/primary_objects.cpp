#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"

using namespace std;

int create_ponto(int x, int y, vector<float> cor, draws &structure_list) {
    ponto p;
    p.x = x;
    p.y = y;
    p.cor = cor;
    structure_list.lista_pontos.push_back(p);
    return structure_list.lista_pontos.size() - 1;
}

void print_point(ponto p) {
    glBegin(GL_POINTS);
        glColor3f(p.cor[0], p.cor[1], p.cor[2]);
        glVertex2i(p.x, p.y);
    glEnd();
}