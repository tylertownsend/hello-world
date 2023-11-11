cmake_minimum_required(VERSION 3.10)
project(SimpleLang)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the include directory for the Bison-generated header file
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find required Bison and Flex packages
find_package(BISON)
find_package(FLEX)

# Define the Bison and Flex input and output files
BISON_TARGET(MyParser src/parser/simple_lang.y ${CMAKE_CURRENT_BINARY_DIR}/simple_lang.tab.c)
FLEX_TARGET(MyScanner src/lexer/simple_lang.l  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

# Add dependency for the parser to the scanner
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

# Include the binary directory to find the parser.tab.h file
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Add main file
add_executable(SimpleLang src/main.cpp ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS})

# If there are any libraries that we need to link against, we would do so here
# target_link_libraries(SimpleLang ${SomeLibrary})
