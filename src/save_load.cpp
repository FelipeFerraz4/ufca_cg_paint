#include <vector>
#include "primary_objects.h"
#include "estruturas.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "save_load.h"
#include "animacao.h"

void save_objects(draws &structure_list) {
    std::cout << "Salvando..." << std::endl;
    std::ofstream arquivo("save.txt");  // Abrir o arquivo de forma adequada

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para salvar!" << std::endl;
        return;
    }

    // Salvando os pontos
    for (const ponto &p : structure_list.lista_pontos) {
        arquivo << p.x << " " << p.y << " ";  // Escreve as coordenadas
        for (double c : p.cor) {
            arquivo << c << " ";  // Escreve os componentes de cor
        }
        arquivo << std::endl;  // Quebra de linha após cada ponto    
    }
    arquivo << "p" << std::endl;

    // Salvando as retas
    for (const reta &r : structure_list.lista_retas) {
        for (const ponto &p : r) {
            arquivo << p.x << " " << p.y << " ";  // Escreve as coordenadas da reta
            for (double c : p.cor) {
                arquivo << c << " ";  // Escreve os componentes de cor
            }
        }
        arquivo << std::endl;  // Quebra de linha após cada reta
    }

    arquivo << "r" << std::endl;  // Identificador de fim das retas

    // Salvando os polígonos
    for (const poligono &p : structure_list.lista_poligonos) {
        int i = 0;
        int total_pontos = p.size();  // Total de pontos no polígono
        for (const ponto &pt : p) {
            arquivo << pt.x << " " << pt.y << " ";  // Coordenadas de cada ponto do polígono
            for (double c : pt.cor) {
                arquivo << c << " ";  // Cor do ponto
            }
            i++;
            if (i == total_pontos) {  // Se for o último ponto
                arquivo << "f";  // Identificador de fim do polígono
            }
        }
        arquivo << std::endl;  // Quebra de linha após o polígono
    }

    arquivo << "p" << std::endl;  // Identificador de fim dos polígonos
    arquivo.close();  // Fecha o arquivo após salvar
}

void load_objects(draws &structure_list) {
    std::cout << "Carregando..." << std::endl;
    std::ifstream arquivo("save.txt");
    std::string linha;
    int modo = 1;
    std::string str = "";

    while (std::getline(arquivo, linha)) {
        if (linha.length() == 1) {
            modo++;
        }

        switch (modo) {
            case 1: {
                int x, y;
                std::vector<double> c;
                int nunV = 1;

                for (int i = 0; i < linha.length(); i++) {
                    int numero = linha[i] - '0';
                    if (numero >= 0 && numero <= 9) {
                        str = str + linha[i];
                    }

                    if (linha[i] == ' ' || i == linha.length() - 1) { 
                        if (!str.empty()) {  // Verifica se a string não está vazia antes de usar
                            switch (nunV) {
                                case 1:
                                    x = std::stoi(str);
                                    break;
                                case 2:
                                    y = std::stoi(str);
                                    break;
                                case 3:
                                case 4:
                                    c.push_back(std::stoi(str));
                                    break;
                                case 5:
                                    c.push_back(std::stoi(str));
                                    create_point(x, y, c, structure_list);
                                    c.clear();
                                    break;
                            }
                            str = "";  // Limpa a string após cada conversão
                            nunV++;
                        }
                    }
                }
                break;
            }

            case 2: {
                int x[2], y[2];
                vector<double> cor1(3);
                vector<double> cor2(3);
                int nunV = 1;  // A variável que controla para qual variável o valor será alocado
                int p = 0; // Marca qual dos dois pontos está sendo marcado

                for (int i = 0; i < linha.length(); i++) {
                    int numero = linha[i] - '0';  // Isso converte o caractere para o número correspondente
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
                                    create_line(x[0], y[0], x[1], y[1], cor1, cor2, structure_list);
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
            case 3: {
                poligono p;
                ponto p1;
                int x, y;
                std::vector<double> cor(3);
                int nunV = 1;

                for (int i = 0; i < linha.length(); i++) {
                    int numero = linha[i] - '0';
                    if (numero >= 0 && numero <= 9) {
                        str = str + linha[i];
                    }
                    if (linha[i] == 'f') {
                        create_polygon(p, structure_list);
                        str = "";
                    }

                    if (linha[i] == ' ' || i == linha.length() - 1) {
                        if (!str.empty()) {
                            switch (nunV) {
                                case 1:
                                    p1.x = std::stod(str);
                                    nunV++;
                                    break;
                                case 2:
                                    p1.y = std::stod(str);
                                    nunV++;
                                    break;
                                case 3:
                                    p1.cor[0] = std::stod(str);
                                    nunV++;
                                    break;
                                case 4:
                                    p1.cor[1] = std::stod(str);
                                    nunV++;
                                    break;
                                case 5:
                                    p1.cor[2] = std::stod(str);
                                    nunV = 1;
                                    p.push_back(p1);
                                    break;
                            }
                            str = "";
                        }
                    }
                }
                break;
            }

            default:
                printf("Modo inválido\n");
                break;
        }
    }

    arquivo.close();
}
