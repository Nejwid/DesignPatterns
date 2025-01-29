#pragma once
#include <iostream>
#include <memory>
#include <string>

namespace dependencyInjection {
    using namespace std;

    class iProdukt {
    protected:
        string name;

    public:
        virtual void sendAlert() const = 0;
        virtual string getName() const;
        virtual ~iProdukt();
    };

    class iPhone : public iProdukt {
    public:
        iPhone();
        void sendAlert() const override;
        string getName() const override;
    };

    class AppleHub {
    private:
        shared_ptr<iProdukt> device;

    public:
        AppleHub(shared_ptr<iProdukt> p);
        void notify() const;
        ~AppleHub();
    };
}
