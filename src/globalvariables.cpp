#include "globalvariables.h"

bool windows=0;
#ifdef _WIN32
windows=1;
#endif

std::ifstream fin;
std::ofstream fout;

std::vector<std::string> features;
std::vector<std::string> locations;
std::vector<std::string> types;
std::vector<room> rVec;
std::vector<user> uVec;
std::vector<reservation> resVec;