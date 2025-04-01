#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
#include "estruturas.h"
#include "string"

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

vector<vector<double>> matrizReflexao(string eixo) {
    vector<vector<double>> matrix(3, vector<double>(3, 0));
    if (eixo == "x") {
        matrix = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
    } else if (eixo == "y") {
        matrix = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    } else if (eixo == "origem") {
        matrix = {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
    } else if (eixo == "y=x") {
        matrix = {{0, 1, 0}, {1, 0, 0}, {0, 0, 1}};
    } else if (eixo == "y=-x") {
        matrix = {{0, -1, 0}, {-1, 0, 0}, {0, 0, 1}};
    }
    return matrix;
}

void calcular_novo_ponto(vector<vector<double>> &matriz, ponto &p) {
    double x = matriz[0][0] * p.x + matriz[0][1] * p.y + matriz[0][2];
    double y = matriz[1][0] * p.x + matriz[1][1] * p.y + matriz[1][2];

    p.x = x;
    p.y = y;
}

bool selecionar_ponto(ponto &p, double mx, double my, int t) {
    if(mx <= p.x + t && mx >= p.x - t) {
        if(my <= p.y + t && my >= p.y - t)
            return true;
    }

    return false;
}

int calcular_regiao(ponto &p, double mx, double my, int t) {

    int saida = dentro;
    if(p.x < mx - t)
        saida |= esquerda;
    if(p.x > mx + t)
        saida |= direita;
    if(p.y < my - t)
        saida |= baixo;
    if(p.y > my + t)
        saida |= cima;

    return saida;
}

bool selecionar_reta(reta &r, double mx, double my, int t) {

    int p1 = calcular_regiao(r[0], mx, my, t);
    int p2 = calcular_regiao(r[1], mx, my, t);

    bool aceita = false;

    while(true) {
        if(!(p1 & p2)) {
            aceita = true;
            break;
        } else if(p1 & p2)
            break;
        else {
            double x, y;
            int p = p1;

            if(p & esquerda) {
                x = mx - t;
                y = r[0].y + (x - r[0].x) * (r[1].y - r[0].y) / (r[1].x - r[0].x);
            } else if(p & direita) {
                x = mx + t;
                y = r[0].y + (x - r[0].x) * (r[1].y - r[0].y) / (r[1].x - r[0].x);
            } else if(p & baixo) {
                y = my - t;
                x = r[0].x + (y - r[0].y) * (r[1].x - r[0].x) / (r[1].y - r[0].y);
            } else if(p & cima) {
                y = my + t;
                x = r[0].x + (y - r[0].y) * (r[1].x - r[0].x) / (r[1].y - r[0].y);
            }

            ponto aux = {x, y};
            p1 = calcular_regiao(aux, mx, my, t);
        }
    }

    return aceita;
}

bool selecionar_area(poligono &p, double mx, double my) {
    int qtd = 0;

    for(int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();

        if(my == p[i].y) {
            if(my > p[(i - 1 + p.size()) % p.size()].y)
                qtd++;
            if(my > p[j].y)
                qtd++;
        }
        else if(p[i].y > my && p[j].y > my)
            continue;
        else if(p[i].y < my && p[j].y < my)
            continue;
        else if(p[i].x < mx && p[j].x < mx)
            continue;
        else if(p[i].x > mx && p[j].x > mx && ((p[i].y > my && p[j].y < my) || p[i].y < my && p[j].y > my))
            qtd++;
        else {
            int xi = p[i].x + (my - p[i].y) * (p[j].x - p[i].x) / (p[j].y - p[i].y);
            if(xi > mx)
                qtd++;
        }
    }

    return qtd;
}

/*
Retorna 1 par de números
O primeiro indica o objeto retornado e o segundo indica sua posição na lista
1 - Pontos
2 - Retas
3 - Polígonos
0 - Nenhum elemento selecionado
*/
pair<int, int> selecionar_objeto(draws &d, double mx, double my) {
    for(int i = 0; i < d.lista_pontos.size(); i++) {
        if(selecionar_ponto(d.lista_pontos[i], mx, my, 5))
            return {1, i};
    }

    for(int i = 0; i < d.lista_retas.size(); i++) {
        if(selecionar_reta(d.lista_retas[i], mx, my, 5))
            return {2, i};
    }

    for(int i = 0; i < d.lista_poligonos.size(); i++) {
        if(selecionar_area(d.lista_poligonos[i], mx, my)) {
            return {3, i};
        }
    }

    return {0, 0};
}

void rotacionar_r(reta &r, double theta) {

    operacoes rot;

    double cent_x = (r[0].x + r[1].x) / 2;
    double cent_y = (r[0].y + r[1].y) / 2;

    rot.push(matrizTransacional(-cent_x, -cent_y));
    rot.push(matrizRotacional(theta));
    rot.push(matrizTransacional(cent_x, cent_y));

    vector<vector<double>> matriz = calcular_matriz(rot);
    
    calcular_novo_ponto(matriz, r[0]);
    calcular_novo_ponto(matriz, r[1]);
}

void rotacionar_p(poligono &p, double theta) {
    operacoes rot;

    double aux = 0;
    for(ponto n: p)
        aux += n.x;
    double cent_x = aux / p.size();

    aux = 0;
    for(ponto n: p)
        aux += n.y;
    double cent_y = aux / p.size();

    rot.push(matrizTransacional(-cent_x, -cent_y));
    rot.push(matrizRotacional(theta));
    rot.push(matrizTransacional(cent_x, cent_y));

    vector<vector<double>> matriz = calcular_matriz(rot);

    for(int i = 0; i < p.size(); i++)
        calcular_novo_ponto(matriz, p[i]);
}

void escalonar_r(reta &r, double Sx, double Sy) {
    operacoes esc;

    double cent_x = (r[0].x + r[1].x) / 2;
    double cent_y = (r[0].y + r[1].y) / 2;

    esc.push(matrizTransacional(-cent_x, -cent_y));
    esc.push(matrizEscalar(Sx, Sy));
    esc.push(matrizTransacional(cent_x, cent_y));

    vector<vector<double>> matriz = calcular_matriz(esc);
    
    calcular_novo_ponto(matriz, r[0]);
    calcular_novo_ponto(matriz, r[1]);
}

void escalonar_p(poligono &p, double Sx, double Sy) {
    operacoes esc;

    double aux = 0;
    for(ponto n: p)
        aux += n.x;
    double cent_x = aux / p.size();

    aux = 0;
    for(ponto n: p)
        aux += n.y;
    double cent_y = aux / p.size();

    esc.push(matrizTransacional(-cent_x, -cent_y));
    esc.push(matrizEscalar(Sx, Sy));
    esc.push(matrizTransacional(cent_x, cent_y));

    vector<vector<double>> matriz = calcular_matriz(esc);

    for(int i = 0; i < p.size(); i++)
        calcular_novo_ponto(matriz, p[i]);
}

void reflect_p(poligono &p, string eixo) {
    operacoes esc;

    double aux = 0;
    for(ponto n: p)
        aux += n.x;
    double cent_x = aux / p.size();

    aux = 0;
    for(ponto n: p)
        aux += n.y;
    double cent_y = aux / p.size();

    esc.push(matrizTransacional(-cent_x, -cent_y));
    esc.push(matrizReflexao(eixo));
    esc.push(matrizTransacional(cent_x, cent_y));

    vector<vector<double>> matriz = calcular_matriz(esc);

    for(int i = 0; i < p.size(); i++)
        calcular_novo_ponto(matriz, p[i]);
}

void reflect_r(reta &r, string eixo) {
    operacoes esc;

    double cent_x = (r[0].x + r[1].x) / 2;
    double cent_y = (r[0].y + r[1].y) / 2;

    esc.push(matrizTransacional(-cent_x, -cent_y));
    esc.push(matrizReflexao(eixo));
    esc.push(matrizTransacional(cent_x, cent_y));

    vector<vector<double>> matriz = calcular_matriz(esc);
    
    calcular_novo_ponto(matriz, r[0]);
    calcular_novo_ponto(matriz, r[1]);
}

void reflect_point(ponto &p, string eixo) {
    operacoes esc;

    esc.push(matrizTransacional(-p.x, -p.y));
    esc.push(matrizReflexao(eixo));
    esc.push(matrizTransacional(p.x, p.y));

    vector<vector<double>> matriz = calcular_matriz(esc);
    
    calcular_novo_ponto(matriz, p);
}

void shear_p(poligono &p, double S, bool vertical) {
    operacoes esc;

    double aux_x = 0, aux_y = 0;
    for (ponto n : p) {
        aux_x += n.x;
        aux_y += n.y;
    }
    double cent_x = aux_x / p.size();
    double cent_y = aux_y / p.size();

    esc.push(matrizTransacional(-cent_x, -cent_y));
    esc.push(matrizSizalhar(S, vertical));          
    esc.push(matrizTransacional(cent_x, cent_y));

    vector<vector<double>> matriz = calcular_matriz(esc);

    for (int i = 0; i < p.size(); i++)
        calcular_novo_ponto(matriz, p[i]);
}

void shear_l(reta &r, double S, bool vertical) {
    operacoes esc;

    double cent_x = (r[0].x + r[1].x) / 2.0;
    double cent_y = (r[0].y + r[1].y) / 2.0;

    esc.push(matrizTransacional(-cent_x, -cent_y)); 
    esc.push(matrizSizalhar(S, vertical));          
    esc.push(matrizTransacional(cent_x, cent_y));  

    vector<vector<double>> matriz = calcular_matriz(esc);

    calcular_novo_ponto(matriz, r[0]);
    calcular_novo_ponto(matriz, r[1]);
}
