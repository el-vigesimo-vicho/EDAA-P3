#include <iostream>
#include <cstdlib>
#include <filesystem>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <parametro1> <parametro2> ..." << std::endl;
        return 1;
    }

    // Nombre del archivo binario a ejecutar
    std::string nombreBinario = "./Texto/gen.bin"; // Ruta relativa al ejecutable

    // Construir los parámetros a pasar al archivo binario
    std::string parametros;
    for (int i = 1; i < argc; ++i) {
        parametros += std::string(argv[i]) + " ";
    }

    // Comando para ejecutar el binario con los parámetros
    std::string comando = nombreBinario + " " + parametros;

    // Ejecutar el comando con system()
    int resultado = system(comando.c_str());

    if (resultado == 0) {
        std::cout << "El programa binario se ejecutó correctamente." << std::endl;
    } else {
        std::cout << "Hubo un error al ejecutar el programa binario." << std::endl;
    }

    return 0;
}
