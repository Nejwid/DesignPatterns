#pragma once
#include <iostream>
#include <memory>

namespace state {
    using namespace std;

    class State; 
    class Gate; 
    class Open; 
    class Close;

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
        Gate(unique_ptr<State> state);
        void changeState(unique_ptr<State> newState);
        void open();
        void close();
        ~Gate();
    };

    class Open : public State {
    public:
        void close(Gate* gate) override;
    };

    class Close : public State {
    public:
        void open(Gate* gate) override;
    };
}
