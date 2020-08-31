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

/* Implementation of the Code module
 */

#include "Code.h"

#include <unordered_map>
#include <stdexcept>

using namespace std;

static unordered_map<string, string> destMap;
static unordered_map<string, string> compMap;
static unordered_map<string, string> jumpMap;

void Code::init()
{
    // initialize dest map
    destMap[""] = "000";
    destMap["M"] = "001";
    destMap["D"] = "010";
    destMap["MD"] = "011";
    destMap["A"] = "100";
    destMap["AM"] = "101";
    destMap["AD"] = "110";
    destMap["AMD"] = "111";
    
    // initialize comp map
    compMap["0"] = "0101010";
    compMap["1"] = "0111111";
    compMap["-1"] = "0111010";
    compMap["D"] = "0001100";
    compMap["A"] = "0110000";
    compMap["!D"] = "0001101";
    compMap["!A"] = "0110001";
    compMap["-D"] = "0001111";
    compMap["-A"] = "0110011";
    compMap["D+1"] = "0011111";
    compMap["A+1"] = "0110111";
    compMap["D-1"] = "0001110";
    compMap["A-1"] = "0110010";
    compMap["D+A"] = "0000010";
    compMap["D-A"] = "0010011";
    compMap["A-D"] = "00000111";
    compMap["D&A"] = "0000000";
    compMap["D|A"] = "0010101";
    compMap["M"] = "1110000";
    compMap["!M"] = "1110001";
    compMap["-M"] = "1110011";
    compMap["M+1"] = "1110111";
    compMap["M-1"] = "1110010";
    compMap["D+M"] = "1000010";
    compMap["D-M"] = "1010011";
    compMap["M-D"] = "1000111";
    compMap["D&M"] = "1000000";
    compMap["D|M"] = "1010101";
    
    // initialize jump map
    jumpMap[""] = "000";
    jumpMap["JGT"] = "001";
    jumpMap["JEQ"] = "010";
    jumpMap["JGE"] = "011";
    jumpMap["JLT"] = "100";
    jumpMap["JNE"] = "101";
    jumpMap["JLE"] = "110";
    jumpMap["JMP"] = "111";
}

string translate(const string &s, unordered_map<string, string> &map)
{
    auto in = map.find(s);
    
    if(in == map.end())
        throw runtime_error("Could not translate '" + s + "'. Invalid option.");
    else
        return map[s];
}

string Code::dest(const string &s)
{
    return translate(s, destMap);
}

string Code::comp(const string &s)
{
    return translate(s, compMap);
}

string Code::jump(const string &s)
{
    return translate(s, jumpMap);
}
