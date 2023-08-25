#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include "Funciones.h"

using namespace std;

int main(int argc, char** argv) {
    string usuario;
    string archivoTexto;
    string contenidoTexto;
    bool validar;
    bool permiso5, permiso6;
    bool valido = false;

    int option;
    while ((option = getopt(argc, argv, "u:f:t:")) != -1) {
        switch (option) {
            case 'u':
                usuario = optarg;
                break;
            case 'f':
                archivoTexto = optarg;
                break;
            case 't':
                contenidoTexto = optarg;
                break;
            default:
                cerr << "Uso: " << argv[0] << " -u <usuario> -f <archivo de texto> -t <contenido de texto> <componentes del vector>" << endl;
                return 1;
        }
    }

    vector<string> menuOptions;
    leerMenuOptions(menuOptions);

    vector<int> permisos;
    if (!leerPermisos(usuario, permisos)) {
        cerr << "Usuario no encontrado en user.txt" << endl;
        return 1;
    }

    // Leer componentes del vector desde los argumentos de la línea de comandos
    vector<int> vectorComponentes;
    for (int i = optind; i < argc; i++) {
        vectorComponentes.push_back(atoi(argv[i]));
    }

    permiso5 = tienePermiso(5,permisos);
    permiso6 = tienePermiso(6,permisos);

    int opcion = -1;
    while (opcion != 0) {
        cout <<"------Opciones de menu-------"<<endl;
        for(string option : menuOptions){
            cerr << option << endl;
        }
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;
        ejecutarOpcion(opcion, valido, vectorComponentes, permisos, archivoTexto, permiso5, permiso6, contenidoTexto, validar);
    }

    return EXIT_SUCCESS;
}
