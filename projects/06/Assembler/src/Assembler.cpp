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

/* Entry point and facade controller of the assembler
 */
#include "Assembler.h"
#include "Code.h"
#include "Parser.h"
#include "Utility.h"

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cassert>
#include <regex>
#include <stdexcept>
#include <fstream>

using namespace std;

Assembler::Assembler(const vector<string> &arguments)
{
    if(arguments.size() == 2)
        inputFile = arguments[1];
    else
        throw runtime_error("1 argument is required.");

    initializeSymbolTable();
}

void Assembler::run()
{
    outputFile = parseFilename(inputFile) + ".hack";
    
    doFirstPass();
    doSecondPass();
}

void Assembler::initializeSymbolTable()
{
    st.addEntry("SP", 0);
    st.addEntry("LCL", 1);
    st.addEntry("ARG", 2);
    st.addEntry("THIS", 3);
    st.addEntry("THAT", 4);

    for (int i = 0; i < 16; i++)
        st.addEntry("R" + to_string(i), i);

    st.addEntry("SCREEN", 16384);
    st.addEntry("KBD", 24576);
}

string Assembler::parseFilename(string filename)
{
    static const string file_expression = R"((?:.*(?:/|\\))*(.*)\.asm$)";
    regex e(file_expression);
    smatch matches;
    
    regex_match(filename, matches, e);
    
    if(matches.size() > 1)
        return matches[1];
    else
        throw runtime_error("Could not parse filename. Must end in .asm");
}

void Assembler::doFirstPass()
{
    // open file for reading
    ifstream ifs(inputFile);
    Parser parse(ifs);

    int outputLineCounter = 0;

    try
    {
        // while there are more commands
        while (parse.hasMoreCommands())
        {
            // read the commands
            parse.advance();

            CommandType type = parse.getCommandType();

            switch (type)
            {
            // if it's an L-command, add symbol to table
            case CommandType::L:
            {
                string symbol = parse.getSymbol();
                if (st.contains(symbol))
                    throw runtime_error("Symbol '" + symbol + "is already defined.");
                else
                    st.addEntry(symbol, outputLineCounter);
                continue;
            }

            // do nothing
            case CommandType::A:
            case CommandType::C:
            {
                outputLineCounter++;
                break;
            }

            default:
            {
                throw runtime_error("Code converion error. Unknown why.");
                break;
            }
            }
        }

    }
    catch (runtime_error& e)
    {
        throw runtime_error("Line " + to_string(parse.getLineNumber()) + ": " + e.what());
    }
}

void Assembler::doSecondPass()
{
    // open file for reading
    ifstream ifs(inputFile);
    Parser parse(ifs);
    
    // open file for writing
    ofstream ofs(outputFile);

    int storeRamAddress = 16;
    
    try
    {
        // while there are more commands
        while(parse.hasMoreCommands())
        {
            // read the commands
            parse.advance();
            if (true)
            {

            }
            CommandType type = parse.getCommandType();
            
            switch(type)
            {
                // skip the command if it's the L-type
                case CommandType::L:
                    break;
                    
                // if it's of the A-type, write the output
                case CommandType::A:
                {
                    string symbol = parse.getSymbol();
                    string address;

                    if (isdigit(symbol[0]))
                        address = symbol;
                    else
                    {
                        if (!st.contains(symbol))
                            st.addEntry(symbol, storeRamAddress++);
                        address = to_string(st.GetAddress(symbol));
                    }

                    ofs << '0' << ntobs(address) << endl;
                    break;
                }
                    
                // if it's of the C-type, write the output
                case CommandType::C:
                {
                    auto comp = Code::comp(parse.getComp());
                    auto dest = Code::dest(parse.getDest());
                    auto jump = Code::jump(parse.getJump());
                    ofs << '1' << "11" << comp << dest  << jump << endl;
                    break;
                }
                
                default:
                {
                    throw runtime_error("Code converion error. Unknown why.");
                    break;
                }
            }
        }
        
    }
    catch(runtime_error &e)
    {
        throw runtime_error("Line " + to_string(parse.getLineNumber()) + ": " + e.what());
    }
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
        // initialize code module
        Code::init();
    
        // pass them to the assembler
        Assembler program(arguments);
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
