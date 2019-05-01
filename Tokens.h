#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

#include <string>
#include <vector>

struct Token
{
    std::string word; // its actual lexeme
    std::string type; // main type

    bool isType(std::string type);
    void addType(std::string type);

private:
    // a vector which contains its main type and its other subtypes
    // Subtypes can be: NUMBER, OPERAND, or OPERATOR
    std::vector<std::string> types;
};

// Just a simple container for tokens with some specific functionality
struct Tokens
{
    Tokens();
    void addToken(std::string word, std::string type);

    // Functions for iterating over the tokens in a loop
    int remainingTokens();
    void movePointerBy(int i);

    // Return the current token pointed by the pointer
    // An offset value can be passed, in which case
    //  the token "offset" steps to the right of the
    //  the current token is returned
    Token getToken(int offset=0);

    // Check if there are no tokens
    // Happens if the source file is not found or is empty
    bool isEmpty();

    // Check whether the next tokens (starting from the current token pointed by the pointer)
    // Follows a specific pattern
    // The pattern is string of types separated by space
    //   Ex.: "type1 type2 type3"
    //   Ex.: "INTO IDENT IS OPERATOR OPERAND OPERAND"
    //
    bool isNextPattern(std::string pattern);

    // Same as above but types are in a vector
    bool isNextPattern(std::vector<std::string> pattern);

private:
    std::vector<Token> tokens;
    int tokenPointer;
};

#endif // TOKENS_H_INCLUDED
