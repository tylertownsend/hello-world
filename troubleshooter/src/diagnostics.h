#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include <troubleshooter/diagnostic.h>
#include <troubleshooter/diagnostic_configuration.h>

class ResourceMonitor : public IDiagnostic {
public:
    void check(const DiagnosticConfig& config) override {
        // Perform resource usage checks
        std::cout << "Checking system resources..." << std::endl;
    }
    std::string getName() override {
        return "ResourceMonitor";
    }
    std::vector<std::string> getDependencies() const override {
        return {};  // No dependencies for this example
    }
};

class PerformanceMonitor : public IDiagnostic {
public:
    void check(const DiagnosticConfig& config) override {
        // Measure response times
        std::cout << "Monitoring performance..." << std::endl;
    }

    std::string getName() override {
        return "PerformanceMonitor";
    }

    std::vector<std::string> getDependencies() const override {
        return {};  // No dependencies for this example
    }
};

class DependencyChecker : public IDiagnostic {
public:
    void check(const DiagnosticConfig& config) override {
        // Check external dependencies
        std::cout << "Checking external dependencies..." << std::endl;
    }

    std::string getName() override {
        return "DependencyChecker";
    }

    std::vector<std::string> getDependencies() const override {
        return {};  // No dependencies for this example
    }
};

class ConfigurationChecker : public IDiagnostic {
public:
    void check(const DiagnosticConfig& config) override {
        // Validate configuration settings
        std::cout << "Validating configuration..." << std::endl;
    }
    std::string getName() override {
        return "ConfigurationChecker";
    }
    std::vector<std::string> getDependencies() const override {
        return {};  // No dependencies for this example
    }
};