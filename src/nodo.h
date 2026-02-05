#ifndef NODO_H
#define NODO_H

#include <vector>
#include <utility>
#include <iostream>

class Nodo {
 public:
  Nodo(int id) : id_(id) {}
  void AddChildren(int destino, double coste);
  int id() const { return id_; }
  const std::vector<std::pair<int, double>>& hijos() const { return hijos_; }
  double DistanceTo(int id_destino) const;
 private:
  int id_;
  std::vector<std::pair<int,double>> hijos_;
};


#endif