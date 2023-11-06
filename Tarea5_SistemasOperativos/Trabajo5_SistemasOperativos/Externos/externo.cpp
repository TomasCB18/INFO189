#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <filesystem>
#include <unordered_map>
#include <algorithm>
#include <unistd.h>

using namespace std;
namespace fs = std::filesystem;

mutex mtx;//evito que hilos multiples accedan al mismo archivo
condition_variable cv;
queue<string> filesToProcess;
bool done = false;



int contarArchivos(const string& directorio, const string& ext) {
    int contador = 0;
    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            contador++;
        }
    }
    return contador;
}


// Función para procesar un archivo de texto y contar palabras
void processFile(int threadId, string outPath) {
    while (true) {
        string filePath;
        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [] { return !filesToProcess.empty() || done; });
            if (filesToProcess.empty() && done) {
                break;
            }
            filePath = filesToProcess.front();
            filesToProcess.pop();
        }

        ifstream inputFile(filePath);
        if (!inputFile) {
            cerr << "Error al abrir el archivo: " << filePath << endl;
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

        string fileName = filePath.substr(filePath.find_last_of('/') + 1);
        string path = outPath;
        string outputPath = path + "/" + fileName;
    

        ofstream outputFile(outputPath);
        if (!outputFile.is_open()) {//verifica si se encuentra la carpeta Output para crear los archivos de salida
            cerr << "No se pudo crear el archivo de salida." << endl;
            return;
        }

        for (const auto& entry : wordCount) {
            outputFile << entry.first << ";" << entry.second << endl;
        }
        outputFile.close();

        mtx.lock();
        cout << "proceso pid =  " <<getpid()<<"- archivo procesado " <<filePath << ", procesado por el thread " << threadId << endl;
        mtx.unlock();         
    }
}

// Función para procesar archivos en paralelo
void processFilesInParallel(string extension, string inFiles, string outFiles, string amountThreads) {
    vector<thread> threads;
    int hilo = stoi(amountThreads);

    for (int i = 0; i < hilo ; i++) {
        threads.emplace_back(processFile, i , outFiles);
    }

    for (const auto& entry : fs::directory_iterator(inFiles)) {
        string temp = extension;
        string filename = entry.path().filename().string();
        if ((entry.is_regular_file()) && (filename.rfind("file",0) == 0) && (entry.path().extension() == "." + temp)) {//si el archivo es de extension txt, se agrega a la cola filesToProcess para ser leida por algun hilo que termine de procesar un archivo txt del input
            string filePath = entry.path().string();
            {
                lock_guard<mutex> lock(mtx);
                filesToProcess.push(filePath);
            }
            cv.notify_one();
        }
    }

    {
        lock_guard<mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();

    for (thread& t : threads) {
        t.join();
    }
}

int main(int argc, char** argv) {
    if(argc!=5){
        cout<<"el programa debe tener 5 argumentos";
        return EXIT_FAILURE;
    }
    string extension = argv[1];
    string inFiles = argv[2];
    string outFiles = argv[3];
    string amountThreads = argv[4];

    int cantidadMinimaArchivos = 20;
    int cantidadArchivos = contarArchivos(inFiles, extension);
    if (cantidadArchivos <= cantidadMinimaArchivos) {
        cerr << "Error: El número mínimo de archivos no se ha alcanzado (" << cantidadMinimaArchivos << " requeridos, " << cantidadArchivos << " encontrados)." << endl;
        return 1;
    }

    processFilesInParallel(extension, inFiles, outFiles, amountThreads);
    return 0;
}