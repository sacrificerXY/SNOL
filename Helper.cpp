#include "Helper.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <stdio.h>

int toInt(std::string value)
{
    return strtof(value.c_str(), NULL)+0;
}
float toFloat(std::string value)
{
    return strtof(value.c_str(), NULL)+0;
}
// Not sure, but +0 seems to reset the sign bit in the case of "-0"

bool isFloatAnInt(float f)
{
    return static_cast<int>(f) == f;
}

FILE* fopen(std::string path, std::string mode)
{
    FILE * f = fopen(path.c_str(), mode.c_str());
    if( f == NULL )
    {
        std::cout << "\n  Could not open file: " << path << '\n';
    }
    return f;
}

std::ostream& color(std::ostream &out, int color)
{
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    return out;
}

std::ostream& color_red(std::ostream& out)
{
    return color(out, 4);
}
std::ostream& color_lightred(std::ostream& out)
{
    return color(out, 12);
}
std::ostream& color_blue(std::ostream& out)
{
    return color(out, 3);
}
std::ostream& color_yellow(std::ostream& out)
{
    return color(out, 6);
}
std::ostream& color_lightyellow(std::ostream& out)
{
    return color(out, 14);
}
std::ostream& color_green(std::ostream& out)
{
    return color(out, 2);
}
std::ostream& color_lightgreen(std::ostream& out)
{
    return color(out, 10);
}
std::ostream& color_white(std::ostream& out)
{
    return color(out, 7);
}

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
}
std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

