/*
 * Copyright (c) 2020 Haresh Bhachandani
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/* Entry point and facade controller of the translator
 */
#include "Translator.h"

#include <boost/filesystem.hpp>

#include <iostream>
#include <exception>

using namespace std;

Translator::Translator(std::vector<std::string> arguments)
{
    if(arguments.size() != 2)
        throw runtime_error("Error: Program only takes 1 argument");
    
    inputFilename = arguments[1];
}

void Translator::run()
{
    
}

int main(int argc, char *argv[])
{
    // collect arguments passed to the program
    vector<string> arguments;
    
	for(int i = 0; i < argc; i++)
    {
        arguments.push_back(argv[i]);
    }
    
    try
    {    
        // pass them to the assembler
        Translator program(arguments);
        program.run();
    }
    catch(exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    catch(...)
    {
        cerr << "Unknown error!" << endl;
        return 2;
    }
    
    return 0;
}
