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
    const char* vectorNumeros = nullptr;
    string usuario;
    string archivoTexto;
    string contenidoTexto;
    bool validar;
    bool permiso5, permiso6, permiso7;
    bool valido = false;
    string archivoEntrada;
    string archivoSalida;
    vector<int> vectorComponentes;
    vector<int> numeros;
    vector<int> permisos;

    int option;
    while ((option = getopt(argc, argv, "u:f:t:v:i:o:")) != -1) {
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
            case 'v': 
                vectorNumeros = optarg; 
                break;
            case 'i':
                archivoEntrada = optarg;
                break;
            case 'o':
                archivoSalida = optarg;
                break;
            default:
                cerr << "Uso: " << argv[0] << " -u <usuario> -f <archivo de texto> -t <contenido de texto> -v <componentes del vector> -i <texto de entrada> -o <conteo de palabras>" << endl;
                return 1;
        }
    }
    cout<<endl;

    vector<string> menuOptions;
    leerMenuOptions(menuOptions);


    string perfil = obtenerPerfilDeUsuario(usuario);
    if (!leerPermisos(perfil, permisos)) {
        cerr << "Usuario no encontrado en user.txt" << endl;
        return 1;
    }
    
    /*if (!leerPermisos(usuario, permisos)) {
        cerr << "Usuario no encontrado en user.txt" << endl;
        return 1;
    }*/

    //lee componentes del vector desde consola y convierte los caracteres a enteros
    while (optind < argc && *argv[optind] != '-' && *argv[optind] != 'v') {
        vectorComponentes.push_back(atoi(argv[optind]));
        optind++;
    }

   
    permiso5 = tienePermiso(5,permisos);
    permiso6 = tienePermiso(6,permisos);
    permiso7 = tienePermiso(7,permisos);

    int opcion = -1;
    while (opcion != 0) {
        cout<<"Nombre_de_usuario: "<< usuario << endl;
        cout<<"Perfil_de_usuario: "<< perfil << endl;
        cout<<endl;
        cout <<"------Opciones de menu-------"<<endl;
        for(string option : menuOptions){
            cerr << option << endl;
        }
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cout << endl;
        ejecutarOpcion(opcion, valido, vectorComponentes, permisos, archivoTexto, permiso5, permiso6, contenidoTexto, validar, archivoEntrada, archivoSalida,permiso7);
    }

    return EXIT_SUCCESS;
}
