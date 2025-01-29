#pragma once
#include <iostream>
#include <thread>
#include <list>

namespace observer_ {
    using namespace std;

    class Obiekt {
    private:
        string name;
    public:
        Obiekt(const string& n);
        string getName() const;
    };

    class Obserwator {
    public:
        virtual void nastapilaZmianaObiektu(const Obiekt& o) const;
    };

    class Radar : public Obserwator {
    public:
        void nastapilaZmianaObiektu(const Obiekt& o) const override;
    };

    class InterfejsZmian {
    private:
        list<Obserwator*> obs;  // Observe pointers instead of objects
        Obiekt& obj;
    public:
        InterfejsZmian(Obiekt& o);
        void addObserwator(Obserwator* o);
        void powiadom();
    };
}
