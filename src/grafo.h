#ifndef GRAFO_H
#define GRAFO_H

#include "nodo.h"
#include <vector>
#include <fstream>
#include <sstream>

class Grafo {
 public:
  Grafo() = default;
  Grafo(const std::string& grafo_info, int& error_flag);
  ~Grafo();
  void Build(const std::string& grafo_info, int& error_flag);
  void Destroy();
  void Update(const std::string& grafo_info, int& error_flag);
  void AddCost(int node1, int node2, double coste);
  const Nodo& nodos(int id_nodo) const { return nodos_[id_nodo]; }
  const int numnodos() const { return numnodos_; }
  const int EdgeCount() const;
  bool AdjacencyList(const std::string& out_path) const;
 private:
  int numnodos_{0};
  std::vector<Nodo> nodos_;
};

#endif