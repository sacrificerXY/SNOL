#include "Program.h"

#include <iostream>
#include "Tokens.h"
#include "Tokenizer.h"
#include "Helper.h"

using namespace std;

Operand::Operand()
{
    varName = "";
    value = 0;
}

void Operand::setToken(Token token)
{
    if (token.isType("IDENT"))
        varName = token.word;
    else
        value = toFloat(token.word);
}

Program::Program(Tokens tokens)
{
    error = false;

    // This just create the correct instruction for each snol statement
    //   and adds it to the program
    while (tokens.remainingTokens() > 0)
    {
        if (tokens.isNextPattern("BEG IDENT"))
        {
            Instruction inst;
            inst.type = "BEG";
            inst.op1.setToken(tokens.getToken(1));  // IDENT
            instructions.push_back(inst);
            tokens.movePointerBy(2);
        }
        else if (tokens.isNextPattern("PRINT OPERAND"))
        {
            Instruction inst;
            inst.type = "PRINT";
            inst.op1.setToken(tokens.getToken(1)); // OPERATOR
            instructions.push_back(inst);
            tokens.movePointerBy(2);
        }
        else if (tokens.isNextPattern("INTO IDENT IS OPERATOR OPERAND OPERAND"))
        {
            // If the INTO statement contains an arithmetic statement
            // It generates 2 instructions, in this order:
            //      1. The arithmetic instruction
            //      2. The into statement
            Instruction instOp;
            instOp.type = tokens.getToken(3).word;      // operator type (ADD, SUB, etc.)
            instOp.op1.setToken(tokens.getToken(4));    // operand 1
            instOp.op2.setToken(tokens.getToken(5));    // operand 2
            instructions.push_back(instOp);

            Instruction instINTO;
            instINTO.type = "INTO";
            instINTO.op1.setToken(tokens.getToken(1));  // destination variable
            instINTO.op2.varName = "_LAST";             // source variable
            instructions.push_back(instINTO);
            // NOTE: The source operand is set to the "_LAST" variable
            //  since the all arithmetic instructions store their result
            //  in the "_LAST" variable

            tokens.movePointerBy(6);
        }
        else if (tokens.isNextPattern("INTO IDENT IS OPERAND"))
        {
            Instruction instINTO;
            instINTO.type = "INTO";
            instINTO.op1.setToken(tokens.getToken(1));  // destination variable
            instINTO.op2.setToken(tokens.getToken(3));  // source variable
            instructions.push_back(instINTO);
            tokens.movePointerBy(4);
        }
        else
            tokens.movePointerBy(1);   // if for some reason execution reaches this point, just skip
    }
}

