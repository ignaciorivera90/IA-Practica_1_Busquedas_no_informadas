#include "busqueda.h"

void Busqueda::print_sep(std::ofstream& out) {
  out << "------------------------------------------" << std::endl;
}



bool Busqueda::BFS(const int start, const int end, const std::string &out_file) {
  std::ofstream out(out_file);
  if (!out.is_open()) return false;

  if (start < 1 || start > grafoevaluado_.numnodos() || end < 1 || end > grafoevaluado_.numnodos()) {
    print_sep(out);
    out << "Parámetros de inicio/destino fuera de rango." << std::endl;
    print_sep(out);
    return true;
  }

  const int inicio = start - 1;
  const int final = end  - 1;

  // Cabecera
  print_sep(out);
  out << "Número de nodos del grafo: " << grafoevaluado_.numnodos() << std::endl;
  out << "Número de aristas del grafo: " << grafoevaluado_.EdgeCount() << std::endl;
  out << "Vértice origen: "  << start << std::endl;
  out << "Vértice destino: " << end  << std::endl;
  print_sep(out);

  // Caso trivial: origen == destino
  if (inicio == final) {
    out << "Iteración 1" << std::endl;
    out << "Nodos generados: " << start << std::endl;
    out << "Nodos inspeccionados: -" << std::endl;
    print_sep(out);
    out << "Camino: " << start << std::endl;
    print_sep(out);
    out << "Costo: 0.00" << std::endl;
    print_sep(out);
    return true;
  }

  


  return true;
}
