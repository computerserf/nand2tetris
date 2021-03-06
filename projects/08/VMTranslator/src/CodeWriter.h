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

 /* Interface of the CodeWriter module.
  */

#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include "Common.h"

#include <string>
#include <ostream>

// Refer to the API documentation in chapters 7, 8
class CodeWriter
{
public:
	CodeWriter(std::ostream &outputStream);
	void setFilename(std::string filename);
    void writeInit();
    void writeLabel(std::string label);
    void writeGoto(std::string label);
    void writeIf(std::string label);
    void writeCall(std::string functionName, int numArgs);
    void writeFunction(std::string functionName, int numArgs);
    void writeReturn();
	void writeArithmetic(std::string command);
	void writePushPop(CommandType type, std::string segment, int index);
    void writeAnnotation(CommandType type, std::string argument1, std::string argument2);
    
protected:
    void setFunctionName(std::string name);
    std::string getFunctionName();

private:
	std::ostream &out;
	std::string prefix;
    std::string function_name;
	unsigned int branchCount;
    unsigned int returnCount;
    
    inline std::string nextReturnLabel()
    {
        return "ret_" + std::to_string(returnCount++);
    }

	inline std::string branchLabel()
	{
		return prefix + ".vm" + "$" + std::to_string(branchCount);
	}
	
	inline std::string file_prefix()
    {
        return prefix;
    }
};

#endif // CODE_WRITER_H
