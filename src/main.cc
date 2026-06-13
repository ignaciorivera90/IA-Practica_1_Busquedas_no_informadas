#include "funciones.h"
#include "grafo.h"
#include "busqueda.h"

int main(int argc, char *argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    help();
    exit(0);
  }

  if (argc != 3) {
    help();
    exit(1);
  }

  int option;
  std::string in_file = std::string(argv[1]);
  const std::string out_file = std::string(argv[2]);

  int in_status  = classify_path_code(in_file);
  if (in_status  != 1) {
    std::cout << "El archivo de entrada " << classify_path_str(in_status ) << std::endl;
    pressanykey();
    clrscr();
    return 2;
  }
  int out_status = classify_path_code(out_file);
  if (out_status != 1) {
    std::cout << "El archivo de salida " << classify_path_str(out_status) << std::endl;
    pressanykey();
    clrscr();
    return 2;
  }

  int build_err{0};
  Grafo grafo_evaluado{in_file, build_err};
  if (!HandleGraphBuildError(build_err, in_file)) {
    return 1; 
  }

  Busqueda busqueda_prueba{grafo_evaluado};

  while (true) {
    clrscr();
    menu(option);
    switch (option) {
      case 1 :
        clrscr();
        std::cout << "Introducir la ruta completa del archivo (ejemplo: docs/Grafo1.txt)" << std::endl;
        std::cin >> in_file;
        grafo_evaluado.Update(in_file, build_err);

        if (!HandleGraphBuildError(build_err, in_file)) {
          std::cout << "Error a abrir el archivo: verifique la ruta y la extensión" << std::endl;
        } else {
          busqueda_prueba.ChangeGrafo(grafo_evaluado);
          std::cout << "Archivo cargado con éxito desde " << in_file << std::endl;
        }
        pressanykey();
        clrscr();
        break;
      case 2:
        clrscr();
        if (!grafo_evaluado.AdjacencyList(out_file)) {
          break;
        }
        std::cout << "Abra el archivo " << out_file << " para ver el resultado" << std::endl;
        pressanykey();
        clrscr();
        break;
      case 3:
        clrscr();
        std::cout << "Ingrese el nodo de inicio: ";
        int inicio_bfs;
        std::cin >> inicio_bfs;
        std::cout << std::endl;
        std::cout << "Ingrese el nodo final: ";
        int final_bfs;
        std::cin >> final_bfs;
        std::cout << std::endl;
        //busqueda
        if (!busqueda_prueba.BFS(inicio_bfs, final_bfs, out_file)) {
          std::cerr << "Error: No se pudo realizar la busqueda en amplitud" << std::endl;
        } else {
          std::cout << "Revise el resultado en " << out_file << std::endl;
        }

        pressanykey();
        clrscr();
        break;
      case 4:
        clrscr();
        std::cout << "Ingrese el nodo de inicio: ";
        int inicio_dfs;
        std::cin >> inicio_dfs;
        std::cout << std::endl;
        std::cout << "Ingrese el nodo final: ";
        int final_dfs;
        std::cin >> final_dfs;
        std::cout << std::endl;

        if (!busqueda_prueba.DFS(inicio_dfs, final_dfs, out_file)) {
          std::cerr << "Error: No se pudo realizar la busqueda en profundidad" << std::endl;
        } else {
          std::cout << "Revise el resultado en " << out_file << std::endl;
        }

        pressanykey();
        clrscr();
        break;
      case 5:
        clrscr();
        return 0;
        break;
    }
  }
  return 0;
}
