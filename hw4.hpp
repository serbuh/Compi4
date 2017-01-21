
#include <string>



typedef enum {CELSIUS_T, FAHRENHEIT_T, KELVIN_T, BOOL_T, INT_T, STRING_T} Type;


typedef struct{
	std::string id;
	std::string string;
	
	int integer;
	bool boolean;
	Type type;
	
	std::string rel_op;
	std::string place;
	//int lineNum;

}Var;

#define YYSTYPE Var
