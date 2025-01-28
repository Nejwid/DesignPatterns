#pragma once
#include <memory>
#include <iostream>


namespace fabryka
{
	using namespace::std;
	
	class Produkt
	{
	public:
		Produkt(){}
		virtual void info() const = 0;
		virtual ~Produkt(){}
	};

	class ProduktA : public Produkt
	{
	public:
		ProduktA():Produkt(){}
		void info() const override
		{
			cout << " this is produkt A " << endl;
		}
	};

	class ProduktB : public Produkt
	{
	public:
		ProduktB() :Produkt() {}
		void info() const override
		{
			cout << " this is produkt B " << endl;
		}
	};

	class Fabryka
	{
	public:
		virtual unique_ptr<Produkt> factor() = 0;
		virtual ~Fabryka(){}
	};

	class FabrykaA : public Fabryka
	{
	public:
		FabrykaA():Fabryka(){}
		unique_ptr<Produkt> factor() override
		{
			return make_unique<ProduktA>();
		}
	};

	class FabrykaB : public Fabryka
	{
	public:
		FabrykaB() :Fabryka() {}
		unique_ptr<Produkt> factor() override
		{
			return make_unique<ProduktB>();
		}
	};


	void test()
	{
		unique_ptr<Fabryka> fa = make_unique<FabrykaA>();
		unique_ptr<Fabryka> fb = make_unique<FabrykaB>();
		unique_ptr<Produkt> a = fa->factor();
		unique_ptr<Produkt> b = fb->factor();
		a->info();
		b->info();
	}
}