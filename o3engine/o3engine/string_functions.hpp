#ifndef STRUP_H_INCLUDED
#define STRUP_H_INCLUDED

//TODO: REmove it, we have boost....
#include <string>
#include <vector>

extern char * strup(char *);
std::vector<std::string> tokenize_string(const std::string & str, const std::string & delimiters);
std::string fgetline(FILE * fin);
std::string trim_white_space(const std::string & str);
#endif // STRUP_H_INCLUDED
