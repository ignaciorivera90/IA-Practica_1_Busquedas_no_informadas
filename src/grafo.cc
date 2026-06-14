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
// Archivo grafo.cc: implementación de la clase Grafo, encargada de leer,
//                   construir, actualizar y mostrar la estructura del grafo.

#include "grafo.h"
#include <sstream>
#include <algorithm>
#include <cmath>

/**
 * @brief Lee un valor numérico desde un flujo de entrada.
 * @param in Flujo desde el que se lee el dato.
 * @param out Variable donde se almacena el número leído.
 * @return true si el token leído se pudo convertir correctamente a double.
 */
bool read_number_token(std::istream& in, double& out) {
  std::string tok;
  if (!(in >> tok)) return false;      // EOF o fallo
  for (char& c : tok) if (c == ',') c = '.';
  try { out = std::stod(tok); }
  catch (...) { return false; }        // no era número válido
  return true;
}

/**
 * @brief Añade una arista no dirigida entre dos nodos.
 * @param node1 Primer nodo de la arista.
 * @param node2 Segundo nodo de la arista.
 * @param coste Coste asociado a la arista.
 */
void Grafo::AddCost(int node1, int node2, double coste) {
  nodos_[node1].AddChildren(node2, coste);
  nodos_[node2].AddChildren(node1, coste);
}

/**
 * @brief Constructor de la clase Grafo a partir de un fichero.
 * @param grafo_info Ruta del fichero con la información del grafo.
 * @param error_flag Código de error generado durante la construcción.
 */
Grafo::Grafo(const std::string &grafo_info, int& error_flag) {
  Build(grafo_info, error_flag);
}

/**
 * @brief Construye el grafo a partir de un fichero de entrada.
 * @param grafo_info Ruta del fichero con la información del grafo.
 * @param error_flag Código de error generado durante la lectura.
 */
void Grafo::Build(const std::string& grafo_info, int& error_flag) {
  std::ifstream input(grafo_info);
  if (!input.is_open()) { error_flag = 1; return; }  // no abre

  // 1) leer n (entero o double tipo "5" / "5.0")
  double nd = 0.0;
  if (!read_number_token(input, nd)) { error_flag = 2; return; }    // n inválido
  numnodos_ = static_cast<int>(std::llround(nd));
  if (numnodos_ <= 0) { error_flag = 2; return; }

  // 2) inicializar nodos 0..n-1
  nodos_.clear();
  nodos_.reserve(numnodos_);
  for (int i = 0; i < numnodos_; ++i) nodos_.emplace_back(i);

  // 3) leer matriz de adyacencia triangular superior
  for (int i = 0; i < numnodos_; ++i) {
    for (int j = i + 1; j < numnodos_; ++j) {
      double w;
      if (!read_number_token(input, w)) { error_flag = 3; return; } // EOF prematuro
      if (w >= 0.0) {                            // -1 => sin arista
        AddCost(i, j, w);                         // arista válida
      }
    }
  }

  // éxito
  error_flag = 0;
  input.close();
}

/**
 * @brief Actualiza el grafo actual usando un nuevo fichero.
 * @param grafo_info Ruta del nuevo fichero de entrada.
 * @param error_flag Código de error generado durante la actualización.
 */
void Grafo::Update(const std::string &grafo_info, int &error_flag) {
  Grafo tmp;
  tmp.Build(grafo_info, error_flag);
  if (error_flag != 0) return;
  std::swap(*this, tmp);
}

/**
 * @brief Destructor de la clase Grafo.
 */
Grafo::~Grafo() {
  Destroy();
}

/**
 * @brief Libera la información almacenada en el grafo.
 */
void Grafo::Destroy() {
  numnodos_ = 0;
  nodos_.clear();
}

/**
 * @brief Escribe la lista de adyacencia del grafo en un fichero.
 * @param out_path Ruta del fichero de salida.
 * @return true si la escritura se realizó correctamente.
 */
bool Grafo::AdjacencyList(const std::string& out_path) const {
  std::ofstream out(out_path);
  if (!out.is_open()) {
    std::cerr << "No se pudo abrir el archivo de salida: " << out_path << std::endl;
    return false;
  }

  // Se recorren todos los nodos del grafo.
  for (int u = 0; u < numnodos_; ++u) {
    const auto& node = nodos_[u];
    out << "Nodo " << (u + 1) << ":";

    // Si el nodo no tiene vecinos, se indica explícitamente.
    if (node.hijos().empty()) {
      out << " (sin conexiones)" << std::endl;
      continue;
    }

    // Se muestran todos los nodos adyacentes junto con el coste.
    for (const auto& par : node.hijos()) {
      int v = par.first;
      double w = par.second;
      out << " (" << (v + 1) << ", " << w << ")";
    }
    out << std::endl;
  }

  out.close();
  return true;
}

/**
 * @brief Calcula el número total de aristas del grafo.
 * @return Número de aristas no dirigidas.
 */
int Grafo::EdgeCount() const {
  long unsigned sum = 0;
  for (int i{0}; i < numnodos_; ++i) sum += static_cast<long unsigned>(nodos_[i].hijos().size());
  return static_cast<int>(sum / 2);
}