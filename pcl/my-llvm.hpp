#ifndef __LLVM_H__
#define __LLVM_H__
#include "my-ast.hpp"
extern "C" {
#include "symbol.h"
#include "error.h"
}
void compile(Program*);  
bool isLibFunction(string id);
#endif