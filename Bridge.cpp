#include "Bridge.h"

namespace bridge_Shelter {
    Animal::Animal(string s, int n) : name(s), age(n) {}

    void Animal::displayInfo() const {
        cout << name << ", " << age << " ";
    }

    int Animal::getAge() const {
        return age;
    }

    bool Animal::operator<(const Animal& other) {
        return age < other.age;
    }

    Animal::~Animal() {}

    Dog::Dog(string s, int n) : Animal(s, n) {}

    void Dog::speak() const {
        cout << "wooof" << endl;
    }

    Cat::Cat(string s, int n) : Animal(s, n) {}

    void Cat::speak() const {
        cout << "meoow" << endl;
    }

    Bird::Bird(string s, int n) : Animal(s, n) {}

    void Bird::speak() const {
        cout << "tweet" << endl;
    }
//=============================================================//
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

namespace interfaceShelter { // w strategiach przekazujemy kopię listy więc zwracam wskaznik na element który będę chciał usunąć 
//usuwam element w funkcji wyżej, porównując zawartość wskaźników (zawartość wskaźnika z kopii listy -który wskazuje na element który chce usunąć-, z zawartością wskaźników na oryginalnej liście)

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
