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
// Archivo nodo.h: definición de la clase Nodo utilizada para representar
//                 los vértices del grafo y sus conexiones.

#ifndef NODO_H
#define NODO_H

#include <vector>
#include <utility>
#include <iostream>

/**
 * @brief Representa un vértice del grafo.
 *
 * Cada nodo almacena su identificador y una lista de nodos adyacentes
 * junto con el coste de la arista que los conecta.
 */
class Nodo {
 public:
  /**
   * @brief Constructor de la clase Nodo.
   * @param id Identificador del nodo.
   */
  Nodo(int id) : id_(id) {}

  /**
   * @brief Añade un nodo adyacente junto con el coste de la arista.
   * @param destino Identificador del nodo destino.
   * @param coste Coste asociado a la arista.
   */
  void AddChildren(int destino, double coste);

  /**
   * @brief Devuelve el identificador del nodo.
   * @return Identificador del nodo.
   */
  int id() const { return id_; }

  /**
   * @brief Devuelve la lista de nodos adyacentes.
   * @return Vector con los nodos hijos y sus costes.
   */
  const std::vector<std::pair<int, double>>& hijos() const { return hijos_; }

  /**
   * @brief Obtiene el coste de la arista hacia un nodo adyacente.
   * @param id_destino Identificador del nodo destino.
   * @return Coste de la arista.
   */
  double DistanceTo(int id_destino) const;

 private:
  /// Identificador único del nodo.
  int id_;

  /// Lista de nodos adyacentes y sus costes.
  std::vector<std::pair<int,double>> hijos_;
};

#endif