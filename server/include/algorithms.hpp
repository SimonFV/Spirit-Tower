#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace std;

class algorithms
{

private:
    vector<vector<int>> population;

public:
    // Metodos algoritmo genetico
    void mostrarPoblacion(vector<vector<int>> population) const;
    vector<vector<int>> crearPoblacion() const;
    vector<vector<int>> fitness(vector<vector<int>> population, int valor_modelo) const;
    vector<vector<int>> selection_and_reproduction(vector<vector<int>> population, int valor_modelo) const;
    vector<vector<int>> mutation(vector<vector<int>> population, int max_valor) const;
    vector<vector<int>> eliminar_valores_vector(vector<vector<int>> population) const;
    vector<vector<int>> quitar_individuos(vector<vector<int>> population) const;
    vector<vector<int>> evolucionar(vector<vector<int>> population, int max_valor, int valor_modelo) const;

    void setPopulation(vector<vector<int>> population_nueva)
    {
        population = population_nueva;
    }

    // Metodos algoritmo Bresenham
    std::string algoritmo_bresenham(int x_begin, int y_begin, int x_end1, int y_end1) const;

    // Metodos algoritmo Backtracking
    int algoritmo_backtracking(int r, int c, int x_end, int y_end, vector<vector<int>> mapa, vector<vector<int>> solution) const;
    std::string ruta_backtracking() const;
    vector<vector<int>> generar(int row, int col, vector<vector<int>> solution) const;

    // Metodos algortimo A Star
    typedef pair<int, int> Pair;
    std::string algoritmo_aStar(Pair src, Pair dest, vector<vector<int>> mapa) const;

public:
    vector<vector<int>> getPopulation() { return population; }
};

#endif