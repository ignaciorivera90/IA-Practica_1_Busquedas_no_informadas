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