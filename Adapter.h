#pragma once
#include <iostream>
#include <memory>
#include <thread>

namespace adapter_ {
    using namespace std;

    // Klasa Bazowa - adaptowana
    class Bazowa {
    public:
        void funkcja();
    };

    // Klasa Docelowa - oczekiwany interfejs
    class Docelowa {
    public:
        Docelowa();
        virtual void funkcjaOczekiwana() = 0;
        virtual ~Docelowa() = default;
    };

    // Klasa Adapter - adaptująca Bazowa do Docelowa
    class Adapter : public Docelowa {
    private:
        unique_ptr<Bazowa> baza;
    public:
        Adapter(unique_ptr<Bazowa> b);
        void funkcjaOczekiwana() override;
    };
}
