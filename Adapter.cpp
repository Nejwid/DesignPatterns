#include "Adapter.h"

namespace adapter_ {

    void Bazowa::funkcja() {
        cout << "funkcja bazowa";
    }

    Docelowa::Docelowa() {}

    Adapter::Adapter(unique_ptr<Bazowa> b) : baza(move(b)) {}

    void Adapter::funkcjaOczekiwana() {
        baza->funkcja();
        cout << " zaadaptowana do docelowej" << endl;
    }
}
