#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;

int calcularSuma(const vector<int>& v);// Función para calcular la suma de un vector de números

double calcularPromedio(const vector<int>& v);// Función para calcular el promedio de un vector de números

int calcularModa(const vector<int>& v);// Función para calcular la moda de un vector de números (no implementada)

int main(int argc, char** argv) {
    string usuario;

    // Procesar argumentos de línea de comandos utilizando getopt
    int option;
    while ((option = getopt(argc, argv, "u:")) != -1) {
        switch (option) {
            case 'u':
                usuario = optarg;
                break;
            default:
                cerr << "Uso: " << argv[0] << " -u <usuario> -v <componentes del vector>" << endl;
                return 1;
        }
    }

    // Leer el archivo user.txt y buscar el usuario y sus permisos
    ifstream archivo("user.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo user.txt" << endl;
        return 1;
    }

    string linea;
    bool usuarioEncontrado = false;
    vector<int> permisos; // Vector para almacenar los permisos del usuario
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        if (pos != string::npos && usuario == linea.substr(0, pos)) {
            usuarioEncontrado = true;
            istringstream ss(linea.substr(pos + 1));
            string permiso_str;
            while (getline(ss, permiso_str, ';')) {
                permisos.push_back(stoi(permiso_str));
            }
            break;
        }
    }

    if (!usuarioEncontrado) {
        cerr << "Usuario no encontrado en user.txt" << endl;
        return 1;
    }

    // Leer componentes del vector desde la línea de comandos
    vector<int> vectorComponentes;
    for (int i = optind ; i < argc; i++) {  // Se inicializa el vector
        vectorComponentes.push_back(atoi(argv[i]));
    }

    // Realizar el cálculo según los permisos y mostrar el resultado
    for (int permiso : permisos) {
        switch (permiso) {
            case 1:
                cout << "Resultado (Suma): " << calcularSuma(vectorComponentes) << endl;
                break;
            case 2:
                cout << "Resultado (Promedio): " << calcularPromedio(vectorComponentes) << endl;
                break;
            case 3:
                cout << "Resultado de la moda de v es: " << calcularModa(vectorComponentes) << endl;
                break;
            case 4:
                cout << "Resultado del largo del v: " << vectorComponentes.size() << endl;
                break;
            default:
                cerr << "Permiso no válido" << endl;
                return 1;
        }
    }

    return EXIT_SUCCESS;
}
int calcularSuma(const vector<int>& v) {
    int suma = 0;
    for(int i = 0; i<v.size(); i++){
        suma = suma + v[i];
    }
    return suma;
}
double calcularPromedio(const vector<int>& v) {
    int suma = calcularSuma(v);
    return static_cast<double>(suma) / v.size();//uso de static_cast para operar un double con un int
}

int calcularModa(const vector<int>& v){
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