cmake_minimum_required (VERSION 3.8)

project ("Translator")


# Find Boost
find_package(Boost COMPONENTS filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Add source to this project's executable.
add_executable (Translator "src/Translator.cpp" "src/Parser.cpp" "src/CodeWriter.cpp")

# Enable C++11
target_compile_features(Translator PUBLIC cxx_std_11)
set_target_properties(Translator PROPERTIES CXX_EXTENSIONS OFF)

# Link Boost
target_link_libraries(Translator LINK_PUBLIC ${Boost_LIBRARIES})
