#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream archivo("texto/concatenacion.txt");

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    std::string contenido;

    // Leer el contenido del archivo línea por línea
    std::string linea;
    while (std::getline(archivo, linea)) {
        contenido += linea + "\n"; // Agregar cada línea al contenido
    }

    archivo.close();

    // Mostrar el contenido del archivo
    std::cout << "Contenido del archivo concatenacion.txt:" << std::endl;
    std::cout << contenido << std::endl;

    return 0;
}
