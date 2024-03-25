#pragma once

#include <string>
#include <map>

struct DiagnosticConfig {
    std::string name;
    bool enabled;
    std::map<std::string, std::string> parameters;
};