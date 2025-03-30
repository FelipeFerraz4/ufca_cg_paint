#ifndef ESTRUTURAS_H  // Evita múltiplas inclusões
#define ESTRUTURAS_H

#include <vector>
#include <stack>
#include <cmath>

using namespace std;

const int esquerda = 0b1000;
const int direita = 0b0100;
const int dentro = 0b0000;
const int baixo = 0b0010;
const int cima = 0b0001;

struct ponto {
    double x;
    double y;
    vector<double> cor = {0.0, 0.0, 0.0};
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
vector<vector<double>> matrizEscalar(double Sx, double Sy);
vector<vector<double>> matrizSizalhar(double S, bool vertical);
vector<vector<double>> calcular_matriz(operacoes &pilha);
void calcular_novo_ponto(vector<vector<double>> &matriz, ponto &p);
bool selecionar_ponto(ponto &p, double mx, double my, int t);
int calcular_regiao(ponto &p, double mx, double my, int t);
bool selecionar_reta(reta &r, double mx, double my, int t);
bool selecionar_area(poligono &p, double mx, double my);
pair<int, int> selecionar_objeto(draws &d, double mx, double my);
void rotacionar_r(reta &r, double theta);
void rotacionar_p(poligono &p, double theta);
void escalonar_r(reta &r, double Sx, double Sy);
void escalonar_p(poligono &p, double Sx, double Sy);

#endif