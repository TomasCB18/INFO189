#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>

using namespace std;

void leerMenuOptions(vector<string>& menuOptions);
bool leerPermisos(const string& usuario, vector<int>& permisos);
bool tienePermiso(int permiso, const vector<int>& permisos);
void ejecutarOpcion(int opcion,bool valido, const vector<int>& vectorComponentes, const vector<int>& permisos, const string& archivoTexto, bool permiso5, bool permiso6, string contenidoTexto);

int calcularSuma(const vector<int>& v);
double calcularPromedio(const vector<int>& v);
int calcularModa(const vector<int>& v);
bool validaNombreArchivo(const string& archivoTexto);

#endif
