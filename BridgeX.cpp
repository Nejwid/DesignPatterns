#include "BridgeX.h"

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
}
