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
// Archivo busqueda.h: definición de la clase Busqueda, encargada de ejecutar
//                     los algoritmos BFS y DFS sobre un grafo.

#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <vector>
#include <fstream>

#include "grafo.h"

// Modos de selección preparados para posibles modificaciones de la práctica.
enum class SelectionMode {
  NORMAL,
  LOWEST_COST,
  HIGHEST_COST,
  EVEN_NODES,
  ODD_NODES,
  PRIME_NODES,
  MULTIPLE_OF_N
};

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

  // Funciones auxiliares para posibles modificaciones de la corrección.
  bool es_primo(int value) const;
  std::vector<std::pair<int,double>> filtrar_candidatos(std::vector<std::pair<int,double>> candidates, SelectionMode mode, int n, int multiple_value = 1) const;
  int elegir_aleatorio(const std::vector<std::pair<int,double>>& candidates) const;
  int elegir_mejor(const std::vector<std::pair<int,double>>& candidates) const;
  void ordenar_por_menor_coste(std::vector<std::pair<int,double>>& candidates) const;
  void ordenar_por_mayor_coste(std::vector<std::pair<int,double>>& candidates) const;
};

#endif