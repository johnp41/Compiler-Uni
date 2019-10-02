#ifndef _semh
#define _semh
extern "C"{
#include "symbol.h"
#include "error.h"
}

#include "my-ast.hpp"
#include "stack"

extern stack<SymbolEntry* > func_stack ;
extern SymbolEntry* dummy ;

void sem_rvalue(Rval* r);
void sem_if(Stmt* s);
void sem_expr(Expr* e);
void sem_call(Call* call);
void sem_lvalue(Lval* p);
void sem_stmt (Stmt* s);
void sem_formal(Formal* p,SymbolEntry* f);
void sem_formals(list<Formal *> *p , SymbolEntry* f);
void sem_header(Header* p , Body* body);
void sem_prog(Program* p);
void sem_body(Body* p);
void sem_local(Local* p); 
void sem_block(Block* p);
void add_lib_func();

#endif
