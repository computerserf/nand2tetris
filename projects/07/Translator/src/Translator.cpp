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
#include "Parser.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#include <iostream>
#include <fstream>
#include <exception>

using namespace std;
using namespace boost::filesystem;

const string OUTPUT_PREFIX("asm");

Translator::Translator(vector<string> arguments)
{
    if(arguments.size() != 2)
        throw runtime_error("Error: Program only takes 1 argument");
    
    inputFilename = arguments[1];
}

void Translator::translate(string inputFilename, CodeWriter &writer)
{
    // prepare file for parsing
    std::ifstream input(inputFilename);    
    Parser parser(input);
    
    writer.setFilename(path(inputFilename).filename().string());
    
    try
    {
        // while there is more to parse
        while(parser.hasMoreCommands())
        {
            // parse it
            parser.advance();
            
            CommandType type = parser.getCommandType();
            
            // write the correct command
            switch(type)
            {
                case CommandType::Arithmetic:
                {
                    writer.writeArithmetic(parser.getArg1());
                    break;
                }
                
                case CommandType::Push:
                case CommandType::Pop:
                {
                    try
                    {
                        int index = stoi(parser.getArg2());
                        writer.writePushPop(type, parser.getArg1(), index);
                    }
                    catch(invalid_argument &e)
                    {
                        throw runtime_error("Could not convert '" + parser.getArg2() + "' to integer");
                    }
                    catch(out_of_range &e)
                    {
                        throw runtime_error("'" + parser.getArg2() + "' does not fit in an integer");
                    }
                }
                
                default:
                    break;
            }
        }
    }
    catch(runtime_error &e)
    {
        throw runtime_error(inputFilename + " (" + to_string(parser.getLineNumber()) + "): " + e.what());
    }
}

void Translator::run()
{
    // if the file is a directory, parse and translate all .vm files
    if(is_directory(inputFilename))
    {
        std::ofstream out(path(inputFilename).filename().stem().string() + "." + OUTPUT_PREFIX);
        CodeWriter cw(out);
        
        for(auto&& f : directory_iterator(path(inputFilename)))
        {
            if(is_vm(f.path().filename().string()))
            {
                string input_name = path(f).string();
                translate(input_name, cw);
            }
        }
    }
    // otherwise, if the file is a regular file, make sure it's a vm file and translate it
    else if(is_regular_file(inputFilename))
    {
        if(is_vm(path(inputFilename).filename().string()))
        {
            std::ofstream out(path(inputFilename).filename().stem().string() + + "." + OUTPUT_PREFIX);
            CodeWriter cw(out);
            
            translate(inputFilename, cw);
        }
        else
            throw runtime_error("Error: '" + inputFilename + "' does not end in a .vm extension");
    }
    // otherwise it's not a supported file
    else
        throw runtime_error("Error: '" + inputFilename + "' is not a .vm file or directory");
        
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
