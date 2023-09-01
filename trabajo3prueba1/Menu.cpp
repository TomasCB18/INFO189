#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

void ejecutarOpcion(int opcion, bool valido, const vector<int>& vectorComponentes, const vector<int>& permisos, const string& archivoTexto, bool permiso5, bool permiso6,const string& contenidoTexto,bool validar, const string& archivoEntrada, const string& archivoSalida, bool permiso7) {
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
                    validar  = validaNombreArchivo(archivoTexto);
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
                         archivoSalida<<contenidoTexto;
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
            case 7:
                system("clear");
                if(permiso7){
                    if (!archivoEntrada.empty() && !archivoSalida.empty()) {
                        contarPalabras(archivoEntrada, archivoSalida);
                    }
                    else{
                         cerr << "Debes especificar un archivo de entrada y un archivo de salida." << endl;
                    }
                }
                else{
                    cerr << "No tienes permiso para ingresar un texto y hacer un conteo de palabras." << endl;
                }
                /*if (!archivoEntrada.empty() && !archivoSalida.empty()) {
                    contarPalabras(archivoEntrada, archivoSalida);
                } else {
                    cerr << "Debes especificar un archivo de entrada y un archivo de salida." << endl;
                }*/
                break;
            default:
                system("clear");
                cerr << "La opcion " <<opcion<<" aun no ha sido implementada "<< endl;
                break;
            }
            cout << endl;
}

