#include <vector>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "primary_objects.h"
#include "estruturas.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>

void save_objects(draws &structure_list) {

    ofstream arquivo;
    arquivo.open("save.txt");
    for (const ponto &p : structure_list.lista_pontos) {
        arquivo << p.x << " " << p.y << " ";  // Escreve as coordenadas
        for (float c : p.cor) {
            arquivo << c << " ";  // Escreve os componentes de cor
        }
        arquivo << endl;  // Quebra de linha após cada ponto
    }

    arquivo << "p"; //para identificar quando acaba
    arquivo << endl;

// Salvando as retas
    for (const reta &r : structure_list.lista_retas) {
        arquivo << r.p1.x << " " << r.p1.y << " ";  // Ponto inicial da reta
        for (float c : r.p1.cor) {
            arquivo << c << " ";  // Cor do ponto inicial
        }

        arquivo << r.p2.x << " " << r.p2.y << " ";  // Ponto final da reta
        for (float c : r.p2.cor) {
            arquivo << c << " ";  // Cor do ponto final
        }
        arquivo << endl;  // Quebra de linha após cada reta
    }

    arquivo << "p";
    arquivo << endl;

    // Salvando os polígonos
    for (const poligono &p : structure_list.lista_poligonos) {
        int i = 0;
        for (const ponto &pt : p.pontos) {
            int total_pontos = p.pontos.size(); // Checa quantos pontos tem
            arquivo << pt.x << " " << pt.y << " ";  // Coordenadas de cada ponto do polígono
            for (float c : pt.cor) {
                arquivo << c << " ";  // Cor do ponto
            }
            i++;
            if (i = total_pontos) {
                arquivo << "f";
            }
        }
        arquivo << endl;  // Quebra de linha após o polígono
    }

    arquivo.close();
    

}

void save_objects(draws &structure_list){
    std::ifstream arquivo("save.txt");  // Abre o arquivo
    std::string linha;
    int modo = 1;
    std::string str = "";

    // Lê a primeira linha do arquivo
    while (std::getline(arquivo, linha)) {
        if (linha.length() == 1) {
            modo++;
        }

        switch (modo) {
            case 1: {
                int x, y;
                float cor[3];
                int nunV = 1;  // A variável que controla para qual variável o valor será alocado

                for (int i = 0; i < linha.length(); i++) {
                    int numero = linha[i] - '0'; 
                    if (numero >= 0 && numero <= 9) {
                        str = str + linha[i];
                    }

                    switch (nunV) {
                        case 1:
                            if (linha[i] == ' ') {
                                x = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 2:
                            if (linha[i] == ' ') {
                                y = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 3:
                            if (linha[i] == ' ') {
                                cor[0] = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 4:
                            if (linha[i] == ' ') {
                                cor[1] = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 5:
                            if (linha[i] == ' ') {
                                cor[2] = std::stoi(str);
                                str = "";
                                nunV++;
                                create_point(x,y, cor, &structure_list);
                            }
                            break;

                        default:
                            printf("%d ", x);
                            printf("%d ", y);
                            for (int j = 0; j < 3; j++) {
                                printf("%f ", cor[j]);
                            }
                            printf("\n");
                            break;
                    }
                }
                break;
            }

            case 2: {
                int x[2], y[2];
                float cor1[3];
                float cor2[3];
                int nunV = 1;  // A variável que controla para qual variável o valor será alocado
                int p = 0; // Marca qual dos dois pontos está sendo marcado

                for (int i = 0; i < linha.length(); i++) {
                    int numero = linha[i] - '0'; 
                    if (numero >= 0 && numero <= 9) {
                        str = str + linha[i];
                    }

                    switch (nunV) {
                        case 1:
                            if (linha[i] == ' ') {
                                if (p == 0) {
                                    x[0] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                } else {
                                    x[1] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                }
                            }
                            break;

                        case 2:
                            if (linha[i] == ' ') {
                                if (p == 0) {
                                    y[0] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                } else {
                                    y[1] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                }
                            }
                            break;

                        case 3:
                            if (linha[i] == ' ') {
                                if (p == 0) {
                                    cor1[0] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                } else {
                                    cor2[0] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                }
                            }
                            break;

                        case 4:
                            if (linha[i] == ' ') {
                                if (p == 0) {
                                    cor1[1] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                } else {
                                    cor2[1] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                }
                            }
                            break;

                        case 5:
                            if (linha[i] == ' ') {
                                if (p == 0) {
                                    cor1[2] = std::stoi(str);
                                    str = "";
                                    p++;
                                    nunV = 1;
                                } else {
                                    cor2[2] = std::stoi(str);
                                    str = "";
                                    nunV++;
                                    create_line(x[0], y[0], x[1], y[1], cor1, cor2, &structure_list);
                                }
                            }
                            break;

                        default:
                            printf("erro");
                            break;
                    }
                }
                break;
            }

            case 3:
                 {
                pontos listaDePontos;
                typedef std::vector<ponto> pontos;
                ponto p1;
                int x, y;
                float cor[3];
                int nunV = 1;  // A variável que controla para qual variável o valor será alocado

                for (int i = 0; i < linha.length(); i++) {
                    int numero = linha[i] - '0'; 
                    if (numero >= 0 && numero <= 9) {
                        str = str + linha[i];
                    }
                    if(linha[i] == 'f'){
                        create_polygon(p1, &structure_list);
                        free(p1);
                    }
                    switch (nunV) {
                        case 1:
                            if (linha[i] == ' ') {
                                p1.x = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 2:
                            if (linha[i] == ' ') {
                                p1.y = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 3:
                            if (linha[i] == ' ') {
                                p1.cor[0] = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 4:
                            if (linha[i] == ' ') {
                                p1.cor[1] = std::stoi(str);
                                str = "";
                                nunV++;
                            }
                            break;

                        case 5:
                            if (linha[i] == ' ') {
                                p1.cor[2] = std::stoi(str);
                                str = "";
                                nunV++;
                                listaDePontos.push_back(p1);
                            }
                            break;

                        default:
                            printf("%d ", x);
                            printf("%d ", y);
                            for (int j = 0; j < 3; j++) {
                                printf("%f ", cor[j]);
                            }
                            printf("\n");
                            break;
                    }
                }
                break;
            }

            default:
                printf("modof");
                break;
        }
    }

    arquivo.close();  // Fecha o arquivo
}