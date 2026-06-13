#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <vector>
#include <fstream>

#include "grafo.h"

class Busqueda {
 public:
  Busqueda(const Grafo& grafo) : grafoevaluado_(grafo) {}

  void ChangeGrafo(const Grafo& cambio) { grafoevaluado_ = cambio; }

  bool BFS(const int start, const int end, const std::string& out_file);
  bool DFS(const int start, const int end, const std::string& out_file);

 private:
  Grafo grafoevaluado_;

  void print_sep(std::ofstream& out);
  void print_vec_enteros(std::ofstream& out, const std::vector<int>& v);
  double coste_camino(const Grafo& g, const std::vector<int>& path1);
};

#endif