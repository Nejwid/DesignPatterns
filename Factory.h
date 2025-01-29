#pragma once
#include <memory>
#include <iostream>

namespace fabryka {
    using namespace std;

    class Produkt {
    public:
        Produkt();
        virtual void info() const = 0;
        virtual ~Produkt();
    };

    class ProduktA : public Produkt {
    public:
        ProduktA();
        void info() const override;
    };

    class ProduktB : public Produkt {
    public:
        ProduktB();
        void info() const override;
    };

    class Fabryka {
    public:
        virtual unique_ptr<Produkt> factor() = 0;
        virtual ~Fabryka();
    };

    class FabrykaA : public Fabryka {
    public:
        FabrykaA();
        unique_ptr<Produkt> factor() override;
    };

    class FabrykaB : public Fabryka {
    public:
        FabrykaB();
        unique_ptr<Produkt> factor() override;
    };
}
