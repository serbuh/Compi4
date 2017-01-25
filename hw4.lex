%{

/* Declarations section */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "hw4.hpp"
#include "hw4.tab.hpp"

extern int yylineno;
#include "output.hpp"
using namespace output;

%}

%option yylineno
%option noyywrap


LP   			(\()
RP   			(\))
LC   			(\{)
RC   			(\})
SC	        	(;)
COLON 			(:)
ASSIGN			(=)
PLUS			(\+)
MINUS			(-)
MULT			(\*)
DIV				(\/)
REL_OP			(<=|>=|==|!=|>|<)
AND				(and)
OR				(or)
CELSIUS			(C)
FAHRENHEIT		(F)
KELVIN 			(K)
INT 			(int)
PRINT     		(print)
INPUT			(input)
ID 				(([a-zA-Z_])+)
STRING 			(\"[^"]*\")
TRUE 			(true)
FALSE 			(false)
IF 				(if)
ELSE 			(else)
WHILE 			(while)
BREAK 			(break)
NOT 			(not)
BOOL 			(bool)
NUM 			([1-9][0-9]*|0)
SWITCH 			(switch)
CASE 			(case)
COMMENT 		("\/\/"[^\n]*\n)
whitespace		([ \t\n])

%%

{LP}				{return LP;}
{RP}				{return RP;}
{LC}				{return LC;}
{RC}				{return RC;}
{SC}				{return SC;}
{COLON}				{return COLON;}
{ASSIGN}			{return ASSIGN;}
{PLUS}				{return PLUS;}
{MINUS}				{return MINUS;}
{MULT}				{return MULT;}
{DIV}				{return DIV;}
{REL_OP}			{
						yylval.rel_op = yytext;
						return REL_OP;
					}
{AND}				{return AND;}
{OR}				{return OR;}

{CELSIUS}			{
						yylval.type = CELSIUS_T;
						return CELSIUS;
					}

{FAHRENHEIT}		{
						yylval.type = FAHRENHEIT_T;
						return FAHRENHEIT;
					}

{KELVIN} 			{
						yylval.type = KELVIN_T;
						return KELVIN;
					}

{INT} 				{
						yylval.type = INT_T;
						return INT;
					}

{PRINT}     		{return PRINT;}
{INPUT}				{return INPUT;}

{TRUE} 				{
						yylval.type = BOOL_T; 
						yylval.boolean = true; 
						return TRUE;
					}

{FALSE} 			{
						yylval.type = BOOL_T;
						yylval.boolean = false;
 						return FALSE;
 					}
{IF} 				{return IF;}
{ELSE} 				{return ELSE;}
{WHILE} 			{return WHILE;}
{BREAK} 			{return BREAK;}
{NOT} 				{return NOT;}

{BOOL} 				{
						yylval.type = BOOL_T;
						return BOOL;
					}

{NUM} 				{
						yylval.num = atoi(yytext);
						return NUM;
					}

{SWITCH} 			{return SWITCH;}
{CASE} 				{return CASE;}

{ID} 				{
						yylval.id = yytext;
						return ID;
					}

{STRING} 			{
						yylval.type = STRING_T; 
						yylval.string = yytext;
						return STRING;
					}
{whitespace}		;
{COMMENT}			;
.					{
						errorLex(yylineno);
						exit(1);
					}		

%%
