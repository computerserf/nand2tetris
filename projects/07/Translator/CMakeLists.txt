cmake_minimum_required (VERSION 3.8)

project ("Translator")

# Add source to this project's executable.
add_executable (Translator "src/Translator.cpp" "src/Parser.cpp" "src/CodeWriter.cpp")

# Enable C++11
target_compile_features(Translator PUBLIC cxx_std_11)
set_target_properties(Translator PROPERTIES CXX_EXTENSIONS OFF)
