#include "State.h"

namespace state {

    Gate::Gate(unique_ptr<State> state) : current(move(state)) {}

    void Gate::changeState(unique_ptr<State> newState) {
        current = move(newState);
    }

    void Gate::open() {
        current->open(this);
    }

    void Gate::close() {
        current->close(this);
    }

    Gate::~Gate() {}

    void Open::close(Gate* gate) {
        cout << "Gate is closing." << endl;
        gate->changeState(make_unique<Close>());
    }

    void Close::open(Gate* gate) {
        cout << "Gate is opening." << endl;
        gate->changeState(make_unique<Open>());
    }
}
