#include "Factory.h"

namespace fabryka {

    Produkt::Produkt() {}

    Produkt::~Produkt() {}

    ProduktA::ProduktA() : Produkt() {}

    void ProduktA::info() const {
        cout << "this is produkt A" << endl;
    }

    ProduktB::ProduktB() : Produkt() {}

    void ProduktB::info() const {
        cout << "this is produkt B" << endl;
    }

    Fabryka::~Fabryka() {}

    FabrykaA::FabrykaA() : Fabryka() {}

    unique_ptr<Produkt> FabrykaA::factor() {
        return make_unique<ProduktA>();
    }

    FabrykaB::FabrykaB() : Fabryka() {}

    unique_ptr<Produkt> FabrykaB::factor() {
        return make_unique<ProduktB>();
    }
}
