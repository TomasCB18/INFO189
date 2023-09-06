#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

int calcularSuma(const vector<int>& v) {
    int suma = 0;
    for (int i = 0; i < v.size(); i++) {
        suma = suma + v[i];
    }
    return suma;
}

double calcularPromedio(const vector<int>& v) {
    int suma = calcularSuma(v);
    return static_cast<double>(suma) / v.size();
}

int calcularModa(const vector<int>& v) {
    int moda = 0;
    int maxFrequency = 0;

    for (size_t i = 0; i < v.size(); ++i) {
        int c = 0;
        for (size_t j = 0; j < v.size(); ++j) {
            if (v[j] == v[i]) {
                ++c;
            }
        }

        if (c > maxFrequency) {
            maxFrequency = c;
            moda = v[i];
        }
    }

    return moda;
}

bool validaNombreArchivo(const string& archivoTexto) {
    ifstream archivo(archivoTexto.c_str());
    return archivo.good();
}
