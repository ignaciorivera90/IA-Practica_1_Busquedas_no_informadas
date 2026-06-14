// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 2025-2026
// Práctica 1: Búsquedas no informadas
//
// Autor: Ignacio Andrés Rivera Barrientos
// Correo: alu0101675053@ull.edu.es
// Fecha: 10/06/2026
// Archivo funciones.cc: implementación de las funciones auxiliares
//                       utilizadas por el programa.

#include "funciones.h"

/**
 * @brief Muestra el menú principal del programa.
 * @param option Variable donde se almacena la opción seleccionada.
 */
void menu (int &option) {
  std::cout << "1. Cargar grafo" << std::endl;     
  std::cout << "2. Mostrar la lista de adyasencia " << std::endl;
  std::cout << "3. Ejecutar algoritmo de búsqueda en amplitud(BFS)" << std::endl;
  std::cout << "4. Ejecutar algoritmo de búsqueda en profundidad(DFS)" << std::endl;          
  std::cout << "5. Salir del programa" << std::endl;
  std::cout << "Introduce un numero > ";
  std::cin >> option;
};

/**
 * @brief Muestra la ayuda de uso del programa.
 */
void help () {
  std::cout << "Como usarlo: ./busquedas_no_informadas <input> <output>" << std::endl;     
  std::cout << "<input>: texto en formato .txt especificar un gráfico" << std::endl;
  std::cout << "<output> Archivo para almacenar resultados de búsqueda" << std::endl;
}

/**
 * @brief Comprueba si la opción introducida es válida.
 * @param option Opción seleccionada por el usuario.
 * @return true si la opción pertenece al menú.
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
 * @brief Pausa la ejecución hasta que el usuario pulse una tecla.
 */
void pressanykey() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  std::cin.get(); 
}

/**
 * @brief Limpia la pantalla de la consola.
 */
void clrscr() {
  system("clear");
}

/**
 * @brief Determina el tipo de una ruta del sistema de archivos.
 * @param path_str Ruta a analizar.
 * @return Tipo de ruta detectado.
 */
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

/**
 * @brief Convierte el tipo de una ruta en un código numérico.
 * @param path_str Ruta a analizar.
 * @return Código asociado al tipo de ruta.
 */
// Códigos:
// 0 = no existe
// 1 = archivo regular
// 2 = directorio
// 3 = enlace simbólico
// 4 = otro tipo
// 5 = error
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

/**
 * @brief Convierte un código de ruta en una descripción textual.
 * @param code Código de clasificación.
 * @return Descripción asociada al código.
 */
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

/**
 * @brief Devuelve una descripción textual para un código de error
 *        producido durante la construcción del grafo.
 * @param code Código de error.
 * @return Mensaje descriptivo del error.
 */
const char* GraphBuildErrorStr(int code) {
  switch (code) {
    case 0: return "OK";
    case 1: return "No se pudo abrir el archivo";
    case 2: return "Número de nodos inválido";
    case 3: return "Archivo incompleto o token no legible al leer pesos";
    // case 4: return "Token de peso inválido (no numérico)";
    default: return "Error desconocido";
  }
}

/**
 * @brief Gestiona los errores producidos durante la carga del grafo.
 * @param error_flag Código de error detectado.
 * @param path Ruta del fichero procesado.
 * @return true si no se produjo ningún error.
 */
bool HandleGraphBuildError(int error_flag, const std::string& path) {
  // Si no hay error se continúa normalmente.
  if (error_flag == 0) return true;

  std::cerr << "[Grafo] "
            << GraphBuildErrorStr(error_flag)
            << " en '" << path << "'. ";

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