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

 /* Impementation of the CodeWriter module.
  */

#include "CodeWriter.h"

#include <stdexcept>

using namespace std;

const string TEMP{"R5"};

CodeWriter::CodeWriter(ostream& outputStream) : out{outputStream}
{
}

void CodeWriter::setFilename(string f)
{
	filename = f;
	branchCount = 0;

	out << endl << "// " << filename << ":" << endl;
}

void CodeWriter::writeArithmetic(string command)
{
	if(command == "add")
	{
		out <<
			"\t@SP\n"
			"\tA=M-1\n"
			"\tD=M\n"
			"\tA=A-1\n"
			"\tM=M+D\n"
			"\t@SP\n"
			"\tM=M-1\n";
	}
	else if(command == "sub")
	{
		out <<
			"\t@SP\n"
			"\tA=M-1\n"
			"\tD=M\n"
			"\tA=A-1\n"
			"\tM=M-D\n"
			"\t@SP\n"
			"\tM=M-1\n";
	}
	else if(command == "neg")
	{
		out <<
			"\t@SP\n"
			"\tA=M\n"
			"\tM=-M\n";
	}
	else if (command == "eq")
	{
		out <<
			"\t@SP\n"
			"\tA=M-1\n"
			"\tD=M\n"
			"\tA=A-1\n"
			"\tD=M-D\n"
			"\t@" + branchLabel() + "T\n"
			"\tD;JEQ\n"
			"\tM=-1\n"
			"\t@" + branchLabel() + "E\n"
			"\t0;JMP\n"
			"(" + branchLabel() + "T)\n"
			"\tM=0\n"
			"(" + branchLabel() + "E)\n"
			"\t@SP\n"
			"\tM=M-1\n";

		branchCount++;
	}
	else if (command == "gt")
	{
		out <<
			"\t@SP\n"
			"\tA=M-1\n"
			"\tD=M\n"
			"\tA=A-1\n"
			"\tD=M-D\n"
			"\t@" + branchLabel() + "T\n"
			"\tD;JGT\n"
			"\tM=-1\n"
			"\t@" + branchLabel() + "E\n"
			"\t0;JMP\n"
			"(" + branchLabel() + "T)\n"
			"\tM=0\n"
			"(" + branchLabel() + "E)\n"
			"\t@SP\n"
			"\tM=M-1\n";

		branchCount++;
	}
	else if (command == "lt")
	{
		out <<
			"\t@SP\n"
			"\tA=M-1\n"
			"\tD=M\n"
			"\tA=A-1\n"
			"\tD=M-D\n"
			"\t@" + branchLabel() + "T\n"
			"\tD;JLT\n"
			"\tM=-1\n"
			"\t@" + branchLabel() + "E\n"
			"\t0;JMP\n"
			"(" + branchLabel() + "T)\n"
			"\tM=0\n"
			"(" + branchLabel() + "E)\n"
			"\t@SP\n"
			"\tM=M-1\n";

		branchCount++;
	}
	else if (command == "and")
	{
		out <<
			"\t@SP\n"
			"\tA=M-1\n"
			"\tD=M\n"
			"\tA=A-1\n"
			"\tM=M&D\n"
			"\t@SP\n"
			"\tM=M-1\n";
	}
	else if (command == "or")
	{
	out <<
		"\t@SP\n"
		"\tA=M-1\n"
		"\tD=M\n"
		"\tA=A-1\n"
		"\tM=M|D\n"
		"\t@SP\n"
		"\tM=M-1\n";
	}
	else if (command == "not")
	{
	out <<
		"\t@SP\n"
		"\tA=M\n"
		"\tM=!M\n";
	}
	else
		throw runtime_error("Arithmetic command '" + command + "' not valid command");
}

