#pragma once
#include <iostream>
#include <memory>
/*
namespace state_
{
	using namespace::std;

	class Door; class State;  class Close; class Open;

	class State
	{
	public:
		virtual void open(Door* d) = 0;
		virtual void close(Door* d) = 0;
		virtual ~State(){}
	};

	class Door
	{
	private:
		unique_ptr<State> stan;
	public:
		Door(unique_ptr<State> current):stan(move(current)){}
		void changeState(unique_ptr<State> newState)
		{
			stan = move(newState);
		}
		void open()
		{
			stan->open(this);
		}
		void close()
		{
			stan->close(this);
		}
		~Door(){}
	};

	class Open : public State
	{
	public:
		void open(Door* d) override
		{
			cout << "already opened" << endl;
		}
		void close(Door* d) override
		{
			d->changeState(make_unique<Close>());
			cout << "closed" << endl;
		}
	};

	class Close : public State
	{
	public:
		void open(Door* d) override
		{
			d->changeState(make_unique<Open>());
			cout << "opened" << endl;
		}
		void close(Door* d) override
		{
			cout << "already closed" << endl;
		}
	};

	void test()
	{
		Door* drzwi = new Door(make_unique<Close>());
		drzwi->close();
		drzwi->open();
		drzwi->open();
		delete drzwi;
	}
}*/


namespace state_{
    using namespace std;

    class Door;  // Forward declaration of Door class

    // Abstract State class
    class State{
    public:
        virtual void open(Door* d) = 0;
        virtual void close(Door* d) = 0;
        virtual ~State() {}
    };

    // Class representing the Door
    class Door{
    private:
        unique_ptr<State> stan;  // Pointer to current state
    public:
        Door(unique_ptr<State> current) : stan(move(current)) {}

        void changeState(unique_ptr<State> newState){
            stan = move(newState);  // Changing state to the new state
        }

        void open()
        {
            stan->open(this);  // Calling open on the current state
        }

        void close()
        {
            stan->close(this);  // Calling close on the current state
        }

        ~Door() {}
    };

    // Concrete State class representing an Open door
    class Open : public State
    {
    public:
        void open(Door* d) override
        {
            cout << "Door is already opened." << endl;
        }

        void close(Door* d) override
        {
            d->changeState(make_unique<Close>());  // Change state to Close
            cout << "Door is now closed." << endl;
        }
    };

    // Concrete State class representing a Closed door
    class Close : public State
    {
    public:
        void open(Door* d) override
        {
            d->changeState(make_unique<Open>());  // Change state to Open
            cout << "Door is now opened." << endl;
        }

        void close(Door* d) override
        {
            cout << "Door is already closed." << endl;
        }
    };

    // Testing function
    void test()
    {
        Door drzwi(make_unique<Close>());  // Initial state is Closed
        drzwi.close();  // Attempt to close a closed door (should print "Door is already closed.")
        drzwi.open();   // Open the door (should print "Door is now opened.")
        drzwi.open();   // Attempt to open an opened door (should print "Door is already opened.")
    }
}

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