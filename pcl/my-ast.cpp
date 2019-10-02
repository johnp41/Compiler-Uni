#include "symbol.h"
#include "my-ast.hpp"
using namespace std;
//edw sto cpp arxei
//8a exw me8do do,hshs 
// kai apodo,hsh
// na 8umammi :: gian na naver8w sto objext


//o deikths this exei na kanei ws ekshs
//otan kalhs mia me8odos thn kaleis profanws apo
//ena antikeimeno ..tote sth synaryhsh paraxw
//reitai o deikths this pou deixnei sto antikeimeno 
//apo to opoio kli8uke
//
//



std::ostream& operator<<(std::ostream &out,const T_id& t){
    out<< t.id;
    return out ;
  }




std::ostream& operator<<(std::ostream &out,const T_real& t){
    out<< t.num;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_int& t){
    out<< t.num;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_string& t){
    out<< t.s;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_char& t){
    out<< t.c;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const Body& t){
    out<< "Body starts " <<endl ;
    for ( Local *lis : *(t.locals)){
      
      out << (*lis);

    }
    return out ;
  }




std::ostream& operator<<(std::ostream &out,const Local& t){
  
    out<< "Local" ;
    return out ;
  }

/*
std::ostream& operator<<(std::ostream &out,const T_id& t){
    out<< t.id;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_id& t){
    out<< t.id;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_id& t){
    out<< t.id;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_id& t){
    out<< t.id;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_id& t){
    out<< t.id;
    return out ;
  }


std::ostream& operator<<(std::ostream &out,const T_id& t){
    out<< t.id;
    return out ;
  }


*/



Program::Program(T_id *a, Body *b){
  this->id = a;
  this->body = b;
};






//meta th methodo domhshs
//methodo apodomhshs
//
T_id::T_id(std::string s){
  this->id=s ;
};



/*
Local::Local(std::string id,std::list<T_id *> *ids,Type *type, Header *header){
  
  this->id = id ;
  this->ids =ids ;
  this->type=type;
  this->header=header ;

};
*/
/*
Local::Local(std::list<T_id *> *ids,Type *type){
  this->ids =ids ;
  this->type=type;
};
*/



T_real::T_real(float num){

  this->num=num ;

};


T_int::T_int(int i ){
  this->num=i;
};



T_string::T_string(std::string s ){
  this->s= s ;
};


T_char::T_char(char c){
  this->c=c;
};








//Local::Local(){};


/*
Local::Local(Header *a ){
  this->header = a ;
};

Local::Local(std::list<T_id *> *ids){
  this->ids = ids ;
};


Local::Local(Header *a , Body *b){
  this->header = a ;
  this->body  = b ;
};



*/


//Local::Local(std::list<T_id *> *ids){
//  this->ids = ids ;
//};





Block::Block(Stmt *a,std::list<Stmt *> *stmts){
  this->stmt = a ;
  this->stmts = stmts ;
};


Body::Body(std::list<Local *> *a,Block *b){
  
  this->locals = a ;
  this->block =b ;
};

/*
Header::Header(std::string a,Formal *formal,std::list<Formal *> formals,Type *b){
  this->id = a ;
  this->formal = formal ;
  this->formals = formals ;
  this->type = b ;
};
*/


/*
Header:: Header(T_id *a ,std::list<Formal *> *b ){
  this->id = a;
  this->formals = b;
};
  
*/



/*
Header::Header(T_id *a ,std::list<Formal *> *b , Type *c ){
  this->id = a ;
  this->formals = b;
  this->type = type;
};
*/


/*
Formal::Formal(std::list<T_id *> *a, Type *b){

  this->ids = a ;
  this->type = b;
};
*/



/*
Formal::Formal(std::string a,std::list<T_id *> ids,Type *type){
  this->id = a ;
  this->ids = ids ;
  this->type = type ;
};

*/


/*
Type::Type(std::string a,int i,Type *t){
  
  this->name = a ;
  this->integ = i ;
  this->type = t  ;
};




Type::Type(char c ){

  this->c = c;
};



Type::Type(char a,int i,Type *t){
  
  this->c = a ;
  this->integ = i ;
  this->type = t  ;
};



*/





