#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <string>
#include <vector>

struct Token;
struct Tokens;

struct Variable
{
    std::string name;
    float value;
};

// An operand hold information about the values
// used in an instruction (i.e. a variable name or a number)
struct Operand
{
    // If "varName" is set, this operands value is from a variable
    // Otherwise, it is just the "value"
    std::string varName;
    float value;
    Operand();

    // Takes care of initializing this operand
    // If the token is a variable, "varName" is set
    // if the token is a number(int/float), "value" is set
    void setToken(Token token);
};

struct Instruction
{
    std::string type;
    Operand op1;
    Operand op2;
};

// This runs the source code
// A program contains a set of instructions to run and variables
// The instructions are created from a token stream
// IMPORTANT: Assumes the tokens are syntax-error free
struct Program
{
    std::vector<Instruction> instructions;
    std::vector<Variable> variables;

    float _LAST; // will contain the result of the last arithmetic instruction
    bool error; // a flag for detecting errors when running the code

    Program(Tokens tokens); // constructor - converts the tokens into instructions
    void run();

private:
    // Checks whether a variable already exists or was initialized before
    bool hasVariable(std::string name);

    // Returns a variable if it exists
    // Otherwise, will output an error to console
    Variable* getVariable(std::string name);

    // Sets a variables value
    // If the variables doesn't exist, create it
    void setVariable(std::string name, float value);

    float getOperandValue(Operand op);
};

#endif // PROGRAM_H_INCLUDED
