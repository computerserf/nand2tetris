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

/* Interface of the facade controller of the assembler
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <vector>
#include <string>

class Assembler
{
public:
    
    // constructs the assembler by passing in command line arguments as configuration
    Assembler(const std::vector<std::string> &arguments);
    
    // runs the assember
    void run();

private:
    
    std::string parseFilename(std::string);
    void doFirstPass();
    void doSecondPass();
    
    std::string inputFile;
    std::string outputFile;
};

#endif // ASSEMBLER_H
