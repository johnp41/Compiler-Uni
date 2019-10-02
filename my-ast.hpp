#ifndef ast_h
#define ast_h

using namespace std;


#include <iostream>
#include <map>
#include <vector>
#include <list> 
extern "C"{
#include "symbol.h"
}
enum exp_type{
  rva,
  lva
};


enum rval_type{
  tint_r,
  tbool_r,
  treal_r,
  tchar_r,
  trval_r,
  tnill_r,
  tcall_r,
  tderfe_r,
  tuminus_r,
  tuplus_r,
  tnot_r,
  tplus_r,
  tminus_r,
  tmul_r,
  tdiv_r,
  tslash_r,
  tmod_r,
  tor_r,
  tand_r,
  tequal_r,
  twhot_r,
  tless_r,
  tleseq_r,
  tge_r,
  tgeq_r
};


enum lval_type{
  tid_l,
  tresult_l,
  tstring_l,
  tref_lv,
  tref_rv,
  tarr_l,
  tarr_r,
  texp_l,
  t_group_l
};

enum stmt_type {
  tlva,
  tblock,
  tcall,
  tif,
  twhile,
  tid,
  tgoto,
  treturn,
  tnew,
  tnew_ex,
  tdispose,
  tdispose_ar
};

enum header_type{
  function,
  procedure

};

enum local_type {
  var,
  label,
  header,
  forwad
};

enum formal_type{
  refernce,
  value
};


class Program ;
class Body ;
//class Type ;
class Rval ;
class Lval ;
class Block ;
class Local ;
class Header ;
class Formal ;
class Stmt ;
class T_id ;
class Binop ;
class Unop ;
class Expr ;
class Stmt ;
class Call ;
class T_real ;
class T_char;
class T_string ;
class T_int;


class T_id {
public:
  std::string id;
  friend std::ostream& operator<<(std::ostream &out,const T_id& t);  
/*  friend std::ostream& operator<<(std::ostream &out,const T_id& t );*/
  T_id(std::string s);

  int   offset ;
};





class T_real{
public:
  float num ;
  friend std::ostream& operator<<(std::ostream &out,const T_real& t); 
  T_real(float num);
};

class T_int{
public:
  int num ;
  friend std::ostream& operator<<(std::ostream &out,const T_int& t); 

  T_int(int num);
};


class T_string{
public:
  std::string s ;
 friend std::ostream& operator<<(std::ostream &out,const T_string& t);


  T_string(std::string s);
};


class T_char{
public:
  char c ;
 friend std::ostream& operator<<(std::ostream &out,const T_char& t); 
  T_char(char c );
};




class Body{
public:
  /*list of local */
  std::list<Local *> *locals ;
 //kalsh block
  Block *block ;
 friend std::ostream& operator<<(std::ostream &out,const Body& t); 



  Body(Local *a,Block *b);
  Body(std::list<Local *> *a , Block *b);
  
};




class Program {
public:
  T_id *id;
  Body *body;
  
  void prit(){   
    cout << "Program "<< "Id =(" << *(id)  << ")  Body("<< *body  << "akuro" <<")"<<endl;
     }

//   Program(T_id *a,Body *b):id(a),body(b){}
  Program(T_id *a, Body *b);
};













class Block{
public:
  Stmt *stmt ;
  std::list<Stmt *>  *stmts ;
 friend std::ostream& operator<<(std::ostream &out,const Block& t); 
  Block(Stmt *a,std::list<Stmt *> *stmts);
};


class Local{
public:
  local_type   loc_type;
  std::string  id;
  std::list<T_id *> *ids;
  Type  type ;
  Header *header ;
  Local *next ;
  Body   *body;

 friend std::ostream& operator<<(std::ostream &out,const Local& t); 

 // Local(Header *a,Body *b);
  Local(local_type l,Header *a,Body *b):loc_type(l),header(a),body(b){}
  //Local(Header *a);
  Local(local_type l ,Header *a):loc_type(l),header(a){}
  Local(local_type l ,list<T_id *> *ids):loc_type(l),ids(ids){}
 // Local(std::list<T_id *> *ids);
//  Local(std::list<T_id *> *a,Type *b );
  Local(local_type l,std::list<T_id *> *a , Type b):loc_type(l),ids(a),type(b) {}
  Local(){};
  Local(local_type l) :loc_type(l){}
/*  
  Local(std::string id,std::list<T_id *> ids,Type *type, Header *header);

 Local(std::string id,std::list<T_id *> ids,Type *type, Header *header,Local *next);
*/

};


class Header{
public:
//  std::string           id;
  header_type           kind;
  Formal                *formal;
  std::list<Formal *>   *formals;
  Type                  type;
  T_id                  *id;
  std::string           parent;


 friend std::ostream& operator<<(std::ostream &out,const Header& t); 
  
  
  Header(header_type kind,T_id *a ,std::list<Formal *> *b,Type type ):kind(kind),formals(b),type(type),id(a) {}
  Header(header_type kind,T_id *a ,std::list<Formal *> *b ):kind(kind),formals(b),id(a){};
 
};





class Formal{
public:

  formal_type kind;
  //std::string id;
  std::list<T_id *> *ids; 
  Type type ;

 friend std::ostream& operator<<(std::ostream &out,const Formal& t); 


  Formal(formal_type kind,std::list<T_id *> *a, Type b):kind(kind),ids(a),type(b){}
//  Formal(std::string a,std::list<T_id *> ids,Type *type);
  
};


//orizetai allo
/*
class Type {
public:

  std::string name ;  
  int integ ;
  Type *type;
  char c;
 friend std::ostream& operator<<(std::ostream &out,const Type& t); 

  Type(char c , int inte ,Type *ty);
  Type(char c);
  Type(std::string a,int i,Type *t);
};
*/


