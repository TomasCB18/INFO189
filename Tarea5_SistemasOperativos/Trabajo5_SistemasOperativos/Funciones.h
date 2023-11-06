#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>

using namespace std;

//estas funciones son las que manipulan archivos de extension txt, son llamdas desde Archivos.cpp
void leerMenuOptions(vector<string>& menuOptions, const string& menuPath);
bool leerPermisos(const string& usuario, vector<int>& permisos, const string& userProfilePath);
bool tienePermiso(int permiso, const vector<int>& permisos);
void contarPalabras(const string& archivoEntrada, const string& archivoSalida);
string obtenerPerfilDeUsuario(const string& usuario,const string& userPath);
void almacenarTXT(string& menuPath,string& userPath,string& userProfilePath);




//estas funciones son las que hacen operaciones con respecto al vector dado por terminal, se llaman desde Operaciones.cpp
int calcularSuma(const vector<int>& v);
double calcularPromedio(const vector<int>& v);
int calcularModa(const vector<int>& v);
bool validaNombreArchivo(const string& archivoTexto);


//esta funcion es la de muestra las opciones a ejecutar segun los permisos del usuario, es llamada desde Menu.cpp
void ejecutarOpcion(int opcion,bool valido, const vector<int>& vectorComponentes, const vector<int>& permisos, const string& archivoTexto, bool permiso5, bool permiso6, const string& contenidoTexto, bool validar,const string& archivoEntrada, const string& archivoSalida, bool permiso7, bool permiso8, bool permiso9,bool permiso10);
void preparandoIndex();
void crearIndiceInvertido();
void buscarPalabras();
#endif
