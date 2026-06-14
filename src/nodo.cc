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
// Archivo nodo.cc: implementación de la clase Nodo utilizada para
//                  representar los vértices del grafo.

#include "nodo.h"

/**
 * @brief Añade un nodo adyacente junto con el coste de la arista.
 * @param destino Identificador del nodo destino.
 * @param coste Coste asociado a la arista.
 */
void Nodo::AddChildren(int destino, double coste) {
  hijos_.emplace_back(destino, coste);
}

/**
 * @brief Obtiene la distancia hasta un nodo adyacente.
 * @param id_destino Identificador del nodo destino.
 * @return Coste de la arista que conecta ambos nodos.
 */
double Nodo::DistanceTo(int id_destino) const {
  // Se busca el nodo destino entre los hijos del nodo actual.
  for (const auto& [auxid, auxcoste] : hijos_) {
    if (auxid == id_destino) {
      return auxcoste;
    }
  }

  // Si no existe una conexión directa se informa del error.
  std::cerr << "El nodo " << id_
            << " no tiene al nodo "
            << id_destino
            << " como su hijo" << std::endl;

  return -1;
}