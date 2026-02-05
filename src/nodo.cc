#include "nodo.h"

void Nodo::AddChildren(int destino, double coste) {
  hijos_.emplace_back(destino, coste);
}

double Nodo::DistanceTo(int id_destino) const {
  for (const auto& [auxid, auxcoste] : hijos_) {
    if (auxid == id_destino) {
      return auxcoste;
    }
  }
  std::cerr << "El nodo " << id_ << " no tiene al nodo " << id_destino << " como su hijo" << std::endl;
  return -1;
}
