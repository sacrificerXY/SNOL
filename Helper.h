#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <vector>
#include <string>

// Functions made for the sake of conveniece/fun.

// String to number conversion
int toInt(std::string value);
float toFloat(std::string value);

// check if a float has no fractional part
bool isFloatAnInt(float f);

// fopen for strings instead of const char*
FILE* fopen(std::string path, std::string mode);

// For setting text colors in the console
// From: https://stackoverflow.com/a/4053879
std::ostream& color_red(std::ostream& out);
std::ostream& color_lightred(std::ostream& out);
std::ostream& color_blue(std::ostream& out);
std::ostream& color_green(std::ostream& out);
std::ostream& color_yellow(std::ostream& out);
std::ostream& color_lightyellow(std::ostream& out);
std::ostream& color_lightgreen(std::ostream& out);
std::ostream& color_white(std::ostream& out);

// For splitting strings with a delimiter
// From: https://stackoverflow.com/a/236803
template<typename Out>
void split(const std::string &s, char delim, Out result);
std::vector<std::string> split(const std::string &s, char delim);


#endif // HELPER_H_INCLUDED
