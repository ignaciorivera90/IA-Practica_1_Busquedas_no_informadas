// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 2025-2026
// Práctica 1: Búsquedas no informadas
//
// Autor: Ignacio Andrés Rivera Barrientos
// Correo: alu0101675053@ull.edu.es
// Fecha: XX/XX/2026
// Archivo main.cc: programa principal de la práctica. Gestiona los argumentos
//                  de entrada, carga el grafo y permite ejecutar BFS y DFS.

#include "funciones.h"
#include "grafo.h"
#include "busqueda.h"

/**
 * @brief Punto de entrada principal del programa.
 *
 * El programa recibe por línea de comandos un fichero de entrada con la
 * descripción del grafo y un fichero de salida donde se guardarán los
 * resultados. Después muestra un menú interactivo para consultar el grafo
 * o ejecutar las búsquedas no informadas.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Vector con los argumentos de línea de comandos.
 * @return Código de finalización del programa.
 */
int main(int argc, char *argv[]) {
  // Si el usuario solicita ayuda, se muestra la guía de uso.
  if (argc == 2 && std::string(argv[1]) == "--help") {
    help();
    exit(0);
  }

  // El programa necesita exactamente dos argumentos:
  // fichero de entrada y fichero de salida.
  if (argc != 3) {
    help();
    exit(1);
  }

  int option;
  std::string in_file = std::string(argv[1]);
  const std::string out_file = std::string(argv[2]);

  // Validación inicial del fichero de entrada.
  int in_status = classify_path_code(in_file);
  if (in_status != 1) {
    std::cout << "El archivo de entrada " << classify_path_str(in_status) << std::endl;
    pressanykey();
    clrscr();
    return 2;
  }

  // Validación inicial del fichero de salida.
  int out_status = classify_path_code(out_file);
  if (out_status != 1) {
    std::cout << "El archivo de salida " << classify_path_str(out_status) << std::endl;
    pressanykey();
    clrscr();
    return 2;
  }

  // Construcción inicial del grafo a partir del fichero recibido.
  int build_err{0};
  Grafo grafo_evaluado{in_file, build_err};

  // Si ocurre algún error durante la construcción, se finaliza el programa.
  if (!HandleGraphBuildError(build_err, in_file)) {
    return 1;
  }

  // Objeto encargado de ejecutar las búsquedas sobre el grafo cargado.
  Busqueda busqueda_prueba{grafo_evaluado};

  // Bucle principal del menú interactivo.
  while (true) {
    clrscr();
    menu(option);
    switch (option) {
      case 1:
        clrscr();
        std::cout << "Introducir la ruta completa del archivo " << "(ejemplo: ../docs/Grafo1.txt)" << std::endl;
        std::cin >> in_file;

        // Se intenta actualizar el grafo con el nuevo fichero.
        grafo_evaluado.Update(in_file, build_err);

        if (!HandleGraphBuildError(build_err, in_file)) {
          std::cout << "Error al abrir el archivo: verifique la ruta " << "y la extensión" << std::endl;
        } else {
          // Solo si la carga fue correcta se actualiza el grafo
          // utilizado por los algoritmos de búsqueda.
          busqueda_prueba.ChangeGrafo(grafo_evaluado);
          std::cout << "Archivo cargado con éxito desde "
                    << in_file << std::endl;
        }
        pressanykey();
        clrscr();
        break;

      case 2: 
        clrscr();
        // Se escribe la lista de adyacencia del grafo en el fichero de salida.
        if (!grafo_evaluado.AdjacencyList(out_file)) {
          break;
        }
        std::cout << "Abra el archivo " << out_file << " para ver el resultado" << std::endl;
        pressanykey();
        clrscr();
        break;
      
      case 3:
        clrscr();
        int inicio_bfs;
        int final_bfs;
        std::cout << "Ingrese el nodo de inicio: ";
        std::cin >> inicio_bfs;
        std::cout << std::endl;

        std::cout << "Ingrese el nodo final: ";
        std::cin >> final_bfs;
        std::cout << std::endl;

        // Ejecución de la búsqueda en amplitud.
        if (!busqueda_prueba.BFS(inicio_bfs, final_bfs, out_file)) {
          std::cerr << "Error: No se pudo realizar la búsqueda en amplitud" << std::endl;
        } else {
          std::cout << "Revise el resultado en " << out_file << std::endl;
        }
        pressanykey();
        clrscr();
        break;

      case 4:
        clrscr();
        int inicio_dfs;
        int final_dfs;
        std::cout << "Ingrese el nodo de inicio: ";
        std::cin >> inicio_dfs;
        std::cout << std::endl;

        std::cout << "Ingrese el nodo final: ";
        std::cin >> final_dfs;
        std::cout << std::endl;

        // Ejecución de la búsqueda en profundidad.
        if (!busqueda_prueba.DFS(inicio_dfs, final_dfs, out_file)) {
          std::cerr << "Error: No se pudo realizar la búsqueda en profundidad" << std::endl;
        } else {
          std::cout << "Revise el resultado en " << out_file << std::endl;
        }
        pressanykey();
        clrscr();
        break;

      case 5:
        clrscr();
        return 0;

      default:
        // En caso de introducir una opción no válida, se vuelve al menú.
        std::cout << "Opción no válida." << std::endl;
        pressanykey();
        clrscr();
        break;
        
    }
  }

  return 0;
}