#include "Chain_Of_Responsibility.h"

namespace chainOfResponsibility {

    void CC::setNext(unique_ptr<CC> n) {
        next = move(n);
    }

    void CC::help(Ticket* t) {
        if (next)
            next->help(t);
        else
            cout << "not helped\n";
    }

    CC::~CC() {}

    void BasicCC::help(Ticket* t) {
        Basic* b = dynamic_cast<Basic*>(t);
        if (b)
            cout << "helped basic\n";
        else
            CC::help(t);
    }

    void AdvancedCC::help(Ticket* t) {
        Advanced* a = dynamic_cast<Advanced*>(t);
        if (a)
            cout << "helped advanced\n";
        else
            CC::help(t);
    }

    CustomerCare::CustomerCare() {
        basic = make_unique<BasicCC>();
        advanced = make_unique<AdvancedCC>();
        basic->setNext(move(advanced));
    }

    void CustomerCare::help(Ticket* t) {
        basic->help(t);
    }
}
