


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <iterator>


using namespace std;

typedef map<string, vector<pair<string, int>>> InvertedIndex;

bool loadInvertedIndex(const string& filename, InvertedIndex& index) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se puede abrir el archivo." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string word = line.substr(0, colonPos);
            string docInfo = line.substr(colonPos + 1);
            size_t startPos = 0;
            while (true) {
                size_t openParen = docInfo.find('(', startPos);
                size_t closeParen = docInfo.find(')', openParen);
                if (openParen == string::npos || closeParen == string::npos) {
                    break;
                }
                string docData = docInfo.substr(openParen + 1, closeParen - openParen - 1);
                size_t semicolonPos = docData.find(';');
                if (semicolonPos != string::npos) {
                    string filename = docData.substr(0, semicolonPos);
                    int frequency = stoi(docData.substr(semicolonPos + 1));
                    index[word].push_back(make_pair(filename, frequency));
                }
                startPos = closeParen + 1;
            }
        }
    }
    file.close();
    return true;
}

bool compareDocuments(const pair<string, int>& doc1, const pair<string, int>& doc2) {
    return doc1.second > doc2.second;
}

void searchAndPrintTopK(const InvertedIndex& index, int topK) {
    map<string, int> result;
    string query;
    cout << "Escriba texto a buscar: ";
    cin.ignore();
    getline(cin, query);

    auto start = chrono::high_resolution_clock::now();

    // Dividir la entrada en palabras individuales
    vector<string> queryWords;
    string currentWord;
    for (char c : query) {
        if (c == ' ') {
            if (!currentWord.empty()) {
                queryWords.push_back(currentWord);
                currentWord.clear();
            }
        } else {
            currentWord += c;
        }
    }
    if (!currentWord.empty()) {
        queryWords.push_back(currentWord);
    }

    // Realizar la búsqueda y llenar el mapa 'result'
    for (const string& word : queryWords) {
        if (index.find(word) != index.end()) {
            for (const auto& doc : index.at(word)) {
                result[doc.first] += doc.second;
            }
        }
    }

    // Crear un vector a partir del mapa para ordenar los resultados
    vector<pair<string, int>> sortedResult(result.begin(), result.end());
    sort(sortedResult.begin(), sortedResult.end(), compareDocuments);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Respuesta (tiempo = " << duration << "ns):" << endl;
    for (int i = 0; i < min(topK, static_cast<int>(sortedResult.size())); i++) {
        cout << i + 1 << ") " << sortedResult[i].first << ", " << sortedResult[i].second << endl;
    }

    char choice;
    cout << "Desea salir (S/N): ";
    cin >> choice;
    if (choice == 'S' || choice == 's') {
        exit(0);
    }
}





int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "El programa debe tener tres argumentos: <archivo_de_indice_invertido> <top_K>" << endl;
        return EXIT_FAILURE;
    }
    string indexPath = argv[1];
    int topK = atoi(argv[2]);
    if(topK<4){
        cerr<<"topK deber ser mayor a 4"<<endl;
        return 1;
    }

    InvertedIndex index;

    if (loadInvertedIndex(indexPath, index)) {
        while (true) {
            cout << "BUSCADOR BASADO EN INDICE INVERTIDO "<< getpid() << endl;
            cout << "Los top K documentos serán = " << topK << endl;
            searchAndPrintTopK(index, topK);
        }
    }

    return 0;
}





