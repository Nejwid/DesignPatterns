#pragma once
#include <iostream>
#include <memory>
#include <mutex>

// przykład klasy proxy opóźniającej otwarcie domniemanego połączenia z bazą danych

namespace databaseSingletonProxy{
	using namespace std;

	class DB{
	private:
		string name;
	public:
		DB(string n):name(n){}
		string getName() const {
			return name;
		}
		~DB(){}
	};

	class DatabaseConnect {
	private:
		DatabaseConnect(){}
		static mutex mtx;
		static unique_ptr<DatabaseConnect> instance;
	public:
		DatabaseConnect (const DatabaseConnect&) = delete;
		DatabaseConnect& operator=(DatabaseConnect&) = delete;
		static DatabaseConnect& getInstance() {
			lock_guard<mutex> lock(mtx);
			if (!instance)
				instance.reset(new DatabaseConnect());
			return *instance;
		}
		void dbInfo() {
			cout << "database works" << endl;
		}
	};
	mutex DatabaseConnect::mtx;
	unique_ptr<DatabaseConnect> DatabaseConnect::instance;; // statyczne pola inicjowane poza klasą

	class ProxyDB {
	private:
		DatabaseConnect* proxyDB;
	public:
		ProxyDB():proxyDB(nullptr){}
		void useDB() {
			if (!proxyDB)
				proxyDB = &DatabaseConnect::getInstance();
			proxyDB->dbInfo();
		}
		~ProxyDB(){}
	};
}
