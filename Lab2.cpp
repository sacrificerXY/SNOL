#include "Lab2.h"

#include <stdio.h>

#include "Tokens.h"
#include "Helper.h"

using namespace std;

Lab2Output::Lab2Output(string fileName)
{
    // open output files(adding correct extensions)
    stFile  = fopen(fileName + ".st", "w");
    tokFile = fopen(fileName + ".tok", "w");

    // Print first line of test.st
    fprintf(stFile, "Lexeme, Token\n");
}

Lab2Output::~Lab2Output()
{
    // close files
    fclose(stFile);
    fclose(tokFile);
}


void Lab2Output::printTokens(Tokens tokens)
{
    while (tokens.remainingTokens() > 0)
    {
        string word = tokens.getToken().word;
        string type = tokens.getToken().type;

        // lexemes.insert(word)
        // Return a pair (first, second) where
        //   second is TRUE if it was inserted, FALSE otherwise
        // Gi chain lang ning sa ubos na line
        bool firstTimeReadingThisLexeme = lexemes.insert(word).second;

        // Print to .st file
        if (firstTimeReadingThisLexeme)
            fprintf(stFile, "%s, %s\n", word.c_str(), type.c_str());
        // Print to .tok file
        if (word == type)
            fprintf(tokFile, "%s\n", word.c_str());
        else
            fprintf(tokFile, "<%s-%s>\n", type.c_str(), word.c_str());

        tokens.movePointerBy(1);
    }

}



