#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include <string>
#include "Tokens.h"

// Reads a snol file and creates a token stream
Tokens tokenizeSource(std::string fileName);

// Token type checker functions
bool isKeyword(std::string word);
bool isIdentifier(std::string word);
bool isInt(std::string word);
bool isFloat(std::string word);


#endif // TOKENIZER_H_INCLUDED
