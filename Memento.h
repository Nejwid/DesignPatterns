#pragma once
#include <iostream>
#include <stack>

namespace memento_ {
    using namespace std;

    class Memento {
    private:
        string state;
    public:
        Memento(const string& s);
        string getState() const;
    };

    class Source {
    private:
        string state;
    public:
        void setState(const string& s);
        string getState() const;
        Memento save() const;
        void restore(const Memento& m);
    };

    class Historia {
    private:
        stack<Memento> h;
    public:
        void addMemento(const Memento& m);
        Memento przywróc();
    };

    class HistoryManager {
    private:
        Source& src;
        Historia& hist;
    public:
        HistoryManager(Source& src, Historia& hist);
        void setState(const string& s);
        void saveState();
        void returnState();
        void showState();
        ~HistoryManager();
    };
}
