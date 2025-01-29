#pragma once
#include <iostream>
#include <memory>

namespace chainOfR
{
	string resetHas³a = "R", softConfig = "S", awariaSprzêtu = "A";

	class CC{
	protected:
		unique_ptr<CC> nextCC;
	public:
		void setCC(unique_ptr<CC> next){
			nextCC = move(next);
		}
		virtual void help(const string & task){
			if (nextCC)
				nextCC->help(task);
			else
				cout << "cannot help";
		}
		virtual ~CC(){}
	};

	class BasicCC : public CC{
	public:
		void help(const string& task) override{
			if (task == resetHas³a){
				cout << "password reseted";
			}
			else{
				CC::help(task);
			}
		}
	};

	class AdvancedCC : public CC{
	public:
		void help(const string& task) override{
			if (task == softConfig)
				cout << "soft config done";
			else
				CC::help(task);
		}
	};

	class SpecialistCC : public CC{
	public:
		void help(const string& task) override{
			if (task == awariaSprzêtu)
				cout << "device fixed";
			else
				CC::help(task);
		}
	};


	void test()
	{
		unique_ptr<BasicCC> b = make_unique<BasicCC>();
		unique_ptr<AdvancedCC> a = make_unique<AdvancedCC>();
		unique_ptr<SpecialistCC> s = make_unique<SpecialistCC>();
		a->setCC(move(s));
		b->setCC(move(a)); // TUTAJ NAJWAZNIEJSZY MOMENT - trzeba ustawic wskazniki od góry s->a, a(s)->b = b(a(s))
		b->help("A");
		b->help("S");
		b->help("X");
	}

}

namespace chainOfR_test{
	using namespace::std;

	class Ticket{public: virtual ~Ticket(){} }; class Basic : public Ticket{}; class Advanced : public Ticket{};

	class CC{
	protected:
		unique_ptr<CC> next;
	public:
		void setNext(unique_ptr<CC> n){
			next = move(n);
		}
		virtual void help(Ticket* t){
			if (next)
				next->help(t);
			else cout << "not helped\n";
		}
		virtual ~CC(){}
	};

	class BasicCC : public CC{
	public:
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