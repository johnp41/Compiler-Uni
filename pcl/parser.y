%{
//#include "general.h"
//#include "error.h"
extern "C"{
#include "symbol.h"
}
//#include "symbol.h"
#include  "sem.hpp"
#include "my-ast.hpp"
#include "my-llvm.hpp";
#include <string> 
#include <cstdio>

void yyerror(const char*);
int yylex(void);


extern FILE*    yyin;
Program* t;
bool flag ;
std::list<Local *>  los ;


%}

%token T_array      "array"
%token T_begin      "begin"
%token T_boolean    "boolean"
%token T_char       "char"
%token T_dispose    "dispose"
%token T_do         "do"
%token T_else       "else"
%token T_end        "end"
%token T_false      "false"
%token T_forward    "forward"
%token T_function   "function"
%token T_goto       "goto"
%token T_if         "if"
%token T_integer    "integer"
%token T_label      "label"
%token T_new        "new"
%token T_nil        "nil"
%token T_not        "not"
%token T_of         "of"
%token T_or         "or"
%token T_procedure  "procedure"
%token T_program    "program"
%token T_real       "real"
%token T_result     "result"
%token T_return     "return"
%token T_then       "then"
%token T_true       "true"
%token T_var        "var"
%token T_while      "while"
%token T_someth     "<>"
%token T_gequal     ">="
%token T_lequal     "<="
%token T_assign     ":="
%token<num> T_INTEGER   /* "INTEGERCONST" */
%token<tid> T_ID       /*  "ID" */
%token<fl> T_REAL     /*  "REALCONST" */
%token<op> T_CHAR     /*  "CHARCONST" */
%token<var> T_STRING   /*  "STRINGLITERAL" */



%nonassoc  '=' T_someth T_gequal T_lequal '<' '>'
%left '+' '-' T_or
%left  T_mod  '*' '/' T_div T_and
%nonassoc "not"
%precedence  UNMINUS UNPLUS
%precedence  DER
%precedence  RE
%precedence  ARR





%union {

  T_id                            *tid;

  Type   type;
  int    num ;
  float  fl ;
  std::string                     *var;
  char                            op ;
  Program                         *prog ;
  Body                            *bo ;
  std::list<Local *>              *locs  ;  
//  Local     *locs
  std::list<T_id *>                *kat3 , *kat2 ;
  Local                            *kat1 ;
  Header                           *head;
  std::list<Formal *>              *kat4;
  Formal                           *forma;
  Block                            *blck;
  std::list<Stmt *>                *kat8;
  Stmt                             *stm;
  Expr                             *exo;
  char                               yo;
  Lval                             *lval;
  Rval                             *rval;
  Unop                             *unop;
  Binop                            *binop;
  Call                             *call;
  std::list<Expr *>                *kat13;




}

/*edw ginontai oi dhlwseis ton typon ton
non terminals */
%type<prog>         program 
%type<bo>           body
%type<locs>         locals vars vars2
%type<kat3>         kati3  kati2  kati6
%type<kat1>         kati1  local  
%type<head>         header
%type<kat4>         kati4  kati5
%type<forma>        formal
%type<blck>         block
%type<kat8>         kati8
%type<stm>          stmt  notif withif
%type<lval>         lvalue  lvalue_simple 
%type<rval>         rvalue  rvalue_simple 
%type<call>         call
%type<kat13>        kati13 kati14
%type<type>         type
%type<exo>          expr   
/* to new gurizei deikth --NA 8UMAMAI */

%%
program:/*prepei naorisw type ID terminal */
      "program" T_ID ';' body '.'           {   t = $$ = new Program($2 , $4) ; }
     ;

body:
   locals block                   { $$ = new Body($1,$2);}
    ;

locals:
      /*nothin*/                  {$$ = new std::list<Local *> ;}
      | locals local              { $1->push_back($2) ; $$=$1 ;  }
      | locals vars               { $1->merge(*$2) ; $$ = $1 ;}
      ;

