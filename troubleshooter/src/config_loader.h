#pragma once
#include <vector>

#include <troubleshooter/diagnostic_configuration.h>

class ConfigLoader {
public:
    std::vector<DiagnosticConfig> loadConfig(const std::string& configFile) {
        // Load and parse the configuration file (e.g., JSON, XML, etc.)
        // and populate a vector of DiagnosticConfig objects.
        std::map<std::string, std::string> parameters = {
            {"threshold", "80"},
            {"interval", "5"}
        };
        std::vector<DiagnosticConfig> configs {
            DiagnosticConfig {"ResourceMonitor",      true, parameters },
            DiagnosticConfig {"PerformanceMonitor",   true, parameters },
            DiagnosticConfig {"DependencyChecker",    true, parameters },
            DiagnosticConfig {"ConfigurationChecker", true, parameters }
        };
        // Logic to load and parse the configuration file goes here
        return configs;
    }
};
