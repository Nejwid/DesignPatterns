#include "Memento.h"

namespace memento_ {

    Memento::Memento(const string& s) : state(s) {}

    string Memento::getState() const {
        return state;
    }

    void Source::setState(const string& s) {
        state = s;
    }

    string Source::getState() const {
        return state;
    }

    Memento Source::save() const {
        return Memento(state);
    }

    void Source::restore(const Memento& m) {
        state = m.getState();
    }

    void Historia::addMemento(const Memento& m) {
        h.push(m);
    }

    Memento Historia::przywróc() {
        if (!h.empty()) {
            Memento history = h.top();
            h.pop();
            return history;
        }
        return Memento("");
    }

    HistoryManager::HistoryManager(Source& src, Historia& hist) : src(src), hist(hist) {}

    void HistoryManager::setState(const string& s) {
        src.setState(s);
    }

    void HistoryManager::saveState() {
        hist.addMemento(src.save());
    }

    void HistoryManager::returnState() {
        src.restore(hist.przywróc());
    }

    void HistoryManager::showState() {
        cout << src.getState() << endl;
    }

    HistoryManager::~HistoryManager() {}
}
