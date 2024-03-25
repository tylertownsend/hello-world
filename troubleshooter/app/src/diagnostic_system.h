#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>

#include <troubleshooter/diagnostic.h>

#include "config_loader.h"


class DiagnosticSystem {
private:
    std::vector<std::unique_ptr<IDiagnostic>> checks;
    std::map<std::string, bool> completedChecks;

public:
    void add(std::unique_ptr<IDiagnostic> check) {
      checks.push_back(std::move(check));
    }

    void runDiagnostics() {
      ConfigLoader loader;
      auto configs = loader.loadConfig("diagnostics_config.json");
      for (auto& config : configs) {
        // Find the corresponding health check and run it with the loaded config
        for (auto& check : checks) {
          bool match = config.name == check->getName();
          if (match) {
              runCheckWithDependencies(check.get(), config);
              break; // Assuming each config corresponds to only one check, we can break after finding it
          }
        }
      }
    }

private:
    void runCheckWithDependencies(IDiagnostic* check, const DiagnosticConfig& config) {
        for (const auto& dependency : check->getDependencies()) {
            if (completedChecks.find(dependency) == completedChecks.end() ||
                !completedChecks[dependency]) {
                // Dependency not met, you can handle this case as needed
                std::cout << "Dependency " << dependency << " not met." << std::endl;
                return;
            }
        }

        check->check(config);
        completedChecks[typeid(*check).name()] = true;
    }
};