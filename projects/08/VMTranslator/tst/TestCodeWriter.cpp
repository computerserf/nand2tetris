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

#include <gtest/gtest.h>

#include "../src/CodeWriter.h"

#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

// https://stackoverflow.com/questions/6163611/compare-two-files
bool compareFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

using namespace std;

class CodeWriterWrapper : public CodeWriter
{
public:
    
   CodeWriterWrapper(ostream &outputStream) : CodeWriter(outputStream)
   {
   }
   
   void setFunctionName(string name)
   {
       CodeWriter::setFunctionName(name);
   }
};

// valid output
TEST(CodeWriterTest, TestValidOutput_writeInit)
{
    ofstream out("CodeWriter/writeInit_out");
    CodeWriterWrapper cw(out);
    cw.writeInit();
    out.close();
    ASSERT_TRUE(compareFiles("CodeWriter/writeInit_out", "CodeWriter/writeInit_expected"));
}

// valid output
TEST(CodeWriterTest, TestValidOutput_writeLabel)
{
    ofstream out("CodeWriter/writeLabel_out");
    CodeWriterWrapper cw(out);
    cw.setFunctionName("_");
    cw.writeAnnotation(CommandType::Label, "my_label", "");
    cw.writeLabel("my_label");
    out.close();
    ASSERT_TRUE(compareFiles("CodeWriter/writeLabel_out", "CodeWriter/writeLabel_expected"));
}

// valid output
TEST(CodeWriterTest, TestValidOutput_writeGoto)
{
    ofstream out("CodeWriter/writeGoto_out");
    CodeWriterWrapper cw(out);
    cw.setFunctionName("_");
    cw.writeAnnotation(CommandType::Goto, "my_label", "");
    cw.writeGoto("my_label");
    out.close();
    ASSERT_TRUE(compareFiles("CodeWriter/writeGoto_out", "CodeWriter/writeGoto_expected"));
}

// valid output
TEST(CodeWriterTest, TestValidOutput_writeIf)
{
    ofstream out("CodeWriter/writeIf_out");
    CodeWriterWrapper cw(out);
    cw.setFunctionName("_");
    cw.writeAnnotation(CommandType::If, "my_label", "");
    cw.writeIf("my_label");
    out.close();
    ASSERT_TRUE(compareFiles("CodeWriter/writeIf_out", "CodeWriter/writeIf_expected"));
}
