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

int calcularSuma(const vector<int>& v);
double calcularPromedio(const vector<int>& v);
int calcularModa(const vector<int>& v);
bool validaNombreArchivo(const string& archivoTexto);

int main(int argc, char** argv) {
    string usuario;
    string archivoTexto;
    string menuTexto;
    string contenidoTexto;
    bool permiso5 = false;
    bool permiso6 = false;
    bool valido = false;

    // Procesar argumentos de línea de comandos utilizando getopt
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
    //leer el archivo menu.txt que contiene las opciones
    ifstream menuFile("menu.txt");
    if(!menuFile){
        cerr << "No se pudo abrir el archivo del menu."<< endl;
        return 1;
    }
    //se crea el vector que almacenara las opciones de menu extraidas de menu.txt
    vector<string> menuOptions;
    string line;
    while(getline(menuFile, line)){
        menuOptions.push_back(line);
    }
    menuFile.close();


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

    if (!usuarioEncontrado) {
        cerr << "Usuario no encontrado en user.txt" << endl;
        return 1;
    }

    // Verificar permisos 5 y 6
    if (find(permisos.begin(), permisos.end(), 5) != permisos.end()) {
        permiso5 = true;
    }
    if (find(permisos.begin(), permisos.end(), 6) != permisos.end()) {
        permiso6 = true;
    }


    // Leer componentes del vector desde la línea de comandos
    vector<int> vectorComponentes;
    for (int i = optind ; i < argc; i++) {
        vectorComponentes.push_back(atoi(argv[i]));
    }

    int opcion = -1;
    while(opcion!=0){
        for(string option : menuOptions){
            cerr << option << endl;
        }
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 0:
                cout <<"Saliendo del programa" << endl;
                break;
            case 1:
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
                break;
            case 2:
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
                break;
            case 3:
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
                break;
            case 4:
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

                break;
            case 5:
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
                cerr << "Permiso indefinido" << endl;
                break;
            }
            cout << endl;

    }
    
    // Realizar el cálculo según los permisos y mostrar el resultado
   /* for (int permiso : permisos) {
        switch (permiso) {
            case 0:
                break;
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
            case 5:
                if (permiso5) {
                    bool validar  = validaNombreArchivo(archivoTexto);
                    if(!validar){
                        ofstream archivoSalida(archivoTexto);//creacion del archivo txt
                        cout << "Archivo de texto creado exitosamente." << endl;
                    }
                    else{
                        cerr << "Ya existe un archivo con ese nombre." << endl;
                    }*/                   
                    /*if (archivoSalida.is_open()) {
                        archivoSalida << contenidoTexto;
                        archivoSalida.close();
                        cout << "Archivo de texto creado exitosamente." << endl;
                    } else {
                        cerr << "No se pudo crear el archivo de texto." << endl;
                    }*/
                /*} else {
                    cerr << "No tienes permiso para crear archivos de texto." << endl;
                }
                break;
            case 6:
                if (permiso6) {
                    if(permiso5){//valida si se tiene el permiso 5  para poder escribir en 6
                       ofstream archivoSalida(archivoTexto, ios::app);
                       if (archivoSalida.is_open()) {
                        //archivoSalida << "\n" << contenidoTexto;
                         contenidoTexto;
                         archivoSalida.close();
                         cout << "Texto agregado al archivo de texto exitosamente." << endl;
                         }
                    }else{
                        cerr << "no se puede agregar contenido ya que no hay un archivo.txt creado."<< endl;
                    }/**/
                   /* ofstream archivoSalida(archivoTexto, ios::app);
                    if (archivoSalida.is_open()) {
                        //archivoSalida << "\n" << contenidoTexto;
                        contenidoTexto;
                        archivoSalida.close();
                        cout << "Texto agregado al archivo de texto exitosamente." << endl;
                    } /*else {
                        cerr << "No se pudo abrir el archivo de texto para agregar texto." << endl;
                    }*/
                /*} else {
                    cerr << "No tienes permiso para agregar texto a archivos de texto." << endl;
                }
                break;
            default:
                cerr << "Permiso no válido" << endl;
                return 1;
        }
    }*/

    return EXIT_SUCCESS;
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
bool validaNombreArchivo(const string& archivoTexto){
    ifstream archivo(archivoTexto.c_str());
    return archivo.good();
}