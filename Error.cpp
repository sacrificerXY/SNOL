#include "Error.h"

#include <iostream>
#include "Helper.h"
#include "Tokens.h"

using namespace std;

ErrorResult::ErrorResult()
{
    numErrors = 0;
    fullLine = "";
}

// Print errors to console
void ErrorResult::print()
{
    if (numErrors == 0)
        cout << color_lightgreen << "  + ";
    else
        cout << color_red << "  x ";
    cout << color_yellow <<  fullLine << '\n' << color_white;
    for (int i = 0; i < numErrors; i++)
    {
        cout << "      > " << color_lightyellow << errorTokens[i].word << " " << color_white;
        if (errorTokens[i].isType("ERR"))
            cout << "is an " << color_blue << "invalid word" << color_white << '\n';
        else
            cout << errorMessages[i] << '\n';
    }
}

ErrorChecker& ErrorChecker::addFilter(std::string filterPattern)
{
    filterPatterns.push_back(filterPattern);
    correctPatterns.push_back(filterPattern);
    errorMessages.push_back("");
    return *this;
}

ErrorChecker& ErrorChecker::addCondition(std::string correctPattern, std::string errorMessage)
{
    filterPatterns.push_back("*");
    correctPatterns.push_back(correctPattern);
    errorMessages.push_back(errorMessage);
    return *this;
}

bool ErrorChecker::fitsPattern(Tokens & tokens)
{
    return tokens.isNextPattern(filterPatterns);
}

ErrorResult ErrorChecker::check(Tokens &tokens)
{
    ErrorResult result;
    for (int i = 0; i < filterPatterns.size(); i++)
    {
        // Append current token to the "full" snol statement
        result.fullLine += tokens.getToken(i).word + " ";

        // If the current token does not follow the CORRECT pattern
        // Update the results accordingly
        if (!tokens.getToken(i).isType(correctPatterns[i]))
        {
            result.errorTokens.push_back(tokens.getToken(i));
            result.errorMessages.push_back(errorMessages[i]);
            result.numErrors++;
        }
    }

    // Since we already handled the checking of the current statement
    // Move the token stream to the next set of tokens
    tokens.movePointerBy(filterPatterns.size());
    return result;
}


bool checkPattern(ErrorChecker & checker, Tokens &tokens, int &numErrors)
{
    // IMPORTANT: Check first if the tokens fits the filter pattern
    // If not, do nothing
    if (checker.fitsPattern(tokens))
    {
        // If it fits, check for errors
        ErrorResult result = checker.check(tokens);
        result.print();
        numErrors += result.numErrors;
        return true;
    }
    return false;
}

bool hasTokenErrors(Tokens tokens)
{
    // Constructing the ErrorCheckers for each type of snol statement
    ErrorChecker SNOL = ErrorChecker()
                        .addCondition   ("SNOL", "is first token. Should be \"SNOL\"");

    ErrorChecker LONS = ErrorChecker()
                        .addCondition   ("LONS", "is last token. Should be \"LONS\"");

    ErrorChecker BEG = ErrorChecker()
                       .addFilter      ("BEG")
                       .addCondition   ("IDENT", "is not a variable");

    ErrorChecker PRINT = ErrorChecker()
                         .addFilter      ("PRINT")
                         .addCondition   ("OPERAND", "is not a variable/int/float");

    ErrorChecker INTO_OP = ErrorChecker()
                           .addFilter      ("INTO"                                     )
                           .addCondition   ("IDENT", "is not a variable"           )
                           .addCondition   ("IS", "found instead of \"IS\""     )
                           .addFilter      ("OPERATOR"                                 )
                           .addCondition   ("OPERAND", "is not a variable/int/float" )
                           .addCondition   ("OPERAND", "is not a variable/int/float" );

    ErrorChecker INTO_VAR = ErrorChecker()
                            .addFilter      ("INTO"                                     )
                            .addCondition   ("IDENT", "is not a variable"           )
                            .addCondition   ("IS", "found instead of \"IS\""     )
                            .addCondition   ("OPERAND", "is not a variable/int/float" );

    ErrorChecker UNKNOWN_INSTRUCTION = ErrorChecker()
                                       .addCondition   ("", "- unknown instruction");

    int numErrors = 0;

    checkPattern(SNOL, tokens, numErrors);  // check first token
    while (tokens.remainingTokens() > 1)    // Only loop until the second-to-the-last token
    {
        if (checkPattern(BEG, tokens, numErrors));
        else if (checkPattern(PRINT, tokens, numErrors));
        else if (checkPattern(INTO_OP, tokens, numErrors));
        else if (checkPattern(INTO_VAR, tokens, numErrors));

        else
            checkPattern(UNKNOWN_INSTRUCTION, tokens, numErrors);
    }
    checkPattern(LONS, tokens, numErrors);  // check last token

    if (numErrors > 0)
        return true;
    return false;
}
