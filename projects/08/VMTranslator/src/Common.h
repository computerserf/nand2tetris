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

/* Contains all the common declarations of the program
 */

#ifndef COMMON_H
#define COMMON_H

enum class CommandType
{
    Arithmetic,
    Push,
    Pop,
    Label,
    Goto,
    If,
    Function,
    Return,
    Call,
    Unknown
};

#include <algorithm>
#include <cctype>
#include <string>
#include <regex>
#include <bitset>

/* taken from David G's answer: https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 */
inline std::string trim(const std::string &s)
{
   auto wsfront = find_if_not(s.begin(),s.end(), [](int c){return std::isspace(c);});
   auto wsback = find_if_not(s.rbegin(),s.rend(), [](int c){return std::isspace(c);}).base();
   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

inline std::string removeWhitespace(const std::string &str)
{
    return std::regex_replace(str, std::regex{"\\s+"}, "");
}

// Converts a number string to a bitstring of length 15
inline std::string ntobs(std::string n)
{
    return std::bitset<15>(stoi(n)).to_string();
}

// https://stackoverflow.com/questions/29506426/get-google-test-exception-throw-message
inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}


#endif // COMMON_H
