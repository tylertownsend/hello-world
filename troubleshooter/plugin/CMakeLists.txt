project(plugin)

# Create the plugin executable or library
add_library(plugin SHARED src/plugin.cpp)

# Link with the troubleshooter_api
target_link_libraries(plugin PRIVATE troubleshooter_api)