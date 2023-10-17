#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <filesystem>
#include <unistd.h>


using namespace std;
namespace fs = filesystem;

void actualizarIndice(const string& palabra, const string& archivo, int cantidad, unordered_map<string, unordered_map<string, int>>& indice) {
    indice[palabra][archivo] += cantidad;
}

void guardarIndice(const string& archivoSalida, const unordered_map<string, unordered_map<string, int>>& indice) {
    ofstream archivo(archivoSalida);
    if (archivo.is_open()) {
        for (const auto& palabra : indice) {
            archivo << palabra.first << ":";
            for (const auto& entrada : palabra.second) {
                archivo << "(" << entrada.first << ";" << entrada.second << ");";
            }
            archivo << endl;
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo de salida: " << archivoSalida << endl;
    }
}

/*int contarArchivos(const string& directorio) {
    int contador = 0;
    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            contador++;
        }
    }
    return contador;
}*/

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <directorio_de_archivos_txt> <archivo_de_salida_idx>" << endl;
        return 1;
    }

    string directorioEntrada = argv[1];
    string archivoSalida = argv[2];

    /*int cantidadMinimaArchivos = 20;

    int cantidadArchivos = contarArchivos(directorioEntrada);

    if (cantidadArchivos < cantidadMinimaArchivos) {
        cerr << "Error: El número mínimo de archivos no se ha alcanzado (" << cantidadMinimaArchivos << " requeridos, " << cantidadArchivos << " encontrados)." << endl;
        return 1;
    }*/

    unordered_map<string, unordered_map<string, int>> indice;

    for (const auto& entry : fs::directory_iterator(directorioEntrada)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            ifstream archivo(entry.path());
            if (archivo.is_open()) {
                string linea;
                while (getline(archivo, linea)) {
                    istringstream iss(linea);
                    string palabra;
                    int cantidad;
                    getline(iss, palabra, ';');
                    iss >> cantidad;
                    actualizarIndice(palabra, entry.path().filename(), cantidad, indice);
                }
                archivo.close();
            } else {
                cerr << "Error al abrir el archivo: " << entry.path() << endl;
            }
        }
    }

    guardarIndice(archivoSalida, indice);

    cout << "El proceso pid = " << getpid() << " genero el archivo: " << archivoSalida << endl;


    return 0;
}

