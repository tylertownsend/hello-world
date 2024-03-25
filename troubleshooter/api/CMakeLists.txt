project(troubleshooter_api)

# Create a library target for the API
add_library(troubleshooter_api INTERFACE)

# Specify include directories for this target
target_include_directories(troubleshooter_api INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
