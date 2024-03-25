#include <dirent.h>  // For directory operations
#include <string>
#include <iostream>
#include <memory>

#include "diagnostic_system.h"
#include "diagnostic_plugin.h"

class PluginLoader {
private:
    std::string pluginDirectory;

public:
    PluginLoader(const std::string& pluginDirectory)
        : pluginDirectory(pluginDirectory) {
    }

    void loadPlugins(DiagnosticSystem& diagnosticSystem) {
        DIR* dir = opendir(pluginDirectory.c_str());
        if (dir == nullptr) {
            std::cerr << "Failed to open plugin directory: " << pluginDirectory << std::endl;
            return;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string filename = entry->d_name;
            // Assuming the plugin files have a specific extension, e.g., .so or .dll
            if (filename.find(".so") != std::string::npos || filename.find(".dll") != std::string::npos) {
                std::string fullPath = pluginDirectory + "/" + filename;
                try {
                    // Load the plugin and add it to the diagnostic system
                    diagnosticSystem.add(std::make_unique<DiagnosticPlugin>(fullPath));
                } catch (const std::exception& e) {
                    std::cerr << "Failed to load plugin: " << fullPath << " with error: " << e.what() << std::endl;
                }
            }
        }

        closedir(dir);
    }
};