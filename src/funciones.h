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
// Archivo funciones.h: declaración de funciones auxiliares utilizadas
//                      para la interacción con el usuario, validación
//                      de rutas y gestión de errores.
#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <cstdlib> 
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <filesystem>
#include <string>
#include <system_error>

/**
 * @brief Tipos posibles de ruta encontrados en el sistema de archivos.
 */
enum class PathType {
  NotFound,
  RegularFile,
  Directory,
  Symlink,
  Other,
  Error
};

void menu(int &option);
void help();
bool CheckOption(const int &option);
void pressanykey();
void clrscr();
PathType classify_path(const std::string& path_str);
int classify_path_code(const std::string& path_str);
std::string classify_path_str(int code);
const char* GraphBuildErrorStr(int code);
bool HandleGraphBuildError(int error_flag, const std::string& path);

#endif