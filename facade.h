#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>


namespace heatingSystem
{
	using namespace::std;

	class heatingSystemPart{
	public:
		virtual void on() const = 0;
		virtual void off() const = 0;
		virtual ~heatingSystemPart(){}
	};

	class Boiler : public heatingSystemPart{
	public: 
		void on() const override{
			cout << "boiler on " << endl;
		}
		void off() const override{
			cout << "boiler off " << endl;
		}
	};

	class Thermostat : public heatingSystemPart {
	public:
		void on() const override{
			cout << "thermostat on " << endl;
		}
		void off() const override{
			cout << "thermostat off " << endl;
		}
	};

	class Radiator : public heatingSystemPart{
	public:
		void on() const override{
			cout << "radiator on " << endl;
		}
		void off() const override{
			cout << "radiator off " << endl;
		}
	};

	class HeatingSystemFacade{
	private:
		vector<unique_ptr<heatingSystemPart>> system;
	public:
		HeatingSystemFacade(Boiler& boiler, Thermostat& thermostat, Radiator& radiator){
			system.emplace_back(make_unique<Boiler>(boiler));  // robimy wskaznik do miejsca w pamieci wskazanego za pomoca referencji do obiektu
			system.emplace_back(make_unique<Thermostat>(thermostat)); 
			system.emplace_back(make_unique<Radiator>(radiator)); 
		}
		void turnOn() const {
			for (const auto& it : system){
				it->on();
			}
		}
		void turnOff() const{
			for (const auto& it : system){
				it->off();
			}
		}
		~HeatingSystemFacade(){}
	};
}