/*#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <algorithm>
#include <unistd.h>


using namespace std;


// Función para cargar la estructura desde el archivo de índice
map<string, map<string, int>> loadIndex(const string& indexPath) {
    map<string, map<string, int>> index;
    ifstream file(indexPath);
    
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de índice." << endl;
        exit(1);
    }
    
    string line;
    while (getline(file, line)) {
        size_t openBracket = line.find_first_of('(');
        size_t closeBracket = line.find_first_of(')');
        if (openBracket != string::npos && closeBracket != string::npos) {
            string word = line.substr(0, openBracket);
            string data = line.substr(openBracket + 1, closeBracket - openBracket - 1);
            size_t pos = 0;
            while (pos < data.length()) {
                size_t openParen = data.find('(', pos);
                size_t closeParen = data.find(')', pos);
                string docInfo = data.substr(openParen + 1, closeParen - openParen - 1);
                size_t semicolon = docInfo.find(';');
                string docName = docInfo.substr(0, semicolon);
                int count = stoi(docInfo.substr(semicolon + 1));
                index[word][docName] = count;
                pos = closeParen + 1;
            }
        }
    }
    file.close();
    return index;
}

// Función para buscar palabras en la estructura cargada
vector<pair<string, int>> searchWords(const map<string, map<string, int>>& index, const vector<string>& words) {
    map<string, int> commonDocs;
    for (const string& word : words) {
        if (index.find(word) != index.end()) {
            for (const auto& doc : index.at(word)) {
                commonDocs[doc.first] += doc.second;
            }
        }
    }

    vector<pair<string, int>> result(commonDocs.begin(), commonDocs.end());
    sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return result;
}



int main(int argc, char** argv){
    if (argc != 3) {
        cout <<"EL programa debe tener tres argumentos"<<endl;
        return EXIT_FAILURE;
    }
    string indexPath = argv[1];
    int topK = atoi(argv[2]);
    cout << "BUSCADOR BASADO EN INDICE INVERTIDO" << getpid()<< endl;
    cout << "Los top K documentos serán = " << topK << endl;
    
    while (true) {
        string input;
        cout << "Escriba texto a buscar (separado por espacios): ";
        getline(cin, input);
        
        vector<string> words;
        size_t pos = 0;
        while ((pos = input.find(' ')) != string::npos) {
            words.push_back(input.substr(0, pos));
            input.erase(0, pos + 1);
        }
        words.push_back(input);
        
        auto start = chrono::high_resolution_clock::now();
        vector<pair<string, int>> results = searchWords(loadIndex(indexPath), words);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

        cout << "Respuesta (tiempo = " << duration.count() << "ms):" << endl;
        for (int i = 0; i < topK && i < results.size(); ++i) {
            cout << i + 1 << ") " << results[i].first << ", " << results[i].second << endl;
        }

        cout << "Desea salir (S/N): ";
        string choice;
        getline(cin, choice);
        if (choice == "S" || choice == "s") {
            break;
        }
    }

    return EXIT_SUCCESS;
}*/

/*void searchAndPrintTopK(const InvertedIndex& index, int topK) {
    vector<pair<string, int>> result;
    string query;
    cout << "Escriba texto a buscar: ";
    cin.ignore();
    getline(cin, query);

    auto start = chrono::high_resolution_clock::now();
    // Realizar la búsqueda y llenar el vector 'result'
    for (const auto& word : index) {
        if (query.find(word.first) != string::npos) {
            for (const auto& doc : word.second) {
                bool found = false;
                for (auto& r : result) {
                    if (r.first == doc.first) {
                        r.second += doc.second;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    result.push_back(doc);
                }
            }
        }
    }

    // Ordenar los resultados
    sort(result.begin(), result.end(), compareDocuments);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Respuesta (tiempo = " << duration << "ms):" << endl;
    for (int i = 0; i < min(topK, static_cast<int>(result.size())); i++) {
        cout << i + 1 << ") " << result[i].first << ", " << result[i].second << endl;
    }

    char choice;
    cout << "Desea salir (S/N): ";
    cin >> choice;
    if (choice == 'S' || choice == 's') {
        exit(0);
    }
}*//*void searchAndPrintTopK(const InvertedIndex& index, int topK) {
    vector<pair<string, int>> result;
    string query;
    cout << "Escriba texto a buscar: ";
    cin.ignore();
    getline(cin, query);

    auto start = chrono::high_resolution_clock::now();
    // Realizar la búsqueda y llenar el vector 'result'
    for (const auto& word : index) {
        if (query.find(word.first) != string::npos) {
            for (const auto& doc : word.second) {
                bool found = false;
                for (auto& r : result) {
                    if (r.first == doc.first) {
                        r.second += doc.second;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    result.push_back(doc);
                }
            }
        }
    }

    // Ordenar los resultados
    sort(result.begin(), result.end(), compareDocuments);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Respuesta (tiempo = " << duration << "ms):" << endl;
    for (int i = 0; i < min(topK, static_cast<int>(result.size())); i++) {
        cout << i + 1 << ") " << result[i].first << ", " << result[i].second << endl;
    }

    char choice;
    cout << "Desea salir (S/N): ";
    cin >> choice;
    if (choice == 'S' || choice == 's') {
        exit(0);
    }
}*/