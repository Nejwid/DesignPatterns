#pragma once
#include <iostream>
#include <thread>
#include <list>

namespace observer_{
	using namespace::std;

	class Obiekt{
	private:
		string name;
	public:
		Obiekt(const string& n):name(n){}
		string getName() const{
			return name;
		}
	};

	class Obserwator{
	public:
		virtual void nast¹pi³aZmianaObiektu(const Obiekt& o) const{
			cout << "nastapila zmiana stanu obiektu " << o.getName() << endl;
		}
	};

	class Radar : public Obserwator{
	public:
		void nast¹pi³aZmianaObiektu(const Obiekt& o) const override{
			Obserwator::nast¹pi³aZmianaObiektu(o);
		}
	};

	class InterfejsZmian{
	private:
		list<Obserwator> obs; // w kontenerach stl NIE przechowujemy referencji &&&&&&&&&!!!!!!
		Obiekt& obj;
	public:
		InterfejsZmian(Obiekt& o):obj(o){}
		void addObserwator(Obserwator &o){
			obs.push_back(o);
		}
		void powiadom(){
			for (const auto& it : obs){
				it.nast¹pi³aZmianaObiektu(obj);
			}
		}
	};

	void test(){
		Radar d;
		Radar b;
		Obiekt o("missile");
		InterfejsZmian inf (o);
		inf.addObserwator(b);
		inf.addObserwator(d);
		inf.powiadom();
	}

	void run_test(){
		thread run(test);
		run.join();
	}
}
