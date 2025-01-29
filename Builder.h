#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <string>

namespace builder {
    using namespace std;

    class FortniteLocker {
    private:
        string skin, backbling, pickaxe;

    public:
        FortniteLocker();
        void setSkin(const string& s);
        void setBackbling(const string& b);
        void setPickaxe(const string& p);
        void displayInfo() const;
        ~FortniteLocker();
    };

    class LockerBuilder {
    private:
        unique_ptr<FortniteLocker> locker;

    public:
        LockerBuilder();
        void setSkin(const string& s);
        void setBackbling(const string& b);
        void setPickaxe(const string& p);
        unique_ptr<FortniteLocker>& getLocker();
    };
}

//==============================================================================//

namespace BobTheBuilder {
    using namespace std;

    class House {
    private:
        string paint;
        int floors, bathrooms;

    public:
        House();
        void setFloors(int f);
        void setBathrooms(int b);
        void setPaint(const string& p);
        void displayInfo() const;
        ~House();
    };

    class virtualHouseBuilder {
    protected:
        shared_ptr<House> house;

    public:
        virtualHouseBuilder();
        virtual void setParameters(const string& t1, int a, int b) = 0;
        virtual ~virtualHouseBuilder();
    };

    class HouseBuilder : public virtualHouseBuilder {
    public:
        HouseBuilder();
        void setParameters(const string& paint, int floors, int bathrooms) override;
        shared_ptr<House> getHouse();
    };

    class ConstructionSite {
    private:
        unique_ptr<HouseBuilder> hb;
        vector<shared_ptr<House>> hs;

    public:
        ConstructionSite(unique_ptr<HouseBuilder> hb);
        void build(const string& paint, int floors, int bathrooms);
        void getInfo() const;
        ~ConstructionSite();
    };
}
