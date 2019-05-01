#ifndef LAB2_H_INCLUDED
#define LAB2_H_INCLUDED

#include <string>
#include <set>

// Everything related to Lab Exam 2
// The whole program should still work if this is removed

struct Tokens;

struct Lab2Output
{
    Lab2Output(std::string fileName);
    ~Lab2Output();
    void printTokens(Tokens tokens);

private:
    FILE * stFile;
    FILE *tokFile;

    // set will only contain unique element
    // you cannot insert elements of the same value twice
    // So use it to determine if a lexeme was already read
    std::set<std::string> lexemes;
};




#endif // LAB2_H_INCLUDED
