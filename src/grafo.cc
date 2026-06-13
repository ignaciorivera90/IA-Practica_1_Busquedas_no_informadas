#include "grafo.h"
#include <sstream>
#include <algorithm>
#include <cmath>

bool read_number_token(std::istream& in, double& out) {
  std::string tok;
  if (!(in >> tok)) return false;      // EOF o fallo
  for (char& c : tok) if (c == ',') c = '.';
  try { out = std::stod(tok); }
  catch (...) { return false; }        // no era número válido
  return true;
}

void Grafo::AddCost(int node1, int node2, double coste) {
  nodos_[node1].AddChildren(node2, coste);
  nodos_[node2].AddChildren(node1, coste);
}

Grafo::Grafo(const std::string &grafo_info, int& error_flag) {
  Build(grafo_info, error_flag);
}

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
        AddCost(i, j, w);                         // permite pesos negativos reales
      }
    }
  }

  // éxito
  error_flag = 0;
  input.close();
}

void Grafo::Update(const std::string &grafo_info, int &error_flag) {
  Grafo tmp;
  tmp.Build(grafo_info, error_flag);
  if (error_flag != 0) return;
  std::swap(*this, tmp);
}

Grafo::~Grafo() {
  Destroy();
}

void Grafo::Destroy() {
  numnodos_ = 0;
  nodos_.clear();
}

bool Grafo::AdjacencyList(const std::string& out_path) const {
  std::ofstream out(out_path);
  if (!out.is_open()) {
    std::cerr << "No se pudo abrir el archivo de salida: " << out_path << std::endl;
    return false;
  }

  for (int u = 0; u < numnodos_; ++u) {
    const auto& node = nodos_[u];
    out << "Nodo " << (u + 1) << ":";

    if (node.hijos().empty()) {
      out << " (sin conexiones)" << std::endl;
      continue;
    }

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

int Grafo::EdgeCount() const {
  long unsigned sum = 0;
  for (int i{0}; i < numnodos_; ++i) sum += static_cast<long unsigned>(nodos_[i].hijos().size());
  return static_cast<int>(sum / 2);
}
