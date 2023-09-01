#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>

using namespace std;

void leerMenuOptions(vector<string>& menuOptions) {
 ifstream menuFile("menu.txt");
    if (!menuFile) {
        cerr << "No se pudo abrir el archivo del menú." << endl;
        exit(1);
    }

    string line;
    while (getline(menuFile, line)) {
        menuOptions.push_back(line);
    }
    menuFile.close();

}


string obtenerPerfilDeUsuario(const string& usuario) {
    ifstream archivo("user.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo user.txt" << endl;
        return "";
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        if (pos != string::npos) {
            string usuarioArchivo = linea.substr(0, pos);
            string profile = linea.substr(pos + 1);
            if (usuario == usuarioArchivo) {
                return profile; // Retorna el perfil después del ';'
            }
        }
    }

    //cerr << "Usuario no encontrado en user.txt" << endl;
    return "";
}


bool leerPermisos(const string& perfil, vector<int>& permisos) {
    ifstream archivo("userprofile.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo userprofile.txt" << endl;
        return false;
    }

    string linea;
    bool perfilEncontrado = false;
    while (getline(archivo, linea)) {
        size_t pos = linea.find(';');
        string perfilUsuario = linea.substr(0, pos);
        if (perfil == perfilUsuario) {
            perfilEncontrado = true;
            istringstream ss(linea.substr(pos + 1));
            string permiso_str;
            while (getline(ss, permiso_str, ';')) {
                permisos.push_back(stoi(permiso_str));
            }
            break;
        }
    }
    
    if(perfilEncontrado){
        return true;
    }else{
        return false;
    }
}


/*bool leerPermisos(const string& usuario, vector<int>& permisos) {
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
}*/
void contarPalabras(const string& archivoEntrada, const string& archivoSalida){
    ifstream inputFile(archivoEntrada);
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo de entrada." << endl;
        return;
    }

    unordered_map<string, int> wordCount;
    string word;
    while (inputFile >> word) {
        // Limpia la palabra de caracteres no alfabéticos
        word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());

        if (!word.empty()) {
            transform(word.begin(), word.end(), word.begin(), ::tolower); // Convertir a minúsculas
            wordCount[word]++;
        }
    }
    inputFile.close();

    ofstream outputFile(archivoSalida);
    if (!outputFile.is_open()) {
        cerr << "No se pudo crear el archivo de salida." << endl;
        return;
    }

    for (const auto& entry : wordCount) {
        outputFile << entry.first << ";" << entry.second << endl;
    }
    outputFile.close();

    cout << "Conteo de palabras completado. Resultados guardados en " << archivoSalida << endl;
}

bool tienePermiso(int permiso, const vector<int>& permisos) {
    return find(permisos.begin(), permisos.end(), permiso) != permisos.end();
}