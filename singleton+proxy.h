#pragma once
#include <iostream>
#include <memory>
#include <mutex>

namespace database
{
	using namespace ::std;

	class Database
	{
	private:
		Database(){}
		static mutex mtx;
		static unique_ptr<Database> instance;
	public:
		Database& operator=(const Database&) = delete;
		Database(const Database&) = delete;
		static Database& getInstance()
		{
			lock_guard<mutex> lock(mtx);
			if (!instance)
				instance.reset(new Database);
			return *instance;
		}
		void ShowDatabase() const
		{
			cout << "database access confirmed" << endl;
		}
	};
	mutex Database::mtx;
	unique_ptr<Database> Database::instance;

	class DatabaseProxy
	{
	private:
		Database* db;
	public:
		DatabaseProxy():db(nullptr){}
		void executeDB()
		{
			if (!db)
				db = &Database::getInstance();
			db->ShowDatabase();
		}
	};
}


namespace testSingleton
{
	using namespace::std;
	class Singleton
	{
	private:
		Singleton(){}
		static unique_ptr<Singleton> instance;
		static mutex mtx;
	public:
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		static Singleton& getInstance()
		{
			lock_guard<mutex> lock(mtx);
			if (!instance)
				instance.reset(new Singleton);
			return *instance;
		}
		void success() const
		{
			cout << "\nsuccess\n";
 		}

	};
	mutex Singleton::mtx;
	unique_ptr<Singleton> Singleton::instance;

	class ProxySingleton
	{
	private:
		Singleton* pointer;
	public:
		ProxySingleton() :pointer(nullptr) {}
		void runSingleton()
		{
			if (!pointer)
				pointer = &Singleton::getInstance();

			pointer->success();
		}
	};
}

namespace singletonConfig
{
	using namespace::std;

	class Config
	{
	private:
		Config(){}
		static unique_ptr<Config> instance;
		static mutex mtx;
	public:
		Config& operator=(const Config&) = delete;
		Config(const Config&) = delete;
		static Config& getInstance()
		{
			lock_guard<mutex> lock(mtx);
			if (!instance)
				instance.reset(new Config);
			return *instance;
		}
		bool isConfig(const bool&config)
		{
			return config;
		}
	};
	mutex Config::mtx;
	unique_ptr<Config> Config::instance;

	class ProxyConfig
	{
	private:
		Config* cnfg;
	public:
		ProxyConfig():cnfg(nullptr){}
		void isConfig(const bool& b) 
		{
			if (!cnfg)
				cnfg = &Config::getInstance();
			cout << cnfg->isConfig(b);
		}
		~ProxyConfig()
		{}
	};
		
}

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
			cout << "it works";
		}
	};
	mutex DatabaseConnect::mtx;
	unique_ptr<DatabaseConnect> DatabaseConnect::instance;;


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