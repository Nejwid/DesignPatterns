#pragma once
#include <iostream>
#include <stack>

namespace memento_{
	using namespace::std;

	class Memento{
	private:
		string state;
	public:
		Memento(const string& s):state(s){}
		string getState() const { return state; }  // jedna instancja memento przechowuje jeden stan
	};

	class Source{   // klasa �r�d�owa kt�rej stan przechowuje memento ; za pomoc� memento mo�emy przywr�cic stan �r�d�a
	private:
		string state;
	public:
		void setState(const string& s) { state = s; }
		string getState() const { return state; }
		Memento save() const{
			return Memento(state);    //  za pomoc� funkcji memento mo�emy stworzy� obiekt memento kt�ry od razu zapiszemy do vector<memento>
		}
		void restore(const Memento& m){
			state = m.getState();
		}
	};

	class Historia{
	private:
		stack<Memento> h;
	public:
		void addMemento(const Memento& m){
			h.push(m);
		}
		Memento przywr�c(){
			if (!h.empty()){
				Memento history = h.top();
				h.pop();
				return history;
			}
		}
	};

	class HistoryManager{
	private:
		Source& src;
		Historia& hist;
	public:
		HistoryManager(Source& src, Historia& hist):src(src), hist(hist){}
		void setState(const string& s){
			src.setState(s);
		}
		void saveState(){
			hist.addMemento(src.save());
		}
		void returnState(){
			src.restore(hist.przywr�c());
		}
		void showState(){
			cout << src.getState() << endl;
		}
		~HistoryManager(){}
	};

	void test()
	{
		Source tekstEditor;
		Historia editorHistory;
		HistoryManager menago(tekstEditor, editorHistory);
		menago.setState("fortnite");
		menago.saveState();
		menago.setState("sdadsa");
		menago.setState("cs go");
		menago.saveState();
		menago.showState();
		menago.returnState();
		menago.returnState();
		menago.showState();
	}
}
