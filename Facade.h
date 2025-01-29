#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

// przykład "fasady" gdzie włączamy wszystko jednym guziczkiem
namespace heatingSystem {
    using namespace std;

    class heatingSystemPart {
    public:
        virtual void on() const = 0;
        virtual void off() const = 0;
        virtual ~heatingSystemPart();
    };

    class Boiler : public heatingSystemPart {
    public:
        void on() const override;
        void off() const override;
    };

    class Thermostat : public heatingSystemPart {
    public:
        void on() const override;
        void off() const override;
    };

    class Radiator : public heatingSystemPart {
    public:
        void on() const override;
        void off() const override;
    };

    class HeatingSystemFacade {
    private:
        vector<unique_ptr<heatingSystemPart>> system;

    public:
        HeatingSystemFacade(Boiler& boiler, Thermostat& thermostat, Radiator& radiator);
        void turnOn() const;
        void turnOff() const;
        ~HeatingSystemFacade();
    };
}
