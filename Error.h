#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <string>
#include <vector>

struct Token;
struct Tokens;

struct ErrorResult
{
    int numErrors;                              // how many errors
    std::string fullLine;                       // the full snol statement/line which contains the error
    std::vector<Token> errorTokens;             // the specific tokens which contained errors
    std::vector<std::string> errorMessages;     // error messages to show

    ErrorResult();  // constructor - just sets variables to default values
    void print();   // prints the error results to console
};

// This struct will determine whether the next tokens to check follow a specific pattern
// An ErrorChecker can only check for 1 specific pattern
// A pattern is a set of filters and conditions
// Error checking happens in 2 stages:
//      1. Filtering - Check whether the next tokens follow a specific pattern (i.e. BEG <ANY>, PRINT <ANY>)
//      2. Error checking - Check whether the next tokens follow the ACTUAL CORRECT PATTERN (i.e BEG IDENT, PRINT OPERAND)
// Error messages can also be added if the conditions are not met
struct ErrorChecker
{
    // These functions are for constructing the patterns to check
    // Returns a reference to "this" object to allow chaining
    //   of these functions
    ErrorChecker& addFilter(std::string filterPattern);
    ErrorChecker& addCondition(std::string correctPattern, std::string errorMessage);

    // Does not do error checking
    // Determines whether the next tokens fits the filter pattern
    bool fitsPattern(Tokens & tokens);

    // This is the function which actually runs the error-checking
    // Checks if the next tokens are of the correct patterns
    ErrorResult check(Tokens &tokens);

private:
    std::vector<std::string> filterPatterns;
    std::vector<std::string> correctPatterns;
    std::vector<std::string> errorMessages;
};

// Checks whether the next tokens in the token stream fits a specific pattern
// If it does, it checks for errors and returns the number of errors
bool checkPattern(ErrorChecker const& checker, Tokens &tokens, int &numErrors);

// Checks if an entire token stream is well-formed
bool hasTokenErrors(Tokens tokens);

#endif // ERROR_H_INCLUDED
