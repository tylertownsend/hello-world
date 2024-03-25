cmake_minimum_required(VERSION 3.10)

# Main project name
project(triangle)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for each module
add_subdirectory(api)
add_subdirectory(plugin)
add_subdirectory(app)