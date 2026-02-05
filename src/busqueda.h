#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include "grafo.h"

class Busqueda {
 public:
  Busqueda(const Grafo& grafo) : grafoevaluado_(grafo) {}

  void ChangeGrafo(const Grafo& cambio) { grafoevaluado_ = cambio; }

  bool BFS(const int start, const int end, const std::string& out_file);

 private:
  Grafo grafoevaluado_;

  void print_sep(std::ofstream& out);
  void print_vec_enteros(std::ofstream& out, const std::vector<int>& v);
  double coste_camino(const Grafo& g, const std::vector<int>& path1);
  std::vector<std::pair<int,double>> vecinos_ordenados(const Grafo& g, int u0);
};

#endif