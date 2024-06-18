#include "tokens.hpp"
#include <string>
#include <iostream>

void printToken(int);
std::string tokenToString(int);
std::string stringFormat();
std::string invalidStringFormat(int);
std::string badEscapeFormat();
std::string unclosedStringformat();

int main()
{
	int token;
	while(token == yylex()) {
        printToken(token);
	}
	return 0;
}

void printToken(int token) {
    if(token <= 28)
        std::cout << yylineno << " " << tokenToString(token) << " " << yytext << std::endl;
    if(token == ERROR || token == UNCLOSED_STRING || token == BAD_ESCAPE_SEQUENCE){
        if(token != ERROR) {
            std::cout << tokenToString(token) << std::endl;
        }
        exit(0);
    }
}

std::string tokenToString(int token) {
    switch (token) {
        case INT: return "INT";
        case BYTE: return "BYTE";
        case B: return "B";
        case BOOL: return "BOOL";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        case TRUE: return "TRUE";
        case FALSE: return "FALSE";
        case RETURN: return "RETURN";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case WHILE: return "WHILE";
        case BREAK: return "BREAK";
        case CONTINUE: return "CONTINUE";
        case SC: return "SC";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case ASSIGN: return "ASSIGN";
        case RELOP: return "RELOP";
        case BINOP: return "BINOP";
        case COMMENT: return "COMMENT //";
        case ID: return "ID";
        case NUM: return "NUM";
        case STRING: return stringFormat();
        case ERROR: return std::string("Error ") + yytext;
        case UNCLOSED_STRING: return invalidStringFormat(token);
        case BAD_ESCAPE_SEQUENCE: return invalidStringFormat(token);
        default: break;
    }
    return "";
}
std::string stringFormat(){
    std::string str(yytext);
    return std::string("STRING ") + str;
}
std::string unclosedStringFormat(){
    return "Error unclosed string";
}
std::string badEscapeFormat(){

    return "";
}
std::string invalidStringFormat(int token){
    if(token == UNCLOSED_STRING)
        return unclosedStringFormat();
    else if (token == BAD_ESCAPE_SEQUENCE)
        return badEscapeFormat();

}