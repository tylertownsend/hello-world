#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // For system()

#include <troubleshooter/diagnostic.h>
#include <troubleshooter/diagnostic_configuration.h>

class InternetConnectivityCheck : public IDiagnostic {
public:
    virtual ~InternetConnectivityCheck() {}

    void check(const DiagnosticConfig& config) override {
        std::cout << "Checking internet connectivity..." << std::endl;

        // Using `ping` command as an example to check internet connectivity
        // Here we are pinging google's primary DNS server as an example
        int result = system("ping -c 1 8.8.8.8 > /dev/null 2>&1");

        if (result == 0) {
            std::cout << "Internet connectivity is available." << std::endl;
        } else {
            std::cout << "Internet connectivity is not available." << std::endl;
        }
    }

    std::string getName() override {
        return "InternetConnectivityCheck";
    }

    std::vector<std::string> getDependencies() const override {
        return std::vector<std::string>();  // No dependencies for this simple check
    }
};

extern "C" IDiagnostic* create() {
    return new InternetConnectivityCheck();
}

extern "C" void destroy(IDiagnostic* plugin) {
    delete plugin;
}
