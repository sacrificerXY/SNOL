#include "Tokens.h"

#include <ostream>
#include "Helper.h"

using namespace std;

Tokens::Tokens()
{
    tokenPointer = 0;
}

void Tokens::addToken(string word, string type)
{
    Token token;
    token.word = word;
    token.type = type;

    token.addType(type); // add main type

    // if operator
    if (type == "ADD" || type == "SUB" || type == "MULT" ||
            type == "DIV" || type == "MOD")
    {
        token.addType("OPERATOR");
    }
    // if number
    else if (type == "INT" || type == "FLOAT")
    {
        token.addType("NUMBER");
        token.addType("OPERAND");
    }
    // if variable
    else if (type == "IDENT")
    {
        token.addType("OPERAND");
    }

    tokens.push_back(token);
}

void Tokens::movePointerBy(int i)
{
    tokenPointer += i;
    if (tokenPointer >= tokens.size())
        tokenPointer = tokens.size();
}

int Tokens::remainingTokens()
{
    return tokens.size() - tokenPointer;
}

Token Tokens::getToken(int offset)
{
    return tokens.at(tokenPointer+offset);
}

bool Tokens::isEmpty()
{
    return tokens.empty();
}

bool Tokens::isNextPattern(string pattern)
{
    // First, split the each type in the string
    vector<string> patterns = split(pattern, ' ');
    return isNextPattern(patterns);
}

bool Tokens::isNextPattern(std::vector<string> patterns)
{
    // if the remaining tokens is less than the length
    //   of the pattern, then it can't possibly fit the pattern
    if (tokenPointer+patterns.size() > tokens.size())
        return false;

    int index = 0;

    for (int i = 0; i < patterns.size(); i++)
    {
        bool tokenFollowsPattern = tokens[tokenPointer + index].isType(patterns[i]);
        if (tokenFollowsPattern == false)
            return false;
        else
            index++;
    }
    return true;
}

// Passing "*" always returns true
bool Token::isType(string type)
{
    if (type == "*")
        return true;
    for (int i = 0; i < types.size(); i++)
    {
        if (types[i] == type)
            return true;
    }
    return false;
}

void Token::addType(string type)
{
    // only add type if it doesn't exist already
    if (!isType(type))
        types.push_back(type);
}


