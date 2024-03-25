cmake_minimum_required(VERSION 3.10)

project(troubleshooter_application)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(main
    src/main.cpp
)

# Include directories
target_include_directories(main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add test target
# enable_testing()
# add_subdirectory(tests)