vars: 
     "var" kati1 vars2         { $3->push_back($2) ; $$ = $3 ; }

vars2:
        /*nothin*/                  {$$ = new std::list<Local *> ;}
        | vars2 kati1               {$1->push_back($2) ; $$ = $1 ;}

local:

 /*    "var" kati1                  { $$ = $2 ;   }  */
 /*    | "label" T_ID  kati2 ';'    {$3->push_back($2); $$ = new Local(label,$3); flag = false ;}*/
     "label" T_ID  kati2 ';'    {$3->push_back($2); $$ = new Local(label,$3); flag = false ;}
     | header ';'  body ';'       {$$ = new Local(header,$1,$3); flag = false ;}
     | "forward" header ';'       {$$ = new Local(forwad,$2); flag = false ;}
     ;


/*
kati30 : 
                     {$$ = new Local(var);}
       | kati30 kati1                 {$$ = $1 ; locis->push_back($$2);}
*/

/*eini pointer se lista apo ids */
kati3:
      /*nothing */                {$$ = new std::list<T_id *> ;}
     | kati3  ',' T_ID            {$1->push_back($3);
                                  
                                  $$ = $1 ;}
     ;




/*pointer se local */
kati1:
 /*         {$$ = new Local(var);}  */
 /*    |  T_ID  kati3 ':' type ';'   {$2->push_back($1)  ;     $$ = new Local(var,$2,$4);  } */
       T_ID  kati3 ':' type ';'   {$2->push_back($1)  ;     $$ = new Local(var,$2,$4);  } 

     ;

/*lista apo locals */

kati2:
    /*nothing*/                   {$$ = new std::list<T_id *>;}
    | kati2 ','  T_ID             {$1->push_back($3); $$ = $1 ;}
    ;



/*edw exw meinei na to dw -1244*/ 


header: 
      "procedure" T_ID '(' kati5  ')'       {$$ = new Header(procedure,$2,$4);}
      | "function" T_ID '(' kati5 ')' ':' type  {$$ = new Header(function,$2,$4,$7);}
      ;







kati5:
     /*nothing*/                  {$$ = {} ;}  /* nmz den dxreiazotan */
     | formal kati4                {$2->push_back($1);$$ = $2 ;}
       // formal kati4                 {$2->push_back($1);$$ = $2 ;}
     ; 



/*lista apo formals to kati4*/
kati4:
     /*nothing*/                  {$$ = new std::list<Formal *> ;}
  /*   | kati4 ';' formal           {$1->push_back($3);$$ =  $1 ;} */
      |  ';'  formal kati4          {$3->push_back($2);$$ =  $3 ;} 
     ;


formal:
        T_ID kati6 ':' type    {$2->push_back($1); $$ = new Formal(value,$2,$4);}
      | "var" T_ID kati6 ':' type   {$3->push_back($2); $$ = new Formal(refernce,$3,$5);}
      ;
/*
var2:
    
    | "var" 
    ;
*/
kati6: 
     /*nothing*/                  {$$ = new std::list<T_id *>;}
     | kati6 ',' T_ID             {$1->push_back($3);$$ = $1 ;}
     ;









type: 
     "integer"                    {$$ = typeInteger;}
    | "real"                      {$$ = typeReal; }
    | "boolean"                   {$$ = typeBoolean; }
    | "char"                      {$$ = typeChar;}
    | "array" '[' T_INTEGER ']'   "of" type   {$$ =typeArray($3,$6);}

    | "array"  "of"  type         {$$ = typeIArray($3) ;}
    
    | '^' type                    {$$ = typePointer($2);}
    ;                   







/*

type: 
     "integer"                    {$$ = }
    | "real"                      {$$ = new Type('r');}
    | "boolean"                   {$$ = new Type('b');}
    | "char"                      {$$ = new Type('c');}
    | "array"  kati7  "of" type   {$$ = new Type('a',$2,$4);}
    | '^' type                    {$$ = new Type('^',0,$2);}
    ;                   



kati7:
     /*nothing*/  /*                {$$  = 0 ;}
     | '[' T_INTEGER ']'          {$$ = $2;}
     ;
*/

