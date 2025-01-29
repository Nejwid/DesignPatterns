#include "Facade.h"

namespace heatingSystem {

    heatingSystemPart::~heatingSystemPart() {}

    void Boiler::on() const {
        cout << "boiler on " << endl;
    }

    void Boiler::off() const {
        cout << "boiler off " << endl;
    }

    void Thermostat::on() const {
        cout << "thermostat on " << endl;
    }

    void Thermostat::off() const {
        cout << "thermostat off " << endl;
    }

    void Radiator::on() const {
        cout << "radiator on " << endl;
    }

    void Radiator::off() const {
        cout << "radiator off " << endl;
    }

    HeatingSystemFacade::HeatingSystemFacade(Boiler& boiler, Thermostat& thermostat, Radiator& radiator) {
        system.emplace_back(make_unique<Boiler>(boiler));  
        system.emplace_back(make_unique<Thermostat>(thermostat)); 
        system.emplace_back(make_unique<Radiator>(radiator)); 
    }

    void HeatingSystemFacade::turnOn() const {
        for (const auto& it : system) {
            it->on();
        }
    }

    void HeatingSystemFacade::turnOff() const {
        for (const auto& it : system) {
            it->off();
        }
    }

    HeatingSystemFacade::~HeatingSystemFacade() {}
}
