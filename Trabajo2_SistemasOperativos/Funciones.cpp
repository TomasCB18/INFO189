#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

void leerMenuOptions(vector<string>& menuOptions) {
 ifstream menuFile("menu.txt");
    if (!menuFile) {
        cerr << "No se pudo abrir el archivo del menú." << endl;
        //exit(1);
    }

    string line;
    while (getline(menuFile, line)) {
        menuOptions.push_back(line);
    }
    menuFile.close();

}

bool leerPermisos(const string& usuario, vector<int>& permisos) {
    ifstream archivo("user.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo user.txt" << endl;
        return false;
    }

    string linea;
    bool usuarioEncontrado = false;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        string usuarioArchivo = linea.substr(0, pos);
        if (usuario == usuarioArchivo) {
            usuarioEncontrado = true;
            istringstream ss(linea.substr(pos + 1));
            string permiso_str;
            while (getline(ss, permiso_str, ';')) {
                permisos.push_back(stoi(permiso_str));
            }
            break;
        }
    }
    
    if(usuarioEncontrado){
        return true;
    }else{
        return false;
    }
}

bool tienePermiso(int permiso, const vector<int>& permisos) {
    return find(permisos.begin(), permisos.end(), permiso) != permisos.end();
}

void ejecutarOpcion(int opcion, bool valido, const vector<int>& vectorComponentes, const vector<int>& permisos, const string& archivoTexto, bool permiso5, bool permiso6, string contenidoTexto) {
    switch (opcion)
        {
            case 0:
                system("clear");
                cout <<"Saliendo del programa" << endl;
                break;
            case 1:
                system("clear");
                for(int permiso : permisos){
                    if(permiso == 1){
                        valido = true;
                        break;
                    }
                }
                if(valido){
                    cout << "Resultado (Suma): " << calcularSuma(vectorComponentes) << endl;
                }
                else{
                    cerr << "Permiso no válido" << endl;
                }
                valido = false;
                break;
            case 2:
                system("clear");
                for(int permiso : permisos){
                    if(permiso == 2){
                        valido = true;
                        break;
                    }
                }
                if(valido){
                    cout << "Resultado (Promedio): " << calcularPromedio(vectorComponentes) << endl;
                }
                else{
                    cerr << "Permiso no válido" << endl;
                }
                valido = false;
                break;
            case 3:
                system("clear");
                for(int permiso : permisos){
                    if(permiso == 3){
                        valido = true;
                        break;
                    }
                }
                if(valido){
                    cout << "Resultado de la moda de v es: " << calcularModa(vectorComponentes) << endl;
                }
                else{
                    cerr << "Permiso no válido" << endl;
                }
                valido = false;
                break;
            case 4:
                system("clear");
                for(int permiso : permisos){
                    if(permiso == 4){
                        valido = true;
                        break;
                    }
                }
                if(valido){
                    cout << "Resultado del largo del v: " << vectorComponentes.size() << endl;
                }
                else{
                    cerr << "Permiso no válido" << endl;
                }
                valido = false;
                break;
            case 5:
                system("clear");
                if (permiso5) {
                    bool validar  = validaNombreArchivo(archivoTexto);
                    if(!validar){
                        ofstream archivoSalida(archivoTexto);//creacion del archivo txt
                        cout << "Archivo de texto creado exitosamente." << endl;
                    }
                    else{
                        cerr << "Ya existe un archivo con ese nombre." << endl;
                    }                    
                  
                } else {
                    cerr << "No tienes permiso para crear archivos de texto." << endl;
                }
                break;
            case 6:
                system("clear");
                if (permiso6) {
                    if(permiso5){//valida si se tiene el permiso 5  para poder escribir en 6
                       ofstream archivoSalida(archivoTexto, ios::app);
                       if (archivoSalida.is_open()) {
                         contenidoTexto;
                         archivoSalida.close();
                         cout << "Texto agregado al archivo de texto exitosamente." << endl;
                         }
                    }else{
                        cerr << "no se puede agregar contenido ya que el usuario no puede crear un txt."<< endl;
                    }
            
                } else {
                    cerr << "No tienes permiso para agregar texto a archivos de texto." << endl;
                }
                break;
            default:
                system("clear");
                cerr << "La opcion " <<opcion<<" aun no ha sido implementada "<< endl;
                break;
            }
            cout << endl;
}

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
