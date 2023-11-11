%{
#include "simple_lang.tab.h"
%}

%option noyywrap

%%

[0-9]+                  { yylval = atoi(yytext); return NUMBER; }
[ \t]+                  ; /* Ignore white space. */
\n                      ; /* Ignore new lines. */
"print"                 { return PRINT; }
"("                     { return '('; }
")"                     { return ')'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
";"                     { return ';'; }
.                       { /* Ignore other characters */ }

%%