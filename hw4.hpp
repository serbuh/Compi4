#ifndef EX4
#define EX4

#include <string>
#include <list>
#include <stack>
#include <tuple>


typedef enum {CELSIUS_T, FAHRENHEIT_T, KELVIN_T, BOOL_T, INT_T, STRING_T} Type;
typedef std::tuple<int,int,Type> CaseElem;

typedef struct{
	std::string id;
	std::string string;
	
	int num;
	bool boolean;
	Type type;
	
	std::string rel_op;
	std::string place;

	std::list<int> truelist;
	std::list<int> falselist;
	std::list<int> nextlist;
	std::list<int> breaklist;
	std::stack<CaseElem> caselist;
	//std::stack<int> case_num_list;
	//std::stack<int> case_instr_list;
	int instruct;


}Var;

#define YYSTYPE Var

#endif