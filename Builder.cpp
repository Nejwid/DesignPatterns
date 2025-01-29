#include "Builder.h"

namespace builder {
    FortniteLocker::FortniteLocker() {}

    void FortniteLocker::setSkin(const string& s) {
        this->skin = s;
    }

    void FortniteLocker::setBackbling(const string& b) {
        this->backbling = b;
    }

    void FortniteLocker::setPickaxe(const string& p) {
        this->pickaxe = p;
    }

    void FortniteLocker::displayInfo() const {
        cout << this->skin << ", " << this->backbling << ", " << this->pickaxe << endl;
    }

    FortniteLocker::~FortniteLocker() {}

    LockerBuilder::LockerBuilder() {
        this->locker = make_unique<FortniteLocker>();
    }

    void LockerBuilder::setSkin(const string& s) {
        locker->setSkin(s);
    }

    void LockerBuilder::setBackbling(const string& b) {
        locker->setBackbling(b);
    }

    void LockerBuilder::setPickaxe(const string& p) {
        locker->setPickaxe(p);
    }

    unique_ptr<FortniteLocker>& LockerBuilder::getLocker() {
        return this->locker;
    }
}

//======================================================================//

namespace BobTheBuilder {
    House::House() : floors(0), bathrooms(0), paint("") {}

    void House::setFloors(int f) { this->floors = f; }

    void House::setBathrooms(int b) { this->bathrooms = b; }

    void House::setPaint(const string& p) { this->paint = p; }

    void House::displayInfo() const {
        cout << floors << " floors, " << bathrooms << " bathrooms, " << paint << endl;
    }

    House::~House() {}

    virtualHouseBuilder::virtualHouseBuilder() : house(make_shared<House>()) {}

    virtualHouseBuilder::~virtualHouseBuilder() {}

    HouseBuilder::HouseBuilder() : virtualHouseBuilder() {}

    void HouseBuilder::setParameters(const string& paint, int floors, int bathrooms) {
        this->house->setBathrooms(bathrooms);
        this->house->setFloors(floors);
        this->house->setPaint(paint);
    }

    shared_ptr<House> HouseBuilder::getHouse() {
        return this->house;
    }

    ConstructionSite::ConstructionSite(unique_ptr<HouseBuilder> hb) : hb(move(hb)), hs() {}

    void ConstructionSite::build(const string& paint, int floors, int bathrooms) {
        this->hb->setParameters(paint, floors, bathrooms);
        this->hs.push_back(move(this->hb->getHouse()));
        this->hb.reset(new HouseBuilder);
    }

    void ConstructionSite::getInfo() const {
        if (!this->hs.empty()) {
            for (const auto& it : hs) {
                it->displayInfo();
            }
        }
    }

    ConstructionSite::~ConstructionSite() {}
}
