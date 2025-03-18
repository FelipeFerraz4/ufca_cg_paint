#ifndef PRIMARY_OBJECTS_H  // Evita múltiplas inclusões
#define PRIMARY_OBJECTS_H
#include "estruturas.h"

int create_point(int x, int y, vector<float> cor, draws &structure_list);
int create_line(int x1, int y1, int x2, int y2, vector<float> cor1, vector<float> cor2, draws &structure_list);
void print_point(ponto p);
void print_line(reta r);

#endif
