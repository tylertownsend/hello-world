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
    # ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# If the app directly uses the API, link it as well
target_link_libraries(main PRIVATE troubleshooter_api)

# Link against the dl library to resolve dlopen, dlclose, etc.
target_link_libraries(main PRIVATE ${CMAKE_DL_LIBS})