/*8a mporoysa na to exw kanei kalutera
alla eixa etoimo constractor */
block:
     "begin" stmt kati8 "end"     {$$ = new Block($2,$3);}
     ;


kati8:
     /*nothing*/                   {$$ = new std::list<Stmt *>;}
     | kati8 ';' stmt              {$1->push_back($3);$$ = $1 ;}
     ;


/*to olo stmt*/
stmt: 
    notif                         { $$ = $1 ;}
    |withif                       { $$ = $1 ; }
    ;

/*logika 8a prepei na pros8esw char gia na kserw pou eimai */

/*pointer se stmt*/
notif:                            { $$ =  NULL ;} 
    | lvalue ":=" expr            {$$ = new Stmt(tlva,$1,$3);}
    | block                       {$$ = new Stmt(tblock,$1);}
    | call                        {  $$ = new Stmt(tcall,$1);}

/*    | kati9 */
    | "if" expr "then" notif  "else" notif  {$$ = new Stmt(tif,$2,$4,$6);}
/*    | "if" expr "then" stmt %prec  LOWER  */
    | "while" expr "do" notif     {$$ = new Stmt(twhile,$2,$4);}
    | T_ID ':' notif              {$$ = new Stmt(tid,$1,$3);}
    | "goto" T_ID                 {$$ = new Stmt(tgoto,$2);}
    | "return"                    {$$ = new Stmt(treturn);}
    | "new" '[' expr ']' lvalue         {$$ = new Stmt(tnew_ex,$5,$3);}
    | "new" lvalue                 {$$ = new Stmt(tnew,$2,NULL);}
    | "dispose"  lvalue                 {$$ = new Stmt(tdispose,$2);}
    | "dispose" '[' ']' lvalue          {$$ = new Stmt(tdispose_ar,$4);}
    ;



/*kai auto pinet se stmt*/
withif:
       T_ID ':' withif            {$$ = new Stmt(tid,$1,$3);}
      | "while" expr "do" withif  {$$ = new Stmt(twhile,$2,$4);}
      | "if" expr "then" stmt     {$$ = new Stmt(tif,$2,$4); }
      |  "if" expr   "then"  notif "else" withif {$$ = new Stmt(tif,$2,$4,$6);}
;






/* krataw expr */
/*
kati10:
                      {$$ = NULL; }
      | '[' expr ']'               {$$ = $2 ;}
      ;
*/
/*
kati11:
                                { $$ = 'o' ;}
      | '[' ']'                   { $$ = 'a'; }
      ;
*/
/*
lvalue:
        T_ID
       | "result"
       | T_STRING
       | lvalue  '[' expr ']'
       | expr '^'  /*mporei na mhn einai corect *//*
       | '(' lvalue ')'
       ;
/*
kati12:
      /*nothing*/
/*      | '[' expr ']'
      ;

*/


/*8a prepei meta na valw ena char */
/*edw uparxei provlhma me tid kai tstring 
8a prepei na ta allaksw kapw na ksexwrizoun*/


/* einai pointer se lvlal */
/*
lvalue:
        T_ID                      {$$ = new Lval($1);}
       | "result"                 {$$ = new Lval('r');}
       | T_STRING                 {$$ = new Lval($1);}
       | lvalue  '[' lvalue ']' %prec ARR   {$$ = new Lval($1,$3);}
       | lvalue  '[' rvalue ']' %prec ARR   {$$ = new Lval($1,$3);}
       | lvalue '^' %prec DER              {$$ = new Lval($1);}/*mporei na mhn einai corect */
/*       | rvalue '^'  %prec DER             {$$ = new Lval($1);}
       | '(' lvalue ')'           {$$ = new Lval($2);}
       ;

*/


expr : lvalue                    {$$ = new Expr(lva,$1,NULL);}
     | rvalue                     {$$ = new Expr(rva,NULL,$1);}
  /*   | rvalue2                     {$$ = new Expr(rva,NULL,$1);} */
     ;
