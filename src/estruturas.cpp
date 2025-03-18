#include <vector>
#include <stack>
#include <cmath>
#include "estruturas.h"

using namespace std;

vector<vector<double>> matrizRotacional(double theta) {
    vector<vector<double>> matriz(3, vector<double>(3));

    matriz[0][0] = cos(theta);
    matriz[0][1] = -sin(theta);
    matriz[0][2] = 0;

    matriz[1][0] = sin(theta);
    matriz[1][1] = cos(theta);
    matriz[1][2] = 0;

    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;

    return matriz;
}

vector<vector<double>> matrizTransacional(int x, int y) {
    vector<vector<double>> matriz(3, vector<double>(3));

    matriz[0][0] = 1;
    matriz[0][1] = 0;
    matriz[0][2] = x;

    matriz[1][0] = 0;
    matriz[1][1] = 1;
    matriz[1][2] = y;

    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;

    return matriz;
}

//Reflexão fica pra depois
vector<vector<double>> matrizEscalar(double Sx, double Sy) {
    vector<vector<double>> matriz(3, vector<double>(3));

    matriz[0][0] = Sx;
    matriz[0][1] = 0;
    matriz[0][2] = 0;

    matriz[1][0] = 0;
    matriz[1][1] = Sy;
    matriz[1][2] = 0;

    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;

    return matriz;
}

vector<vector<double>> matrizSizalhar(double S, bool vertical) {
    vector<vector<double>> matriz(3, vector<double>(3));

    matriz[0][0] = 1;
    
    matriz[0][1] = 0;
    matriz[0][2] = 0;

    matriz[1][0] = 0;
    matriz[1][1] = 1;
    matriz[1][2] = 0;

    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;

    if(vertical)
        matriz[1][0] = S;
    else
        matriz[0][1] = S;

    return matriz;
}

vector<vector<double>> calcular_matriz(operacoes &pilha) {
    vector<vector<double>> matriz(3, vector<double>(3));
    vector<vector<double>> auxiliar(3, vector<double>(3));

    matriz[0][0] = 1;
    matriz[0][1] = 0;
    matriz[0][2] = 0;

    matriz[1][0] = 0;
    matriz[1][1] = 1;
    matriz[1][2] = 0;

    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;

    while(!pilha.empty()) {
        vector<vector<double>> temporario = pilha.top();
        pilha.pop();

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                double produto = 0.0;
                for(int k = 0; k < 3; k++)
                    produto += matriz[i][k] * temporario[k][j];

                auxiliar[i][j] = produto;
            }
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++)
                matriz[i][j] = auxiliar[i][j];
        }
    }

    return matriz;
}

void calcular_novo_ponto(vector<vector<double>> &matriz, ponto &p) {
    double x = matriz[0][0] * p.x + matriz[0][1] * p.y + matriz[0][2];
    double y = matriz[1][0] * p.x + matriz[1][1] * p.y + matriz[1][2];

    p.x = x;
    p.y = y;
}