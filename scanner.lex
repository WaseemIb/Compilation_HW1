%{
/* Definiton section */
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap

digit                         ([0-9])
letter                        ([a-zA-Z])
whitespace                    ([\n\r \t])
printableChars                ([ -~]|whitespace)
escapeSeq                     (\\((x[0-7][0-9a-fA-F])|[\\nrt0"]))

%%
/* Rules Section */
"int"                         {return INT;}
"byte"                        {return BYTE;}
//B                           {}
"bool"                        {return BOOL;}
"&&"                          {return AND;}
"||"                          {return OR;}
"!"                           {return NOT;}
"true"                        {return TRUE;}
"false"                       {return FALSE;}
"return"                      {return RETURN;}
"if"                          {return IF;}
"else"                        {return ELSE;}
"while"                       {return WHILE;}
"break"                       {return BREAK;}
"continue"                    {return CONTINUE;}
";"                           ;
"("                           {return LPAREN;}
")"                           {return RPAREN;}
"{"                           {return LBRACE;}
"}"                           {return RBRACE;}
"="                           {return ASSIGN;}
(==|!=|<=|>=|<|>)             {return RELOP;}
[+-*\/]                       {return BINOP;}
//COMMENT                     {}
{letter}({letter}|{digit})*   {return ID;}
{digit}+                      {return NUM;}
//STRING                      {}
.                             {}

%%
