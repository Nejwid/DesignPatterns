#include "Observer.h"

namespace observer_ {

    Obiekt::Obiekt(const string& n) : name(n) {}

    string Obiekt::getName() const {
        return name;
    }

    void Obserwator::nastapilaZmianaObiektu(const Obiekt& o) const {
        cout << "Nastąpiła zmiana stanu obiektu: " << o.getName() << endl;
    }

    void Radar::nastapilaZmianaObiektu(const Obiekt& o) const {
        Obserwator::nastapilaZmianaObiektu(o);
    }

    InterfejsZmian::InterfejsZmian(Obiekt& o) : obj(o) {}

    void InterfejsZmian::addObserwator(Obserwator* o) {
        obs.push_back(o);
    }

    void InterfejsZmian::powiadom() {
        for (const auto& it : obs) {
            it->nastapilaZmianaObiektu(obj);
        }
    }
}
