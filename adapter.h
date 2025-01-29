#pragma once
#include <iostream>
#include <memory>
#include <thread>

namespace adapter_{
	using namespace ::std;

	class Bazowa { // klasa któr¹ adaptujemy do uzyskania docelowej
	public:
		void funkcja() {
			cout << "funkcja bazowa";
		}
	};

	class Docelowa { // oczekiany interfejs 
	public:
		Docelowa(){}
		virtual void funkcjaOczekiwana() = 0;
		virtual ~Docelowa() = default;
	};

	class Adapter : public Docelowa {
	private:
		unique_ptr<Bazowa> baza;
	public:
		Adapter(unique_ptr<Bazowa> b):Docelowa(), baza(move(b)){}
		void funkcjaOczekiwana() override {
			baza->funkcja();
			cout << " zaadaptowana do docelowej" << endl;
		}
	};

	void test() {
		unique_ptr<Bazowa> b = make_unique<Bazowa>();
		Adapter adapter (move(b));
		adapter.funkcjaOczekiwana();
	}

	void run_test() {
		thread t1(test);
		t1.join();
	}
}