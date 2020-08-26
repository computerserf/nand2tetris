/* Entry point and facade controller of the assembler
*/
#include "Assembler.h"

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

Assembler::Assembler(vector<string> arguments)
{
    assert(arguments.size() > 1);
    inputPath = arguments[1];
}

void Assembler::run()
{
    parseFilname(inputPath);
}

void Assembler::parseFilname(string filename)
{
    outputPath = "";
}



int main(int argc, char *argv[])
{
    // collect arguments passed to the program
    vector<string> arguments;
    
	for(int i = 0; i < argc; i++)
    {
        arguments.push_back(argv[i]);
    }
    
    // pass them to the assembler
    Assembler program(arguments);
    program.run();
    
    return 0;
}
