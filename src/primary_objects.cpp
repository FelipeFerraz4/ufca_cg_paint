#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"

using namespace std;

int create_point(int x, int y, vector<double> cor, draws &structure_list) {
    ponto p;
    p.x = x;
    p.y = y;
    p.cor = cor;
    structure_list.lista_pontos.push_back(p);
    return structure_list.lista_pontos.size() - 1;
}

int create_line(int x1, int y1, int x2, int y2, vector<double> cor1, vector<double> cor2, draws &structure_list) {
    ponto p1, p2;

    p1.x = x1;
    p1.y = y1;
    p1.cor = cor1;
    
    p2.x = x2;
    p2.y = y2;
    p2.cor = cor2;
    
    reta r = {p1, p2};
    
    structure_list.lista_retas.push_back(r);
    return structure_list.lista_retas.size() - 1;
}

int create_polygon(vector<ponto> vertices, draws &structure_list) {
    poligono p;
    p = vertices;
    structure_list.lista_poligonos.push_back(p);
    return structure_list.lista_poligonos.size() - 1;
}

void print_point(ponto p) {
    glBegin(GL_POINTS);
        glColor3f(p.cor[0], p.cor[1], p.cor[2]);
        glVertex2i(p.x, p.y);
    glEnd();
}

void print_line(reta r) {
    glBegin(GL_LINES);
        glColor3f(r[0].cor[0], r[0].cor[1], r[0].cor[2]);
        glVertex2i(r[0].x, r[0].y);
        glColor3f(r[1].cor[0], r[1].cor[1], r[1].cor[2]);
        glVertex2i(r[1].x, r[1].y);
    glEnd();
}

void print_polygon(poligono p) {
    glBegin(GL_POLYGON);
        for(int i = 0; i < p.size(); i++) {
            glColor3f(p[i].cor[0], p[i].cor[1], p[i].cor[2]);
            glVertex2i(p[i].x, p[i].y);
        }
    glEnd();
}

void print_objects(draws &structure_list) {
    for(int i = 0; i < structure_list.lista_pontos.size(); i++)
        print_point(structure_list.lista_pontos[i]);
    
    for(int i = 0; i < structure_list.lista_retas.size(); i++)
        print_line(structure_list.lista_retas[i]);
    
    for(int i = 0; i < structure_list.lista_poligonos.size(); i++)
        print_polygon(structure_list.lista_poligonos[i]);
}