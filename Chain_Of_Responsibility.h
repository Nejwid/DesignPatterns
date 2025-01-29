#pragma once
#include <iostream>
#include <memory>

namespace chainOfResponsibility {
    using namespace std;

    class Ticket {
    public:
        virtual ~Ticket() {}
    };

    class Basic : public Ticket {};
    class Advanced : public Ticket {};

    class CC {
    protected:
        unique_ptr<CC> next;
    public:
        void setNext(unique_ptr<CC> n);
        virtual void help(Ticket* t);
        virtual ~CC();
    };

    class BasicCC : public CC {
    public:
        void help(Ticket* t) override;
    };

    class AdvancedCC : public CC {
    public:
        void help(Ticket* t) override;
    };

    class CustomerCare {
    private:
        unique_ptr<BasicCC> basic;
        unique_ptr<AdvancedCC> advanced;
    public:
        CustomerCare();
        void help(Ticket* t);
    };
}
