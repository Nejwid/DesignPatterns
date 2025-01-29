#pragma once
#include <iostream>
#include <memory>

// symulacja Customer Care
namespace chainOfResponsibility {
	using namespace::std;

	class Ticket{public: virtual ~Ticket(){} }; class Basic : public Ticket{}; class Advanced : public Ticket{};

	class CC{
	protected:
		unique_ptr<CC> next;
	public:
		void setNext(unique_ptr<CC> n){
			next = move(n);
		}
		// przenieś do wyższej next instancji jeśli została określona
		virtual void help(Ticket* t){
			if (next)
				next->help(t);
			else cout << "not helped\n";
		}
		virtual ~CC(){}
	};

	class BasicCC : public CC{
	public:
		// jesli ticket jest basic pomóż, else przenieś do wyższej instancji
		void help(Ticket* t) override{ 
			Basic* b = dynamic_cast<Basic*>(t);
			if (b)
				cout << "helped basic\n";
			else
				CC::help(t);
		}
	};

	class AdvancedCC : public CC{
	public:
		void help(Ticket* t) override{
			Advanced* a = dynamic_cast<Advanced*>(t);
			if (a)
				cout << "helped advanced\n";
			else CC::help(t);
		}
	};

	// basic instancja pomoże lub przeniesie ticket do instancji advanced 
	class CustomerCare{
	private:
		unique_ptr<BasicCC> basic;
		unique_ptr<AdvancedCC> advanced;
	public:
		CustomerCare(){
			basic = make_unique<BasicCC>();
			advanced = make_unique<AdvancedCC>();
			basic->setNext(move(advanced));
		}
		void help(Ticket* t){
			basic->help(t);
		}
	};

	void test()
	{
		CustomerCare cc;
		cc.help(new Advanced);
		cc.help(new Basic);
	}

}
