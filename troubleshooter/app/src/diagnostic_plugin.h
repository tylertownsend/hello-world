#pragma once
#include <dlfcn.h>
#include <iostream>
#include <string>

#include <troubleshooter/diagnostic.h>

class DiagnosticPlugin : public IDiagnostic {
private:
    void* handle;
    IDiagnostic* (*create)();
    void (*destroy)(IDiagnostic*);

    std::string name;
    IDiagnostic* plugin;


public:
    DiagnosticPlugin(const std::string& path) : handle(nullptr), create(nullptr), destroy(nullptr) {
        handle = dlopen(path.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Cannot load library: " << dlerror() << '\n';
            return;
        }

        create = (IDiagnostic* (*)())dlsym(handle, "create");
        destroy = (void (*)(IDiagnostic*))dlsym(handle, "destroy");

        if (!create || !destroy) {
            std::cerr << "Cannot load symbols: " << dlerror() << '\n';
        } else {
          std::cout << "Created Plugin\n";
            plugin = create();
            name = plugin->getName();
        }
    }

    std::string getName() override {
        return name;
    }

    std::vector<std::string> getDependencies() const override {
        // This could potentially invoke a method on the plugin to get dependencies,
        // or dependencies could be managed externally based on the plugin's name.
        return {};
    }

    void check(const DiagnosticConfig& config) override {
        if (!create || !destroy) {
            std::cerr << "Plugin not properly loaded, unable to check." << std::endl;
            return;
        }

        if (config.enabled) {
            plugin->check(config);
        }
    }

    ~DiagnosticPlugin() {
      if (destroy) {
        destroy(plugin);
        std::cout << "Destroyed Plugin\n";
      }

      if (handle) {
        std::cout << "Closing Handle\n";
          dlclose(handle);
      }
    }
};
