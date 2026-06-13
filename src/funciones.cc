#include "funciones.h"

void menu (int &option) {
  std::cout << "1. Cargar grafo" << std::endl;     
  std::cout << "2. Mostrar la lista de adyasencia " << std::endl;
  std::cout << "3. Ejecutar algoritmo de búsqueda en amplitud(BFS)" << std::endl;
  std::cout << "4. Ejecutar algoritmo de búsqueda en profundidad(DFS)" << std::endl;          
  std::cout << "5. Salir del programa" << std::endl;
  std::cout << "Introduce un numero > ";
  std::cin >> option;
};

void help () {
  std::cout << "Como usarlo: ./busquedas_no_informadas <input> <output>" << std::endl;     
  std::cout << "<input>: texto en formato .txt especificar un gráfico" << std::endl;
  std::cout << "<output> Archivo para almacenar resultados de búsqueda" << std::endl;
}

/**
 * @brief Check that the opcode is correct
 */
bool CheckOption(const int &option) {
  std::vector<int> opciones = {1, 2, 3, 4, 5};
  for (const int& num : opciones) {
    if (option == num) {
      return true;
    }
  }
  std::cerr << "Error: A usado una opcion incorrecta" << std::endl;
  return false;
}

/**
 * @brief function that waits for the user to press any key
 */
void pressanykey() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  std::cin.get(); 
}

/**
 * @brief function to clear the standard ouput
 */
void clrscr() {
  system("clear");
}


PathType classify_path(const std::string& path_str) {
  std::error_code ec;
  std::filesystem::file_status st = std::filesystem::symlink_status(path_str, ec);
  if (ec) return PathType::Error;

  if (!std::filesystem::exists(st))         return PathType::NotFound;
  if (std::filesystem::is_regular_file(st)) return PathType::RegularFile;
  if (std::filesystem::is_directory(st))    return PathType::Directory;
  if (std::filesystem::is_symlink(st))      return PathType::Symlink;
  return PathType::Other;
}

//(códigos: 0=no existe, 1=archivo, 2=directorio, 3=symlink, 4=otro, 5=error)
int classify_path_code(const std::string& path_str) {
  std::error_code ec;
  std::filesystem::file_status st = std::filesystem::symlink_status(path_str, ec);
  if (ec) return 5;

  if (!std::filesystem::exists(st))         return 0;
  if (std::filesystem::is_regular_file(st)) return 1;
  if (std::filesystem::is_directory(st))    return 2;
  if (std::filesystem::is_symlink(st))      return 3;
  return 4;
}

std::string classify_path_str(int code) {
  switch (code) {
    case 0: return "no existe";
    case 1: return "es un archivo regular";
    case 2: return "es un directorio";
    case 3: return "es un enlace simbólico";
    case 4: return "es otro tipo";
    case 5: return "provoco un error";
    default: return "es desconocido";
  }
}

// Texto corto para cada código (útil si quieres reutilizarlo)
const char* GraphBuildErrorStr(int code) {
  switch (code) {
    case 0: return "OK";
    case 1: return "No se pudo abrir el archivo";
    case 2: return "Número de nodos inválido";
    case 3: return "Archivo incompleto o token no legible al leer pesos";
    // Si en el futuro usas 4 para "token inválido", descomenta:
    // case 4: return "Token de peso inválido (no numérico)";
    default: return "Error desconocido";
  }
}

// Maneja (imprime) el error y devuelve true si no hay error
bool HandleGraphBuildError(int error_flag, const std::string& path) {
  if (error_flag == 0) return true;

  std::cerr << "[Grafo] " << GraphBuildErrorStr(error_flag) << " en '" << path << "'. ";

  switch (error_flag) {
    case 1:
      std::cerr << "Verifica la ruta, permisos o que el archivo exista.";
      break;
    case 2:
      std::cerr << "La primera línea debe contener un entero > 0 (p. ej., 20).";
      break;
    case 3:
      std::cerr << "Faltan pesos: se esperaban n(n-1)/2 valores después de n o hubo un token ilegible durante la lectura.";
      break;
    // case 4:
    //   std::cerr << "Alguno de los pesos no es numérico (usa punto decimal).";
    //   break;
    default:
      std::cerr << "Revise el formato del archivo de entrada.";
      break;
  }

  std::cerr << std::endl;
  return false;
}