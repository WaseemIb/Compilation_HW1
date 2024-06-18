#include "tokens.hpp"
#include <string>
#include <iostream>

using namespace std;

void printToken(int);
string tokenToString(int);
string stringFormat();
string invalidStringFormat(int);
string badEscapeFormat();

int main()
{
	int token;
	while(token == yylex()) {
        printToken(token);
	}
	return 0;
}

void printToken(int token) {
    if(token < END_OF_TYPES)
    {
        string toPrint = to_string(yylineno) + " " + tokenToString(token);
        if(token != COMMENT && token != STRING)
            toPrint += " " + string(yytext);
        cout << toPrint << endl;
        return;
    }
    cout << tokenToString(token) << endl;
    exit(0);
}

string tokenToString(int token) {
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
        case NOT_FOUND: return string("Error ") + yytext;
        case UNCLOSED_STRING: return invalidStringFormat(token);
        case BAD_ESCAPE_SEQUENCE: return invalidStringFormat(token);
        default: break;
    }
    return "";
}

string stringFormat() {
    string str = string(yytext);
    str = str.substr(1, str.size() - 2);
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] != '\\')
            continue;
        string tmp;
        if(str[i + 1] == 'n')
            str = str.substr(0, i) + '\n' + str.substr(i + 2);
        if(str[i + 1] == 'r')
            str = str.substr(0, i) + '\r' + str.substr(i + 2);
        if(str[i + 1] == 't')
            str = str.substr(0, i) + '\t' + str.substr(i + 2);
        if(str[i + 1] == '\\')
            str = str.substr(0, i) + '\\' + str.substr(i + 2);
        if(str[i + 1] == '\"')
            str = str.substr(0, i) + '\"' + str.substr(i + 2);
        if(str[i + 1] == 'x')
        {
            string hex = str.substr(i + 2, 2);
            int asciiVal = stoi(hex, nullptr, 16);
            char c = (char)asciiVal;
            str = str.substr(0, i) + c + str.substr(i + 4);
        }
    }
    return string("STRING ") + str;
}

string badEscapeFormat() {
    string str = string(yytext);
    size_t lastBackSlash = str.find_last_of('\\');
    string badEscape = str.substr(lastBackSlash + 1);
    return "Error undefined escape sequence " + badEscape;
}

string invalidStringFormat(int token) {
    if(token == UNCLOSED_STRING)
        return "Error unclosed string";
    else // BAD_ESCAPE_SEQUENCE
        return badEscapeFormat();
}