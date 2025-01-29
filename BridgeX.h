#pragma once
#include <iostream>
#include <string>

namespace bridge_Shelter {
    using namespace std;

    class Animal {
    protected:
        string name;
        int age;
    public:
        Animal(string s, int n);
        virtual void speak() const = 0;
        void displayInfo() const;
        int getAge() const;
        bool operator<(const Animal& other);
        virtual ~Animal();
    };

    class Dog : public Animal {
    public:
        Dog(string s, int n);
        void speak() const override;
    };

    class Cat : public Animal {
    public:
        Cat(string s, int n);
        void speak() const override;
    };

    class Bird : public Animal {
    public:
        Bird(string s, int n);
        void speak() const override;
    };
}
