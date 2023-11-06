#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <string>
#include <cstdlib>
using namespace std;


void almacenarTXT(string& menuPath,string& userPath,string& userProfilePath){
    ifstream inputFile("PATH.env");
    if (!inputFile.is_open()) {
        cerr << "No se pudo abrir el archivo PATH.env" << endl;
        return exit(1);
    }
    unordered_map<string, string> paths;

    string line;
    while (getline(inputFile, line)) {
        size_t equalsPos = line.find('=');
        if (equalsPos != string::npos) {
            string variable = line.substr(0, equalsPos);
            string value = line.substr(equalsPos + 1);
            paths[variable] = value;
        }
    }

    inputFile.close();

    // Accede a las rutas almacenadas
    menuPath = paths["MENU_PATH"];
    userPath = paths["USER_PATH"];
    userProfilePath = paths["USERPROFILE_PATH"];

    // Ahora puedes usar estas rutas para abrir los archivos correspondientes
    
}
void leerMenuOptions(vector<string>& menuOptions, const string& menuPath) {
 ifstream menuFile(menuPath);
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


string obtenerPerfilDeUsuario(const string& usuario,const string& userPath) {
    ifstream archivo(userPath);
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


bool leerPermisos(const string& perfil, vector<int>& permisos, const string& userProfilePath) {
    ifstream archivo(userProfilePath);
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
    }
    else{
        return false;
    }
}

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



bool minArch = false;
void preparandoIndex(){
    ifstream file;
    file.open("file.idx");
        if (file) { // Si existe el file.idx lo borra
            remove("file.idx");
        }
        string preparar = "Externos/app2 " + string(getenv("EXTENTION")) + " " + string(getenv("PATH_FILES_IN")) + " " + string(getenv("PATH_FILES_OUT")) + " " + string(getenv("AMOUNT_THREADS"));
        int successPrepararArchivos = system(preparar.c_str());
        if (successPrepararArchivos == 0) {
            cout << "Proceso fue llamado correctamente" << endl;
            minArch = true;
        }
        else if(successPrepararArchivos == 1){
            cout<<"No se puede ejecutar el proceso ya que no se cumple con la entrada minima"<<endl;
        }
        else {
            cout << "No se pudo llamar al proceso" << endl;
        }

}
bool valida9 = false;
void crearIndiceInvertido(){
    if(minArch){
        ifstream file;
        file.open("file.idx");
        if (!file) {
            file.close();
            string crearIndice = "Externos/app3 " + string(getenv("PATH_FILES_OUT")) + " " + string(getenv("INVERTED_INDEX_FILE"));
            int successIndice = system(crearIndice.c_str());
            if (successIndice != 0) {
                cout << "Hubo un error al crear el indice" << endl;
            }
            else{
                valida9 = true;

            }
        }
        //else {
          //  cout << "El file.idx ya fue creado" << endl;
        //}
    }
    else{
        cout<<"No se puede crear file.idx ya que no se pudo ejecutar el permiso 8"<<endl;
    }
}
void buscarPalabras(){
    if (valida9) { 
        string buscarP = "Externos/app4 " + string(getenv("INVERTED_INDEX_FILE")) + " " + string(getenv("TOPK"));
        int successBuscarP = system(buscarP.c_str());
        if (successBuscarP != 0) {
            cout << "Hubo un error, no se pudo buscar palabras" << endl;
        }
    } 
    else {
        cout << "No se puede buscar palabras ya que no se ejecutó el permiso 9" << endl;
    }
    /*if(valida9){
        ifstream file;
        file.open("file.idx");
         if(!file){
            string buscarP = "Externos/app4 " + string(getenv("INVERTED_INDEX_FILE")) + " " + string(getenv("TOPK"));
            int sucessBuscarP  = system(buscarP.c_str());
            if(sucessBuscarP != 0){
                cout<< "Hubo un error, no se pudo buscar palabras"<<endl;
            }
        }
    }
    else{
        cout<<"No se puede buscarPalabras ya que no se ejecuto el permiso 9"<<endl;
    }*/
}

/*void preparandoIndex() {
    ifstream file;
    file.open("Out/file.idx");
    if (file) { // Si existe el file.idx lo borra
        remove("Out/file.idx");
    }
    
    const char* extension = getenv("EXTENTION");
    const char* pathFilesIn = getenv("PATH_FILES_IN");
    const char* pathFilesOut = getenv("PATH_FILES_OUT");
    const char* amountThreads = getenv("AMOUNT_THREADS");

    if (extension && pathFilesIn && pathFilesOut && amountThreads) {
        string preparar = "/app2 " + string(extension) + " " + string(pathFilesIn) + " " + string(pathFilesOut) + " " + string(amountThreads);
        int successPrepararArchivos = system(preparar.c_str());
        if (successPrepararArchivos == 0) {
            cout << "Proceso fue llamado correctamente" << endl;
        } else {
            cout << "No se pudo llamar al proceso" << endl;
        }
    } else {
        cout << "Error: Alguna variable de entorno no está definida." << endl;
    }
}

void crearIndiceInvertido() {
    ifstream file;
    file.open("Out/file.idx");
    if (!file) {
        file.close();
        
        const char* pathFilesOut = getenv("PATH_FILES_OUT");
        const char* invertedIndexFile = getenv("INVERTED_INDEX_FILE");

        if (pathFilesOut && invertedIndexFile) {
            string crearIndice = "Externos/app3 " + string(pathFilesOut) + " " + string(invertedIndexFile);
            int successIndice = system(crearIndice.c_str());
            if (successIndice != 0) {
                cout << "Hubo un error al crear el índice" << endl;
            }
        } else {
            cout << "Error: Alguna variable de entorno no está definida." << endl;
        }
    } else {
        cout << "El file.idx ya fue creado" << endl;
    }
}*/
