#include "Tokenizer.h"

#include <string>
#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <vector>

#include "Helper.h"

using namespace std;

Tokens tokenizeSource(string fileName)
{
    // Open source
    FILE *source  = fopen(fileName+".snol", "r");
    if (source != NULL)
        cout << "\n    Source file found!\n";

    Tokens tokens;
    char word[100];
    string tokenType;

    // Get each word from source until end-of-file is reached
    while(fscanf(source, "%s", &word[0]) != -1)
    {
        // Determine the token type
        if (isKeyword   (word))
            tokenType = word; // since tokenType of reserved words are themselves
        else if (isIdentifier(word))
            tokenType = "IDENT";
        else if (isInt       (word))
            tokenType = "INT";
        else if (isFloat     (word))
            tokenType = "FLOAT";
        else
            tokenType = "ERR";

        tokens.addToken(word, tokenType);
    }
    return tokens;
}


// FUNCTION Definitions ----------------------------------
string keywords[11] = {"SNOL", "LONS", "INTO", "IS", "MULT", "BEG", "PRINT", "ADD", "SUB", "DIV", "MOD"};
bool isKeyword(std::string word)
{
    for(int i=0; i<11; i++)
    {
        // Check if word is equal to keyword at index i
        // If yes, return true
        if(word == keywords[i])
            return true;
    }

    // If execution reaches this point, then there was no match
    return false;
}

bool isIdentifier(std::string word)
{
    // Check if first character is a letter
    // If not, return false
    if (!isalpha(word[0]))
        return false;

    // Check if the rest (2nd char to last) is an alphanumeric character
    // If not, return false
    for (int i = 1; i < word.size(); i++)
    {
        if (!isalnum(word[i]))
            return false;
    }

    return true;
}

bool isInt(std::string word)
{
    // Check if every character is a digit
    // If not, return false
    for (int i = 0; i < word.size(); i++)
    {
        if (!isdigit(word[i]))
            return false;
    }

    return true;
}

bool isFloat(std::string word)
{
    // Check if first character is a digit
    // If not, return false
    if (!isdigit(word[0]))
        return false;

    // Check if the rest (2nd char to last) are digits or periods
    // If not, return false
    int numPeriod = 0;  // how many periods in the word
    for(int i = 1; i<word.size(); i++)
    {
        if(word[i]=='.')
            numPeriod++;
        else if(!isdigit(word[i]))
            return false;
    }

    // At this point, we are sure that the word only contains periods or digits
    // But only return true if there is EXACTLY one period
    return numPeriod == 1;
}

