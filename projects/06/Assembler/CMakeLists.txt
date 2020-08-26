cmake_minimum_required (VERSION 3.8)

project ("Assembler")

# Add source to this project's executable.
add_executable (Assembler "src/Assembler.cpp" "src/Code.cpp" "src/Parser.cpp" "src/SymbolTable.cpp")

# TODO: Add tests and install targets if needed.