/*    
rvalue2 :       expr   '+'   expr      
               {$$ = new Rval(tplus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}    
     
     
        |  expr   '-'   expr
               {$$ = new Rval(tminus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       |  expr   '*'   expr
               {$$ = new Rval(tmul_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}
                  

       |  expr   '/'   expr
               {$$ = new Rval(tslash_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       |  expr  T_div  expr
              {$$ = new Rval(tdiv_r , 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  T_mod  expr
               {$$ = new Rval(tmod_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       |  expr  "or"   expr
               {$$ = new Rval(tor_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  T_and expr
               {$$ = new Rval(tand_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   '='  expr
              {$$ = new Rval(tequal_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   "<>" expr
              {$$ = new Rval(twhot_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   '<'  expr
               {$$ = new Rval(tless_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   '>'  expr 
               {$$ = new Rval(tge_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  "<="  expr
               {$$ = new Rval(tleseq_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  ">="  expr 
              {$$ = new Rval(tgeq_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

     
      ;
*/
/*
lvalue2 : lvalue                  {$$ = $1 ;}
*/




/* typos lvalue */
lvalue  : lvalue_simple           {$$ = $1;}
        | lvalue '^' %prec DER    {$$ = new Lval(tref_lv , NULL,"",$1,NULL,NULL);   }
        | rvalue_simple '^' %prec DER {$$ = new Lval(tref_rv,NULL,"",NULL,NULL,$1); }
        ;


/*tupos lvalue */
lvalue_simple:  
       T_ID                       {$$ = new Lval(tid_l,$1,"",NULL,NULL,NULL);}
       | "result"                 {$$ = new Lval(tresult_l,NULL,"",NULL,NULL,NULL);}
       | T_STRING                 {$$ = new Lval(tstring_l,NULL,*($1),NULL,NULL,NULL);}                
       | lvalue_simple  '[' lvalue_simple ']'  %prec ARR             {$$ = new Lval(tarr_l,NULL,"",$1,$3,NULL);}
       | lvalue_simple  '[' rvalue ']'  %prec ARR             {$$ = new Lval(tarr_r,NULL,"",$1,NULL,$3);}
/*     | expr '^'  /*mporei na mhn einai corect   */
       | '(' lvalue_simple ')'    {$$ = new Lval(t_group_l,NULL,"",$2,NULL,NULL);}
       ;

