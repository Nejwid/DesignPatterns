#pragma once
#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

namespace bridge {
	using namespace ::std;

	class Shape {
	public:
		virtual string getType() const = 0;
		virtual ~Shape() {}
	};

	class Drawing {
	protected:
		unique_ptr<Shape> shape;
	public:
		Drawing(unique_ptr<Shape> s):shape(move(s)){}
		virtual void draw() = 0;
		virtual ~Drawing(){}
	};

	//=============================================//

	class DrawOnScreen : public Drawing {
	public:
		DrawOnScreen(unique_ptr<Shape> s):Drawing(move(s)){}
		void draw() override {
			cout << "Drawing on screen" << shape->getType() << endl;
		}
	};

	class Print : public Drawing {
	public:
		Print(unique_ptr<Shape> s) :Drawing(move(s)) {}
		void draw() override {
			cout << "Printing on papersheet " << shape->getType() << endl;
		}
	};

	//==============================================//

	class Rectangle : public Shape {
	public:
		string getType() const override{
			return "rectangle";
		}
	};

	class Triangle : public Shape {
	public:
		string getType() const override{
			return "triangle";
		}
	};
}


namespace bridge_Shelter {
	using namespace ::std;

	class Animal {
	protected:
		string name;
		int age;
	public:
		Animal(string s, int n):name(s), age(n){}
		virtual void speak() const = 0;
		void displayInfo() const{
			cout << name << ", " << age << " ";
		}
		int getAge() const{
			return age;
		}
		bool operator<(const Animal& other){
			return age < other.age;
		}
		virtual ~Animal(){}
	};

	class Dog : public Animal{
	public:
		Dog(string s, int n):Animal(s,n){}
		void speak() const override{
			cout << "wooof" << endl;
		}
	};
	class Cat : public Animal
	{
	public:
		Cat(string s, int n) :Animal(s, n) {}
		void speak() const override{
			cout << "meoow" << endl;
		}
	};
	class Bird : public Animal{
	public:
		Bird(string s, int n) :Animal(s, n) {}
		void speak() const override{
			cout << "tweet" << endl;
		}
	};

	class Shelter{
	private:
		list <unique_ptr<Animal>> animals;
	public:
		void addDog(string s, int n){
			animals.emplace_back(make_unique<Dog>(s, n));
		}
		void addCat(string s, int n){
			animals.emplace_back(make_unique<Cat>(s, n));
		}
		void addBird(string s, int n){
			animals.emplace_back(make_unique<Bird>(s, n));
		}
		void showInfo() const{
			for (const auto& it : animals)
			{
				it->displayInfo(); it->speak();
			}
		}
		list <unique_ptr<Animal>> getAnimals(){
			return animals;
		}
		void adoptAnimal(interfaceShelter::AdoptionStrategy &strategy){
			unique_ptr<Animal> adoptedAnimal = strategy.adopt(animals);
			if (adoptedAnimal)
			{
				for (auto it = animals.begin(); it != animals.end(); ++it)
				{
					if (it->get() == adoptedAnimal.get())
					{
						animals.erase(it);
						break;
					}
				}
			}
		}
	};
}

namespace interfaceShelter{
	using namespace ::std;
	namespace bs = bridge_Shelter;

	class AdoptionStrategy{
	public:
		virtual unique_ptr<bs::Animal> adopt(list <unique_ptr<bs::Animal>> animals) = 0;
		virtual ~AdoptionStrategy(){}
	};

	class AdoptOldest : public AdoptionStrategy{
	public:
		unique_ptr<bs::Animal> adopt(list <unique_ptr<bs::Animal>> animals) override
		{
			if (!animals.empty())
			{
				sort(animals.begin(), animals.end());
				animals.front()->displayInfo();
				return move(animals.front());
			}
			return nullptr;
		}
	};

	class AdoptByType : public AdoptionStrategy{
	private:
		unique_ptr<bs::Animal> animal;
	public:
		AdoptByType(unique_ptr<bs::Animal> animal):AdoptionStrategy(),animal(move(animal)){}
		unique_ptr<bs::Animal> adopt(list <unique_ptr<bs::Animal>> animals) override{ 
			for (auto& it : animals){
				if (dynamic_cast<bs::Bird*>(animal.get()) == dynamic_cast<bs::Bird*>(it.get())){
					it->displayInfo();
					return move(it); 
				}
				else if (dynamic_cast<bs::Cat*>(animal.get()) == dynamic_cast<bs::Cat*>(it.get())){
					it->displayInfo();
;					return move(it); 
				}
				else if (dynamic_cast<bs::Dog*>(animal.get()) == dynamic_cast<bs::Dog*>(it.get())){
					it->displayInfo();
					return move(it);
				}
			}
			return nullptr;
		}
	};

	class AdoptLongestStay : public AdoptionStrategy{
	public:
		unique_ptr<bs::Animal> adopt(list <unique_ptr<bs::Animal>> animals) override{
			if (!animals.empty()){
				animals.front()->displayInfo();
				return move(animals.front());
			}
			return nullptr;
		}
	};
}