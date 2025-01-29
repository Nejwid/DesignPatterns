#include "Singleton_Proxy.h"

namespace databaseSingletonProxy {

    DB::DB(string n) : name(n) {}

    string DB::getName() const {
        return name;
    }

    DB::~DB() {}

    DatabaseConnect::DatabaseConnect() {}

    DatabaseConnect& DatabaseConnect::getInstance() {
        lock_guard<mutex> lock(mtx);
        if (!instance) {
            instance.reset(new DatabaseConnect());
        }
        return *instance;
    }

    void DatabaseConnect::dbInfo() {
        cout << "Database works!" << endl;
    }

    ProxyDB::ProxyDB() : proxyDB(nullptr) {}

    void ProxyDB::useDB() {
        if (!proxyDB) {
            proxyDB = &DatabaseConnect::getInstance();  // get or create bazę danych dopiero gdy jest potrzebna
        }
        proxyDB->dbInfo();
    }

    ProxyDB::~ProxyDB() {}
}
