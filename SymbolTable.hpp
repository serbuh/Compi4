#include <stdlib.h>
#include <iostream>
#include <stack>
#include <list>
#include <tuple>
#include "output.hpp"
#include <string>
#include "hw4.hpp"

#include "output.hpp"

using namespace output;
using namespace std;

typedef tuple<string, int, string, string, bool> tableElement;
typedef list<tableElement> table;
typedef list<table> Tables;
typedef list<int> Offsets;

class SymbolTable{

private:
	Offsets offsets;
	Tables tables;

public:
	SymbolTable(){
		offsets.push_front(0);
		tables.push_front(table());
	}
	
  int tableSize(){
    table currTable = *(tables.begin());
    return currTable.size();
  }

	//Adds an element to the top table on the tables stack
	void addElement(string id,string type,string place, bool isInit){
		//std::cout << id;
		int offset = offsets.front();
		tableElement newElement(id , offset , type , place, isInit);
		tables.front().push_back(newElement);
		offsets.pop_front();
		offsets.push_front(offset + 1);
	}

	//Adds a new table to the tables stack and offsets stack
	void addTable(){
		offsets.push_front(offsets.front());
		tables.push_front(table());
	}

	//Remove a table from the tables stack and an offset from the offsets stack
	void removeTable(){
		tables.pop_front();
		offsets.pop_front();
	}
	
	//Print table when exiting scope
	void printTable(){
		table t = tables.front();
		for (table::iterator iter = t.begin() ; iter != t.end() ; iter++){
			printVar(get<0>(*iter).c_str(), get<1>(*iter), get<2>(*iter).c_str());
		}
	}

	//Find if current scope or any parent scope has an element id
	bool contains(string id){
		//std::cout << "Contains " << id << std::endl;
		string id2search(id);
		for (Tables::iterator table = tables.begin() ; table != tables.end() ; table++ ){
			for (table::iterator elem = (*table).begin(); elem != (*table).end(); elem++){
				string cuurentId(get<0>(*elem));
				if (cuurentId == id2search)
					return true;
			}
		}
		return false;
	}

	// Return the type of the element id
	Type find(string id){
		for (Tables::iterator table = tables.begin(); table != tables.end(); table++){
			for (table::iterator elem = (*table).begin(); elem != (*table).end(); elem++){
				string cuurentId(get<0>(*elem));
				if (cuurentId == id)
					return string2type(get<2>(*elem));
			}
		}
		// never will happen - I hope...
		return BOOL_T;
	}

	string getPlace(string id){
		for (Tables::iterator table = tables.begin(); table != tables.end(); table++){
			for (table::iterator elem = (*table).begin(); elem != (*table).end(); elem++){
				string cuurentId(get<0>(*elem));
				if (cuurentId == id)
					return get<3>(*elem);
			}
		}
		// never will happen - I hope...
		return "FUCK!!";	
	}

	void setInit(string id){
		string id2search(id);
		for (Tables::iterator table = tables.begin(); table != tables.end(); table++){
			for (table::iterator elem = (*table).begin(); elem != (*table).end(); elem++){
				string cuurentId(get<0>(*elem));
				if (cuurentId == id2search)
					get<4>(*elem) = true;
			}
		}
	}

	bool isInit(string id){
		string id2search(id);
		for (Tables::iterator table = tables.begin(); table != tables.end(); table++){
			for (table::iterator elem = (*table).begin(); elem != (*table).end(); elem++){
				string cuurentId(get<0>(*elem));
				if (cuurentId == id2search)
					return get<4>(*elem);
			}
		}
		// should not happen if id exists
		return false;
	}

	list<tableElement> getElementsOfType(Type type){
		list<tableElement> list;
		for (Tables::iterator table = tables.begin(); table != tables.end(); table++){
			for (table::iterator elem = (*table).begin(); elem != (*table).end(); elem++){
				Type cuurentType = string2type(get<2>(*elem));
				if (cuurentType == type)
					list.push_front(*elem);
			}
		}
		return list;
	}

	

	Type string2type(string type){
		if(type == "CELSIUS")
			return CELSIUS_T;
		else if(type == "FAHRENHEIT")
			return FAHRENHEIT_T;
		else if(type == "KELVIN")
			return KELVIN_T;
		else if(type == "BOOL")
			return BOOL_T;
		else if(type == "INT")
			return INT_T;
		else if(type == "STRING")
			return STRING_T;
		else
			cout << "NOT GOING TO HAPPEN!!!" << endl;
	}
};