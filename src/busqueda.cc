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
// Archivo busqueda.cc: implementación de los algoritmos de búsqueda
//                      en amplitud (BFS) y profundidad (DFS).

#include <queue>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <random>
#include <vector>


#include "busqueda.h"

/**
 * @brief Imprime una línea separadora en el fichero de salida.
 * @param out Flujo de salida utilizado.
 */
void Busqueda::print_sep(std::ofstream& out) {
  out << "------------------------------------------" << std::endl;
}



/**
 * @brief Imprime un vector de nodos en formato legible.
 * @param out Flujo de salida utilizado.
 * @param v Vector de nodos a imprimir.
 */
void Busqueda::print_vec_enteros(std::ofstream& out, const std::vector<int>& v) {
  if (v.empty()) {
    out << "-";
    return;
  }

  for (size_t i = 0; i < v.size(); ++i) {
    out << v[i] + 1;
    if (i + 1 < v.size()) out << ", ";
  }
}



/**
 * @brief Calcula el coste total de un camino.
 * @param g Grafo utilizado.
 * @param path Camino encontrado.
 * @return Coste total acumulado del camino.
 */
double Busqueda::coste_camino(const Grafo& g, const std::vector<int>& path) {
  double cost = 0.0;

  // Se suman los costes de las aristas consecutivas del camino.
  for (size_t i = 0; i + 1 < path.size(); ++i) {
    cost += g.nodos(path[i]).DistanceTo(path[i + 1]);
  }

  return cost;
}



/**
 * @brief Ejecuta una búsqueda en amplitud BFS.
 * @param start Nodo origen indicado por el usuario.
 * @param end Nodo destino indicado por el usuario.
 * @param out_file Fichero donde se almacena la salida.
 * @return true si la ejecución finaliza correctamente.
 */
