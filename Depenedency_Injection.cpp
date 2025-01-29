#include "Dependency_Injection.h"

namespace dependencyInjection {

    string iProdukt::getName() const {
        return name;
    }

    iProdukt::~iProdukt() {}

    iPhone::iPhone() : iProdukt() {
        this->name = "iPhone twojego starego";
    }

    void iPhone::sendAlert() const {
        cout << "warning pozor attencion uwaga" << endl;
    }

    string iPhone::getName() const {
        return iProdukt::getName();
    }

    AppleHub::AppleHub(shared_ptr<iProdukt> p) : device(move(p)) {}

    void AppleHub::notify() const {
        cout << this->device->getName() << " sent alert: ";
        this->device->sendAlert();
    }

    AppleHub::~AppleHub() {}
}
