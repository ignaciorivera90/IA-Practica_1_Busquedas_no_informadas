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
// Archivo grafo.h: definición de la clase Grafo, encargada de representar
//                  el grafo mediante una lista de adyacencia.

#ifndef GRAFO_H
#define GRAFO_H

#include "nodo.h"
#include <vector>
#include <fstream>
#include <sstream>

/**
 * @brief Representa un grafo no dirigido con costes en sus aristas.
 *
 * La clase almacena los nodos del grafo y permite construirlo a partir
 * de un fichero de entrada con la matriz triangular superior de costes.
 */
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
  int numnodos() const { return numnodos_; }
  int EdgeCount() const;
  bool AdjacencyList(const std::string& out_path) const;

 private:
  /// Número total de nodos del grafo.
  int numnodos_{0};

  /// Lista de nodos que forman el grafo.
  std::vector<Nodo> nodos_;
};

#endif