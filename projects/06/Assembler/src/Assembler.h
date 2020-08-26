/* Interface of the facade controller of the assembler
*/

#ifndef _ASSEMBLER_H_
#define _ASSEMBLER_H_

#include <vector>
#include <string>

class Assembler
{
public:
    
    // constructs the assembler by passing in command line arguments as configuration
    Assembler(std::vector<std::string> arguments);
    
    // runs the assember
    void run();

private:
    
    void parseFilname(std::string);
    void doFirstPass();
    void doSecondPass();
    
    std::string inputPath;
    std::string outputPath;
};

#endif
