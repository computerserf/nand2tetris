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

bool isFlow(const string &s)
{
	return (s == "label" || s == "goto" || s == "if-goto");
}

bool isFunctionCall(const string &s)
{
	return (s == "function" || s == "call" || s == "RETURN");
}

bool validLabel(const string &s)
{
    static const std::string command_expresssion = R"(^(\s*\D[\w\:_\.]+)$)";
    static const regex e{command_expresssion};
    
    smatch matches;
    regex_match(s, matches, e);
    
    return matches.size() > 1;
}

void Parser::parseCommmand(const string &command)
{
    static const std::string command_expresssion = R"(^(\D[\w\:_\.]+)(\s*(?:\D[\w\:_\.]+|\d+))(\s*(?:\D[\w\:_\.]+|\d+))?$)";
    static const regex e{command_expresssion};
    
    smatch matches;
    regex_match(command, matches, e);
    
    // cout << command << endl;
    
    if(matches.size() > 1)
    {
        // match found; parse command
        arg1 = trim(matches[2]);
        arg2 = trim(matches[3]);
        
        if(isArithmetic(matches[1]))
        {
            if(matches[2] != "")
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
            if(matches[3] == "")
            {
                type = CommandType::Unknown;
                throw runtime_error("Could not parse memory access command. Check syntax.");
            }
            else
            {
                if(matches[1] == "push")
                    type = CommandType::Push;
                else
                    type = CommandType::Pop;
            }
            
        }
        else if(isFlow(matches[1]))
        {
            if(matches[3] != "" || !validLabel(matches[2]))
            {
                type = CommandType::Unknown;
                throw runtime_error("Could not parse flow command. Check syntax.");
            }
            else
            {
                if(matches[1] == "label")
                    type = CommandType::Label;
                else if(matches[1] == "goto")
                    type = CommandType::Goto;
                else
                    type = CommandType::If;
            }
        }
        else if(isFunctionCall(matches[1]))
        {
            if(matches[1] == "function" && validLabel(matches[2]))
                type = CommandType::Function;
            else if(matches[1] == "call" && validLabel(matches[2]))
                type = CommandType::Call;
            else if(matches[1] == "return" && matches[2] == "")
                type = CommandType::Return;
            else
            {
                type = CommandType::Unknown;
                throw runtime_error("Could not parse function-call command. Check syntax.");
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