void Program::run()
{
    variables.clear();

    // Read each instruction and do stuff
    for (int i = 0; i < instructions.size(); i++)
    {
        if (error)
        {
            cout  << "\n    Terminating program..." << '\n' << color_white;
            break;
        }
        Instruction in = instructions[i];
        if (in.type == "BEG")
        {
            cout << color_yellow << "  INPUT(" << in.op1.varName << "): " << color_white;
            string rawInput;
            cin >> rawInput;
            bool isNumber = isFloat(rawInput) or isInt(rawInput);
            float value = toFloat(rawInput);

            if ((isNumber && value >= 0) || (value == 0 && rawInput.at(0) == '-'))
            {
                setVariable(in.op1.varName, toFloat(rawInput));
            }
            else
            {
                error = true;
                cout << color_lightred << "\n  > BEG_ERROR: " << color_lightyellow << rawInput << color_white << " is not a non-negative int/float\n";
            }
        }
        else if (in.type == "PRINT")
        {
            float val = getOperandValue(in.op2);
            if (error)
                continue;
            cout << color_lightyellow << "  PRINT: " << color_white << val << "\n";
        }
        else if (in.type == "INTO")
        {
            float val = getOperandValue(in.op2);
            if (error)
                continue;
            setVariable(in.op1.varName, val);
            cout << "  ... Set value of " << color_lightgreen << in.op1.varName << " to " << val << color_white << "\n";
        }
        // arithmetic
        else if (in.type == "ADD")
        {
            float op1 = getOperandValue(in.op1);
            if (error)
                continue;
            float op2 = getOperandValue(in.op2);
            if (error)
                continue;

            _LAST = op1+op2;
            cout << "  ... Evaluating " << color_blue << "ADD: result is " << _LAST << '\n' << color_white;
        }
        else if (in.type == "SUB")
        {
            float op1 = getOperandValue(in.op1);
            if (error)
                continue;
            float op2 = getOperandValue(in.op2);
            if (error)
                continue;

            _LAST = op1-op2;
            if (_LAST >= 0)
            {
                cout << "  ... Evaluating " << color_blue << "SUB: result is " << _LAST << '\n' << color_white;
            }
            else
            {
                error = true;
                cout << color_lightred << "\n  > SUB_ERROR: " << color_yellow <<"SUB " << op1 << " " << op2 << "\n" << color_white;
                cout << "    - Result cannot be negative\n";
            }
            // negative overflow

        }
        else if (in.type == "MULT")
        {
            float op1 = getOperandValue(in.op1);
            if (error)
                continue;
            float op2 = getOperandValue(in.op2);
            if (error)
                continue;

            _LAST = op1 * op2;
            cout << "  ... Evaluating " << color_blue << "MULT: result is " << _LAST << '\n' << color_white;
        }
        else if (in.type == "DIV")
        {
            float op1 = getOperandValue(in.op1);
            if (error)
                continue;
            float op2 = getOperandValue(in.op2);
            if (error)
                continue;

            if (op2 != 0)
            {
                _LAST = getOperandValue(in.op1) / getOperandValue(in.op2);
                cout << "  ... Evaluating " << color_blue << "DIV: result is " << _LAST << '\n' << color_white;
            }
            else
            {
                error = true;
                cout << color_lightred << "\n  > DIV_ERROR: " << color_yellow <<"DIV " << op1 << " " << op2 << "\n" << color_white;
                cout << "    - Division by zero not allowed\n";
            }
        }
        else if (in.type == "MOD")
        {
            float op1 = getOperandValue(in.op1);
            float op2 = getOperandValue(in.op2);

            if (isFloatAnInt(op1) and isFloatAnInt(op2))
            {
                _LAST = static_cast<int>(op1) % static_cast<int>(op2);
                cout << "  ... Evaluating " << color_blue << "MOD: result is " << _LAST << '\n' << color_white;
            }
            else
            {
                error = true;
                cout << color_lightred << "\n  > MOD_ERROR: " << color_yellow <<"MOD " << op1 << " " << op2 << "\n" << color_white;
                cout << "    - MOD requires both operands to be an int\n";
            }
        }
    }
}

bool Program::hasVariable(string name)
{
    for (int i = 0; i < variables.size(); i++)
    {
        if (variables[i].name == name)
            return true;
    }
    return false;
}

Variable* Program::getVariable(string name)
{
    for (int i = 0; i < variables.size(); i++)
    {
        if (variables[i].name == name)
            return &variables[i];
    }
    return NULL;
}

void Program::setVariable(string name, float value)
{
    if (hasVariable(name))
        getVariable(name)->value = value;
    else
    {
        Variable v;
        v.name = name;
        v.value = value;
        variables.push_back(v);
    }
}

float Program::getOperandValue(Operand op)
{
    if (op.varName == "_LAST")
        return _LAST;
    if (op.varName.empty())
        return op.value;
    if (hasVariable(op.varName))
        return getVariable(op.varName)->value;

    cout << color_lightred << "\n  > ERROR: " << color_white<<"Access to undefined variable: " << color_lightyellow<<op.varName << "\n\n" << color_white;
    error = true;
}



