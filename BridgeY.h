#pragma once
#include <memory>
#include <list>
#include "BridgeX.h"

namespace bridge_Shelter {
    using namespace std;

    class Shelter {
    private:
        list<unique_ptr<Animal>> animals;
    public:
        void addDog(string s, int n);
        void addCat(string s, int n);
        void addBird(string s, int n);
        void showInfo() const;
        list<unique_ptr<Animal>> getAnimals();
        void adoptAnimal(interfaceShelter::AdoptionStrategy& strategy);
    };
}

namespace interfaceShelter {
    using namespace std;
    namespace bs = bridge_Shelter;

    class AdoptionStrategy {
    public:
        virtual unique_ptr<bs::Animal> adopt(list<unique_ptr<bs::Animal>> animals) = 0;
        virtual ~AdoptionStrategy();
    };

    class AdoptOldest : public AdoptionStrategy {
    public:
        unique_ptr<bs::Animal> adopt(list<unique_ptr<bs::Animal>> animals) override;
    };

    class AdoptByType : public AdoptionStrategy {
    private:
        unique_ptr<bs::Animal> animal;
    public:
        AdoptByType(unique_ptr<bs::Animal> animal);
        unique_ptr<bs::Animal> adopt(list<unique_ptr<bs::Animal>> animals) override;
    };

    class AdoptLongestStay : public AdoptionStrategy {
    public:
        unique_ptr<bs::Animal> adopt(list<unique_ptr<bs::Animal>> animals) override;
    };
}