bool Busqueda::BFS(const int start, const int end, const std::string& out_file) {
  std::ofstream out(out_file);
  if (!out.is_open()) return false;

  // Se comprueba que los nodos introducidos estén dentro del rango del grafo.
  if (start < 1 || start > grafoevaluado_.numnodos() ||
      end < 1 || end > grafoevaluado_.numnodos()) {
    print_sep(out);
    out << "Parámetros de inicio/destino fuera de rango.\n";
    print_sep(out);
    return true;
  }

  const int inicio = start - 1;
  const int final = end - 1;

  print_sep(out);
  out << "Búsqueda en amplitud (BFS)\n";
  out << "Número de nodos del grafo: " << grafoevaluado_.numnodos() << "\n";
  out << "Número de aristas del grafo: " << grafoevaluado_.EdgeCount() << "\n";
  out << "Vértice origen: " << start << "\n";
  out << "Vértice destino: " << end << "\n";
  print_sep(out);

  // Estructuras principales de BFS.
  std::queue<int> cola;
  std::vector<bool> visited(grafoevaluado_.numnodos(), false);
  std::vector<int> parent(grafoevaluado_.numnodos(), -1);

  std::vector<int> generated_nodes;
  std::vector<int> inspected_nodes;

  // Se inicializa la búsqueda con el nodo origen.
  cola.push(inicio);
  visited[inicio] = true;
  generated_nodes.push_back(inicio);

  int iteration = 1;
  bool found = false;

  out << "Iteración " << iteration++ << "\n";
  out << "Nodos generados: ";
  print_vec_enteros(out, generated_nodes);
  out << "\nNodos inspeccionados: -\n";
  print_sep(out);

  // Bucle principal de la búsqueda en amplitud.
  while (!cola.empty() && !found) {
    int current = cola.front();
    cola.pop();

    inspected_nodes.push_back(current);

    if (current == final) {
      found = true;
    } else {
      // Parámetros preparados para posibles modificaciones de la práctica.
      // En modo NORMAL el comportamiento coincide con BFS estándar.
      SelectionMode mode = SelectionMode::NORMAL;
      int k = 5;
      int multiple_value = 3;
      std::vector<std::pair<int, double>> candidates;

      // Se guardan como candidatos los sucesores no visitados.
      for (const auto& child : grafoevaluado_.nodos(current).hijos()) {
        int vecino = child.first;

        if (!visited[vecino]) {
          candidates.push_back(child);
        }
      }

      // Se aplica el criterio de selección configurado.
      auto filtered = filtrar_candidatos(candidates, mode, k, multiple_value);

      // En modo NORMAL se generan todos los sucesores.
      // En los demás modos se selecciona uno aleatoriamente.
      if (mode == SelectionMode::NORMAL) {
        for (const auto& child : filtered) {
          int vecino = child.first;

          visited[vecino] = true;
          parent[vecino] = current;
          cola.push(vecino);
          generated_nodes.push_back(vecino);

          if (vecino == final) {
            found = true;
          }
        }
      } else {
        int elegido = elegir_aleatorio(filtered);
        //int elegido = elegir_mejor(filtered);

        if (elegido != -1) {
          visited[elegido] = true;
          parent[elegido] = current;
          cola.push(elegido);
          generated_nodes.push_back(elegido);

          if (elegido == final) {
            found = true;
          }
        }
      }
    }

    out << "Iteración " << iteration++ << "\n";
    out << "Nodos generados: ";
    print_vec_enteros(out, generated_nodes);
    out << "\nNodos inspeccionados: ";
    print_vec_enteros(out, inspected_nodes);
    out << "\n";
    print_sep(out);
  }

  if (!visited[final]) {
    out << "No existe camino entre " << start << " y " << end << ".\n";
    print_sep(out);
    return true;
  }

  // Se reconstruye el camino desde el destino hasta el origen usando parent.
  std::vector<int> path;
  for (int v = final; v != -1; v = parent[v]) {
    path.push_back(v);
  }

  std::reverse(path.begin(), path.end());

  out << "Camino: ";
  for (size_t i = 0; i < path.size(); ++i) {
    out << path[i] + 1;
    if (i + 1 < path.size()) out << " - ";
  }
  out << "\n";

  const double cost = coste_camino(grafoevaluado_, path);

  out << std::fixed << std::setprecision(2);
  out << "Costo: " << cost << "\n";
  print_sep(out);

  return true;
}


/**
 * @brief Ejecuta una búsqueda en profundidad DFS.
 * @param start Nodo origen indicado por el usuario.
 * @param end Nodo destino indicado por el usuario.
 * @param out_file Fichero donde se almacena la salida.
 * @return true si la ejecución finaliza correctamente.
 */