class Stmt {
public:
  stmt_type kind ;
  Lval *lval;
  Expr *expr;
  Block *block;
  Call  *call;
  Stmt *stmt1;
  Stmt *stmt2;
  std::string ret;
  T_id *b;
  char ch;


 friend std::ostream& operator<<(std::ostream &out,const Stmt& t); 

  Stmt(stmt_type t,Lval* l):kind(t),lval(l){}
  Stmt(stmt_type t ,T_id *a):kind(t),b(a){}
  Stmt(stmt_type t ,char ch , Lval *l);
  Stmt(stmt_type t);
  Stmt(stmt_type t,T_id *b,Stmt *c);
  Stmt(stmt_type t,Expr *a,Stmt *b);
  Stmt(stmt_type t,Expr *e, Stmt *a, Stmt *b);
  Stmt(stmt_type t ,Call *c);
  Stmt(stmt_type t ,Block *b);
  Stmt(stmt_type t ,Lval *l,Expr *e);
  Stmt(Lval *a,Expr *expr,Block *b,Call *call,Stmt *stmt1,Stmt *stmt2,std::string ret);
  
};






class Expr {
public: 
  exp_type kind ;
  Lval *lval;  
  Rval *rval;
  Type type;

  friend std::ostream& operator<<(std::ostream &out,const Expr& t); 
  Expr(exp_type kind , Lval *lva,Rval *rval):kind(kind),lval(lva),rval(rval){}
  Expr(Lval *a,Rval *rval);
};


/*



class Lval{
public:
  std::string *var3;
  std::string var2;
  std::string var4;
  Lval *l;
  Lval *r ;
  Expr *expr;
  T_id                  *id;
  char                  c;
  Rval                  *rval;



 friend std::ostream& operator<<(std::ostream &out,const Lval& t); 

  Lval(Rval *r):rval(r){}
  Lval(Lval * l ,Rval *r):l(l),rval(r){}
  Lval(std::string *var3);
  Lval(Lval *l);
  Lval(Lval *l , Lval *r);
  Lval(std::string a);
  Lval(char c);
  Lval(T_id *id);
  Lval(Lval *a,Expr *expr,std::string ret,std::string var2);
};

*/

/*&

class Rval{
public:
  char  flag ;
  
};
*/


class Lval{
public:
  lval_type kind;
  T_id  *id ;
  string  str;
  Lval*   l1;
  Lval*   l2;
  Rval*    r1;
  Type    type;
  int     nesting_diff;
  bool    newed = false ;
  bool    isByRef = false ;

  Lval(lval_type kind, T_id *tid , string str ,Lval* l1,Lval* l2 ,Rval *r1 ):kind(kind) , id(tid) , str(str) , l1(l1), l2(l2) , r1(r1) {}


};



class Rval{
public:
  Type type;
  rval_type kind ;
  int   integer;
  char  boolean;
  float  flot ;
  string  *cha;
  char    cho ;
  Rval  *rval1 ;
  Lval  *lval1 ;
  Call  *call ;
  Expr  *expr1;
  Expr  *expr2;

  Rval(rval_type kind , int integer ,char boolean , float flot , string* cha , Rval *rval1 , Lval *lval1 ,Call *call , Expr *expr1 , Expr *expr2):kind(kind), integer(integer) , boolean(boolean) , flot(flot) , cha(cha) ,rval1(rval1) , lval1(lval1) , call(call) ,expr1(expr1) ,expr2(expr2) {}
  Rval(rval_type kind , int integer ,char boolean , float flot , char cho , Rval *rval1 , Lval *lval1 ,Call *call , Expr *expr1 ):kind(kind), integer(integer) , boolean(boolean) , flot(flot) , cho(cho) ,rval1(rval1) , lval1(lval1) , call(call) ,expr1(expr1)  {}
};




/*

class Rval{
public:
  int intg;
  std::string           *var2;
  std::string var;
  float flot;
  char c ;
  Rval                  *rval1;
  Rval                  *rval2;
  Lval                  *lval1;
  Lval                  *lval2;
  Call *call;
  Unop *unop;
  Expr *expr1;
  Expr *expr2;
  Binop *bino;
  //T_integer             *t;
  T_real                *r;
  T_char                *cho;
  char                  flag;


 friend std::ostream& operator<<(std::ostream &out,const Rval& t); 


  Rval(std::string *b):var2(b){}
  Rval(int t);
  Rval(std::string a);
  Rval(char c);
  Rval(float rel);
  Rval(Rval *r);
  Rval(Call *call);
  Rval(Lval *lva);
  Rval(Unop *uno,Lval *lval);
  Rval(Unop *uno,Rval *lval);
  Rval(Binop *uno,Lval *lval,Rval *Rval);
  Rval(Binop *uno,Lval *lval,Lval *val);
  Rval(Binop *uno,Rval *lval,Rval *rval);
  
  
  
  Rval(Lval *a,Rval *rval ,Expr *expr1,Expr *expr2,Call *call,std::string ret,float flo,char c,Unop *unop, Binop *bino,int intg );
};
*/

class Unop{
public:
  std::string var;
  char c ;

 friend std::ostream& operator<<(std::ostream &out,const Unop& t); 

  Unop(char c);
  Unop(std::string ret);
};


class Binop{
public:
  std::string var;
  char        c;

 friend std::ostream& operator<<(std::ostream &out,const Binop& t); 

  Binop(char c);
//  Binop(std::string ret);
};




class Call{
public:
  T_id                  *id;
  std::list<Expr *>     *e;
  Type                  type;
  std::string           parent;
  int                   nd;

 friend std::ostream& operator<<(std::ostream &out,const Call& t); 

  Call(T_id *id , std::list<Expr *> *e);
};



#endif