/*typos rvalue */
rvalue : rvalue_simple           {$$ = $1 ;} 
       |  expr   '+'   expr      
               {$$ = new Rval(tplus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       |  expr   '-'   expr
               {$$ = new Rval(tminus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       |  expr   '*'   expr
               {$$ = new Rval(tmul_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}
                  

       |  expr   '/'   expr
               {$$ = new Rval(tslash_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       |  expr  T_div  expr
              {$$ = new Rval(tdiv_r , 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  T_mod  expr
               {$$ = new Rval(tmod_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       |  expr  "or"   expr
               {$$ = new Rval(tor_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  T_and expr
               {$$ = new Rval(tand_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   '='  expr
              {$$ = new Rval(tequal_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   "<>" expr
              {$$ = new Rval(twhot_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   '<'  expr
               {$$ = new Rval(tless_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr   '>'  expr 
               {$$ = new Rval(tge_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  "<="  expr
               {$$ = new Rval(tleseq_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}

       |  expr  ">="  expr 
              {$$ = new Rval(tgeq_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$1,$3);}


       | "not"  expr
              {$$ = new Rval(tnot_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$2,NULL);}

        | '+'  expr %prec UNPLUS
               {$$ = new Rval(tuplus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$2,NULL);}


       | '-'  expr %prec UNMINUS
                 {$$ = new Rval(tuminus_r, 0,'0',0.0,NULL,NULL,NULL,NULL,$2,NULL);}



       ;

/* typos rval */
rvalue_simple:
          T_INTEGER               {$$ = new Rval(tint_r,$1,'0',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}
       |  "true"                  {$$ = new Rval(tbool_r, 0,'t',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}

       |  "false"         {$$ = new Rval(tbool_r, 0,'f',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}

       |  T_REAL              {$$ = new Rval(treal_r, 0,'0',$1,NULL,NULL,NULL,NULL,NULL,NULL);}

       |   T_CHAR            {$$ = new Rval(tchar_r, 0,'0',0.0,$1,NULL,NULL,NULL,NULL);}
/* htan rvalue simple */ 
       |  '(' rvalue ')'   {$$ = new Rval(trval_r, 0,'0',0.0,NULL,$2,NULL,NULL,NULL,NULL);}
 
       |  "nil"                   {$$ = new Rval(tnill_r,0,'0',0.0,NULL,NULL,NULL,NULL,NULL,NULL);}
       |  call                     { $$ = new Rval(tcall_r, 0,'0',0.0,NULL,NULL,NULL,$1,NULL,NULL);}
 
       | '@' lvalue_simple  %prec RE
                {$$ = new Rval(tderfe_r, 0,'0',0.0,NULL,NULL,$2,NULL,NULL,NULL);}
/*
       | "not"  lvalue_simple
              {$$ = new Rval(tnot_r, 0,'0',0.0,NULL,NULL,$2,NULL,NULL,NULL);}


       | '+'  lvalue_simple %prec UNPLUS
               {$$ = new Rval(tuplus_r, 0,'0',0.0,NULL,NULL,$2,NULL,NULL,NULL);}


       | '-'  lvalue_simple %prec UNMINUS
                 {$$ = new Rval(tuminus_r, 0,'0',0.0,NULL,NULL,$2,NULL,NULL,NULL);}

*/

       ;



/*
unop:
    "not"                         {$$ = new Unop('n');}
    | '+'  %prec UNPLUS           {$$ = new Unop('+');}
    | '-'  %prec UNMINUS          {$$ = new Unop('-');}
    ;

*/

/*

binop:
     '+'                          {$$ = new Binop('+');}
     | '-'                        {$$ = new Binop('-');}

     | '*'                       {$$ = new Binop('*');}

     | '/'                          {$$ = new Binop('/');}

     | T_div                        {$$ = new Binop('d');}

     | T_mod                          {$$ = new Binop('m');}

     | "or"                            {$$ = new Binop('o');}

     | T_and                              {$$ = new Binop('a');}

     | '='                             {$$ = new Binop('=');}

     | "<>"                          {$$ = new Binop('q');}

     | '<'                          {$$ = new Binop('<');}

     | "<="                         {$$ = new Binop('e');}

     | '>'                          {$$ = new Binop('>');}

     | ">="                         {$$ = new Binop('t');}

     ;


*/


call:
    T_ID '(' kati13 ')'           {$$ = new Call($1,$3);}
    ;

kati13:
                                  {$$ = new std::list<Expr *>;}
      | expr kati14               {$2->push_back($1); $$ = $2 ;}
      ;
/*
kati14:
                                  {$$ = new std::list<Expr *>;}
      | kati14  ',' expr          {$1->push_back($3); $$ = $1 ;}  
        | expr  ',' kati14          {$3->push_back($1); $$ = $3 ;} 
      ;

*/
kati14:
                                  {$$ = new std::list<Expr *>;}
        | ',' expr kati14          {$3->push_back($2); $$ = $3 ;}  
/*      | expr  ',' kati14          {$3->push_back($1); $$ = $3 ;} */
      ;



%%





int main(int argc,char* argv[]) {
  if(argc==2){
        yyin = fopen(argv[1], "r");
  }
 // cout << "eimai edw" << endl ;
  int result = yyparse();
  if (result != 0) exit(1);
  initSymbolTable(997);
 // cout << "ksekinaw semantic" << endl;
  
  sem_prog(t);
  //cout << "teleiwsa semanti mapinw compile " << endl;
  compile(t);
  destroySymbolTable();
  return 0 ;
}