bool Busqueda::DFS(const int start, const int end, const std::string& out_file) {
  std::ofstream out(out_file);
  if (!out.is_open()) return false;

  // Se comprueba que los nodos introducidos estén dentro del rango del grafo.
  if (start < 1 || start > grafoevaluado_.numnodos() ||
      end < 1 || end > grafoevaluado_.numnodos()) {
    print_sep(out);
    out << "Parámetros de inicio/destino fuera de rango.\n";
    print_sep(out);
    return true;
  }

  const int inicio = start - 1;
  const int final = end - 1;

  print_sep(out);
  out << "Búsqueda en profundidad (DFS)\n";
  out << "Número de nodos del grafo: " << grafoevaluado_.numnodos() << "\n";
  out << "Número de aristas del grafo: " << grafoevaluado_.EdgeCount() << "\n";
  out << "Vértice origen: " << start << "\n";
  out << "Vértice destino: " << end << "\n";
  print_sep(out);

  // Estructuras principales de DFS.
  std::stack<int> pila;
  std::vector<bool> visited(grafoevaluado_.numnodos(), false);
  std::vector<int> parent(grafoevaluado_.numnodos(), -1);

  std::vector<int> generated_nodes;
  std::vector<int> inspected_nodes;

  // Se inicializa la búsqueda con el nodo origen.
  pila.push(inicio);
  visited[inicio] = true;
  generated_nodes.push_back(inicio);

  int iteration = 1;
  bool found = false;

  out << "Iteración " << iteration++ << "\n";
  out << "Nodos generados: ";
  print_vec_enteros(out, generated_nodes);
  out << "\nNodos inspeccionados: -\n";
  print_sep(out);

  // Bucle principal de la búsqueda en profundidad.
  while (!pila.empty() && !found) {
    int current = pila.top();
    pila.pop();

    inspected_nodes.push_back(current);

    if (current == final) {
      found = true;
    } else {
      // Parámetros preparados para posibles modificaciones de la práctica.
      // En modo NORMAL el comportamiento coincide con DFS estándar.
      SelectionMode mode = SelectionMode::NORMAL;
      int k = 5;
      int multiple_value = 3;
      std::vector<std::pair<int, double>> candidates;

      // Se guardan como candidatos los sucesores no visitados.
      for (const auto& child : grafoevaluado_.nodos(current).hijos()) {
        int vecino = child.first;

        if (!visited[vecino]) {
          candidates.push_back(child);
        }
      }

      // Se invierte el orden para que la pila explore los vecinos
      // en el orden esperado.
      std::reverse(candidates.begin(), candidates.end());

      // Se aplica el criterio de selección configurado.
      auto filtered = filtrar_candidatos(candidates, mode, k, multiple_value);

      // En modo NORMAL se generan todos los sucesores.
      // En los demás modos se selecciona uno aleatoriamente.
      if (mode == SelectionMode::NORMAL) {
        for (const auto& child : filtered) {
          int vecino = child.first;

          visited[vecino] = true;
          parent[vecino] = current;
          pila.push(vecino);
          generated_nodes.push_back(vecino);

          if (vecino == final) {
            found = true;
          }
        }
      } else {
        int elegido = elegir_aleatorio(filtered);
        //int elegido = elegir_mejor(filtered);

        if (elegido != -1) {
          visited[elegido] = true;
          parent[elegido] = current;
          pila.push(elegido);
          generated_nodes.push_back(elegido);

          if (elegido == final) {
            found = true;
          }
        }
      }
    }

    out << "Iteración " << iteration++ << "\n";
    out << "Nodos generados: ";
    print_vec_enteros(out, generated_nodes);
    out << "\nNodos inspeccionados: ";
    print_vec_enteros(out, inspected_nodes);
    out << "\n";
    print_sep(out);
  }

  if (!visited[final]) {
    out << "No existe camino entre " << start << " y " << end << ".\n";
    print_sep(out);
    return true;
  }

  // Se reconstruye el camino desde el destino hasta el origen usando parent.
  std::vector<int> path;
  for (int v = final; v != -1; v = parent[v]) {
    path.push_back(v);
  }

  std::reverse(path.begin(), path.end());

  out << "Camino: ";
  for (size_t i = 0; i < path.size(); ++i) {
    out << path[i] + 1;
    if (i + 1 < path.size()) out << " - ";
  }
  out << "\n";

  const double cost = coste_camino(grafoevaluado_, path);

  out << std::fixed << std::setprecision(2);
  out << "Costo: " << cost << "\n";
  print_sep(out);

  return true;
}

// MODIFICACIONES PARA CORRECCIÓN

/**
 * @brief Comprueba si un número es primo.
 * @param value Número que se desea comprobar.
 * @return true si el número es primo.
 */
bool Busqueda::es_primo(int value) const {
  if (value < 2) return false;

  for (int i = 2; i * i <= value; ++i) {
    if (value % i == 0) return false;
  }

  return true;
}

/**
 * @brief Filtra un conjunto de candidatos según el modo seleccionado.
 * @param candidates Vector de candidatos.
 * @param mode Criterio de selección utilizado.
 * @param n Número máximo de candidatos que se conservan.
 * @param multiple_value Valor usado para el criterio de múltiplos.
 * @return Vector con los candidatos filtrados.
 */
