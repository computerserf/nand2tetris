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

/* Interface of the Parser module.
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <istream>

enum class CommandType
{
    A,
    C,
    L,
    Unknown
};

// Refer to the API documentation in chapter 6
class Parser
{
public:
    Parser(std::istream &inputStream);
    bool hasMoreCommands();
    void advance();
    CommandType getCommandType(); 
    std::string getSymbol();
    std::string getDest();
    std::string getComp();
    std::string getJump();
    int getLineNumber();
    
private:
    std::istream &input;
    CommandType type;
    int line_no;
    std::string symbol;
    std::string dest;
    std::string comp;
    std::string jump;
    
    void skipComments();
    void parseLabel(const std::string &s);
    void parseAddress(const std::string &s);
    void parseComputation(const std::string &s);
    std::string stripLine(const std::string &line);
};

#endif // PARSER_H
