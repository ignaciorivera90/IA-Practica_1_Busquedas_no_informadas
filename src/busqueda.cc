#include <queue>
#include <algorithm>
#include <iomanip>
#include <stack>


#include "busqueda.h"

void Busqueda::print_sep(std::ofstream& out) {
  out << "------------------------------------------" << std::endl;
}



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



double Busqueda::coste_camino(const Grafo& g, const std::vector<int>& path) {
  double cost = 0.0;

  for (size_t i = 0; i + 1 < path.size(); ++i) {
    cost += g.nodos(path[i]).DistanceTo(path[i + 1]);
  }

  return cost;
}



bool Busqueda::BFS(const int start, const int end, const std::string& out_file) {
  std::ofstream out(out_file);
  if (!out.is_open()) return false;

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

  std::queue<int> cola;
  std::vector<bool> visited(grafoevaluado_.numnodos(), false);
  std::vector<int> parent(grafoevaluado_.numnodos(), -1);

  std::vector<int> generated_nodes;
  std::vector<int> inspected_nodes;

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

  while (!cola.empty() && !found) {
    int current = cola.front();
    cola.pop();

    inspected_nodes.push_back(current);

    if (current == final) {
      found = true;
    } else {
      for (const auto& child : grafoevaluado_.nodos(current).hijos()) {
        int vecino = child.first;

        if (!visited[vecino]) {
          visited[vecino] = true;
          parent[vecino] = current;
          cola.push(vecino);
          generated_nodes.push_back(vecino);

          if (vecino == final) {
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


bool Busqueda::DFS(const int start, const int end, const std::string& out_file) {
  std::ofstream out(out_file);
  if (!out.is_open()) return false;

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

  std::stack<int> pila;
  std::vector<bool> visited(grafoevaluado_.numnodos(), false);
  std::vector<int> parent(grafoevaluado_.numnodos(), -1);

  std::vector<int> generated_nodes;
  std::vector<int> inspected_nodes;

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

  while (!pila.empty() && !found) {
    int current = pila.top();
    pila.pop();

    inspected_nodes.push_back(current);

    if (current == final) {
      found = true;
    } else {
      std::vector<std::pair<int, double>> hijos;

      for (const auto& child : grafoevaluado_.nodos(current).hijos()) {
        hijos.push_back(child);
      }

      std::reverse(hijos.begin(), hijos.end());

      for (const auto& child : hijos) {
        int vecino = child.first;

        if (!visited[vecino]) {
          visited[vecino] = true;
          parent[vecino] = current;
          pila.push(vecino);
          generated_nodes.push_back(vecino);

          if (vecino == final) {
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