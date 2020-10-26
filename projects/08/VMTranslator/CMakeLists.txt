cmake_minimum_required (VERSION 3.8)

project ("VMTranslator")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests "tst/TestParser.cpp" "src/Parser.cpp")
target_link_libraries(runTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

# Find Boost
find_package(Boost COMPONENTS filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Add source to this project's executable.
add_executable (VMTranslator "src/Translator.cpp" "src/Parser.cpp" "src/CodeWriter.cpp")

# Enable C++11
target_compile_features(VMTranslator PUBLIC cxx_std_11)
set_target_properties(VMTranslator PROPERTIES CXX_EXTENSIONS OFF)

# Link Boost
target_link_libraries(VMTranslator LINK_PUBLIC ${Boost_LIBRARIES})
