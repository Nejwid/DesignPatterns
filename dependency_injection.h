#pragma once
#include <iostream>
#include <memory>
#include <string>

namespace dependencyInjection
{
	using namespace ::std;

	class iProdukt
	{
	protected:
		string name;
	public:
		virtual void sendAlert() const = 0;
		virtual string getName() const
		{
			return name;
		}
		virtual ~iProdukt(){}
	};

	class iPhone : public iProdukt
	{
	public:
		iPhone():iProdukt()
		{
			this->name = "iPhone twojego starego";
		}
		void sendAlert() const override
		{
			cout << "" << endl;
		}
		string getName() const override
		{
			return iProdukt::getName();
		}
	};

	class AppleHub
	{
	private:
		shared_ptr<iProdukt> device;
	public:
		AppleHub(shared_ptr<iProdukt> p):device(move(p)){}
		void notify() const
		{
			cout << this->device->getName() << " sent alert: ";
			this->device->sendAlert();
		}
		~AppleHub(){}
	};

	void test()
	{
		shared_ptr<iProdukt> iphone = make_shared<iPhone>();
		unique_ptr<AppleHub> hub = make_unique<AppleHub>(iphone);
		hub->notify();
	}

}
