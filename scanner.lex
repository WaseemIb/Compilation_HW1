%{
/* Definiton section */
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap

digit                         ([0-9])
letter                        ([a-zA-Z])
whitespace                    ([\n\r \t])
printableChar                 ((\\[nrt\\"0])|(\\(x[0-7][0-9a-fA-F]))|([ -!#-\[\]-~\t]))
//escapeSeq                   (\\((x[0-7][0-9a-fA-F])|[\\nrt0\"]))

%%
/* Rules Section */
"int"                         return INT;
"byte"                        return BYTE;
"b"                           return B;
"bool"                        return BOOL;
"&&"                          return AND;
"||"                          return OR;
"!"                           return NOT;
"true"                        return TRUE;
"false"                       return FALSE;
"return"                      return RETURN;
"if"                          return IF;
"else"                        return ELSE;
"while"                       return WHILE;
"break"                       return BREAK;
"continue"                    return CONTINUE;
";"                           return SC;
"("                           return LPAREN;
")"                           return RPAREN;
"{"                           return LBRACE;
"}"                           return RBRACE;
"="                           return ASSIGN;
(==|!=|<=|>=|<|>)             return RELOP;
[+\-*\/]                      return BINOP;
(\/\/)[^\n\r]*                return COMMENT;
{letter}({letter}|{digit})*   return ID;
(([1-9]{digit}*)|0)           return NUM;
\"{printableChar}*\"          return STRING;
\"{printableChar}*            return UNCLOSED_STRING;
\"{printableChar}*\\([^\\ntr\"0])|x(([^0-7][^0-9a-fA-F])|([^0-7][0-9a-fA-F])|([0-7][^0-9a-fA-F]))
                              return  BAD_ESCAPE_SEQUENCE;
{whitespace}                  ;
.                             return ERROR;
%%
