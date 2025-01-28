#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <string>

namespace builder
{
	using namespace ::std;

	class FortniteLocker
	{
	private:
		string skin, backbling, pickaxe;
	public:
		FortniteLocker(){}
		void setSkin(const string& s)
		{
			this->skin = s;
		}
		void setBackbling(const string& b)
		{
			this->backbling = b;
		}
		void setPickaxe(const string& p)
		{
			this->pickaxe = p;
		}
		void displayInfo() const
		{
			cout << this->skin << ", " << this->backbling << ", " << this->pickaxe << endl;
		}
		~FortniteLocker(){}
	};

	class LockerBuilder
	{
	private:
		unique_ptr<FortniteLocker> locker;
	public:
		LockerBuilder()
		{
			this->locker = make_unique<FortniteLocker>();
		}
		void setSkin(const string& s)
		{
			locker->setSkin(s);
		}
		void setBackbling(const string& b)
		{
			locker->setBackbling(b);
		}
		void setPickaxe(const string& p)
		{
			locker->setPickaxe(p);
		}
		unique_ptr<FortniteLocker> &getLocker()
		{
			return this->locker;
		}

	};

	void test()
	{
		LockerBuilder builder;
		builder.setBackbling("frozen wings");
		builder.setSkin("black knight");
		builder.setPickaxe("the reaper");
		unique_ptr<FortniteLocker> mySkin = move(builder.getLocker());
		mySkin->displayInfo();
	}
}

namespace BobTheBuilder
{
	using namespace::std;
	class House
	{
	private:
		string paint;
		int floors, bathrooms;
	public:
		House():floors(0), bathrooms(0), paint(""){}
		void setFloors(int f) { this->floors = f; }
		void setBathrooms(int b) { this->bathrooms = b; }
		void setPaint(const string& p) { this->paint = p; }
		void displayInfo() const
		{
			cout << floors << "floors, " << bathrooms << "bathrooms, " << paint << endl;
		}
		~House(){}
	};

	class virtualHouseBuilder
	{
	protected:
		shared_ptr<House> house;
	public:
		virtualHouseBuilder() :house(make_shared<House>()) {}
		virtual void setParameters(const string& t1, int a, int b) = 0;
		virtual ~virtualHouseBuilder(){}
	};

	class HouseBuilder : public virtualHouseBuilder
	{
	public:
		HouseBuilder():virtualHouseBuilder(){}
		void setParameters(const string& paint, int floors, int bathrooms) override
		{
			this->house->setBathrooms(bathrooms);
			this->house->setFloors(floors);
			this->house->setPaint(paint);
		}
		shared_ptr<House> getHouse() 
		{
			return this->house;
		}
	};

	// dependency injection; iniekcja instancji House Builder buduj¹ca obiekty House 

	class ConstructionSite
	{
	private:
		unique_ptr<HouseBuilder> hb;
		vector<shared_ptr<House>> hs;
	public:
		ConstructionSite(unique_ptr<HouseBuilder>hb):hb(move(hb)), hs(){}
		void build(const string& paint, int floors, int bathrooms)
		{
			this->hb->setParameters(paint, floors, bathrooms);
			this->hs.push_back(move(this->hb->getHouse()));
			this->hb.reset(new HouseBuilder);
		}
		void getInfo() const
		{
			if(!this->hs.empty())
			for (const auto& it : hs)
			{
				it->displayInfo();
			}
		}
		~ConstructionSite(){}
	};

	void test()
	{
		unique_ptr<ConstructionSite> budowa = make_unique<ConstructionSite>(make_unique<HouseBuilder>());
		budowa->build("baby blue", 2, 2);
		budowa->build("celeste", 3, 4);
		budowa->getInfo();
	}

}