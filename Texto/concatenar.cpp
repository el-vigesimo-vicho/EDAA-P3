#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

void concatenarArchivos(const std::vector<std::string>& nombresArchivos, const std::string& archivoConcatenado) {
    std::ofstream archivoSalida(archivoConcatenado, std::ios::out | std::ios::binary);

    if (!archivoSalida.is_open()) {
        std::cerr << "No se pudo abrir el archivo de salida." << std::endl;
        return;
    }

    for (size_t i = 0; i < nombresArchivos.size(); ++i) {
        std::ifstream archivoEntrada(nombresArchivos[i]);

        if (!archivoEntrada.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << nombresArchivos[i] << std::endl;
            continue;
        }

        archivoSalida << archivoEntrada.rdbuf(); // Escribir contenido del archivo en el archivo concatenado

        if (i != nombresArchivos.size() - 1) {
            archivoSalida << "$"; // Agregar el separador solo si no es el último archivo
        }

        archivoEntrada.close();
    }

    archivoSalida.close();
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " archivoConcatenado archivo1 archivo2 archivo3..." << std::endl;
        return 1;
    }

    std::string archivoConcatenado = argv[1];
    std::vector<std::string> nombresArchivos;

    for (int i = 2; i < argc; ++i) {
        nombresArchivos.push_back(argv[i]);
    }

    concatenarArchivos(nombresArchivos, archivoConcatenado);

    std::cout << "Archivos concatenados exitosamente en " << archivoConcatenado << std::endl;

    return 0;
}
