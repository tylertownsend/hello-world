#include <memory>
#include <vector>

#include "diagnostics.h"
#include "diagnostic_system.h"
#include "plugin_loader.h"

int main() {
    DiagnosticSystem DiagnosticSystem;

    DiagnosticSystem.add(std::make_unique<ResourceMonitor>());
    DiagnosticSystem.add(std::make_unique<PerformanceMonitor>());
    DiagnosticSystem.add(std::make_unique<DependencyChecker>());
    DiagnosticSystem.add(std::make_unique<ConfigurationChecker>());

    PluginLoader pluginLoader("./plugins");
    pluginLoader.loadPlugins(DiagnosticSystem);

    DiagnosticSystem.runDiagnostics();
    return 0;
}