%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern void yyerror(char *s);

#define YYSTYPE int  // Define the type of `yylval` here if not using %union

%}

%token NUMBER PRINT
%left '+' '-'
%left '*' '/'

%start program

%%

program
    : statements
    ;

statements
    : /* empty */
    | statements statement
    ;

statement
    : PRINT expression ';'  { printf("%d\n", $2); }
    ;

expression
    : NUMBER                { $$ = $1; }
    | expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { $$ = $1 / $3; }
    | '(' expression ')'    { $$ = $2; }
    ;

%%

void yyerror(char *s) {
  fprintf(stderr, "Error: %s\n", s);
}