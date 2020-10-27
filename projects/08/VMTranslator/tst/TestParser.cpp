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

#include <sstream>
#include <stdexcept>

#include "../src/Parser.h"

using namespace std;

// has a non comment/whitespace character
TEST(ParserTest, TestHasNonWSOrComments_hasMorCommands)
{
    istringstream input("\t\t//\n//\n/");
    Parser p(input);
    ASSERT_TRUE(p.hasMoreCommands());
}

// has a only comment/whitespace characters
TEST(ParserTest, TestHasOnlyWSOrComments_hasMoreCommands)
{
    istringstream input("\t\t//\n//\t\n");
    Parser p(input);
    ASSERT_FALSE(p.hasMoreCommands());
}

// stream is empty
TEST(ParserTest, TestEmpty_hasMoreCommands)
{
    istringstream input("");
    Parser p(input);
    ASSERT_FALSE(p.hasMoreCommands());
}

// Unknown, "", "" by default
TEST(ParserTest, TestDefault_advance)
{
    istringstream input("");
    Parser p(input);
    ASSERT_EQ(p.getCommandType(), CommandType::Unknown);
    ASSERT_EQ(p.getArg1(), "");
    ASSERT_EQ(p.getArg2(), "");
}


// special character invalid command
TEST(ParserTest, TestSpecialCharacterInvalidCommand_advance)
{
    istringstream input("eulo.1 :s_e4. tp");
    Parser p(input);
    ASSERT_THROW(p.advance(), runtime_error);
    ASSERT_EQ(p.getCommandType(), CommandType::Unknown);
    ASSERT_EQ(p.getArg1(), ":s_e4.");
    ASSERT_EQ(p.getArg2(), "tp");
}

// without special character invalid command
TEST(ParserTest, TestWithoutSpecialCharacterInvalidCommand_advance)
{
    istringstream input("dedf a b");
    Parser p(input);
    ASSERT_THROW(p.advance(), runtime_error);
    ASSERT_EQ(p.getCommandType(), CommandType::Unknown);
    ASSERT_EQ(p.getArg1(), "a");
    ASSERT_EQ(p.getArg2(), "b");
}

// valid command with 1 argument
TEST(ParserTest, TestValid1Command_advance)
{
    istringstream input("goto e4");
    Parser p(input);
    p.advance();
    ASSERT_EQ(p.getCommandType(), CommandType::Goto);
    ASSERT_EQ(p.getArg1(), "e4");
    ASSERT_EQ(p.getArg2(), "");
}

// 1 argument for a command with 2 arguments
TEST(ParserTest, Test1Command2Argument_advance)
{
    istringstream input("pop 10");
    Parser p(input);
    ASSERT_THROW(p.advance(), runtime_error);
    ASSERT_EQ(p.getCommandType(), CommandType::Unknown);
    ASSERT_EQ(p.getArg1(), "10");
    ASSERT_EQ(p.getArg2(), "");
}

// valid command with 2 argumentss
TEST(ParserTest, TestValid2Command_advance)
{
    istringstream input("push static 5");
    Parser p(input);
    p.advance();
    ASSERT_EQ(p.getCommandType(), CommandType::Push);
    ASSERT_EQ(p.getArg1(), "static");
    ASSERT_EQ(p.getArg2(), "5");
}

// more than 2 argument command
TEST(ParserTest, Test3Command_advance)
{
    istringstream input("pop static 5 e_");
    Parser p(input);
    ASSERT_THROW(p.advance(), runtime_error);
    ASSERT_EQ(p.getCommandType(), CommandType::Unknown);
    ASSERT_EQ(p.getArg1(), "");
    ASSERT_EQ(p.getArg2(), "");
}

// 1 by default
TEST(ParserTest, TestDefault_getLineNumber)
{
    istringstream input("");
    Parser p(input);
    int lineNumber = p.getLineNumber();
    ASSERT_EQ(lineNumber, 1);
}

// correct line number after skipping comments and white space
TEST(ParserTest, TestOnlyCommentsAndWS_getLineNumber)
{
    istringstream input("//\n\t\t\n//\n");
    Parser p(input);
    p.hasMoreCommands();
    int lineNumber = p.getLineNumber();
    ASSERT_EQ(lineNumber, 4);
}

// correct line number after skipping whitespace and characters and encountering a valid character
TEST(ParserTest, TestCommentsWSAndInput_getLineNumber)
{
    istringstream input("//\n\t@\t\n//\n");
    Parser p(input);
    p.hasMoreCommands();
    int lineNumber = p.getLineNumber();
    ASSERT_EQ(lineNumber, 2);
}