void CodeWriter::writePushPop(CommandType type, std::string segment, int index)
{
    if(index < 0 || index > 32767)
        throw runtime_error("Push/pop command: " + to_string(index) + " not a valid indes");
    
    if(type == CommandType::Push)
    {
        if(segment == "constant")
        {
            out <<
                "\t@" + to_string(index) + "\n"
                "\tD=A\n"
                "\t@SP\n"
                "\tA=M\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n";
        }
        else if(segment == "local")
        {
            out <<
                "\t@" + to_string(index) + "\n"
                "\tD=A\n"
                "\t@LCL\n"
                "\tA=M\n"
                "\tA=A+D\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tA=M\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n";
        }
        else if(segment == "argument")
        {
            out <<
                "\t@" + to_string(index) + "\n"
                "\tD=A\n"
                "\t@ARG\n"
                "\tA=M\n"
                "\tA=A+D\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tA=M\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n";
        }
        else if(segment == "this")
        {
            out <<
                "\t@" + to_string(index) + "\n"
                "\tD=A\n"
                "\t@THIS\n"
                "\tA=M\n"
                "\tA=A+D\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tA=M\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n";
        }
        else if(segment == "that")
        {
            out <<
                "\t@" + to_string(index) + "\n"
                "\tD=A\n"
                "\t@THAT\n"
                "\tA=M\n"
                "\tA=A+D\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tA=M\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n";
        }
        else if(segment == "pointer")
        {
            if(index > 1)
                throw runtime_error("Push command: 'pointer' segment index must be betweeen 0 and 1");
            
            if(index == 0)
            {
                out <<
                    "\t@THIS\n"
                    "\tD=M\n"
                    "\t@SP\n"
                    "\tA=M\n"
                    "\tM=D\n"
                    "\t@SP\n"
                    "\tM=M+1\n";
            }
            else
            {
                out <<
                    "\t@THAT\n"
                    "\tD=M\n"
                    "\t@SP\n"
                    "\tA=M\n"
                    "\tM=D\n"
                    "\t@SP\n"
                    "\tM=M+1\n";
            }
        }
        else if(segment == "temp")
        {
            if(index > 7)
                throw runtime_error("Push command: 'temp' segment index must be betweeen 0-7");
            
            out <<
                "\t@" + to_string(index) + "\n"
                "\tD=A\n"
                "\t@" + TEMP + "\n"
                "\tA=M\n"
                "\tA=A+D\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tA=M\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n";
        }
        else if(segment == "static")
        {
            if(index > 239)
                throw runtime_error("Push command: 'static' segment index must be betweeen 0-239");
            
            out <<
                "\t@" + file_prefix() + "." + to_string(index) + "\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tA=M\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n"
        }
        else
            throw runtime_error("Push command: '" + segment + "' not a valid segment");
    }
    else if(type == CommandType::Pop)
    {
        if(segment == "constant")
        {
            out <<
                "\t@SP\n"
                "\tM=M-1\n";
        }
        else if(segment == "local")
        {
            out <<
                "\t@SP\n"
                "\tA=M-1\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tM=M-1\n"
                "\t@R13\n"
                "\tM=D\n"
                "\t@" + to_string(index) + "\n"
                "\tD=M\n"
                "\t@LCL\n"
                "\tA=M\n"
                "\tD=A+D\n"
                "\t@R14\n"
                "\tM=D\n"
                "\t@R13\n"
                "\tD=M\n"
                "\t@R14\n"
                "\tA=M\n"
                "\tM=D\n";
        }
        else if(segment == "argument")
        {
            out <<
                "\t@SP\n"
                "\tA=M-1\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tM=M-1\n"
                "\t@R13\n"
                "\tM=D\n"
                "\t@" + to_string(index) + "\n"
                "\tD=M\n"
                "\t@ARG\n"
                "\tA=M\n"
                "\tD=A+D\n"
                "\t@R14\n"
                "\tM=D\n"
                "\t@R13\n"
                "\tD=M\n"
                "\t@R14\n"
                "\tA=M\n"
                "\tM=D\n";
        }
        else if(segment == "this")
        {
            out <<
                "\t@SP\n"
                "\tA=M-1\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tM=M-1\n"
                "\t@R13\n"
                "\tM=D\n"
                "\t@" + to_string(index) + "\n"
                "\tD=M\n"
                "\t@THIS\n"
                "\tA=M\n"
                "\tD=A+D\n"
                "\t@R14\n"
                "\tM=D\n"
                "\t@R13\n"
                "\tD=M\n"
                "\t@R14\n"
                "\tA=M\n"
                "\tM=D\n";
        }
        else if(segment == "that")
        {
            out <<
                "\t@SP\n"
                "\tA=M-1\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tM=M-1\n"
                "\t@R13\n"
                "\tM=D\n"
                "\t@" + to_string(index) + "\n"
                "\tD=M\n"
                "\t@THAT\n"
                "\tA=M\n"
                "\tD=A+D\n"
                "\t@R14\n"
                "\tM=D\n"
                "\t@R13\n"
                "\tD=M\n"
                "\t@R14\n"
                "\tA=M\n"
                "\tM=D\n";
        }
        else if(segment == "pointer")
        {
            if(index > 1)
                throw runtime_error("Pop command: 'pointer' segment index must be betweeen 0 and 1");
            
            if(index == 0)
            {
                out <<
                    "\t@SP\n"
                    "\tA=M-1\n"
                    "\tD=M\t"
                    "\t@THIS\n"
                    "\tM=D\n"
                    "\t@SP\n"
                    "\tM=M-1\n";
            }
            else
            {
                out <<
                    "\t@SP\n"
                    "\tA=M-1\n"
                    "\tD=M\t"
                    "\t@THAT\n"
                    "\tM=D\n"
                    "\t@SP\n"
                    "\tM=M-1\n";
            }
        }
        else if(segment == "temp")
        {
            if(index > 7)
                throw runtime_error("Pop command: 'temp' segment index must be betweeen 0-7");
            
            out <<
                "\t@SP\n"
                "\tA=M-1\n"
                "\tD=M\n"
                "\t@SP\n"
                "\tM=M-1\n"
                "\t@R13\n"
                "\tM=D\n"
                "\t@" + to_string(index) + "\n"
                "\tD=M\n"
                "\t@" + TEMP + "\n"
                "\tA=M\n"
                "\tD=A+D\n"
                "\t@R14\n"
                "\tM=D\n"
                "\t@R13\n"
                "\tD=M\n"
                "\t@R14\n"
                "\tA=M\n"
                "\tM=D\n";
        }
        else if(segment == "static")
        {
            if(index > 239)
                throw runtime_error("Pop command: 'static' segment index must be betweeen 0-239");
            
            out <<
                "\t@SP\n"
                "\tA=M-1\n"
                "\tD=M\n"
                "\t@" + file_prefix() + "." + to_string(index) + "\n"
                "\tM=D\n"
                "\t@SP\n"
                "\tM=M+1\n"
        }
        else
            throw runtime_error("Pop command: '" + segment + "' not a valid segment");
    }
    else
        throw runtime_error("Push/pop command: invalid command type");
}
