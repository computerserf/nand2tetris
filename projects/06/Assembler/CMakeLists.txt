cmake_minimum_required (VERSION 3.8)

project ("Assembler")

# Add source to this project's executable.
add_executable (Assembler "src/Assembler.cpp" "src/Code.cpp" "src/Parser.cpp" "src/SymbolTable.cpp" "src/Utility.cpp")

# Enable C++11
target_compile_features(Assembler PUBLIC cxx_std_11)
set_target_properties(Assembler PROPERTIES CXX_EXTENSIONS OFF)
