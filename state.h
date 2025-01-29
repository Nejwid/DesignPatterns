#pragma once
#include <iostream>
#include <memory>

namespace state {
    using namespace::std;

    class State; class Gate; class Open; class Close;

    class State {
    public:
        virtual void open(Gate* gate) = 0;
        virtual void close(Gate* gate) = 0;
        virtual ~State() = default;
    };

    class Gate {
    private:
        unique_ptr<State> current;
    public:
        Gate(unique_ptr<State> state):current(move(state)){}
        void changeState(unique_ptr<State> newState) {
            current = move(newState);
        }
        void open() {
            current->open(this);
        }
        void close() {
            current->close(this);
        }
        ~Gate(){}
    };

    class Open : public State {
    public:
        void close(Gate* gate) override {
            gate->changeState(make_unique<Close>());
        }
    };

    class Close : public State {
    public:
        void open(Gate* gate) override {
            gate->changeState(make_unique<Open>());
        }
    };
}
