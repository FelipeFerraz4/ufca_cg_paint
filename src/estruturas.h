#ifndef ESTRUTURAS_H  // Evita múltiplas inclusões
#define ESTRUTURAS_H

#include <vector>
#include <stack>
#include <cmath>

using namespace std;

struct ponto {
    int x;
    int y;
    vector<float> cor = {0.0, 0.0, 0.0};
};

typedef vector<ponto> pontos;
typedef vector<ponto> reta;
typedef vector<reta> retas;
typedef vector<ponto> poligono;
typedef vector<poligono> poligonos;

struct draws {
    pontos lista_pontos;
    retas lista_retas;
    poligonos lista_poligonos;
};

typedef stack<vector<vector<double>>> operacoes;

vector<vector<double>> matrizRotacional(double theta);
vector<vector<double>> matrizTransacional(int x, int y);
vector<vector<double>> matrizEscalonamento(double S, bool vertical);
vector<vector<double>> calcular_matriz(operacoes &pilha);
void calcular_novo_ponto(vector<vector<double>> &matriz, ponto &p);

#endif
