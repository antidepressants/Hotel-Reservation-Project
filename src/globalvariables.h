#pragma once
#include "classes.h"
#include <fstream>

extern bool windows;

extern std::ifstream fin;
extern std::ofstream fout;

extern std::vector<std::string> features;
extern std::vector<std::string> locations;
extern std::vector<std::string> types;
extern std::vector<room> rVec;
extern std::vector<user> uVec;
extern std::vector<reservation> resVec;