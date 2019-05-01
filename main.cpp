//Lab Exam number 2

#include <iostream>
#include <string>
#include "Tokenizer.h"
#include "Program.h"
#include "Error.h"
#include "Helper.h"
#include "Lab2.h"

using namespace std;

int main()
{
    string fileName;
    cout << "\n\n  Enter SNOL source file(without extensions): ";
    cin >> fileName;

    Tokens tokens = tokenizeSource(fileName);
    if (tokens.isEmpty())
        return 0;

    // The whole program should still work if this line is removed
    Lab2Output(fileName).printTokens(tokens);

    cout << "    Checking for errors...\n";
    cout << "--------------------------------\n";

    if (hasTokenErrors(tokens))
    {
        cout << "--------------------------------\n";
        cout << "    Errors detected. Can't run program.\n";
        return 0;
    }

    cout << "--------------------------------\n";
    cout << "    Running program\n\n";

    Program program(tokens);
    program.run();

    cout << "--------------------------------\n";
} // END MAIN ------------------------------------

