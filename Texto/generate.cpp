#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

void concatenarArchivos(const vector<string>& nombresArchivos) {
    ofstream archivoFinal("Texto/final.txt");

    if (!archivoFinal.is_open()) {
        cerr << "No se pudo abrir el archivo final.txt" << endl;
        return;
    }

    for (size_t i = 0; i < nombresArchivos.size(); ++i) {
        ifstream archivoActual(nombresArchivos[i]);

        if (!archivoActual.is_open()) {
            cerr << "No se pudo abrir el archivo: " << nombresArchivos[i] << endl;
            archivoFinal.close();
            return;
        }

        string contenidoArchivo((istreambuf_iterator<char>(archivoActual)), (istreambuf_iterator<char>()));
        archivoActual.close();

        // Eliminar el salto de línea al inicio del archivo si existe
        if (!contenidoArchivo.empty() && contenidoArchivo[0] == '\n') {
            contenidoArchivo = contenidoArchivo.substr(1);
        }

        // Eliminar el salto de línea al final del archivo si existe
        if (!contenidoArchivo.empty() && contenidoArchivo[contenidoArchivo.size() - 1] == '\n') {
            contenidoArchivo.pop_back();
        }

        archivoFinal << contenidoArchivo; // Concatenar contenido del archivo actual al final.txt

        if (i != nombresArchivos.size() - 1) {
            archivoFinal << "$"; // Insertar el símbolo "$" entre documentos (excepto en el último)
        }
    }

    archivoFinal.close();
    cout << "Archivos concatenados exitosamente en final.txt" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <cantidadArchivos> <longitudDeseada> <patronAInsertar>" << endl;
        return 1;
    }

    int cantidadArchivos = atoi(argv[1]);
    int longitudDeseada = atoi(argv[2]);
    string patronAInsertar = argv[3];

    srand(static_cast<unsigned>(time(0)));
    fs::create_directory("Texto");

    vector<string> nombresArchivos; // Vector para almacenar los nombres de los archivos creados

    for (int archivoNumero = 1; archivoNumero <= cantidadArchivos; ++archivoNumero) {
        string nombreArchivo = "Texto/D" + to_string(archivoNumero) + ".txt";
        nombresArchivos.push_back(nombreArchivo); // Agregar el nombre del archivo al vector

        ofstream archivo(nombreArchivo);

        if (!archivo) {
            cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
            return 1;
        }

        int caracteresEscritos = 0;
        vector<int> posicionesInsercion;

        while (caracteresEscritos < longitudDeseada) {
            int longitudLinea = rand() % 101 + 100; // Entre 100 y 200 caracteres
            if (longitudDeseada - caracteresEscritos < 100) {
                longitudLinea = longitudDeseada - caracteresEscritos;
            }

            for (int i = 0; i < longitudLinea; ++i) {
                char caracter;
                int tipoCaracter = rand() % 3; // 0: Mayúscula, 1: Minúscula, 2: Número
                if (tipoCaracter == 0) {
                    caracter = 'A' + rand() % 26; // Mayúscula
                } else if (tipoCaracter == 1) {
                    caracter = 'a' + rand() % 26; // Minúscula
                } else {
                    caracter = '0' + rand() % 10; // Número
                }

                archivo << caracter;

                if (caracteresEscritos < longitudDeseada - patronAInsertar.size() && rand() % 100 < 5) {
                    posicionesInsercion.push_back(caracteresEscritos); // Almacenar la posición de inserción aleatoria
                }

                ++caracteresEscritos;
            }
        }

        archivo.close();

        ifstream archivoEntrada(nombreArchivo);

        if (!archivoEntrada) {
            cerr << "No se pudo abrir el archivo de entrada: " << nombreArchivo << endl;
            return 1;
        }

        string contenidoArchivo((istreambuf_iterator<char>(archivoEntrada)), (istreambuf_iterator<char>()));
        archivoEntrada.close();

        int totalCaracteres = contenidoArchivo.size();

        int repeticiones = rand() % 5; // Generar aleatoriamente la cantidad de repeticiones (hasta 4 repeticiones)

        for (int i = 0; i < repeticiones; ++i) {
            if (!posicionesInsercion.empty()) {
                int insertarPatron = rand() % 2; // Decidir aleatoriamente si se inserta el patrón o no
                if (insertarPatron == 1) {
                    int posicionInsercion = rand() % posicionesInsercion.size(); // Seleccionar una posición aleatoria
                    contenidoArchivo.insert(posicionesInsercion[posicionInsercion], patronAInsertar);
                }
            }
        }

        ofstream archivoSalida(nombreArchivo);

        if (!archivoSalida) {
            cerr << "No se pudo abrir el archivo de salida: " << nombreArchivo << endl;
            return 1;
        }

        archivoSalida << contenidoArchivo;
        archivoSalida.close();

        cout << "El archivo " << nombreArchivo << " se ha modificado exitosamente." << endl;
    }
    concatenarArchivos(nombresArchivos);
    return 0;
}