std::vector<std::pair<int,double>>
Busqueda::filtrar_candidatos( std::vector<std::pair<int,double>> candidates, SelectionMode mode, int n, int multiple_value) const {
  std::vector<std::pair<int,double>> result;

  // Se aplica el criterio de filtrado indicado por mode.
  switch (mode) {
    case SelectionMode::NORMAL:
      result = candidates;
      break;

    case SelectionMode::LOWEST_COST:
      ordenar_por_menor_coste(candidates);
      result = candidates;
      break;

    case SelectionMode::HIGHEST_COST:
      ordenar_por_mayor_coste(candidates);
      result = candidates;
      break;

    case SelectionMode::EVEN_NODES:
      for (const auto& candidate : candidates) {
        if ((candidate.first + 1) % 2 == 0) {
          result.push_back(candidate);
        }
      }
      break;

    case SelectionMode::ODD_NODES:
      for (const auto& candidate : candidates) {
        if ((candidate.first + 1) % 2 != 0) {
          result.push_back(candidate);
        }
      }
      break;

    case SelectionMode::PRIME_NODES:
      for (const auto& candidate : candidates) {
        if (es_primo(candidate.first + 1)) {
          result.push_back(candidate);
        }
      }
      break;

    case SelectionMode::MULTIPLE_OF_N:
      for (const auto& candidate : candidates) {
        if (multiple_value != 0 &&
            (candidate.first + 1) % multiple_value == 0) {
          result.push_back(candidate);
        }
      }
      break;
  }

  // Si hay más candidatos que el límite indicado, se conservan solo los primeros.
  if (n > 0 && result.size() > static_cast<size_t>(n)) {
    result.resize(n);
  }
  return result;
}



/**
 * @brief Elige aleatoriamente un candidato de una lista.
 * @param candidates Vector de candidatos disponibles.
 * @return Identificador del nodo elegido, o -1 si no hay candidatos.
 */
int Busqueda::elegir_aleatorio(const std::vector<std::pair<int,double>>& candidates) const {
  if (candidates.empty()) {
    return -1;
  }

  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, candidates.size() - 1);
  return candidates[dist(gen)].first;
}



/**
 * @brief Selecciona el mejor candidato de una lista.
 * @param candidates Vector de candidatos previamente filtrados y ordenados.
 * @return Identificador del nodo seleccionado, o -1 si no hay candidatos.
 *
 * Esta función devuelve siempre el primer elemento del vector.
 * Puede utilizarse después de aplicar cualquier criterio de selección,
 * como menor coste, mayor coste, números primos, pares, impares o
 * múltiplos de un valor determinado.
 */
int Busqueda::elegir_mejor(
    const std::vector<std::pair<int,double>>& candidates) const {

  if (candidates.empty()) {
    return -1;
  }

  return candidates.front().first;
}



/**
 * @brief Ordena los candidatos por coste ascendente.
 * @param candidates Vector de candidatos a ordenar.
 *
 * Tras la ordenación, el primer elemento será el de menor coste.
 * Puede utilizarse directamente sobre los costes de las aristas o
 * adaptarse para ordenar utilizando el identificador de los nodos.
 */
void Busqueda::ordenar_por_menor_coste(std::vector<std::pair<int,double>>& candidates) const {
  std::sort( candidates.begin(), candidates.end(), [](const auto& a, const auto& b) { return a.second < b.second; });
}



/**
 * @brief Ordena los candidatos por coste descendente.
 * @param candidates Vector de candidatos a ordenar.
 *
 * Tras la ordenación, el primer elemento será el de mayor coste.
 * Puede utilizarse directamente sobre los costes de las aristas o
 * adaptarse para ordenar utilizando el identificador de los nodos.
 */
void Busqueda::ordenar_por_mayor_coste( std::vector<std::pair<int,double>>& candidates) const {
  std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
}