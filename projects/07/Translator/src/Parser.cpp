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

/* Implementation of the Parser module
 */

#include "Parser.h"

#include <istream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <regex>
#include <iostream>

using namespace std;

Parser::Parser(istream& inputStream) : input{inputStream}, type{CommandType::Unknown}, line_no{1}, arg1{""}, arg2{""}
{
}

bool Parser::hasMoreCommands()
{
    skipComments();
    
    return !input.eof();
}

void Parser::advance()
{
    // Get the line
    string line;
    
    getline(input, line);
    
    // Strip comments and trim
    string command = stripLine(line);
    
    if(command.size() == 0)
        throw runtime_error("Could not parse line. Check syntax.");

    parseCommmand(command);
    
    line_no++;
}

CommandType Parser::getCommandType()
{
    return type;
}

std::string Parser::getArg1()
{
    return arg1;
}

std::string Parser::getArg2()
{
    return arg2;
}

int Parser::getLineNumber()
{
    return line_no;
}


void Parser::skipComments()
{
    // Keep getting the next character, skipping whitespace
    while(input && !input.eof())
    {
        char ch;
        
        input.get(ch);
        
        if(input.eof())
            break;
        
        // Keep track of newlines
        if(ch == '\n')
            line_no++;
        
        if(isspace(ch))
            continue;
        
        string ignore;
        
        // If the next character is a comment, skip the line
        if(ch == '/' && input.peek() == '/') 
        {
            getline(input, ignore);
            line_no++;
        }
        
       // Otherwise place it back in the stream and exit
        else
        {
            input.putback(ch);
            break;
        }
    }
}

bool isArithmetic(const string &s)
{
	return (s == "add" || s == "sub" || s == "neg" || s == "eq" ||
		s == "gt" || s == "lt" || s == "and" || s == "or" || s == "not");
}

bool isMemoryAccess(const string &s)
{
	return (s == "push" || s == "pop");
}

void Parser::parseCommmand(const string &command)
{
    static const std::string command_expresssion = R"(^(\w+)(\s*\w+){0,2}$)";
    static const regex e{command_expresssion};
    
    smatch matches;
    regex_match(command, matches, e);
    
    if(matches.size() > 1)
    {
        // match found; parse command
        
        if(isArithmetic(matches[1]))
        {
            if(matches.size() > 2)
            {
                type = CommandType::Unknown;
                throw runtime_error("Could not parse arithmetic command. Check syntax.");;
            }            
            else
            {
                type = CommandType::Arithmetic;
                arg1 = matches[1];
                arg2 = "";
            }
        }
        else if(isMemoryAccess(matches[1]))
        {
            if(matches.size() != 4)
            {
                type = CommandType::Unknown;
                throw runtime_error("Could not memory access command. Check syntax.");
            }
            else
            {
                if(matches[1] == "push")
                    type = CommandType::Push;
                else
                    type = CommandType::Pop;
                
                arg1 = trim(matches[2]);
                arg2 = trim(matches[3]);
            }
            
        }
        else
        {
            type = CommandType::Unknown;
            throw runtime_error("Could not parse command. Check syntax.");
        }
    }
    else
    {
        type = CommandType::Unknown;
        throw runtime_error("Could not parse command. Check syntax.");
    }
}


string Parser::stripLine(const string &line)
{
    string str{line};
    
    // Strip comment to end
    for(int  i = 0; i < line.size() - 1; i++)
        if(line[i] == '/' && line[i+1] == '/')
        {
            str = line.substr(0, i);
            break;
        }
    
    return trim(str);
}

/*

const string label_expression = R"(^\(([a-zA-z_\.\$:][a-zA-z_\.\$:0-9]*)\)$)";

void Parser::parseLabel(const string &s)
{
    regex e{label_expression};
    smatch matches;
    
    regex_match(s, matches, e);
    
    if(matches.size() > 1)
        symbol = matches[1];
    else
    {
        type = CommandType::Unknown;
        throw runtime_error("Could not parse L-command. Check syntax.");
    }
}

const string address_expression = R"(^@(\d+|[a-zA-z_\.\$:][a-zA-z_\.\$:0-9]*)$)";

void Parser::parseAddress(const string &s)
{
    regex e{address_expression};
    smatch matches;
    
    regex_match(s, matches, e);
    
    if(matches.size() > 1)
        symbol = matches[1];
    else
    {
        type = CommandType::Unknown;
        throw runtime_error("Could not parse A-command. Check syntax.");
    }
}

const string computation_expession = R"(^(?:([AMD]{1,3})=)?(0|-?1|[\-!]?[ADM]|[ADM][\+\-&|](?:1|[ADM]))(?:;([A-Z]{3}))?$)";

void Parser::parseComputation(const string &s)
{
    regex e{computation_expession};
    smatch matches;
    
    regex_match(s, matches, e);
    
    if(matches.size() > 3)
    {
        dest = matches[1];
        comp = matches[2];
        jump = matches[3];
    }
    
    else
    {
        type = CommandType::Unknown;
        throw runtime_error("Could not parse C-command. Check syntax.");
    }
}

*/
