%{
//#include "general.h"
//#include "error.h"
#include "fix.hpp"
#include "my-symbol.h"
#include "my-ast.hpp"
#include <iostream>
#include "parser.hpp" //prepei na ereunisw
//`#include "parser.tab.h"
#include "lexer.h"
#include <cstdlib>
//exw kanei malakia
//o compiler c++ 
//pernaei ta pragmata mia fora
//prepei na frontisw na kserei apo 
//prin
//opote na exw sto nou mou 
//oti ta header files
// na mpoun me katallhlh seira
// #include  "my-ast.hpp"
//#include  "yolo.h"


#define T_eof 0
%}


/*%locations*/
%option yylineno
%option noyywrap



START         "(*"
END           "*)"
SIMPLE        [^*]
COMPLEX       "*"[^)]


ID            [a-zA-Z][a-zA-Z0-9_]*
DIGIT         [0-9]
ESCAPE        \\n|\\t|\\r|\\0|\\\\|\\\'|\\\"
NEW_LINE      [\n]
CHAR          [^\'\"\\]
SPACE         [ \t\n\r]

%%



"and"           { return T_and ; } 

"array"         { return T_array ;}

"begin"         { return T_begin ; }

"boolean"       { return T_boolean ;}

"char"          { return T_char ; }

"dispose"      { return T_dispose ; }

"div"          { return T_div ; }

"do"           { return T_do ; }

"else"          { return T_else ; }

"end"           { return T_end ; }

"false"        { return T_false ; }

"forward"       { return T_forward ; }

"function"     { return T_function ; } 

"goto"         { return T_goto ; }

"if"           { return  T_if ; }

"integer"      { return T_integer ; }
 
"label"        { return T_label ; }

"mod"        { return T_mod ; }

"new"       { return T_new ; }

"nil"       { return T_nil ; }

"not"       { return T_not ; }

"of"        { return T_of ; }
 
"or"        { return T_or ; }

"procedure"  { return T_procedure ; }
 
"program"      { return T_program ; }

"real"        { return T_real ;  }

"result"     { return T_result ;  }

"return"     { return T_return ;  }

"then"      { return T_then ; }

"true"     { return T_true ; }

"var"         { return T_var ; }

"while"       { return T_while ; }

"="     { yylval.op = yytext[0]; return yytext[0];  }  

">"      { yylval.op = yytext[0]; return yytext[0]; }

"<"   { yylval.op = yytext[0]; return yytext[0];  }

"<>"   { return T_someth ; }

">="    { return T_gequal ; }

"<="    { return T_lequal ; }
 
"+"     { yylval.op = yytext[0]; return yytext[0] ; }

"-"    { yylval.op = yytext[0]; return yytext[0];  }

"*"    { yylval.op = yytext[0]; return yytext[0];  }

"/"    {  yylval.op = yytext[0]; return yytext[0]; }

"^"    { yylval.op = yytext[0]; return yytext[0]; }

"@"    { yylval.op = yytext[0]; return yytext[0]; }

":="   { return T_assign ; }

";"    { yylval.op = yytext[0]; return yytext[0]; }



\.    {  yylval.op = yytext[0]; return yytext[0]; }


"("   {  yylval.op = yytext[0]; return yytext[0]; }

")"   {  yylval.op = yytext[0]; return yytext[0]; }

":"    { yylval.op = yytext[0]; return yytext[0];  }

","   { yylval.op = yytext[0]; return yytext[0];  } 


"["   { yylval.op = yytext[0]; return yytext[0]; }

"]"    {  yylval.op = yytext[0]; return yytext[0]; }

{ID}   { yylval.tid = new  T_id(std::string(yytext,yyleng)); return T_ID ;  }

{DIGIT}+  { yylval.num= std::atoi(yytext); return T_INTEGER ; }   

{DIGIT}+\.{DIGIT}+((E|e)("+"|"-")?{DIGIT}+)?     {  yylval.fl = std::atof(yytext) ; return T_REAL ;   }  


    /* sxolio

\'({ESCAPE}|{CHAR})\'    {  yylval.var= new std::string(yytext,yyleng) ; return T_CHAR ;         }

    */
 
\'({ESCAPE}|{CHAR})\'    {  int n = 0; yylval.op = fixChar(yytext + 1, n) ; return T_CHAR;          }



    /*
\"({ESCAPE}|{CHAR})*{NEW_LINE}?\"     { yylval.var= new std::string(yytext +1 ,yyleng -2 ); return T_STRING ; }
    */

\"({ESCAPE}|{CHAR})*{NEW_LINE}?\"     {  yylval.var = new std::string( fixString(yytext + 1) )    ; return T_STRING; }
                                            


{SPACE}+   { ;  }


{START}({SIMPLE}|{COMPLEX})*{END}   { ; }

.    { yyerror("MALLON KATI PHGE STRAVAAAAAA") ; }

%%
/*
int main(int argc, char *argv[]){
  
    yyin = fopen(argv[1], "r");
    yylex();
    fclose(yyin);
}
*/
void yyerror(const char *str)
{
    fprintf(stderr,"Error | Line: %d\n%s\n",yylineno,str);
}
