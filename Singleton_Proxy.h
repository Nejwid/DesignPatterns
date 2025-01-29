#pragma once
#include <iostream>
#include <memory>
#include <mutex>

// przykład klasy proxy opóźniającej otwarcie domniemanego połączenia z bazą danych

namespace databaseSingletonProxy {
    using namespace std;

    class DB {
    private:
        string name;
    public:
        DB(string n);
        string getName() const;
        ~DB();
    };

    class DatabaseConnect {
    private:
        DatabaseConnect();
        static mutex mtx;
        static unique_ptr<DatabaseConnect> instance;
    public:
        DatabaseConnect(const DatabaseConnect&) = delete;
        DatabaseConnect& operator=(DatabaseConnect&) = delete;
        static DatabaseConnect& getInstance();
        void dbInfo();
    };
    
    // inicjalizacja pól statycznych poza klasą
    mutex DatabaseConnect::mtx;
    unique_ptr<DatabaseConnect> DatabaseConnect::instance;

    class ProxyDB {
    private:
        DatabaseConnect* proxyDB;
    public:
        ProxyDB();
        void useDB();
        ~ProxyDB();
    };
}
