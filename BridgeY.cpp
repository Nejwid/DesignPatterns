#include "BridgeY.h"

namespace bridge_Shelter {

    void Shelter::addDog(string s, int n) {
        animals.emplace_back(make_unique<Dog>(s, n));
    }

    void Shelter::addCat(string s, int n) {
        animals.emplace_back(make_unique<Cat>(s, n));
    }

    void Shelter::addBird(string s, int n) {
        animals.emplace_back(make_unique<Bird>(s, n));
    }

    void Shelter::showInfo() const {
        for (const auto& it : animals) {
            it->displayInfo();
            it->speak();
        }
    }

    list<unique_ptr<Animal>> Shelter::getAnimals() {
        return animals;
    }

    void Shelter::adoptAnimal(interfaceShelter::AdoptionStrategy& strategy) {
        unique_ptr<Animal> adoptedAnimal = strategy.adopt(animals);
        if (adoptedAnimal) {
            for (auto it = animals.begin(); it != animals.end(); ++it) {
                if (it->get() == adoptedAnimal.get()) {
                    animals.erase(it);
                    break;
                }
            }
        }
    }

namespace interfaceShelter {

    AdoptionStrategy::~AdoptionStrategy() {}

    unique_ptr<bs::Animal> AdoptOldest::adopt(list<unique_ptr<bs::Animal>> animals) {
        if (!animals.empty()) {
            animals.sort();  // Sortowanie zwierząt po wieku (najstarsze na początku)
            animals.front()->displayInfo();
            return move(animals.front());
        }
        return nullptr;
    }

    AdoptByType::AdoptByType(unique_ptr<bs::Animal> animal) : AdoptionStrategy(), animal(move(animal)) {}

    unique_ptr<bs::Animal> AdoptByType::adopt(list<unique_ptr<bs::Animal>> animals) {
        for (auto& it : animals) {
            if (dynamic_cast<bs::Bird*>(animal.get()) && dynamic_cast<bs::Bird*>(it.get())) {
                it->displayInfo();
                return move(it);
            }
            else if (dynamic_cast<bs::Cat*>(animal.get()) && dynamic_cast<bs::Cat*>(it.get())) {
                it->displayInfo();
                return move(it);
            }
            else if (dynamic_cast<bs::Dog*>(animal.get()) && dynamic_cast<bs::Dog*>(it.get())) {
                it->displayInfo();
                return move(it);
            }
        }
        return nullptr;
    }

    unique_ptr<bs::Animal> AdoptLongestStay::adopt(list<unique_ptr<bs::Animal>> animals) {
        if (!animals.empty()) {
            animals.front()->displayInfo();
            return move(animals.front());
        }
        return nullptr;
    }
}
