#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "diagnostic_configuration.h"

class IDiagnostic {
public:
    virtual ~IDiagnostic() {}
    virtual void check(const DiagnosticConfig& config) = 0;
    virtual std::string getName() = 0;
    virtual std::vector<std::string> getDependencies() const = 0;
};