Stmt::Stmt(Lval *a,Expr *expr,Block *b,Call *call,Stmt *stmt1,Stmt *stmt2,std::string ret){
  
  this->lval = a ;
  this->expr = expr ;
  this->block = b ;
  this->call = call ;
  this->stmt1 = stmt1 ;
  this->stmt2 = stmt2 ;
  this->ret=ret ;
};



Stmt::Stmt(stmt_type t ,T_id *b,Stmt *c){
  this->kind= t ;
  this->b = b ;
  this->stmt1 = c ; 
};



Stmt::Stmt(stmt_type t,Expr *a,Stmt *c){
  this->kind  = t;
  this->expr  = a;
  this->stmt1 = c;
};



Stmt::Stmt(stmt_type t ,Expr *e,Stmt *c , Stmt *q){
  this->expr = e;
  this->kind = t;
  this->stmt1 = c;
  this->stmt2 = q;
};


Stmt::Stmt(stmt_type t){


  this->kind = t ; 

};



Stmt::Stmt(stmt_type t ,char ch , Lval *l){
  this->kind  = t ;
  this->ch =            ch;
  this->lval =          l;
};

Stmt::Stmt(stmt_type t ,Call *c){
  this->kind = t ;
  this->call = c ;
};



Stmt::Stmt(stmt_type t ,Block *c){
  this->kind= t;
  this->block = c ;
};




Stmt::Stmt(stmt_type t ,Lval *l,Expr *c){
  this->kind = t ;
  this->lval  = l;
  this->expr = c;
};






Expr::Expr(Lval *a,Rval *rval){
  
  this->lval = a ;
  this->rval = rval ;
};




//ta evgala 22/4/19 gt alalaksa th klash
/*
Lval::Lval(Lval *a,Expr *expr,std::string ret,std::string var2){
  
  this->l = a ;
  this->expr = expr ;
  this->var4 = ret;
  this->var2 = var2 ;
};




Lval::Lval(Lval *l){

  this->l=l;
};


Lval::Lval(Lval *l,Lval *r){

  this->l = l;
  this->r = r;
};



Lval::Lval(std::string *a){

  this->var3 = a;
};



Lval::Lval(char c){

  this->c = c;
};





Lval::Lval(T_id *id){

  this->id = id;
};


*/


/*

Rval::Rval(Lval *a,Rval *rval ,Expr *expr1,Expr *expr2,Call *call,std::string ret,float flo,char c,Unop *unop, Binop *bino,int intg ){
  
  this->intg = intg ;
  this->var = ret ;
  this->lval = a ;
  this->rval = rval ;
  this->c = c ;
  this->flot = flo ;
  this->call = call ;
  this->expr1 = expr1 ;
  this->expr2 = expr2 ;
  this->unop = unop ;
  this->bino = bino ;

};

*/


//ta vgazw kai auta ekswgia prwsopikoys logoys 
/*

Rval::Rval(int t){

  this->intg = t ;

};


Rval::Rval(std::string a){

  this->var = a ;

};


Rval::Rval(char c){
  
  this->c = c ;

};



Rval::Rval(float c){

  this->flot = c ;

};





Rval::Rval(Rval *t){

  this->rval1 = t ;

};

Rval::Rval(Call *t){

  this->call = t ;

};


Rval::Rval(Lval *t){

  this->lval1 = t ;

};


Rval::Rval(Unop *un ,Rval *t){

  this->unop  = un;
  this->rval1 = t ;

};



Rval::Rval(Unop *un ,Lval *t){

  this->unop  = un;
  this->lval1 = t ;

};




Rval::Rval(Binop *bi ,Lval *l,Rval *t){

  this->bino  = bi;
  this->rval1 = t ;
  this->lval1 = l ;

};



Rval::Rval(Binop *bi ,Rval *l,Rval *t){

  this->bino  = bi;
  this->rval1 = t ;
  this->rval2 = l ;

};


Rval::Rval(Binop *bi ,Lval *l,Lval *t){

  this->bino  = bi;
  this->lval2 = t ;
  this->lval1 = l ;

};
*/


Unop::Unop(char c){
  this->c = c ;
};


Binop::Binop(char c){
  this->c = c ;
};




Unop::Unop(std::string ret){
  
  this->var = ret ;
};


//Binop::Binop(std::string ret){
//  this->var = ret ;
//};




Call::Call(T_id *id , std::list<Expr *> *e){

  this->id = id ;
  this->e  = e  ;

};



